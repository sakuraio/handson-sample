# sakuraio-send.py
# sakura.io�Υǡ��������ƥ��ȥץ����
# (Raspberry Pi��sakura.io����³���Ƽ¹�)
# �Ȥ���:
# % python3�ǥ��󥿥饯�ƥ��֥������ư����
# >>> ���ФƤ�����1�Ԥ������Ϥ���ENTER
# �⤷����
# % python3 sakuraio-send.py
#
# ����:
# sakuraio.enqueue_tx(0, 1)��1��Ǥ�դ��ͤ��Ѥ����
# sakura.io������������ͤ��Ѥ��


# coding: utf-8
from sakuraio.hardware.rpi import SakuraIOSMBus
sakuraio = SakuraIOSMBus()
sakuraio.enqueue_tx(0, 1)
sakuraio.send()
