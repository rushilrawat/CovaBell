/*
  CovaBell - Smart Contactless Doorbell and Lock System
  Contributors: Rushil Rawat, Arnav Bansal
*/

#include <LiquidCrystal.h>
#include <Servo.h>

// Pins
const int buzzerPin = 13;
const int servoPin1 = 8;
const int servoPin2 = 9;
const int tempSensorPin = A1;
const int pingPin = 7;
const int echoPin = 6;

// Objects
Servo servo1;
Servo servo2;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variables
bool visitorDetected = false;
bool cameFromOther = true;
int attemptCounter = 0;
const int maxAttempts = 3;
unsigned long lastVisitorTime = 0;
const unsigned long timeoutDuration = 30000; // 30 seconds

// Function Prototypes
void initializeSystem();
long getDistance();
int readTemperature();
void handleVisitor();
void accessGranted();
void accessDenied();
void idleScreen();

void setup() {
  initializeSystem();
}

void loop() {
  long distance = getDistance();

  if (distance > 50) {
    if (cameFromOther) {
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Come closer to");
    lcd.setCursor(0, 1);
    lcd.print("the sensor...");
    cameFromOther = false;
    if (millis() - lastVisitorTime > timeoutDuration) {
      idleScreen();
    }
  } else {
    handleVisitor();
    lastVisitorTime = millis();
  }
}

void initializeSystem() {
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(0);
  servo2.write(0);
  idleScreen();
}

void idleScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  lcd.setCursor(0, 1);
  lcd.print("Awaiting Visitor");
}

void handleVisitor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning...");
  delay(1000);

  int tempReading = readTemperature();

  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(tempReading);
  lcd.print((char)223);
  lcd.print("C");
  delay(2000);

  if (tempReading > 38) {
    attemptCounter++;
    if (attemptCounter >= maxAttempts) {
      accessDenied();
      attemptCounter = 0;
    } else {
      lcd.clear();
      lcd.print("High Temp!");
      lcd.setCursor(0, 1);
      lcd.print("Rescan... ");
      delay(3000);
    }
  } else {
    accessGranted();
    attemptCounter = 0;
  }

  cameFromOther = true;
}

void accessGranted() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Granted!");
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);

  servo1.write(90);
  servo2.write(90);
  delay(5000);
  servo1.write(0);
  servo2.write(0);
  idleScreen();
}

void accessDenied() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Denied");
  lcd.setCursor(0, 1);
  lcd.print("Wait & Retry!");
  delay(5000);
  idleScreen();
}

int readTemperature() {
  int reading1 = analogRead(tempSensorPin);
  delay(500);
  int reading2 = analogRead(tempSensorPin);
  int avgReading = (reading1 + reading2) / 2;

  int celsius = map((avgReading - 20) * 3.04, 0, 1023, -40, 125);
  return celsius;
}

long getDistance() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  long cm = duration / 29 / 2;
  return cm;
}
