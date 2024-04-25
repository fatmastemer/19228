const int sensorPin = A1;  // Soil moisture sensor pin
const int ldrPin = A0;
const int motorPin = 13;
const int minLdrValue = 0;
const int maxLdrValue = 100;
const int led1 = 3, led2 = 4, led3 = 5, led4 = 6, led5 = 7, led6 = 8, led7 = 9, led8 = 10, led9 = 11;
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT), pinMode(led2, OUTPUT), pinMode(led3, OUTPUT), pinMode(led4, OUTPUT), pinMode(led5, OUTPUT), pinMode(led6, OUTPUT), pinMode(led7, OUTPUT), pinMode(led8, OUTPUT), pinMode(led9, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(motorPin, OUTPUT);

  // Bluetooth module setup
  BTSerial.begin(9600);  // Bluetooth module connection
  Serial.println("Bluetooth Module HC-06 connected!");
}

void loop() {
  // Soil moisture sensor
  float moisturePercentage;
  int sensorAnalog;
  sensorAnalog = analogRead(sensorPin);
  moisturePercentage = 100.0 - (sensorAnalog / 1023.0) * 100.0;
  Serial.print("Moisture Percentage = ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Light-dependent resistor (LDR) and LED
  int ldrStatus = analogRead(ldrPin);
  double ldrVolt = (double)ldrStatus * 5 / 1024;
  double ldrR = (ldrVolt * 10000) / (5 - ldrVolt);
  double lux = pow((1.25 * 10), 7);
  lux *= ldrR - 1.4059;
  Serial.print("Lux : ");
  Serial.println(lux);
  Serial.print("LDR Percentage = ");
  Serial.print(ldrStatus);
  Serial.println("%");

  if (ldrStatus <= (maxLdrValue * 1 / 4)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, HIGH);
    Serial.println("All LEDs are ON");
  } else if (ldrStatus <= (maxLdrValue * 2 / 4)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    Serial.println("1/3 LEDs are ON");
  } else if (ldrStatus <= (maxLdrValue * 3 / 4)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    Serial.println("All LEDs are OFF");
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
  }

  // Motor control based on soil moisture
  if (moisturePercentage < 40) {
    Serial.println("Start pump");
    digitalWrite(motorPin, HIGH);
  } else {
    Serial.println("Stop pump");
    digitalWrite(motorPin, LOW);
  }
}
