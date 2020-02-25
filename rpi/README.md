# Raspberry Pi & sakura.io 体験ハンズオン用サンプルプログラム集

## 概要

「Raspberry Pi & sakura.io 体験ハンズオン」にて使用するサンプルプログラム集です。本ハンズオンでは、sakura.ioのコンセプトをより深く体験いただくため、簡単なIoTサービスを構築します。具体的には「温度センサとLEDを搭載するIoTデバイス」および「センサデータの可視化とデバイスの制御を行うサービス」を構築します。IoTデバイス側のコンピュータとしてRaspberry Pi、IoTデバイスとしてFabo、プログラミング言語はPythonを使用します。

## rpi-fabo.py

* Raspberry Piで動かすプログラムです。
* Raspberry Piとsakura.ioの間で、Faboに接続されたセンサーやLEDのデータを送受信します。

### 使い方

% python3 Fabo-RasPi.py

## websocket-recv.py

* PCで動かすプログラムです。
* sakura.ioから送られてきたデータを受信するプログラムです。
* 使用前に、WebSocketのURLを設定する必要があります。

### 使い方

% python3 websocket-recv.py

## websocket-send.py

* PCで動かすプログラムです。
* Faboに接続されたLEDを操作するデータをsakura.ioに送信するプログラムです。
* 使用前に、WebSocketのURLと、sakura.ioモジュールのIDを設定する必要があります。

### 使い方

% python3 websocket-send.py
