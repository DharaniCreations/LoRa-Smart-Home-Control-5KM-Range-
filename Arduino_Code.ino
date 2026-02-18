//Dharani Creations 
//Lora Home Automation 


#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LoRa ----------------
String lora_band       = "868000000"; //according to your country 
String lora_networkid  = "5";
String lora_address    = "2";   // Arduino
String lora_RX_address = "1";   // NodeMCU

SoftwareSerial lora(10, 11);    // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- Relay ----------------
#define RELAY_PIN 8
bool relayState = false;        // TRUE = relay ON (logical)
bool loraLinked = false;

void setup() {
  Serial.begin(9600);
  lora.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  delay(1000);
  lora.println("AT+BAND=" + lora_band);
  delay(300);
  lora.println("AT+NETWORKID=" + lora_networkid);
  delay(300);
  lora.println("AT+ADDRESS=" + lora_address);

  // Relay OFF initially (ACTIVE-LOW)
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {

  if (lora.available()) {
    String s = lora.readString();
    s.trim();
    loraLinked = true;

    // Command detection (robust)
    if (s.indexOf("CMD:ON") >= 0)       relayState = true;
    else if (s.indexOf("CMD:OFF") >= 0) relayState = false;
    else if (s.indexOf("CMD:TOGGLE") >= 0) relayState = !relayState;

    // ACTIVE-LOW relay control
    digitalWrite(RELAY_PIN, relayState ? HIGH:LOW);

    // Send ACK back
    if (s.indexOf("CMD:") >= 0) {
      String ack = relayState ? "ACK:ON" : "ACK:OFF";
      lora.println("AT+SEND=1," + String(ack.length()) + "," + ack);
    }
  }

  // LCD status
  lcd.setCursor(0, 0);
  lcd.print("LoRa : ");
  lcd.print(loraLinked ? "OK " : "NO ");

  lcd.setCursor(0, 1);
  lcd.print("Relay: ");
  lcd.print(relayState ? "ON " : "OFF");
}
