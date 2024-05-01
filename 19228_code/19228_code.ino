const int sensorPin = A1;  // Soil moisture sensor pin
const int ldrPin = A0;
const int motorPin = 13;
const int minLdrValue = 800;
const int maxLdrValue = 2300;
const int led1 = 2, led2 = 3, led3 = 4, led4 = 5, led5 = 6, led6 = 7;
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT), pinMode(led2, OUTPUT), pinMode(led3, OUTPUT), pinMode(led4, OUTPUT), pinMode(led5, OUTPUT), pinMode(led6, OUTPUT);
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
  double ldrVolt = (double)ldrStatus * 5;
  ldrVolt /= 1023;
  double ldrR = (ldrVolt * 70) / (5 - ldrVolt);
  double lux = 500 / pow(ldrR, -0.25);
  Serial.print("Lux : ");
  Serial.println(lux);
  Serial.print("ldrR = ");
  Serial.println(ldrR);


  if (lux <= (maxLdrValue * 1 / 4)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    Serial.println("All LEDs are ON");
  } else if (lux <= (maxLdrValue * 2 / 4)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    Serial.println("1/3 LEDs are OFF");
  } else if (lux <= (maxLdrValue * 3 / 4)) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    Serial.println("1/3 LEDs are ON");
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    Serial.println("all LEDs are OFF");
  }

  // Motor control based on soil moisture
  if (moisturePercentage < 40) {
    Serial.println("Start pump");
    digitalWrite(motorPin, HIGH);
  } else {
    Serial.println("Stop pump");
    digitalWrite(motorPin, LOW);
  }
  delay(1000);
}
