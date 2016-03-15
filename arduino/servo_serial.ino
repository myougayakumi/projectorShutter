#include <Servo.h>

Servo myservo;

void setup()
{
  myservo.attach(9);
  myservo.write(91);
  // myservo.writeMicroseconds(1500);  // set servo to mid-point
  Serial.begin(9600);
}
int i = 0;
int d = 0;
int angle = 91;
char input[30];
String buf;

void loop() {
  while (Serial.available() <= 0) {
    delay(50);
  }
  if (Serial.available() > 0) {
    i = 0;
    while (Serial.available() > 0) {
      input[i] = Serial.read();
      i++;
    }
    buf = String(input);
    Serial.println(buf);
    angle = buf.toInt();
    if(angle <= 90) angle = 90;
    else if(angle >= 178) angle = 178;
    myservo.write(angle);
    delay(50);
  }
}
