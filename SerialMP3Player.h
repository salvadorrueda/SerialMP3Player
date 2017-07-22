/*
 * SerialMP3Player.h - Library for Serial MP3 Player board from Catalex (YX5300 chip)
 * Created by Salvador Rueda Pau, July 23, 2016.
 * License as GPL v3 (http://www.gnu.org/licenses/gpl.html)
 */

#ifndef SerialMP3Player_h
#define SerialMP3Player_h

#include <Arduino.h>

#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play.
#define CMD_SEL_DEV       0X09
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F

#define CMD_STOP_PLAY     0X16
#define CMD_FOLDER_CYCLE  0X17
#define CMD_SHUFFLE_PLAY  0x18 //
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle.

#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01
  
#define CMD_PLAY_W_VOL    0X22
#define CMD_PLAYING_N     0x4C

/************ Opitons **************************/  
#define DEV_TF            0X02  
#define SINGLE_CYCLE_ON   0X00
#define SINGLE_CYCLE_OFF  0X01


// Uncomment SoftwareSerial for Arduino Uno or Nano.
#include <SoftwareSerial.h>

#define ARDUINO_RX 5  //should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 6  //connect to RX of the module

class SerialMP3Player{
   SoftwareSerial mp3 = SoftwareSerial(ARDUINO_RX, ARDUINO_TX);
   byte ansbuf[10] = {0}; // Buffer for the answers.     

  
   public:
     String setup();
     String decodeMP3Answer();
     String play();           // Play
     String play(int n);      // Play n file
     String play(int n, int vol); // Play n file with volume

   private:
     String sendCommand(byte command, byte dat1, byte dat2);
     String sanswer();
     int shex2int(char *s, int n);
     String sbyte2hex(byte b);

};


#endif
