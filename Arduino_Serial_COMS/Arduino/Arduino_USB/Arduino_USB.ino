#define trigPin 12
#define echoPin 13
#define intPin A0

String inputString = "";
String inputMode[2] = {"I","U"};
bool stringComplete = false;
long distance = 0; 
long intensity = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  inputString.reserve(200);
}

void loop() {
  if(stringComplete){
  if(inputString == inputMode[0]){
    intensity = analogRead(intPin);
    Serial.print(intensity);
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

