/*
  Simple SerialMP3Player example of YX5300 chip.
  This example code is in the public domain.

   
  by Salvador Rueda
 */

#include "SerialMP3Player.h"


SerialMP3Player mp3;


void setup() {
  Serial.begin(9600);
  mp3.begin(9600);
  delay(500);

  mp3.sendCommand(CMD_SEL_DEV, 0, 2);
  delay(500);
}

// the loop function runs over and over again forever
void loop() {
  char op; // Menu option from Serial
  String r = "";

  if (Serial.available()){
    op = Serial.read();
    menu(op);
  }
  
 // Check for the answer.
  r = mp3.decodeMP3Answer();
  if(r!="") Serial.println(r);
  //delay(1000);
}

void menu(char op){
  // Menu 
   switch (op) {
    case '?':
    case 'h':
      Serial.println("Testig SerialMP3Player Commands:  ");
      Serial.println(" t     Test a command");
      Serial.println(" s     Stop ");
      break;
      
    case 't':
      // Test play next
      //  mp3.playNext();

      // Test play previous
      //  mp3.playPrevious();

      // Test play with index
      // Play the 3rth song
      //  mp3.play(3); 

      // Test play with volumen
      // Play n file with volume  
      // Play the 3rth song at maximum volume
      //  mp3.play(3,30);
          
      // Test volumen up 
      //  mp3.volUp();

      // Test volumen down
      //  mp3.volDown();

      // Test set volumen
      // Set Volumen (0-30) 
      //  mp3.setVol(15);     

      // Test play single loop
      // Play single loop n file 
      //  mp3.playSL(3);

      // Test play
      //  mp3.play();

      // Test pause
      //  mp3.pause();
          
      // Test playFN(f, n) ERROR need to be checked.
      // Play n file (name not number) in the f folder 
      
        mp3.playFN(15,4);

      // Test stop
      //  mp3.stop();

      // Test playF 
      // Play all the files in the f folder 
      //  mp3.playF(1);

      // Test qPlaying 
      // Ask for the file is playing 
      //   mp3.qPlaying();

      // Test qVol
      // Ask for the volumen
      //  mp3.qVol();   // Sometimes Board stop working properly.

      // Test qTFolders 
      // Ask for the number of folders
      //    mp3.qTFolders(); // Nonsense answer
          
      // Test qFTracks
      // Ask for the number of tracks folders
      //    mp3.qFTracks();   // Nonsense answer

      // Test qTTracks    
      // Ask for the total of tracks 
      //    mp3.qTTracks();  

          
      // Test qStatus. 
      //  Ask for the status
      //    0. stopped
      //    1. playing
      //    2. paused
      //    mp3.qStatus();

      
      // Testing sending a Command;
      // Choose a command to send or its number.   
      //  mp3.sendCommand(CMD_NEXT);
      //  mp3.sendCommand(1);

      
      
      break;

    case 'l':
      Serial.println("loop ");
      mp3.playSL(3);
      break;

    case 'p':
      Serial.println("pause ");
      mp3.pause();
      break;

    case 'P':
      Serial.println("play ");
      mp3.play();
      break;

      
    case 's':
      Serial.println("Stop ");
      mp3.stop();
      break;
      
 case 'n':
      Serial.println("Next ");
      mp3.playNext();
      break;

 case 'u':
      Serial.println("VolUp ");
      mp3.volUp();
      break;

 case 'd':
      Serial.println("VolDown ");
      mp3.volDown();
      break;
      
 case 'w':
      Serial.println("w. vol 20");
      mp3.setVol(20);
      break;
      
      
   }
}

