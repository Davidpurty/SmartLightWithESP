
#if defined(ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#else
  #error "This board is not supported"
#endif

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include "webPage.h"
#include "batteryManager.h"
BatteryManager battery;
#include "lightingManager.h"
LightingManager lighting;


//add RTC library
#include "I2C_RTC.h"
static DS1307 RTC;


// ===== WiFi Credentials =====
const char* ssid = "Lakshmi Luxury pg 3rd sub"; //Lakshmi Luxury pg 3rd floor-5G
const char* password = "9705560260@03";

// ===== Web Server =====
#if defined(ESP32)
  WebServer server(80);
#elif defined(ESP8266)
  ESP8266WebServer server(80);
#endif

#if defined(ESP32)
  #define I2C_SDA 21
  #define I2C_SCL 22
#elif defined(ESP8266)
  #define I2C_SDA 4   // D2
  #define I2C_SCL 5   // D1
#else
  #error "Unsupported board"
#endif
//display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ===== Variables =====
int sliderVal[4] = {0,0,0,0};
int switchVal[4] = {0,0,0,0};
int prevSliderVal[4] = {0,0,0,0};
int prevSwitchVal[4] = {0,0,0,0};

// ===== Routes =====
void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

void handleSet() {
  for (int i = 0; i < 4; i++) {
    String key = "s" + String(i+1);
    if (server.hasArg(key)) sliderVal[i] = server.arg(key).toInt();
  }
  for (int i = 0; i < 4; i++) {
    String key = "w" + String(i+1);
    if (server.hasArg(key)) switchVal[i] = server.arg(key).toInt();
  }
  Serial.println("Printing all the data");
  Serial.println("\n===== WEB DATA =====");
  for (int i = 0; i < 4; i++)
    Serial.printf("Slider %d = %d\n", i+1, sliderVal[i]);
  for (int i = 0; i < 4; i++)
    Serial.printf("Switch %d = %d\n", i+1, switchVal[i]);
  Serial.println("==================\n");

  server.send(200, "text/plain", "OK");
  updateLED();
  updatedisplay();
}
void updatedisplay(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("SW1:");
  display.print(switchVal[0]);
  display.setCursor(36, 0);
  display.print("slider:");
  display.print(sliderVal[0]);


  display.setCursor(0, 10);
  display.print("SW2:");
  display.print(switchVal[1]);
  display.setCursor(36, 10);
  display.print("slider:");
  display.print(sliderVal[1]);

  display.setCursor(0, 20);
  display.print("SW3:");
  display.print(switchVal[2]);
  display.setCursor(36, 20);
  display.print("slider:");
  display.print(sliderVal[2]);

  display.display();

}
void handleState() {
  String json = "{";
  json += "\"s1\":" + String(sliderVal[0]) + ",";
  json += "\"s2\":" + String(sliderVal[1]) + ",";
  json += "\"s3\":" + String(sliderVal[2]) + ",";
  json += "\"s4\":" + String(sliderVal[3]) + ",";
  json += "\"w1\":" + String(switchVal[0]) + ",";
  json += "\"w2\":" + String(switchVal[1]) + ",";
  json += "\"w3\":" + String(switchVal[2]) + ",";
  json += "\"w4\":" + String(switchVal[3]);
  json += "}";

  server.send(200, "application/json", json);
}
void updateRTC(){
  if(RTC.isRunning())
	{
    Serial.print(RTC.getWeekString().substring(0, 3));
    Serial.print(" ");
    Serial.print(RTC.getDateString());
    Serial.print(" ");
    Serial.print(RTC.getTimeString());
    Serial.println();
    }
}
void updateLED(){
  for(int i=0;i<4;i++){
    if(switchVal[i]!= prevSwitchVal[i]){
      int flag=switchVal[i];
      if(flag){
        lighting.turnOnLight(i);
     }
      else{
        lighting.turnOffLight(i);
     }
    }
    else if(prevSliderVal[i] != sliderVal[i]){
      lighting.setBrightness(i, sliderVal[i]);
    }
    //update current value
    prevSliderVal[i] = sliderVal[i];
    prevSwitchVal[i] =switchVal[i];
  }
  
}
void setup() {
  Serial.begin(115200);
  //static IP configuration

  IPAddress local_IP(192, 168, 0, 11);   // same subnet as router
  IPAddress gateway(192, 168, 0, 1);     // router IP
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);
  IPAddress secondaryDNS(103, 6, 156, 199);

  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Wire.begin(I2C_SDA, I2C_SCL); // SDA, SCL

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Stop if display fails
    Serial.println("display not working");
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ESP slider");
  display.println("Connecting to WiFi...");
  display.display();

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
  }
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("IP:");
  display.print(WiFi.localIP());
  display.display();
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(5000);
  //RTC setup
  RTC.begin();
  RTC.setHourMode(CLOCK_H12);
  RTC.setDay(22);
  RTC.setMonth(5);
  RTC.setYear(2020);

  RTC.setHours(23);
  RTC.setMinutes(47);
  RTC.setSeconds(56);

  RTC.updateWeek();
  //RTC setup done

  //start lightning
  lighting.begin();

  // Routes
  server.on("/", handleRoot);
  server.on("/set", handleSet);

  server.begin();
  Serial.println("Web Server Started");
  server.on("/state", handleState);
  
}

void loop() {
  server.handleClient();
}
