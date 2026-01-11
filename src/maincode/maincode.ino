#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// ===== WiFi Credentials =====
const char* ssid = "Lakshmi Luxury pg 3rd sub";
const char* password = "9705560260@03";

// ===== Web Server =====
WebServer server(80);

//display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// ========= HTML PAGE =========
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { font-family: Arial; padding: 20px; }
.card { padding: 15px; margin-bottom: 20px; background: #e8e8e8; border-radius: 10px; }
</style>
</head>

<body>
<h2>ESP32 Control Panel</h2>

<div class="card">
  <h3>Sliders</h3>
  Slider 1: <input type="range" id="s1" min="0" max="255" value="0" oninput="sendData()"><br><br>
  Slider 2: <input type="range" id="s2" min="0" max="255" value="0" oninput="sendData()"><br><br>
  Slider 3: <input type="range" id="s3" min="0" max="255" value="0" oninput="sendData()"><br><br>
  Slider 4: <input type="range" id="s4" min="0" max="255" value="0" oninput="sendData()"><br><br>
</div>

<div class="card">
  <h3>Switches</h3>
  Switch 1: <input type="checkbox" id="w1" onchange="sendData()"><br><br>
  Switch 2: <input type="checkbox" id="w2" onchange="sendData()"><br><br>
  Switch 3: <input type="checkbox" id="w3" onchange="sendData()"><br><br>
  Switch 4: <input type="checkbox" id="w4" onchange="sendData()"><br><br>
</div>

<script>
function sendData() {
  let url = "/set?s1=" + document.getElementById("s1").value +
            "&s2=" + document.getElementById("s2").value +
            "&s3=" + document.getElementById("s3").value +
            "&s4=" + document.getElementById("s4").value +
            "&w1=" + (document.getElementById("w1").checked ? 1 : 0) +
            "&w2=" + (document.getElementById("w2").checked ? 1 : 0) +
            "&w3=" + (document.getElementById("w3").checked ? 1 : 0) +
            "&w4=" + (document.getElementById("w4").checked ? 1 : 0);

  fetch(url);
}

// Load current ESP32 values on page load
window.onload = function() {
  fetch("/state")
    .then(response => response.json())
    .then(data => {
      document.getElementById("s1").value = data.s1;
      document.getElementById("s2").value = data.s2;
      document.getElementById("s3").value = data.s3;
      document.getElementById("s4").value = data.s4;

      document.getElementById("w1").checked = data.w1;
      document.getElementById("w2").checked = data.w2;
      document.getElementById("w3").checked = data.w3;
      document.getElementById("w4").checked = data.w4;
    });
};
</script>


</body>
</html>
)=====";


// ===== Variables =====
int sliderVal[4] = {0,0,0,0};
int switchVal[4] = {0,0,0,0};

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

  Serial.println("\n===== WEB DATA =====");
  for (int i = 0; i < 4; i++)
    Serial.printf("Slider %d = %d\n", i+1, sliderVal[i]);
  for (int i = 0; i < 4; i++)
    Serial.printf("Switch %d = %d\n", i+1, switchVal[i]);
  Serial.println("==================\n");

  server.send(200, "text/plain", "OK");
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

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Wire.begin(21, 22);  // SDA, SCL

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


  // Routes
  server.on("/", handleRoot);
  server.on("/set", handleSet);

  server.begin();
  Serial.println("Web Server Started");
  server.on("/state", handleState);

}

void loop() {
  server.handleClient();
  updatedisplay();
}
