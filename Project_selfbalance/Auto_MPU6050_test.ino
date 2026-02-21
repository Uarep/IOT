#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire); // สร ้างออบเจกต์ MPU6050
long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // เรมิ่ การสอื่ สาร I2C
  mpu6050.begin(); // เรมิ่ การท างานของเซน็ เซอร์
  mpu6050.calcGyroOffsets(true); // ปรับเทียบค่า Gyroscope อัตโนมัติ
}

void loop() {
  mpu6050.update(); // อปั เดตคา่ จากเซน็ เซอร์
  if(millis() - timer > 1000){
    Serial.println("==================================================");
    Serial.print("temp : "); // แสดงอุณหภูมิ
    Serial.println(mpu6050.getTemp());

    Serial.print("accX : "); // แสดงค่าความเร่ง (Accelerometer)
    Serial.print(mpu6050.getAccX());
    Serial.print("\t accY : ");
    Serial.print(mpu6050.getAccY());
    Serial.print("\t accZ : ");
    Serial.println(mpu6050.getAccZ());

    Serial.print("gyroX : "); // แสดงคา่ ความเร็วเชงิมมุ (Gyroscope)
    Serial.print(mpu6050.getGyroX());
    Serial.print("\t gyroY : ");
    Serial.print(mpu6050.getGyroY());
    Serial.print("\t gyroZ : ");
    Serial.println(mpu6050.getGyroZ());

    Serial.print("accAngleX : ");
    Serial.print(mpu6050.getAccAngleX()); //ค านวณมุมรอบแกน X (Roll) จาก Accelerometer เท่านั้น
    Serial.print("\t accAngleY : ");
    Serial.println(mpu6050.getAccAngleY()); // ค านวณมุมรอบแกน Y (Pitch) จาก Accelerometer เท่านั้น

    Serial.print("gyroAngleX : ");
    Serial.print(mpu6050.getGyroAngleX()); //ค านวณมุมรอบแกน X (Roll) จาก Gyroscope เท่านั้น
    Serial.print("\t gyroAngleY : ");
    Serial.print(mpu6050.getGyroAngleY()); // ค านวณมุมรอบแกน Y (Pitch) จาก Gyroscope เท่านั้น
    Serial.print("\t gyroAngleZ : ");
    Serial.println(mpu6050.getGyroAngleZ()); // ค านวณมุมรอบแกน Z (Yaw) จาก Gyroscope เท่านั้น

    //ค านวณมุมจากการรวมข ้อมูล Accelerometer + Gyroscope) เพอื่ ลดสญั ญาณรบกวน
    Serial.print("angleX : ");
    Serial.print(mpu6050.getAngleX()); // มุมรอบแกน X (Roll)
    Serial.print("\t angleY : ");
    Serial.print(mpu6050.getAngleY()); // มุมรอบแกน Y (Pitch)
    Serial.print("\t angleZ : ");
    Serial.println(mpu6050.getAngleZ()); // มุมรอบแกน Z (Yaw)
    Serial.println("================================================\n");
    timer = millis();
  }
}
