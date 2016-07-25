/*
 * SerialMP3Player.h - Library for Serial MP3 Player board from Catalex (YX5300 chip)
 * Created by Salvador Rueda Pau, July 23, 2016.
 * License as GPL v3 (http://www.gnu.org/licenses/gpl.html)
 *
 */

#include "Arduino.h"
#include "SerialMP3Player.h"


SerialMP3Player::SerialMP3Player(){
 
}

String SerialMP3Player::sendCommand(int8_t command, int16_t dat){
  static int8_t Send_buf[8] = {0}; // Buffer for Send commands.  

  delay(20);
  Send_buf[0] = 0x7e;   //
  Send_buf[1] = 0xff;   //
  Send_buf[2] = 0x06;   // Len 
  Send_buf[3] = command;//
  Send_buf[4] = 0x01;   // 0x00 NO, 0x01 feedback
  Send_buf[5] = (int8_t)(dat >> 8);  //datah
  Send_buf[6] = (int8_t)(dat);       //datal
  Send_buf[7] = 0xef;   //
  for(uint8_t i=0; i<8; i++)
  {
    mp3.write(Send_buf[i]) ;
  }

  delay(200); // 
  return decodeMP3Answer();  
}

String sanswer(void);
int iansbuf = 0;                 // Index for answer buffer.
static uint8_t ansbuf[10] = {0}; // Buffer for the answers.     



String SerialMP3Player::setup(){
  //Serial.begin(9600);
  mp3.begin(9600);
  delay(500);
  return sendCommand(CMD_SEL_DEV, DEV_TF);
  //delay(200);  
  
}



String SerialMP3Player::decodeMP3Answer(){

  String decodedMP3Answer="";
  
      decodedMP3Answer+=sanswer();
  // we have at all message? or just part of it?
  // if iansbuf is zero is because it was reset to it when 0xEF (end) was readed.  
   if(iansbuf==0)
    {   
     switch (ansbuf[3])
     {
      case 0x3A:
         decodedMP3Answer+=" -> Memory card inserted.";
         break; 
         
      case 0x3D:
         decodedMP3Answer+=" -> Completed play num "+String(ansbuf[6],DEC);
         break; 
         
      case 0x4C:
         decodedMP3Answer+=" -> Playing: "+String(ansbuf[6],DEC);
         break;
      
      case 0x41:
         decodedMP3Answer+=" -> Data recived correctly. ";
         break;     
     } 
    }  
   return decodedMP3Answer;
}





/********************************************************************************/
/*Function: sbyte2hex. Returns a byte data in HEX format.	                */
/*Parameter:- uint8_t b. Byte to convert to HEX.                                */
/*Return: String                                                                */


String sbyte2hex(uint8_t b)
{
  String shex;
  
  //Serial.print("0x");
  shex="0X";
  
  //if (b < 16) Serial.print("0");
  if (b < 16) shex+="0";
  //Serial.print(b, HEX);
  shex+=String(b,HEX);
  //Serial.print(" ");
  shex+=" ";
  return shex;
}


/********************************************************************************/
/*Function: sanswer. Returns a String answer from mp3 UART module.	        */
/*Parameter:- uint8_t b. void.                                                  */
/*Return: String.  the answer (partial or full).                                */

String sanswer(void)
{
  
  // start to read from mp3 serial.
  // if there are "0x7E" it's a beginning.
  //     iansbuf=0; //  ansbuf index to zero.
  //     ansbuf[iansbuf] = b;
  //     mp3answer=""; 
  //     // while there are something to read and it's not the end "0xEF"
  //
    // there are something and it is not a beginning.
    // if we are not in the middle of a message we have a problem.
      // we are in the middle of a message so let's continue.
      //  or at the beginning, anyway go for the reads.
      // if there are "0XEF" then we have a message.


  uint8_t b;
  String mp3answer;                // Answer from the MP3.   


  // start to read from mp3 serial.
  b = mp3.read();
  
  // if there are "0x7E" it's a beginning.
  if(b == 0x7E)
   {
      iansbuf=0; //  ansbuf index to zero.
      ansbuf[iansbuf] = b;
      mp3answer="";
      // while there are something to read and it's not the end "0xEF"
   }
    else  // there are something and it is not a beginning.
   {
    // if we are not in the middle of a message we have a problem.
    if(iansbuf==0)
     {
       return "ERROR ";
     }
   }
      // we are in the middle of a message so let's continue.
      //  or at the beginning, anyway go for the reads.
     
      while (mp3.available() && ansbuf[iansbuf] != 0XEF)
      {
        iansbuf++; //  increase this index.
        ansbuf[iansbuf] = mp3.read();
        mp3answer+=sbyte2hex(ansbuf[iansbuf]);
        
      }
      // if there are "0XEF" then we have a message.
      if(ansbuf[iansbuf] == 0XEF)
      {      
         iansbuf=0;
         
      }       
     
  return mp3answer; 
 }
 




String SerialMP3Player::play(){
   return sendCommand(CMD_PLAY, 0);
} 

