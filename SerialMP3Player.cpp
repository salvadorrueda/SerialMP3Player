/*
 * SerialMP3Player.h - Library for Serial MP3 Player board from Catalex (YX5300 chip)
 * Created by Salvador Rueda Pau, July 23, 2016.
 * License as GPL v3 (http://www.gnu.org/licenses/gpl.html)
 *
 */

#include "Arduino.h"
#include "SerialMP3Player.h"

// Uncomment next line if you are using an Arduino Mega.
//#define mp3 Serial3    // Connect the MP3 Serial Player to the Arduino MEGA Serial3 (14 TX3 -> RX, 15 RX3 -> TX)

String SerialMP3Player::setup(){
  //Serial.begin(9600);
  mp3.begin(9600);
  delay(500);
  return sendCommand(CMD_SEL_DEV, DEV_TF);
  //delay(200);  
  
}

int SerialMP3Player::available(){
  return mp3.available();
}


String SerialMP3Player::play(){
   return sendCommand(CMD_PLAY, 0);
} 


String SerialMP3Player::play(int n){
   // n number of the file that must be played  
   
   return sendCommand(CMD_PLAY_W_INDEX, n);
} 







String SerialMP3Player::sendCommand(int8_t command, int16_t dat){
  static int8_t Send_buf[8] = {0}; // Buffer for Send commands.  

  // Command Structure 0x7E 0xFF 0x06 CMD FBACK DAT1 DAT2 0xEF
   
  //delay(20);
  Send_buf[0] = 0x7E;    // Start byte
  Send_buf[1] = 0xFF;    // Version
  Send_buf[2] = 0x06;    // Command length not including Start and End byte.
  Send_buf[3] = command; // Command
  Send_buf[4] = 0x01;    // Feedback 0x00 NO, 0x01 YES
  Send_buf[5] = (int8_t)(dat >> 8);  // DATA1 datah
  Send_buf[6] = (int8_t)(dat);       // DATA2 datal
  Send_buf[7] = 0xEF;    // End byte

  for(uint8_t i=0; i<8; i++)
  {
    mp3.write(Send_buf[i]) ;
  }

  delay(200); 
  
  return decodeMP3Answer();  
}

//String sanswer(void);
//int iansbuf = 0;                 // Index for answer buffer.
//static uint8_t ansbuf[10] = {0}; // Buffer for the answers.     


String SerialMP3Player::decodeMP3Answer(){
 // Response Structure  0x7E 0xFF 0x06 RSP 0x00 0x00 DAT 0xFE 0xBA 0xEF
  // 
  // RSP Response code 
  // DAT Response additional data
 
  String decodedMP3Answer="";
  
   decodedMP3Answer=sanswer();
  
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
   ansbuf[3] = 0; // Clear ansbuff.
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
/*Function: sanswer. Returns a String answer from mp3 UART module.	            */
/*Return: String.  the answer                                                   */

String SerialMP3Player::sanswer(void)
{
  // Response Structure  0x7E 0xFF 0x06 RSP 0x00 0x00 DAT 0xFE 0xBA 0xEF
  // 
  // RSP Response code 
  // DAT Response additional data
  
  // if there are something available start to read from mp3 serial.
  // if there are "0x7E" it's a beginning.
  //     
  //  read while something readed and it's not the end "0xEF"
  

  uint8_t b;
  String mp3answer="";                // Answer from the MP3.  
  int iansbuf = 0;  

  if (mp3.available()){
   do{
    b = mp3.read();
    
    if(b == 0x7E){  // if there are "0x7E" it's a beginning.
      iansbuf=0;    //  ansbuf index to zero.
      mp3answer="";
    }
    
    ansbuf[iansbuf] = b;
    mp3answer+=sbyte2hex(ansbuf[iansbuf]);       
    iansbuf++; //  increase this index.     
    
   }while(b != 0xEF);
   // while there are something to read and it's not the end "0xEF"
     
  }   
  return mp3answer; 
 }
 
 




