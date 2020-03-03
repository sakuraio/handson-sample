# Raspberry Pi & sakura.io 体験ハンズオン用サンプルプログラム集

## 概要

「Raspberry Pi & sakura.io 体験ハンズオン」にて使用するサンプルプログラム集です。本ハンズオンでは、sakura.ioのコンセプトをより深く体験いただくため、簡単なIoTサービスを構築します。具体的には「温度センサとLEDを搭載するIoTデバイス」および「センサデータの可視化とデバイスの制御を行うサービス」を構築します。IoTデバイス側のコンピュータとしてRaspberry Pi、IoTデバイスとしてFabo、プログラミング言語はPython 3を使用します。

## install-devtools.sh

* Raspberry Piで動かすプログラムです。
* Raspberry Piの開発環境をセットアップします。

### 使い方

* スクリプトを1行ずつコマンドラインに入力して実行します。
* もしくは下記のコマンドでも実行できます。(sudo apt updateに時間がかかるのでご注意ください)

% bash install-devtools.sh


## rpi-fabo.py

* Raspberry Piで動かすプログラムです。
* Raspberry Piとsakura.ioの間で、Faboに接続されたセンサーやLEDのデータを送受信します。

### 使い方

% python3 rpi-fabo.py


## sakuraio-send.py

* sakura.ioのデータ送信テストプログラムです。
* Raspberry Piにsakura.ioを接続して実行します。

### 使い方

* % python3でインタラクティブシェルを起動し、>>> が出てきたら1行ずつ入力してENTERを押します。
* もしくは、下記のコマンドでも実行できます。

% python3 sakuraio-send.py

* sakuraio.enqueue_tx(0, 1)の1を任意の値に変えると、sakura.ioに送信される値が変わります。


## sakuraio-test.py

* sakura.ioの動作テストプログラムです。
* Raspberry Piにsakura.ioを接続して実行します。

### 使い方

* % python3でインタラクティブシェルを起動し、>>> が出てきたら1行ずつ入力してENTERを押します。
* もしくは、下記のコマンドでも実行できます。

% python3 sakuraio-test.py

* 出力されるのは個々のsakura.ioモジュールに割り振られた固有のIDです。


## websocket-recv.py

* PCもしくはサーバで動かすプログラムです。
* sakura.ioから送られてきたデータを受信するプログラムです。
* 事前に、Pythonのwebsocketモジュールをインストールしてください。
* WebSocketのURLを設定してから実行してください。

### 使い方

% python3 websocket-recv.py


## websocket-send.py

* PCもしくはサーバで動かすプログラムです。
* Faboに接続されたLEDを操作するデータをsakura.ioに送信するプログラムです。
* 事前に、Pythonのwebsocketモジュールをインストールしてください。
* WebSocketのURLと、sakura.ioモジュールのIDを設定してから実行してください。

### 使い方

% python3 websocket-send.py
