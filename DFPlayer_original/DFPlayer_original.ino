#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

//
void setup () {
  Serial.begin (9600);
  Serial1.begin (9600);
  mp3_set_serial (Serial1);  //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (20);          // 15 is low for unpowered speaker 
                                      // 30 good for unpowered speaker - requires power off to reset volume
}


//
void loop () {        
  mp3_play (1);
  delay (6000);
  mp3_next ();
  delay (6000);
   mp3_next ();
  delay (6000);
   mp3_next ();
  delay (6000);
   mp3_next ();
  delay (6000);
   mp3_next ();
  delay (6000);
   
}
