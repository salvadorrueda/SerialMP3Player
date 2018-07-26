/******************************************************************************
  Basic Commands examples for the SerialMP3Player YX5300 chip.

  Copy the files of "SDcard_example" to an empty SD card
  Connect the Serial MP3 Player to the Arduino board
    GND → GND
    VCC → 5V
    TX → pin 11
    RX → pin 10

  After compile and upload the code,
  you can test some basic commands by sending the letters
  ? - Display Menu options.
  P01 - Play 01 file
  F01 - Play 01 folder
  S01 - Play 01 file in loop
  p - play
  a - pause
  s - stop
  > - Next
  < - Previous
  ...

  Some commands like 'P' must be followed by two digits.

  This example code is in the public domain.

  https://github.com/salvadorrueda/ArduinoSerialMP3Player

  by Salvador Rueda
 *******************************************************************************/

#include "SerialMP3Player.h"

#define TX 11
#define RX 10

SerialMP3Player mp3(RX,TX);


void setup() {
  mp3.showDebug(1);       // print what we are sending to the mp3 board.

  Serial.begin(9600);     // start serial interface
  mp3.begin(9600);        // start mp3-communication
  delay(500);             // wait for init

  mp3.sendCommand(CMD_SEL_DEV, 0, 2);   //select sd-card
  delay(500);             // wait for init

  menu('?',0); // print the menu options.
}

 char c;  // char from Serial
 char cmd=' ';
 char cmd1=' ';


// the loop function runs over and over again forever
void loop() {

  if (Serial.available()){
    c = Serial.read();
    decode_c(); // Decode c.
  }
  // Check for the answer.
  if (mp3.available()){
    Serial.println(mp3.decodeMP3Answer()); // print decoded answers from mp3
  }
}

void menu(char op, int nval){
  // Menu
  switch (op){
    case '?':
    case 'h':
        Serial.println("SerialMP3Player Basic Commands:");
        Serial.println(" ? - Display Menu options. ");
        Serial.println(" P01 - Play 01 file");
        Serial.println(" F01 - Play 01 folder");
        Serial.println(" S01 - Play 01 file in loop");
        Serial.println(" V01 - Play 01 file, volume 30");
        Serial.println(" p - Play");
        Serial.println(" a - pause");
        Serial.println(" s - stop ");
        Serial.println(" > - Next");
        Serial.println(" < - Previous");
        Serial.println(" + - Volume UP");
        Serial.println(" - - Volume DOWN");
        Serial.println(" v15 - Set Volume to 15");
        Serial.println(" c - Query current file");
        Serial.println(" q - Query status");
        Serial.println(" x - Query folder count");
        Serial.println(" t - Query total file count");
        Serial.println(" r - Reset");
        Serial.println(" e - Sleep");
        Serial.println(" w - Wake up");
        break;

    case 'P':
        Serial.println("Play");
        mp3.play(nval);
        break;

    case 'F':
        Serial.println("Play Folder");
        mp3.playF(nval);
        break;

    case 'S':
        Serial.println("Play loop");
        mp3.playSL(nval);
        break;

    case 'V':
        Serial.println("Play file at 30 volume");
        mp3.play(nval,30);
        break;


    case 'p':
        Serial.println("Play");
        mp3.play();
        break;

    case 'a':
        Serial.println("Pause");
        mp3.pause();
        break;

    case 's':
        Serial.println("Stop");
        mp3.stop();
        break;

    case '>':
        Serial.println("Next");
        mp3.playNext();
        break;

    case '<':
        Serial.println("Previous");
        mp3.playPrevious();
        break;

    case '+':
        Serial.println("Volume UP");
        mp3.volUp();
        break;

    case '-':
        Serial.println("Volume Down");
        mp3.volDown();
        break;

    case 'v':
        Serial.println("Set to Volume");
          mp3.setVol(nval);
          mp3.qVol();
        break;

    case 'c':
        Serial.println("Query current file");
        mp3.qPlaying();
        break;

    case 'q':
        Serial.println("Query status");
        mp3.qStatus();
        break;

    case 'x':
        Serial.println("Query folder count");
        mp3.qTFolders();
        break;

    case 't':
        Serial.println("Query total file count");
        mp3.qTTracks();
        break;

    case 'r':
        Serial.println("Reset");
        mp3.reset();
        break;

    case 'e':
        Serial.println("Sleep");
        mp3.sleep();
        break;

    case 'w':
        Serial.println("Wake up");
        mp3.wakeup();
        break;
  }
}

void decode_c(){
  // Decode c looking for a specific command or a digit

  // if c is a 'v', 'P', 'F', 'S' or 'V' wait for the number XX
  if (c=='v' || c=='P' || c=='F' || c=='S' || c=='V'){
    cmd=c;
  }else{
    // maybe c is part of XX number
    if(c>='0' && c<='9'){
      // if c is a digit
      if(cmd1==' '){
        // if cmd1 is empty then c is the first digit
        cmd1 = c;
      }else{
        // if cmd1 is not empty c is the second digit
        menu(cmd, ((cmd1-'0')*10)+(c-'0'));
        cmd = ' ';
        cmd1 = ' ';
      }
    }else{
      // c is not a digit nor 'v', 'P', 'F' or 'S' so just call menu(c, nval);
      menu(c, 0);
    }
  }
}
