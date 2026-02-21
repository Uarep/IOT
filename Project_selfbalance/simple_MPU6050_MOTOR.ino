//อันนี้แค่มากกว่า0 หรือ น้อยกว่า0 มอเตอร์แค่เปลี่ยนทิศทาง
#include <MPU6050_tockn.h>
#include <Wire.h>
#define IN1 13
#define IN2 12
#define ENA 11
#define ENB 10
#define IN3 9
#define IN4 8
MPU6050 mpu6050(Wire); // สร้างออบเจกต์ MPU6050

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

// เขียนโปรแกรมทดสอบการหมุนของมอเตอร์ เมื่อมุมเปลี่ยนไป
void loop() {
  mpu6050.update(); // อัปเดตค่าจากเซ็นเซอร์

  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX()); // มุมรอบแกน X (Roll)
  Serial.print("\t angleY : ");
  Serial.print(mpu6050.getAngleY()); // มุมรอบแกน Y (Pitch)
  Serial.print("\t angleZ : ");
  Serial.println(mpu6050.getAngleZ()); // มุมรอบแกน Z (Yaw)

  if (mpu6050.getAngleX() > 0) { // ถ้ามุมเปลี่ยนไปมีค่ามุมมากกว่า 0
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, HIGH); // ให้มอเตอร์หมุน เพื่อเคลื่อนที่ไปข้างหน้า
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else { // ถ้ามุมเปลี่ยนไปมีค่ามุมน้อยกว่า 0
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, LOW); // ให้มอเตอร์หมุน เพื่อเคลื่อนที่ไปข้างหลัง
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  delay(10);
}
