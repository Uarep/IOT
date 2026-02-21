#include <Servo.h>

Servo myservo;
void setup() {
  myservo.attach(13);//เปลี่ยนขาเอาว่าจะเทสตัวไหน
}
void loop() {
  myservo.write(90);
  delay(15);
}
