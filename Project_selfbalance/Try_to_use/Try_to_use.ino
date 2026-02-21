#include <Wire.h>
#include <MPU6050.h>
#include <IRremote.h>

MPU6050 mpu;

int tcrtPin = 2;              // Sensor TCRT5000 (Digital)
int joyX = A0, joyY = A1;     // Joystick
int irPin = 3;                // IR Receiver
IRrecv irrecv(irPin);
decode_results results;

// PID Variables
float Kp = 1.2, Ki = 0.01, Kd = 0.5;
float error, previousError = 0, integral = 0;
float output;

void setup() {
  Serial.begin(9600);

  // IR
  irrecv.enableIRIn();

  // MPU6050
  Wire.begin();
  mpu.initialize();

  // TCRT
  pinMode(tcrtPin, INPUT);
}

void loop() {
  // ===== Read IR Remote =====
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); // ดูค่า HEX ของปุ่ม
    irrecv.resume(); // รอรับรอบต่อไป
  }

  // ===== Read TCRT5000 =====
  int lineDetected = digitalRead(tcrtPin);
  Serial.print("Line: ");
  Serial.println(lineDetected);

  // ===== Read Joystick =====
  int joyXval = analogRead(joyX); // 0-1023
  int joyYval = analogRead(joyY);
  Serial.print("Joy X:");
  Serial.print(joyXval);
  Serial.print(" Y:");
  Serial.println(joyYval);

  // ===== Read MPU6050 =====
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  int tilt = ay; // หรือ ax แล้วแต่ทิศที่ต้องการควบคุม

  // ===== PID Controller =====
  error = 0 - tilt; // ต้องการให้หุ่นตรง → ค่าเป้าหมาย = 0
  integral += error;
  float derivative = error - previousError;

  output = Kp * error + Ki * integral + Kd * derivative;
  previousError = error;

  Serial.print("PID output: ");
  Serial.println(output);

  // ===== ใช้ output ปรับสปีดมอเตอร์ (สมดุล หรือทิศทาง) =====
  // analogWrite(motorPinL, baseSpeed - output);
  // analogWrite(motorPinR, baseSpeed + output);

  delay(50);
}
