# sakuraio-send.py
# sakura.ioのデータ送信テストプログラム
# (Raspberry Piでsakura.ioを接続して実行)
# 使い方:
# % python3でインタラクティブシェルを起動し、
# >>> が出てきたら1行ずつ入力してENTER
# もしくは
# % python3 sakuraio-send.py
#
# 参考:
# sakuraio.enqueue_tx(0, 1)の1を任意の値に変えると
# sakura.ioに送信される値が変わる


# coding: utf-8
from sakuraio.hardware.rpi import SakuraIOSMBus
sakuraio = SakuraIOSMBus()
sakuraio.enqueue_tx(0, 1)
sakuraio.send()
