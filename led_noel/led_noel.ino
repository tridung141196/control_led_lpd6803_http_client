#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <LPD6803.h>
#include <Ticker.h>
#include "ets_sys.h"
#include "osapi.h"

#define USE_US_TIMER

char* server="http://light-up-hope.sosvietnam.org/led";
char* num="500";
int currentLed=0, lastLed=0;
int dataPin  = 13;
int clockPin = 14;
LPD6803 strip = LPD6803(100, dataPin, clockPin);

//void rainbowCycle() {
// int i, j;
// byte WheelPos;
// LPD6803::color_t color;
// for (j = 0; j < 256 * 5; j++) {   // 5 cycles of all 96 colors in the wheel
//   for (i = 0; i < 1001; i++) {
//     // tricky math! we use each pixel as a fraction of the full 96-color wheel
//     // (thats the i / strip.numPixels() part)
//     // Then add in j which makes the colors go around per pixel
//     // the % 96 is to make the wheel cycle around
//
//     WheelPos = ( ((i * 256 / 50) + j) &255) ;
//     if(WheelPos <85){
//         color.r = WheelPos*3; //Red down
//         color.g = 255-WheelPos*3;    // Green up
//         color.b = 0;                //blue off
//     }
//      else if(WheelPos < 170){
//         WheelPos -=85;
//         color.r = 255 - WheelPos*3; //green down
//         color.g = 0;    //blue up
//         color.b = WheelPos*3;                //red off
//     }
//       else{
//       WheelPos-=170;
//         color.r = 0; //blue down
//         color.g = WheelPos*3;    //red up
//         color.b = 255-WheelPos*3;                //green off
//       }
//     strip.setPixelColor (i, color);
//   }
//   strip.show();
//   // write all the pixels out
//   delay(100);
// }
//}

//void ShowLedUtilN(int n){
//  for(int i=0;i<1001;i++){
//    if(i<n)
//      strip.setPixelColor (i, 249,248,134);
//    else if(i==n)
//      strip.setPixelColor (i, 249,244,0);
//    else
//      strip.setPixelColor (i, 0,0,0);
//  }
//}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    WiFiManagerParameter custom_server("server", "ex://",server, 40);
    WiFiManagerParameter custom_num_led("Num LED", "ex: 10", num, 10);
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    wifiManager.addParameter(&custom_server);
    wifiManager.addParameter(&custom_num_led);
    if (!wifiManager.autoConnect("WifiManager")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
    }
    Serial.println("connected...:)");
    Serial.println(WiFi.localIP());
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();
    strcpy(server, custom_server.getValue());
    strcpy(num, custom_num_led.getValue());
    Serial.println(server);
    Serial.println(num);
}

void loop() {
    delay(2000);
    HTTPClient http;
    Serial.print("connecting to ");
    Serial.println(server);
    http.begin(server);
    int httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      currentLed = payload.toInt();
    }
    http.end();
    WiFi.disconnect();
    strip.begin();
      if(currentLed == lastLed){
      Serial.println("khong co thay doi");
      //ShowLedUtilN(currentLed);
        
      strip.setPixelColor (5, 255,0,0);
    }
    else{
      Serial.println("co thay doi");
      //rainbowCycle();
      strip.setPixelColor (5, 0,255,0);
    }
    lastLed = currentLed;
    WiFi.reconnect();
}
