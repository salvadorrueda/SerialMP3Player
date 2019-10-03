# SerialMP3Player
Arduino Library for Serial MP3 Player board (YX5300 chip)

![Serial MP3 Player (YX5300 chip)](https://github.com/salvadorrueda/SerialMP3Player/blob/master/extras/SerialMP3Player_YX5300.png)


You can buy the MP3 module on

http://www.dx.com/p/uart-control-serial-mp3-music-player-module-for-arduino-avr-arm-pic-blue-silver-342439#.VfHyobPh5z0

https://www.aliexpress.com/item/YX5300-UART-Control-Serial-MP3-Music-Player-Module-For-Arduino-AVR-ARM-PIC-CF-Micro-SD/32673728703.html


Documentation and some Arduino code examples:

(Spanish)
http://joanruedapauweb.com/blog/index.php/2017/02/07/arduino-serial-mp3-player-yx5300-es/

(Chinese)(Catalex_YX5300_Docs.zip files)
http://pan.baidu.com/s/1hqilpB2


## A Note on Delays:

To ensure the integrity of serial communication, this library implements a very conservative 20 ms delay before and 1000 ms delay after sending a command. More complicated sketches that can manage their own delays between serial commands can disable this delay with the preprocessor definition NO_SERIALMP3_DELAY.