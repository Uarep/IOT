#include <Servo.h>

Servo base;
Servo forward_backward;
Servo up_down;
Servo grip;
int servoPos1,servoPos2,servoPos3,servoPos4;
int currentPos[4];
int prevPos[4]={90,90,90,40};
int servonum;
String cmdstring;
String cmdcode;
String parmstring;
bool newcmd = 0;
int sepIndex;
bool noparm = 0;
void servodrive(int servonum,int servoPos){
  if (servonum == 0){
    base.write(servoPos);
  }else if (servonum == 1){
    forward_backward.write(servoPos);
  }else if (servonum==2){
    up_down.write(servoPos);
  }else if (servonum==3){
    grip.write(servoPos);
  }
}
void servomotion(int servonum,int servoPos){
  int i;
  currentPos[servonum] = servoPos;
  if (prevPos[servonum] < currentPos[servonum]){
    for(i=prevPos[servonum] ; i < currentPos[servonum]; i++){
      servodrive(servonum,i);
      delay(10);
    }
  }
  if (prevPos[servonum] > currentPos[servonum]){
    for(i=prevPos[servonum] ; i > currentPos[servonum]; i--){
      servodrive(servonum,i);
      delay(10);
    }
  }
  prevPos[servonum] = currentPos[servonum];
}
void setup(){
  Serial.begin(9600);
  base.attach(8);
  forward_backward.attach(9);
  up_down.attach(10);
  grip.attach(11);
  delay(10);
  base.write(prevPos[0]);
  forward_backward.write(prevPos[1]);
  up_down.write(prevPos[2]);
  grip.write(prevPos[3]);
  delay(1000);
}
void loop(){

  if (Serial.available() > 0) { // detect new input
    cmdstring = Serial.readString();
    newcmd = 1;
  }
  if (newcmd == 1){
    Serial.println(cmdstring);
    callcmd();
    newcmd = 0;
  }
  delay(1000);

}
void callcmd(){
  cmdstring.trim();
  sepIndex = cmdstring.indexOf('='); //จะได ้ต ําแหน่งของ =
  if (sepIndex==-1) {
    cmdcode = cmdstring;
    noparm = 1;
  }
  else {
    // แยก command (servo) และ parameter (มุม)
    cmdcode = cmdstring.substring(0, sepIndex);
    cmdcode.trim();
    parmstring = cmdstring.substring(sepIndex+1);
    parmstring.trim();
    noparm = 0;
  }
  if (cmdcode.equalsIgnoreCase("base")) {
    if (noparm==0) {
      servoPos1 = parmstring.toInt();
      servomotion(0,servoPos1);
      Serial.print("Base's Degree: "); // base's degree : 0-180
      Serial.println(servoPos1);
    }
  }
  else if (cmdcode.equalsIgnoreCase("fb")) {
    if (noparm==0) {
      servoPos2 = parmstring.toInt();
      servomotion(1,servoPos2);
      Serial.print("Forward Backward's Degree: "); //Forward Backward's
      Serial.println(servoPos2); //Degree: 80-160
    }
  }
  else if (cmdcode.equalsIgnoreCase("ud")) {
    if (noparm==0) {
      servoPos3 = parmstring.toInt();
      servomotion(2,servoPos3);
      Serial.print("Up Down's Degree: "); //Up Down's Degree: 80-160
      Serial.println(servoPos3);
    }
  }
  else if (cmdcode.equalsIgnoreCase("gp")) {
    if (noparm==0) {
      servoPos4 = parmstring.toInt();
      servomotion(3,servoPos4);
      Serial.print("Gripper's Degree: "); //"Gripper's Degree: 40-60
      Serial.println(servoPos4);
    }
  }
  else if (cmdcode.equalsIgnoreCase("rs")) {
    if (noparm==0) {
      servomotion(0,90); // base's degree : 90
      servomotion(1,90); //Forward Backward's Degree: 90
      servomotion(2,90); //Up Down's Degree: 140
      servomotion(3,40); //"Gripper's Degree: 50
      Serial.print("Ready ");
      Serial.println();
    }
  }
}
