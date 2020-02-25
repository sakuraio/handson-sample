# sakuraio-test.py
# sakura.ioの動作テストプログラム
# (Raspberry Piでsakura.ioを接続して実行)
# 使い方:
# % python3でインタラクティブシェルを起動し、
# >>> が出てきたら1行ずつ入力してENTER
# もしくは
# % python3 sakuraio-test.py


# coding: utf-8
import sakuraio
from sakuraio.hardware.rpi import SakuraIOSMBus
sakuraio = SakuraIOSMBus()
print(sakuraio.get_unique_id())
