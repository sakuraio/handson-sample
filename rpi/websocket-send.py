# websocket-send.py
# Raspberry Pi + Faboにデータを送信するプログラム
# (PCで動かすプログラム)
# 使い方:
# % python3 websocket-send.py

# 【要設定】WebSocketのURI
uri = "wss://api.sakura.io/ws/v1/xxxxxxx"

# 【要設定】sakura.ioモジュールのID
module_id = "uxxxxxxxxxxx"


# ライブラリのインポート
from websocket import create_connection
import time
import sys
import json

# JSONデータ
# channelはArduino版との互換性のため0,1,2を定義しているが
# 本プログラムではchannel 0のみ使用
json_data = {
    "type": "channels",
    "module": module_id,
    "payload": {
        "channels": [
            {"channel":0,"type":"I","value":0},
            {"channel":1,"type":"I","value":0},
            {"channel":2,"type":"I","value":0}
        ]
    }
}

# WebSocketのURIに接続
ws = create_connection(uri)
print("Sending...")

# Ctrl-Cが押されるまで無限ループ
try:
    while True:
        # コマンドラインから値を入力
        print('input data: (0=OFF/1=ON/other=NOP)')
        input_data = input('>> ')
#       print(input_data)
        # 値が0か1なら整数値に変換してJSONデータに代入しWebSocketで送信
        if input_data == '0' or input_data == '1':
            int_data = int(input_data)
            json_data['payload']['channels'][0]['value'] = int_data
            ws.send(json.dumps(json_data))
#           print(json.dumps(json_data))
        # それ以外なら何もしない
        else:
            print("nothing send ...")
        
# Ctrl-Cが押されたら終了処理
except KeyboardInterrupt:
    ws.close()
    sys.exit(0)
