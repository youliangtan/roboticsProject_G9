#include <Servo.h>
Servo servoMain;
Servo servoGate;



String inputString = "";
String inputMode[2] = {"I","U"};
bool stringComplete = false;
long distance = 0; 
long intensity = 0;
int count = 0;

void setup() {
  Serial.begin (9600);
  inputString.reserve(200);
  servoMain.attach(10);
  servoGate.attach(9);//this is the activated motr
}

void loop() {
  Serial.print("run motor");
  delay(1000);
  
  //open gate
  servoGate.write(180);
  delay(900);
  servoGate.write(95);
  
  delay(1000);
  
  //close gate
  servoGate.write(0);
  delay(900);
  servoGate.write(95);
  Serial.print("DONE\n");

}


