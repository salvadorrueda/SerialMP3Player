/*
  Simple SerialMP3Player example of YX5300 chip.
  This example code is in the public domain.

   
  by Salvador Rueda
 */

#include "SerialMP3Player.h"


SerialMP3Player mp3;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println(mp3.setup());
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
  if (mp3.available())
  {
    Serial.println(mp3.decodeMP3Answer());
  }
  
  delay(1000);
}

void menu(char op){
  // Menu 
   switch (op) {
    case '?':
    case 'h':
      Serial.println("Testig SerialMP3Player Commands:  ");
      Serial.println(" p     Play");
      Serial.println(" Pn.   Play the file number n. Ex P2 (Play 2nd file) ");
      Serial.println(" ' '   Pause. 'Space key'");
      Serial.println(" h     Display this Help ");
      break;
      
    case 'p':
      mp3.play();
      break;
      
    case ' ':
      Serial.println("Pause");
      //mp3.pause();
      break;
   }
}

