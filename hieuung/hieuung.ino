#include <ESP8266WiFi.h>
#include <LPD6803.h>
#include <Ticker.h>
#include "ets_sys.h"
  
// Number of RGB LEDs in strand:
int nLEDs = 1001;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 13;
int clockPin = 14;
LPD6803 strip = LPD6803(nLEDs, dataPin, clockPin);
void rainbowCycle2() {
 int i, j;
 byte WheelPos;
 byte red,green,blue;
 for (j = 65*5; j < 75*5; j++) {   // 5 cycles of all 96 colors in the wheel
   for (i = 0; i < 2*strip.getNrPixels (); i++) {
     // tricky math! we use each pixel as a fraction of the full 96-color wheel
     // (thats the i / strip.numPixels() part)
     // Then add in j which makes the colors go around per pixel
     // the % 96 is to make the wheel cycle around

     WheelPos = ( ((i * 96 / strip.getNrPixels ()) + j) % 96) ;
     switch (WheelPos >> 5)
     {
       case 0:
         red = 50 - WheelPos % 128; //Red down
         green = WheelPos % 128;    // Green up
         blue = 0;                //blue off
         break;
       case 1:
         green = 50 - WheelPos % 128; //green down
         blue = WheelPos % 128;    //blue up
         red = 0;                //red off
         break;
       case 2:
         blue = 50 - WheelPos % 128; //blue down
         red = WheelPos % 128;    //red up
         green = 0;                //green off
         break;
     }
     strip.setPixelColor (i, red, green, blue);
   }
   strip.show();   // write all the pixels out
   delay(300);
 }
}
void rainbowCycle() {
 int i, j;
 byte WheelPos;
 byte red,blue,green;
 for (j = 0; j < 5 * 5; j++) {   // 5 cycles of all 96 colors in the wheel
   for (i = 0; i < strip.getNrPixels (); i++) {
     // tricky math! we use each pixel as a fraction of the full 96-color wheel
     // (thats the i / strip.numPixels() part)
     // Then add in j which makes the colors go around per pixel
     // the % 96 is to make the wheel cycle around

     WheelPos = ( ((i * 256 / 50) + j) &255) ;
     if(WheelPos <85){
         red = WheelPos*3; //Red down
         green = 255-WheelPos*3;    // Green up
         blue = 0;                //blue off
     }
      else if(WheelPos < 170){
         WheelPos -=85;
         red = 255 - WheelPos*3; //green down
         green = 0;    //blue up
         blue = WheelPos*3;                //red off
     }
       else{
       WheelPos-=170;
         red = 0; //blue down
         green = WheelPos*3;    //red up
         blue = 255-WheelPos*3;                //green off
       }
     strip.setPixelColor (i, red, green, blue);
   }
   strip.show();
   delay(200);
   // write all the pixels out
 }
}

void runningLight(byte red, byte green, byte blue){
  int Position=0;
  for(int i=0;i<50*2;i++){
    for(int i=0;i<strip.getNrPixels ();i++){
      Position++;
      strip.setPixelColor(i,((sin(i+Position) * 127 + 128)/255)*red,
                            ((sin(i+Position) * 127 + 128)/255)*green,
                            ((sin(i+Position) * 127 + 128)/255)*blue);
    }
    strip.show();
    delay(50);
  }
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.getNrPixels (); i=i+3) {
        strip.setPixelColor(i+q, red, green, blue);    //turn every third pixel on
      }
      strip.show();
      delay(SpeedDelay);
      for (int i=0; i < strip.getNrPixels (); i=i+3) {
        strip.setPixelColor(i+q, 0,0,0);        //turn every third pixel off
      }
      strip.show();
      delay(SpeedDelay);
    }
  }
}

void ShowLedUtilN(int n){
  for(int i=0;i<1001;i++){
    if(i<n)
      strip.setPixelColor (i, 249,0,0);
    else if(i==n)
      strip.setPixelColor (i, 249,244,0);
    else
      strip.setPixelColor (i, 0,0,0);
  }
  strip.show();
  delay(2000);
}
void ShowLedUtilN1(int n){
  for(int j = 0; j<5;j++){
    for(int i=0;i<50;i++){
      if(i%2 == 0)
       strip.setPixelColor (i, 0,255,0);
      else
       strip.setPixelColor (i, 0, 0, 0);
    }
    strip.show();
    delay(500);
        for(int i=0;i<50;i++){
      if(i%2 == 1)
       strip.setPixelColor (i, 0,255,0);
      else
       strip.setPixelColor (i, 0, 0, 0);
    }
    strip.show();
    delay(500);
  }
}



void setup()
{
 Serial.begin(115200);
 Serial.println("start");
 strip.begin();
 strip.show();
 Serial.println("LEDS initalized");

}
void loop()
{
  ShowLedUtilN1(10);
  Serial.println("hieu ung cau vong 1");
  ShowLedUtilN(10);
  Serial.println("hieu ung sang den led duoc chon");
  rainbowCycle2();
  Serial.println("hieu ung cau vong 2");
  runningLight(255,0,0);        // red
  Serial.println("hieu ung led chay");
  runningLight(255,255,255);  // white
  runningLight(0,0,255);        // blue 
  Serial.println("hieu ung");
  theaterChase(255,0,0,100);
}
