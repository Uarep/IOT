#define IN1 13
#define IN2 12
#define ENA 11
#define ENB 10
#define IN3 9
#define IN4 8
#define GPIO_Pin 2

unsigned int counter = 0;  // ตัวแปรนับจำนวน pulse ที่รับจากเซ็นเซอร์
int rpm;  // ตัวแปรเก็บค่า RPM (รอบต่อนาที)

// ฟังก์ชันที่ถูกเรียกทุกครั้งที่มีสัญญาณขาขึ้น (RISING) เข้ามาที่ GPIO_Pin
void countpulse() {
  counter++;  // เพิ่มค่าตัวนับ pulse ทีละ 1
}

void setup() {
  Serial.begin(9600);  // เริ่มต้น serial สำหรับส่งข้อมูลไปที่ monitor

  // กำหนดโหมดให้ขาออกสำหรับควบคุมมอเตอร์
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(GPIO_Pin, INPUT);  // กำหนดขารับสัญญาณจากเซ็นเซอร์เป็น input

  // ตั้ง interrupt ให้เรียก countpulse ทุกครั้งที่มีสัญญาณขาขึ้นที่ GPIO_Pin
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin), countpulse, RISING);
}

void loop() {
  analogWrite(ENA, 255);  // เปิดมอเตอร์ A ที่ความเร็วสูงสุด
  digitalWrite(IN1, HIGH);  // มอเตอร์ A เดินหน้า
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 255);  // เปิดมอเตอร์ B ที่ความเร็วสูงสุด
  digitalWrite(IN3, LOW);  // มอเตอร์ B ถอยหลัง
  digitalWrite(IN4, HIGH);

  static uint32_t previousMillis;  // ใช้สำหรับจับเวลาทุก 1 วินาที

  // ถ้าผ่านไปแล้วอย่างน้อย 1000 มิลลิวินาที (1 วินาที)
  if (millis() - previousMillis >= 1000) {
    rpm = (counter / 20.0) * 60;  // คำนวณความเร็วรอบต่อนาทีจากจำนวน pulse ที่นับได้
    counter = 0;  // รีเซ็ต counter เพื่อเริ่มนับใหม่
    previousMillis += 1000;  // อัปเดตเวลาอ้างอิง
  }

  Serial.print("Speed: ");  // แสดงผลความเร็ว
  Serial.print(rpm);
  Serial.println(" rpm");

  delay(1);  // หน่วงเวลาเล็กน้อยเพื่อความเสถียร
}
