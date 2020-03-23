# sakuraio-recv.py
# sakura.ioのデータ受信テストプログラム
# (Raspberry Piでsakura.ioを接続して実行)
# 使い方:
# sakura.ioコントロールパネルのメッセージ送信機能でデータを送ってから、
# % python3 sakuraio-recv.py

# ライブラリのインポートと初期化
from sakuraio.hardware.rpi import SakuraIOSMBus
sakuraio = SakuraIOSMBus()

# sakura.ioのキューからデータを受信
dict_data = sakuraio.dequeue_rx_raw()
# 取得したデータ全体を表示
print(dict_data)
# 0チャンネルにセットされたデータを取得しledに代入して表示
led = dict_data['data'][0]
print("led = %i" % (led))
