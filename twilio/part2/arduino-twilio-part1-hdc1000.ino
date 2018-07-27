// ヘッダファイル指定　Including header files
#include <HDC1000.h>
#include <SakuraIO.h>

// LEDの定義　Definition of LED
#define LED_1 7
#define LED_2 6
#define LED_3 5

// 変数の定義　Definition of variables
SakuraIO_I2C sakuraio;
HDC1000 hdc1000;
uint32_t cnt = 0;

// 起動時に1回だけ実行　Run once at startup
void setup() {
  hdc1000.begin();
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

  // 温度情報の取得　Get temperature
  float temp = hdc1000.getTemperature();

  if (temp == HDC1000_ERROR_CODE) {
    hdc1000.begin(); // retry once
    temp = hdc1000.getTemperature();
  }
  Serial.print("Temperature: ");
  Serial.println(temp);

  // さくらの通信モジュールへの各値の閾値判定およびキューイング　Threshold determination and queuing of each value to module
  if (temp >= 30) { // temp値による判定
    if (sakuraio.enqueueTx(0, cnt) != CMD_ERROR_NONE) {
      Serial.println("[ERR] enqueue error");
    }
    if (sakuraio.enqueueTx(1, temp) != CMD_ERROR_NONE) {
      Serial.println("[ERR] enqueue error");
    }

    // キューイングされた値の送信　Sending queued values
    sakuraio.send();
    Serial.println("* Sent to sakura.io *");
    for (int i = 0; i < 10; i++) // 送信時にLED_3を10回点滅　LED_3 blinks 10 times during transmission
    {
      digitalWrite(LED_3, HIGH);
      delay(1000);
      digitalWrite(LED_3, LOW);
      delay(1000);
    }
    delay(10000); // 送信後の待機時間　Wait time after transmission
  } else {
    delay(1000); // 送信を行わない場合の計測周期　Measurement cycle when transmission is not performed
  }

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

  // sakura.ioからの受信データに応じたLED点灯（Digital7）　Lights the LED according to received data
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
      if (ch == 0) { // ch0への受信時の動作定義　Definition of operation upon reception on ch0
        if (value[0] == 1) {
          digitalWrite(LED_1, HIGH);
        } else {
          digitalWrite(LED_1, LOW);
        }
      } else if (ch == 1) { // ch1への受信時の定義　Definition of operation upon reception on ch1

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