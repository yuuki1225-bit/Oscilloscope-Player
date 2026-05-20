#include <Arduino.h>

// シリアル速度（921,600bps）
#define BAUD_RATE 921600

void setup() {
  // PCとのシリアル通信を開始
  Serial.begin(BAUD_RATE);
  
  // DACピン（25: X軸, 26: Y軸）
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
}

void loop() {
  // 同期ヘッダー(2byte) + 座標(2byte) の計4バイト待機
  if (Serial.available() >= 4) {
    // ヘッダー 0xFF 0xFF を確認
    if (Serial.read() == 0xFF) {
      if (Serial.read() == 0xFF) {
        // X座標とY座標を読み取って出力
        uint8_t x = Serial.read();
        uint8_t y = Serial.read();
        
        dacWrite(25, x);
        dacWrite(26, y);
      }
    }
  }
}