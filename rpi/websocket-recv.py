# websocket-recv.py
# Raspberry Pi + Faboからのデータを受信するプログラム
# (PCで動かすプログラム)
# 使い方:
# % python3 websocket-recv.py

# 【要設定】WebSocketのURI
uri = "wss://api.sakura.io/ws/v1/xxxxxxx"


# ライブラリのインポート
from websocket import create_connection
import time
import sys
import json

# WebSocketのURIに接続
ws = create_connection(uri)
print("Receiving...")

# Ctrl-Cが押されるまで無限ループ
try:
    while True:
        # WebSocketでデータを受信
        result =  ws.recv()
#       print("Received '%s'" % result)
        # JSONのデータ構造に格納
        json_load = json.loads(result)
        # カウンターと温度のデータを取り出して表示
        if json_load['type'] == "channels":
            cnt = json_load['payload']['channels'][0]['value']
            temp = json_load['payload']['channels'][1]['value']
            print("cnt = %i" % (cnt))
            print("temp = %f" % (temp))

        # 1秒待って繰り返し
        time.sleep( 1 )

# Ctrl-Cが押されたら終了処理
except KeyboardInterrupt:
    ws.close()
    sys.exit(0)







