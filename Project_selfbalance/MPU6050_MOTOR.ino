//motorเปลี่ยนตามค่าของมุม
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

// เขียนโปรแกรมทดสอบ การหมุนของมอเตอร์ เมื่อมุมเปลี่ยนไป
void loop() {
mpu6050.update(); // อัปเดตค่า จากเซ็นเซอร์
Serial.print("angleX : ");
Serial.print(mpu6050.getAngleX()); // มุมรอบแกน X (Roll)
Serial.print("\t angleY : ");
Serial.print(mpu6050.getAngleY()); // มุมรอบแกน Y (Pitch)
Serial.print("\t angleZ : ");
Serial.println(mpu6050.getAngleZ()); // มุมรอบแกน Z (Yaw)
int speed = map(mpu6050.getAngleX(),-90,90,-255,255); // ปรับเทียบค่ามุมกับค่า PWM ที่ใช้ปรับความเร็วมอเตอร์
if (mpu6050.getAngleX() > 0) { // ถ้ามุมเปลี่ยนไปมีค่ามุมมากกว่า 0
  analogWrite(ENA, abs(speed)); //ปรับความเร็วมอเตอร์A เพื่อให้รองรับมุมที่เปลี่ยนไป
  digitalWrite(IN1, HIGH); // ให้มอเตอร์หมุน เพื่อเคลื่อนที่ไปข้างหน้า
  digitalWrite(IN2, LOW);
  analogWrite(ENB, abs(speed)); //ปรับความเร็วมอเตอร์ B เพื่อให้รองรับมุมที่เปลี่ยนไป
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
} else { // ถ้ามุมเปลี่ยนไปมีค่ามุมน้อยกว่า 0
  analogWrite(ENA, abs(speed));
  digitalWrite(IN1, LOW); // ให้มอเตอร์หมุน เพื่อเคลื่อนที่ไปข้างหลัง
  digitalWrite(IN2, HIGH);
  digitalWrite(ENB, abs(speed));
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
delay(10);
}
