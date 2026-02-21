#include <Servo.h>  // เรียกใช้ไลบรารี Servo

Servo base;  // ประกาศ Servo ชื่อ base (ฐานหมุน)
Servo forward_backward;  // Servo เดินหน้า-ถอยหลัง
Servo up_down;  // Servo ขึ้น-ลง
Servo grip;  // Servo หนีบ-ปล่อย

const int joystick_x_pin = A0;  // ขา analog joystick ด้าน X
const int joystick_y_pin = A1;  // ขา analog joystick ด้าน Y

int x_adc_val, y_adc_val;  // ค่า analog ที่อ่านจาก joystick
float x_volt, y_volt;  // ค่าแรงดันที่แปลงจาก analog
int baseAngle, fbAngle, udAngle, gripAngle;  // เก็บมุมของ servo แต่ละตัว
int currentPos[4];  // เก็บมุมปัจจุบัน
int prevPos[4]={90,90,90,40};  // ค่าเริ่มต้นมุมของ servo
int servonum;  // ตัวแปรเลือก servo

// ฟังก์ชันเขียนมุมไปที่ servo ตามหมายเลข servonum
void servodrive(int servonum,int servoPos){
  if (servonum == 0){
    base.write(servoPos);
  } else if (servonum == 1){
    forward_backward.write(servoPos);
  } else if (servonum == 2){
    up_down.write(servoPos);
  } else if (servonum == 3){
    grip.write(servoPos);
  }
}

// ฟังก์ชันหมุน servo ทีละองศา (เพื่อให้หมุนเนียน ๆ ไม่กระชาก)
void servomotion(int servonum,int servoPos){
  int i;
  currentPos[servonum] = servoPos;  // เซฟตำแหน่งใหม่
  if (prevPos[servonum] < currentPos[servonum]){
    for(i=prevPos[servonum]; i < currentPos[servonum]; i++){
      servodrive(servonum,i);
      delay(10);
    }
  }
  if (prevPos[servonum] > currentPos[servonum]){
    for(i=prevPos[servonum]; i > currentPos[servonum]; i--){
      servodrive(servonum,i);
      delay(10);
    }
  }
  prevPos[servonum] = currentPos[servonum];  // อัพเดตตำแหน่งปัจจุบัน
}

void setup() {
  Serial.begin(9600);  // เปิด serial monitor

  base.attach(8);  // ต่อ servo base ที่ขา 8
  forward_backward.attach(9);  // ต่อ servo fb ที่ขา 9
  up_down.attach(10);  // ต่อ servo ud ที่ขา 10
  grip.attach(11);  // ต่อ servo grip ที่ขา 11

  base.write(prevPos[0]);  // ตั้งค่าเริ่มต้น servo base
  forward_backward.write(prevPos[1]);
  up_down.write(prevPos[2]);
  grip.write(prevPos[3]);

  baseAngle = prevPos[0];  // เซฟค่ามุมเริ่มต้น
  fbAngle = prevPos[1];
  udAngle = prevPos[2];
  gripAngle = prevPos[3];

  delay(2000);  // หน่วงรอ 2 วินาที
}

void loop() {
  int x_adc_val, y_adc_val;  // อ่านค่า analog จาก joystick
  float x_volt, y_volt;
  x_adc_val = analogRead(joystick_x_pin);  // อ่าน joystick x
  y_adc_val = analogRead(joystick_y_pin);  // อ่าน joystick y
  x_volt = ( ( x_adc_val * 5.0 ) / 1023 );  // แปลงเป็น volt
  y_volt = ( ( y_adc_val * 5.0 ) / 1023 );

  Serial.print("X_Vol = ");  // แสดงค่า volt X
  Serial.print(x_volt);
  Serial.print("\t");
  Serial.print("Y_Vol = ");  // แสดงค่า volt Y
  Serial.println(y_volt);

  // joystick กดขึ้น (Y ~ 0V, X ~ 2.5V): หมุน base เพิ่ม
  if ((x_volt <= 2.60 && x_volt >= 2.40) && (y_volt <= 0.1 && y_volt >= 0.00)){
    if(baseAngle < 180){
      baseAngle++;
    } else {
      baseAngle = 180;
    }
    servomotion(0, baseAngle);  // หมุน base ไป baseAngle
  }

  // joystick กดลง (Y ~ 5V, X ~ 2.5V): หมุน base ลด
  if ((x_volt <= 2.60 && x_volt >= 2.40) && (y_volt <= 5.00 && y_volt >= 4.90)){
    if(baseAngle > 0){
      baseAngle--;
    } else {
      baseAngle = 0;
    }
    servomotion(0, baseAngle);
  }

  // joystick กดขวา (X ~ 5V, Y ~ 2.5V): หมุน fb เพิ่ม
  if ((x_volt <= 5.00 && x_volt >= 4.90) && (y_volt <= 2.60 && y_volt >= 2.40)){
    if(fbAngle < 150){
      fbAngle++;
    } else {
      fbAngle = 150;
    }
    servomotion(1, fbAngle);
  }

  // joystick กดซ้าย (X ~ 0V, Y ~ 2.5V): หมุน fb ลด
  if ((x_volt <= 0.1 && x_volt >= 0.00) && (y_volt <= 2.60 && y_volt >= 2.40)){
    if(fbAngle > 70){
      fbAngle--;
    } else {
      fbAngle = 70;
    }
    servomotion(1, fbAngle);
  }

  delay(10);  // หน่วงนิดหน่อย
}
