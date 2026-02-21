#include <MPU6050_tockn.h>
#include <Wire.h>
#define IN1 13
#define IN2 12
#define ENA 11
#define ENB 10
#define IN3 9
#define IN4 8
MPU6050 mpu6050(Wire); // สร้างออบเจกต์ MPU6050
float kp = 20, ki = 0, kd = 1; // ค่าพารามิเตอร์ PID
float setpoint = 0; // มุมที่ต้องการ (สมดุล)
float error, lastError, integral, derivative, output; // ตัวแปรสำหรับ PID : P(error), I(integral), D(derivative) , ค่า PID (output)
String cmdstring;
String cmdcode;
String parmstring;
bool newcmd = 0;
int sepIndex;
bool noparm = 0;

// เขียนโปรแกรมทดสอบ เพื่อกำหนดค่า Kx ผ่าน Serial input
void pidControl(float pitch) {
  error = setpoint - pitch;
  integral += error;
  derivative = error - lastError;
  output = kp * error + ki * integral + kd * derivative;
  lastError = error;
  motorcontrol(output); // เรียก function ควบคุมมอเตอร์
}

// เขียนโปรแกรมทดสอบ การหมุนของมอเตอร์โดยใช้ PID Control
void motorcontrol(float output){
  // ควบคุมมอเตอร์
  int motorSpeed = constrain(output, -255, 255);
  analogWrite(ENA, abs(motorSpeed));
  digitalWrite(IN1, motorSpeed > 0 ? HIGH : LOW);
  digitalWrite(IN2, motorSpeed > 0 ? LOW : HIGH);
  analogWrite(ENB, abs(motorSpeed));
  digitalWrite(IN3, motorSpeed > 0 ? LOW : HIGH);
  digitalWrite(IN4, motorSpeed > 0 ? HIGH : LOW);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(); // เริ่มการสื่อสาร I2C
  mpu6050.begin(); // เริ่มการทำงานของเซ็นเซอร์
  mpu6050.calcGyroOffsets(true); // ปรับเทียบค่า Gyroscope อัตโนมัติ
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  mpu6050.update(); // อัปเดตค่า จากเซ็นเซอร์
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX()); // มุมรอบแกน X (Roll)
  Serial.print("\t angleY : ");
  Serial.print(mpu6050.getAngleY()); // มุมรอบแกน Y (Pitch)
  Serial.print("\t angleZ : ");
  Serial.println(mpu6050.getAngleZ()); // มุมรอบแกน Z (Yaw)
  pidControl(mpu6050.getAngleX());

  // เขียนโปรแกรมทดสอบ การหมุนของมอเตอร์โดยใช้ PID Control
  if (Serial.available() > 0) { // detect new input
    cmdstring = Serial.readString();
    newcmd = 1;
  }
  if (newcmd == 1){
    Serial.println(cmdstring);
    callcmd();
    newcmd = 0;
  }
  delay(10);
}

// เขียนโปรแกรมทดสอบ การหมุนของมอเตอร์โดยใช้ PID Control
void callcmd(){
  cmdstring.trim();
  sepIndex = cmdstring.indexOf('='); // จะได้ตำแหน่งของ =
  if (sepIndex == -1) {
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
  if (cmdcode.equalsIgnoreCase("kp")) {
    if (noparm == 0) {
      kp = parmstring.toInt();
      Serial.print("Kp: ");
      Serial.println(kp);
    }
  }
  else if (cmdcode.equalsIgnoreCase("ki")) {
    if (noparm == 0) {
      ki = parmstring.toInt();
      Serial.print("Ki: ");
      Serial.println(ki);
    }
  }
  else if (cmdcode.equalsIgnoreCase("kd")) {
    if (noparm == 0) {
      kd = parmstring.toInt();
      Serial.print("Kd: ");
      Serial.println(kd);
    }
  }
}
