#include<LiquidCrystal.h>
#include<Servo.h>

int buzzerPin = 13;
int servoPin1 = 8;
int celsius = 0;
bool cameFromOther;
int servoPin2 = 9;
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

Servo servo1;
Servo servo2;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
 lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
 Serial.begin(9600); //[for untrasonic] Starting Serial Terminal
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(0);
  servo2.write(0);
}

void loop(){
  lcd.setCursor(0,0);   
  long distance = getDistance();
  if(distance > 50){
    if(cameFromOther == true){
       lcd.clear();
    }
    lcd.print("Come nearer to");
    lcd.setCursor(0,1);
    lcd.print("temp. sensor");
    cameFromOther = false;
   }else{
      lcd.clear();
        lcd.print("Bring your head");
      lcd.setCursor(0,1);
      lcd.print("near sensor");
    delay(1000);
    int celsius = map(((analogRead(A1) - 20) * 3.04), 0, 1023, -40, 125);
    delay(1000);
    int celsius2 = map(((analogRead(A1) - 20) * 3.04), 0, 1023, -40, 125);
    int finalCelsius = (celsius + celsius2) / 2;
    if(finalCelsius > 38){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sorry You");
      lcd.setCursor(0,1);
      lcd.print("Cant go in");
      delay(5000);
    }else{
      lcd.clear();
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      lcd.setCursor(0,0);
      lcd.print("Welcome!");
      servo1.write(90);
      servo2.write(90);
      delay(5000);
      servo2.write(0);
      servo1.write(0);
      
    }
    cameFromOther = true;
    
    
    }
}

long getDistance(){
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
  return inches;
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
