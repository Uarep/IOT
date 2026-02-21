#define out5 7   // กำหนดขาอินพุตจากเซ็นเซอร์ตัวที่ 5
#define out4 6   // กำหนดขาอินพุตจากเซ็นเซอร์ตัวที่ 4
#define out3 5   // กำหนดขาอินพุตจากเซ็นเซอร์ตัวที่ 3
#define out2 4   // กำหนดขาอินพุตจากเซ็นเซอร์ตัวที่ 2
#define out1 3   // กำหนดขาอินพุตจากเซ็นเซอร์ตัวที่ 1

void setup() {
  Serial.begin(9600);         // เริ่มต้นการสื่อสารผ่าน Serial ที่ความเร็ว 9600 bps
  pinMode(out5, INPUT);       // ตั้งขา out5 เป็น input
  pinMode(out4, INPUT);       // ตั้งขา out4 เป็น input
  pinMode(out3, INPUT);       // ตั้งขา out3 เป็น input
  pinMode(out2, INPUT);       // ตั้งขา out2 เป็น input
  pinMode(out1, INPUT);       // ตั้งขา out1 เป็น input
}

void loop() {
  Serial.print(digitalRead(out1)); // อ่านค่า digital จากเซ็นเซอร์ 1 แล้วพิมพ์ออก
  Serial.print(" ");               // เว้นวรรคระหว่างค่า
  Serial.print(digitalRead(out2)); // อ่านค่า digital จากเซ็นเซอร์ 2 แล้วพิมพ์ออก
  Serial.print(" ");
  Serial.print(digitalRead(out3)); // อ่านค่า digital จากเซ็นเซอร์ 3 แล้วพิมพ์ออก
  Serial.print(" ");
  Serial.print(digitalRead(out4)); // อ่านค่า digital จากเซ็นเซอร์ 4 แล้วพิมพ์ออก
  Serial.print(" ");
  Serial.print(digitalRead(out5)); // อ่านค่า digital จากเซ็นเซอร์ 5 แล้วพิมพ์ออก
  Serial.println();                // ขึ้นบรรทัดใหม่ใน Serial Monitor
  delay(1000);                     // หน่วงเวลา 1 วินาที (1000 มิลลิวินาที)
}
