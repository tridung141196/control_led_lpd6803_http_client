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

void rainbowCycle() {
 int i, j;
 byte WheelPos;
 LPD6803::color_t color;
 for (j = 0; j < 256 * 5; j++) {   // 5 cycles of all 96 colors in the wheel
   for (i = 0; i < 1001; i++) {
     // tricky math! we use each pixel as a fraction of the full 96-color wheel
     // (thats the i / strip.numPixels() part)
     // Then add in j which makes the colors go around per pixel
     // the % 96 is to make the wheel cycle around

     WheelPos = ( ((i * 256 / 50) + j) &255) ;
     Serial.println(WheelPos);
     if(WheelPos <85){
         color.r = WheelPos*3; //Red down
         color.g = 255-WheelPos*3;    // Green up
         color.b = 0;                //blue off
     }
      else if(WheelPos < 170){
         WheelPos -=85;
         color.r = 255 - WheelPos*3; //green down
         color.g = 0;    //blue up
         color.b = WheelPos*3;                //red off
     }
       else{
       WheelPos-=170;
         color.r = 0; //blue down
         color.g = WheelPos*3;    //red up
         color.b = 255-WheelPos*3;                //green off
       }
     strip.setPixelColor (i, color);
   }
   strip.show();
   // write all the pixels out
   delay(100);
 }
}

void ShowLedUtilN(int n){
  for(int i=0;i<1001;i++){
    if(i<n)
      strip.setPixelColor (i, 249,248,134);
    else if(i==n)
      strip.setPixelColor (i, 249,244,0);
    else
      strip.setPixelColor (i, 0,0,0);
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
  for(int i=0;i<1001;i++){
    if(i==900)
      strip.setPixelColor (i, 255,0,0);
    else
      strip.setPixelColor (i,0,0,0);
      //strip.show();
  }
//ShowLedUtilN(6);
  
}


