#include <IRremote.h>
#define RECV_PIN 4
#define IN1 13
#define IN2 12
#define ENA 11
#define ENB 10
#define IN3 9
#define IN4 8
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long lastCode = 0; // เก็บค่าปุ่มล่าสุด

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // เริ่มรับข้อมูล
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

if (irrecv.decode(&results)) { // ตรวจสอบว่ามีข้อมูล?
  Serial.println(results.value, HEX); //แสดงข้อมูลในรูปแบบฐาน 16
  unsigned long code = results.value;
  if (code == 0xFFFFFFFF) { //ตรวจสอบถ้ามีการกดค้างให้ใช้ข้อมูลเดิม
    code = lastCode; //เก็บข้อมูลเดิม
  } else {
    lastCode = code; // อัปเดตค่าล่าสุดเมื่อกดปุ่มใหม่
  }
  if (code == 0xFF629D) { //ตรวจสอบถ้าค่าที่ส่งมาตรงกับ code ของปุ่ม Forward
    Serial.println("Forward");
    digitalWrite(ENA, HIGH); //ให้มอเตอร์หมุนไปข้างหน้า
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  if (code == 0xFFA857) { // ตรวจสอบถ้าค่าที่ส่งมาตรงกับ code ของปุ่ม Backward
    Serial.println("Backward");
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  if (code == 0xFF22DD) { //ตรวจสอบถ้าค่าที่ส่งมาตรงกับ code ของปุ่ม Stop
    Serial.println("Stop");
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  irrecv.resume(); // รับค่าใหม่
}

//if (code == 0xFFFFFFFF) {
//  code = lastCode;  // ถ้ากดค้าง → ใช้รหัสปุ่มครั้งก่อน
//} else {
//  lastCode = code;  // ถ้ากดใหม่ → เก็บรหัสปุ่มล่าสุด
//}
