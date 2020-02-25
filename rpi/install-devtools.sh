#!/bin/bash

# install-devtools.sh
# 開発環境をセットアップするプログラム
# (Raspberry Piで実行)

# Raspberry Piにインストールされているソフトウェアを最新にします。
sudo apt update

# Python3およびパッケージ管理ツールをインストールします。
sudo apt install python3 python3-pip

# Pythonでハードウェアを制御するためのライブラリをインストールします。
sudo apt install python3-smbus python3-rpi.gpio i2c-tools

# pipを使用してsakura.ioライブラリをインストールします。
sudo pip3 install sakuraio pyserial
