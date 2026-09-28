#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define MQ2_AO 34
#define MQ2_DO 33

#define GREEN_LED 14
#define YELLOW_LED 27
#define RED_LED 26

#define BUZZER 25

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

const int GAS_CAUTION = 3000;
const int GAS_HIGH = 3700;

const float TEMP_CAUTION = 35.0;
const float TEMP_HIGH = 45.0;

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_DO, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  dht.begin();

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("LABSHIELD");

  display.setTextSize(1);
  display.setCursor(25, 40);
  display.println("SAFETY SYSTEM");

  display.display();

  delay(2000);
}

void loop() {

  float temperature = dht.readTemperature();

  int gasValue = analogRead(MQ2_AO);
  int gasDigital = digitalRead(MQ2_DO);

  if (isnan(temperature)) {
    temperature = 25.0;
  }

  int riskScore = 0;

  if (temperature >= TEMP_HIGH) {
    riskScore += 2;
  }
  else if (temperature >= TEMP_CAUTION) {
    riskScore += 1;
  }

  if (gasValue >= GAS_HIGH) {
    riskScore += 2;
  }
  else if (gasValue >= GAS_CAUTION) {
    riskScore += 1;
  }

  String status;

  if (riskScore >= 4) {
    status = "EMERGENCY";
  }
  else if (riskScore >= 2) {
    status = "HIGH RISK";
  }
  else if (riskScore >= 1) {
    status = "CAUTION";
  }
  else {
    status = "NORMAL";
  }

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  if (status == "NORMAL") {

    digitalWrite(GREEN_LED, HIGH);

  }
  else if (status == "CAUTION") {

    digitalWrite(YELLOW_LED, HIGH);

  }
  else if (status == "HIGH RISK") {

    digitalWrite(RED_LED, HIGH);

    digitalWrite(BUZZER, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);

  }
  else if (status == "EMERGENCY") {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

  }

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("LABSHIELD MONITOR");

  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  display.setCursor(0, 17);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 29);
  display.print("Gas: ");
  display.println(gasValue);

  display.setCursor(0, 41);
  display.print("Gas DO: ");

  if (gasDigital == LOW) {
    display.println("ALERT");
  }
  else {
    display.println("SAFE");
  }

  display.setCursor(0, 53);
  display.print("Status: ");
  display.println(status);

  display.display();

  Serial.println("-------------------------");
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");

  Serial.print("Gas AO: ");
  Serial.println(gasValue);

  Serial.print("Gas DO: ");

  if (gasDigital == LOW) {
    Serial.println("ALERT");
  }
  else {
    Serial.println("SAFE");
  }

  Serial.print("Status: ");
  Serial.println(status);

  delay(1000);
}