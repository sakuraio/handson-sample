# sakuraio-test.py
# sakura.io��ư��ƥ��ȥץ����
# (Raspberry Pi��sakura.io����³���Ƽ¹�)
# �Ȥ���:
# % python3�ǥ��󥿥饯�ƥ��֥������ư����
# >>> ���ФƤ�����1�Ԥ������Ϥ���ENTER
# �⤷����
# % python3 sakuraio-test.py


# coding: utf-8
import sakuraio
from sakuraio.hardware.rpi import SakuraIOSMBus
sakuraio = SakuraIOSMBus()
print(sakuraio.get_unique_id())
