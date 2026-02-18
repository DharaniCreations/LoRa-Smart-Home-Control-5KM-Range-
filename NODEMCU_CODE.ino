//Dharani Creations
//Lora Home Automation

#define BLYNK_TEMPLATE_ID   "TMPL3knZhgyQ1"
#define BLYNK_TEMPLATE_NAME "Lora Home Automation"
#define BLYNK_AUTH_TOKEN    "nTxPciko2UpwvmQtFXkyuNlGYuQx6x0s"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------- WiFi --------
char ssid[] = "7"; // wifi name
char pass[] = "freewifi"; // wifi password

// -------- LoRa params --------
String lora_band       = "868000000"; // according to your country
String lora_networkid  = "5";
String lora_address    = "1";   // NodeMCU
String lora_RX_address = "2";   // Arduino

// -------- Pins --------
#define TOUCH_PIN D5
SoftwareSerial lora(D7, D8);   // RX, TX

// -------- OLED --------
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// -------- State --------
bool loraLinked = false;
String lastSource = "----";
String lastCmd = "----";
unsigned long lastRx = 0;
unsigned long lastHello = 0;

// -------- Blynk Relay Button --------
BLYNK_WRITE(V0) {
  lastSource = "BLYNK";
  if (param.asInt() == 1) {
    lastCmd = "ON";
    sendCmd("CMD:ON");
  } else {
    lastCmd = "OFF";
    sendCmd("CMD:OFF");
  }
}

void setup() {
  Serial.begin(9600);
  lora.begin(9600);
  pinMode(TOUCH_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Wire.begin(D2, D1);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // ---- LoRa Init ----
  delay(1000);
  lora.println("AT+BAND=" + lora_band);
  delay(300);
  lora.println("AT+NETWORKID=" + lora_networkid);
  delay(300);
  lora.println("AT+ADDRESS=" + lora_address);
}

void loop() {
  Blynk.run();

  // ---- Touch control ----
  if (digitalRead(TOUCH_PIN)) {
    lastSource = "TOUCH";
    lastCmd = "TOGGLE";
    sendCmd("CMD:TOGGLE");
    delay(600);
  }

  // ---- Receive from LoRa (robust: just look for ACK patterns) ----
  while (lora.available()) {
    String s = lora.readString();
    s.trim();

    lastRx = millis();
    loraLinked = true;

    // When ACK arrives, sync Blynk button (relay still works!)
    if (s.indexOf("ACK:ON") >= 0)  Blynk.virtualWrite(V0, 1);
    if (s.indexOf("ACK:OFF") >= 0) Blynk.virtualWrite(V0, 0);
  }

  // ---- Hidden HELLO for link check ----
  if (millis() - lastHello > 3000) {
    lora.println("AT+SEND=" + lora_RX_address + ",5,HELLO");
    lastHello = millis();
  }

  // ---- LoRa timeout ----
  if (millis() - lastRx > 7000) loraLinked = false;

  // ---- Blynk LoRa Status LED (V1) ----
  Blynk.virtualWrite(V1, loraLinked ? 1 : 0);

  drawOLED();
}

// -------- Send Command --------
void sendCmd(String cmd) {
  lora.println("AT+SEND=" + lora_RX_address + "," + String(cmd.length()) + "," + cmd);
}

// -------- OLED Display (NO relay ON/OFF shown) --------
void drawOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print(WiFi.status() == WL_CONNECTED ? "WiFi:ON " : "WiFi:OFF ");
  display.print(loraLinked ? "LoRa:OK" : "LoRa:NO");

  display.setCursor(0, 20);
  display.print("SRC: ");
  display.print(lastSource);

  display.setCursor(0, 35);
  display.print("CMD: ");
  display.print(lastCmd);

  display.display();
}
