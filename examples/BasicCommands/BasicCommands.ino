/******************************************************************************
  Basic Commands examples for the SerialMP3Player YX5300 chip.

  Copy the "hello.mp3" file to an empty SD card
  Connect the Serial MP3 Player to the Arduino board
    GND → GND
    VCC → 5V
    TX → pin 11
    RX → pin 10

  After compile and upload the code,
  you can test some basic commands by sending the letters
  h -> help menu
  P -> play
  p -> pause
  s -> stop

  This example code is in the public domain.

  https://github.com/salvadorrueda/ArduinoSerialMP3Player

  by Salvador Rueda
 *******************************************************************************/

#include "SerialMP3Player.h"

SerialMP3Player mp3;

void setup() {
  Serial.begin(9600);     // start serial interface
  mp3.begin(9600);        // start mp3-communication
  delay(500);             // wait for init

  mp3.sendCommand(CMD_SEL_DEV, 0, 2);   //select sd-card
  delay(500);             // wait for init

  menu(' '); // print the menu options.
}

// the loop function runs over and over again forever
void loop() {
  char op; // Menu option from Serial

  if (Serial.available()){
    op = Serial.read();
    menu(op);
  }
}

void menu(char op){
  // Menu
  switch (op){
    case 'P':
        Serial.println("Play");
        mp3.play();
        break;

    case 'p':
        Serial.println("Pause");
        mp3.pause();
        break;

    case 's':
        Serial.println("Stop");
        mp3.stop();
        break;

    default:
        Serial.println("SerialMP3Player Basic Commands:");
        Serial.println("P - Play");
        Serial.println("p - pause");
        Serial.println("s - stop ");
        break;
  }
}
