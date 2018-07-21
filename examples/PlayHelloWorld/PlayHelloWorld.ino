/******************************************************************************
  Simple SerialMP3Player "Hello World" example of YX5300 chip.

  Copy the "hello.mp3" file to an empty SD card
  Connect the Serial MP3 Player to the Arduino board
    GND → GND
    VCC → 5V
    TX → pin 5
    RX → pin 6

  After compile and upload the code you must hear “Hello world” over and over.


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
}

// the loop function runs over and over again forever
void loop() {
  mp3.play();     // Play "hello.mp3". You must hear "Hello World"
  delay(3000);    // wait 3 seconds
}
