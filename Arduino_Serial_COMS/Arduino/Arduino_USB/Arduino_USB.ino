#define trigPin 13
#define echoPin 12
#define intPin A0
#define Servo_move_time 750
#define Servo_delay 1000
#define delay_margin 2000
#include <Servo.h>

Servo servoGate;
String inputString = "";
String inputMode[2] = {"D","U"};
bool stringComplete = false;
long distance = 0; 
long intensity = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  servoGate.attach(9);//this is the activated motor
  inputString.reserve(200);
}

void loop() {
  if(stringComplete){
  if(inputString == inputMode[0]){
    Serial.print(2*Servo_move_time + Servo_delay + delay_margin);
    delay(1000);
    //open gate
    servoGate.write(180);
    delay(Servo_move_time);
    servoGate.write(95);
    delay(Servo_delay);
    //close gate
    servoGate.write(0);
    delay(Servo_move_time);
    servoGate.write(95);
  }
  else if(inputString == inputMode[1]){
    long duration;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    if(distance >= 200)Serial.print("-1");
    else if(distance < 4)Serial.print("-1");
    else Serial.print(distance);
  }
  else Serial.print("-1");
  inputString = "";
  stringComplete = false;
  }
}

void serialEvent(){
  if(Serial.available())
  {
  while (Serial.available()) {
    // get the new byte:
    delay(10);
    char inChar = (char)Serial.read();
    if(inChar != '\0')inputString += inChar;
    }
  stringComplete = true;
  }
}

