#include "BluetoothSerial.h"
#include <Wire.h>
#include "DHT.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Ticker.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled.
#endif

#define DHTPIN 33
#define DHTTYPE DHT11
#define LDR_PIN 26
#define smokeSensor 27
#define echo 2
#define trigger 15

#define fanRelay 5
#define lightRelay 4

#define smokeBuzzer 12

#define smokeLed 19
#define ultrasonicLed 18

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET -1

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
BluetoothSerial SerialBT;
Ticker ultrasonic;

bool fanStatus = false;
bool lightStatus = false;
bool smokeStatus = false;
bool ultrasonicStatus = false;

float temperature = 0;
float humidity = 0;
int ldrValue = 0;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  Wire.begin(22, 23);
  SerialBT.begin("ESP32_SMART_HOME");
  dht.begin();
  ultrasonic.attach(1, ultrasonicDetect);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  pinMode(fanRelay, OUTPUT);
  pinMode(lightRelay, OUTPUT);
  pinMode(smokeLed, OUTPUT);
  pinMode(ultrasonicLed, OUTPUT);
  pinMode(smokeBuzzer, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(fanRelay, HIGH);
  digitalWrite(lightRelay, HIGH);
  digitalWrite(smokeBuzzer, LOW);
  digitalWrite(smokeLed, LOW);
  digitalWrite(ultrasonicLed, LOW);

  introDisplay();
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  ldrValue = analogRead(LDR_PIN);

  if (ldrValue >= 2200) {
    digitalWrite(lightRelay, LOW);
    lightStatus = true;
  } else {
    digitalWrite(lightRelay, HIGH);
    lightStatus = false;
  }

  smokeDetect();
  ultrasonicDetect();
  bluetoothControl();
  displayStatus();
  delay(1000);
}

void smokeDetect() {
  int smokeValue = analogRead(smokeSensor);
  Serial.print("Smoke level: ");
  Serial.println(smokeValue);

  if (smokeValue >= 3200) {
    digitalWrite(smokeLed, HIGH);
    digitalWrite(smokeBuzzer, HIGH);
    smokeStatus = true;
  } else {
    digitalWrite(smokeLed, LOW);
    digitalWrite(smokeBuzzer, LOW);
    smokeStatus = false;
  }
}

void ultrasonicDetect() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  int duration = pulseIn(echo, HIGH);
  int distance = (duration / 2) * 0.0343;

  if (distance <= 20) {
    digitalWrite(ultrasonicLed, HIGH);
    ultrasonicStatus = true;
  } else {
    digitalWrite(ultrasonicLed, LOW);
    ultrasonicStatus = false;
  }
}

void bluetoothControl() {
  if (SerialBT.available()) {
    char input = SerialBT.read();
    switch (input) {
      case 'F': digitalWrite(fanRelay, LOW); fanStatus = true; break;
      case 'Y': digitalWrite(fanRelay, HIGH); fanStatus = false; break;
      case 'L': digitalWrite(lightRelay, LOW); lightStatus = true; break;
      case 'Z': digitalWrite(lightRelay, HIGH); lightStatus = false; break;
      case 'S': digitalWrite(smokeBuzzer, LOW); digitalWrite(smokeLed, LOW); smokeStatus = false; break;
    }
  }
}

void introDisplay() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("Smart Home");
  display.setCursor(10, 40);
  display.println("System");
  display.display();
  delay(3000);
}

void displayStatus() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 10);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 20);
  display.print("LDR: ");
  display.println(ldrValue);

 display.setCursor(0, 30);
 display.print("Motion: ");
 display.println(ultrasonicStatus ? "DETECTED" : "CLEAR");

 display.setCursor(0, 40);
 display.print("Smoke: ");
 display.println(smokeStatus ? "YES" : "NO");

  display.display();
}
