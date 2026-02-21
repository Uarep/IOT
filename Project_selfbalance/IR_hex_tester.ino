#include <IRremote.h>       // เรียกใช้ไลบรารีสำหรับใช้งานรีโมตอินฟราเรด

#define RECV_PIN 4          // กำหนดให้ขา D4 เป็นขารับสัญญาณ IR

IRrecv irrecv(RECV_PIN);    // สร้างอ็อบเจกต์ irrecv เพื่อรับข้อมูลจากรีโมต
decode_results results;     // สร้างตัวแปร results สำหรับเก็บผลลัพธ์ที่รับได้

void setup() {
  Serial.begin(115200);     // เริ่มต้น Serial Monitor ที่ความเร็ว 115200 bps
  irrecv.enableIRIn();      // เริ่มต้นการรับสัญญาณ IR
}

void loop() {
  if (irrecv.decode(&results)) {        // ถ้ามีข้อมูลจากรีโมตส่งเข้ามา
    Serial.println(results.value, HEX); // แสดงค่าที่อ่านได้ในรูปแบบเลขฐาน 16 (HEX)
    irrecv.resume();                    // เตรียมตัวรับข้อมูลครั้งถัดไป
  }
}
