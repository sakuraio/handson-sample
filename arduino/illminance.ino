// ヘッダファイル指定　Including header files
#include <SakuraIO.h>

// 照度センサの定義　Definition of illuminance sensor
#define CDS A0

// LEDの定義　Definition of LED
#define LED_0 12
#define LED_1 10
#define LED_2 9
#define LED_3 8

// 照度センサーの上限値設定　Set the upper limit of the illuminance sensor
#define UPPERLIMIT 750

// 変数の定義　Definition of variables
SakuraIO_I2C sakuraio;
uint32_t illuminance = 0;
uint32_t cnt = 0;
uint32_t upperlimit = UPPERLIMIT;

// 起動時に1回だけ実行　Run once at startup
void setup() {
  Serial.begin(9600);

  // オンライン状態に遷移するまで待機　Wait until transition to online state
  Serial.print("Waiting to come online");
  for(;;){
    if( (sakuraio.getConnectionStatus() & 0x80) == 0x80 ) break;
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

// 以下ループ実行　Loop execution
void loop() {

  // cnt値のカウントアップ　Count up cnt value
  cnt++;
  Serial.println(cnt);

  // 照度情報の取得　Get illuminance
  illuminance = (uint32_t)analogRead(CDS);
  Serial.print("light value: ");
  Serial.println(illuminance);

  // さくらの通信モジュールへの各値のキューイング　Queuing each value to module
  if(sakuraio.enqueueTx(0,illuminance) != CMD_ERROR_NONE){
    Serial.println("[ERR] enqueue error");
  }
  if(sakuraio.enqueueTx(1,upperlimit) != CMD_ERROR_NONE){
    Serial.println("[ERR] enqueue error");
  }

  // 照度を検知してLEDを点灯　Detect illuminance and light LED
  if (illuminance > UPPERLIMIT) {
    digitalWrite(LED_0, HIGH);
  } else {
    digitalWrite(LED_0, LOW);
  }

  // キューイングされた値の送信　Sending queued values
  sakuraio.send();
  delay(100);

  // 利用可能な領域（Available）とデータが格納された領域（Queued）の取得　Get Available and Queued
  uint8_t available;
  uint8_t queued;
  if(sakuraio.getTxQueueLength(&available, &queued) != CMD_ERROR_NONE){
    Serial.println("[ERR] get tx queue length error");
  }
  Serial.print("Available :");
  Serial.print(available);
  Serial.print(" Queued :");
  Serial.println(queued);

  // sakura.ioからの受信データに応じたLED点灯（Digital10，9，8）　Lights the LED according to received data
  available = 0;
  if (sakuraio.getRxQueueLength(&available, &queued) != CMD_ERROR_NONE) {
    Serial.println("[ERR] get rx queue length error");
  }
  if (available > 0) {
    uint8_t ch, type, value[8];
    int64_t offset;
    sakuraio.dequeueRx(&ch, &type, value, &offset);
    Serial.print("ch:");
    Serial.println(ch);
    Serial.print("value:");
    Serial.println(value[0]);
    if (ch == 10) {
      if (value[0] == 1) {
        digitalWrite(LED_1, HIGH);
        delay(1000);
        digitalWrite(LED_1, LOW);
      }
    } else if (ch == 20) {
      if (value[0] == 1) {
        digitalWrite(LED_2, HIGH);
        delay(1000);
        digitalWrite(LED_2, LOW);
      }
    } else if (ch == 30) {
      if (value[0] == 1) {
        digitalWrite(LED_3, HIGH);
        delay(1000);
        digitalWrite(LED_3, LOW);
      }
    }
    sakuraio.clearRx();
  }

  delay(4900);
}