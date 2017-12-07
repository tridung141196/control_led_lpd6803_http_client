#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
WiFiClient client;
// Tạo 1 biến
const char* ssid = "Wifi";
const char* password = "quenpassroi";
const char* server = "192.168.1.105";
const int port = 8000;
const int sendingInternval = 2 * 1000;
void setup() {
  Serial.begin(115200);
  Serial.println("Connecting"); 
  WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(100);
}
Serial.println("\r\nWiFi connected");
  
}

void loop() {
  float temp = 5;//dht.readHumidity();
  float humi = 6;//dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(temp) || isnan(humi)) {
 
Serial.println("Failed to read from DHT sensor!");
 
return;
  }
  if (client.connect(server, port)) {
String req_uri = "/update?temp=" + String(temp, 1) + "&humd=" + String(humi, 1);
 
client.print("GET " + req_uri + " HTTP/1.1\n" + "Host: "+ server +"\n" + "Connection: close\n" + "Content-Length:0\n" +"\n\n");
Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp, 1).c_str(), String(humi, 1).c_str());
  }
  client.stop();
  delay(sendingInternval);
}
