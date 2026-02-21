#include <Servo.h>

Servo base;
Servo forward_backward;
Servo up_down;
Servo grip;
String cmdstring;
int prevPos=90 ,currentPos, i;
void setup(){
Serial.begin(9600);
base.attach(8);
forward_backward.attach(9);
up_down.attach(10);
grip.attach(11);
delay(10);
base.write(prevPos);
forward_backward.write(90);
up_down.write(90);
grip.write(40);
delay(1000);
}
void loop(){

if (Serial.available() > 0) {
cmdstring = Serial.readString();
Serial.println(cmdstring);
currentPos = cmdstring.toInt();
}

if (prevPos < currentPos){
for(i=prevPos ; i < currentPos; i++){
base.write(i);
delay(10);
}
}
if (prevPos > currentPos){
for(i=prevPos ; i > currentPos; i--){
base.write(i);
delay(10);
}
}
prevPos = currentPos;
delay(500);
}
