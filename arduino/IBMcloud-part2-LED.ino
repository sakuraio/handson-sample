// ヘッダファイル指定　Including header files
#include <SakuraIO.h>

// LEDの定義　Definition of LED
#define LED_1 7
#define LED_2 6
#define LED_3 5

// 変数の定義　Definition of variables
SakuraIO_I2C sakuraio;
uint32_t cnt = 0;

// 起動時に1回だけ実行　Run once at startup
void setup() {
  Serial.begin(9600);
  Serial.print("Waiting to come online");
  for (;;) {
    if ( (sakuraio.getConnectionStatus() & 0x80) == 0x80 ) break;
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

// 以下ループ実行　Loop execution
void loop() {

  // cnt値のカウントアップ　Count up cnt value
  cnt++;
  Serial.println(cnt);

  // データの即時送信　Immediate transmission of data
  if (sakuraio.sendImmediately(0, cnt) != CMD_ERROR_NONE) {
    Serial.println("[ERR] enqueue error");
  }
  digitalWrite(LED_3, HIGH);
  delay(500);
  digitalWrite(LED_3, LOW);
  delay(500);

  // 利用可能な領域（Available）とデータが格納された領域（Queued）の取得　Get Available and Queued
  uint8_t available;
  uint8_t queued;
  if (sakuraio.getTxQueueLength(&available, &queued) != CMD_ERROR_NONE) {
    Serial.println("[ERR] get tx queue length error");
  }
  Serial.print("Available :");
  Serial.print(available);
  Serial.print(" Queued :");
  Serial.println(queued);

  // sakura.ioからの受信データに応じたLED点灯（Digital7，6）　Lights the LED according to received data
  available = 0;
  if (sakuraio.getRxQueueLength(&available, &queued) != CMD_ERROR_NONE) {
    Serial.println("[ERR] get rx queue length error");
  }
  if (available > 0)
  {
    for (int i = 0; i < available; i++)
    {
      uint8_t ch, type, value[8];
      int64_t offset;
      sakuraio.dequeueRx(&ch, &type, value, &offset);
      if (ch == 0) {
        if (value[0] == 1) {
          digitalWrite(LED_1, HIGH);
        } else {
          digitalWrite(LED_1, LOW);
        }
      } else if (ch == 1) {
        if (value[0] == 1) {
          digitalWrite(LED_2, HIGH);
        } else {
          digitalWrite(LED_2, LOW);
        }
      }
    }
    sakuraio.clearRx();
  }
}