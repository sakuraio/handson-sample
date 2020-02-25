# coding: utf-8

# Fabo-RasPi.py
# Raspberry Pi + Faboとsakura.ioでデータの送受信をするプログラム
# (Raspberry Pi側で動かすプログラム)
# 使い方:
# % python3 Fabo-RasPi.py


from sakuraio.hardware.rpi import SakuraIOSMBus
import RPi.GPIO as GPIO
import spidev
import time
import sys

# A0に温度センサー(#108)を接続
TEMPPIN = 0
# GPIO4にLED(#101)を接続
LEDPIN = 4

# 温度センサーからデータを取得
def readadc(channel):
    adc = spi.xfer2([1,(8+channel)<<4,0])
    data = ((adc[1]&3) << 8) + adc[2]
    return data

# 取得した値の変換
def arduino_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

# 初期化
spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz = 5000
GPIO.setwarnings(False)
GPIO.setmode( GPIO.BCM )
GPIO.setup( LEDPIN, GPIO.OUT )
sakuraio = SakuraIOSMBus()
cnt = 0
led = 0

# Ctrl-Cが押されるまで無限ループ
try:
    while True:
        # 温度センサーから値を取得し電圧を経て温度に変換
        data = readadc(TEMPPIN)
        volt = arduino_map(data, 0, 1023, 0, 5000)
        temp = arduino_map(volt, 300, 1600, -30, 100)
        # ch0にカウンター、ch1に温度を入れて送信
        sakuraio.enqueue_tx(0, cnt)
        sakuraio.enqueue_tx(1, temp)
        sakuraio.send()
        print("cnt = %i" % (cnt))
        print("temp = %f" % (temp))
        # カウンターを+1
        cnt+=1

        # sakura.ioのキューにデータがあったら受信し値をledに入れる
        if (sakuraio.get_rx_queue_length()).get('queued'):
            dict_data = sakuraio.dequeue_rx_raw()
            led = dict_data['data'][0]
            print(led)
        else:
            print("nothing recv...")
        # ledが1ならLEDを点灯、0なら消灯、それ以外なら何もしない
        if led == 1:
            GPIO.output( LEDPIN, True )
        elif led == 0:
            GPIO.output( LEDPIN, False )
        else:
            print("no operation...")
        # キューを空にする
        sakuraio.clear_rx()
        
        # 5秒待って繰り返し
        time.sleep( 5 )

# Ctrl-Cが押されたら終了処理
except KeyboardInterrupt:
    GPIO.cleanup()
    spi.close()
    sys.exit(0)

