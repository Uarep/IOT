#define IN1 13
#define IN2 12
#define ENA 11
#define ENB 10
#define IN3 9
#define IN4 8

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  // มอเตอร์ A เดินหน้า
  digitalWrite(ENA, HIGH);  // เปิดความเร็ว
  digitalWrite(IN1, HIGH);  // เดินหน้า
  digitalWrite(IN2, LOW);
  
  // มอเตอร์ B ถอยหลัง
  digitalWrite(ENB, HIGH);  // เปิดความเร็ว
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(2000);  // รอ 2 วินาที

  // หยุดมอเตอร์
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  delay(1000);  // รอ 1 วินาที ก่อนเริ่มใหม่
}

//Serial.println("Forward");
//digitalWrite(IN1, HIGH);  // มอเตอร์ A เดินหน้า
//digitalWrite(IN2, LOW);
//digitalWrite(IN3, HIGH);  // มอเตอร์ B เดินหน้า
//digitalWrite(IN4, LOW);
//
//Serial.println("Backward");
//digitalWrite(IN1, LOW);   // มอเตอร์ A ถอยหลัง
//digitalWrite(IN2, HIGH);
//digitalWrite(IN3, LOW);   // มอเตอร์ B ถอยหลัง
//digitalWrite(IN4, HIGH);
//
//Serial.println("LEFT");
//digitalWrite(IN1, LOW);   // มอเตอร์ A ถอยหลัง
//digitalWrite(IN2, HIGH);
//digitalWrite(IN3, HIGH);  // มอเตอร์ B เดินหน้า
//digitalWrite(IN4, LOW);
//
//Serial.println("RIGHT");
//digitalWrite(IN1, HIGH);  // มอเตอร์ A เดินหน้า
//digitalWrite(IN2, LOW);
//digitalWrite(IN3, LOW);   // มอเตอร์ B ถอยหลัง
//digitalWrite(IN4, HIGH);
