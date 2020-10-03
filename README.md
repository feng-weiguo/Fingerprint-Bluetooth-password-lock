# Fingerprint-Bluetooth-password-lock
Fingerprint Bluetooth password lock based on STC89C52, AS608, BT06, SG90
Important parameters:
Working temperature: -30℃～50℃
Working voltage: 5V

Password lock function:
1. With fingerprint entry and identification functions, only the original fingerprint library can be identified during work
2. With Bluetooth serial communication function, the Bluetooth connection is password protected
3. Have motor drive function
4. Has the function of adding other modules

Usage and principle:
Method 1: Put one of your fingers on the fingerprint module, the fingerprint module can start the verification mode, after the verification is successful, it will send a signal to the servo, and the servo will turn to open the door lock.
Method 2: Take out the Android phone, turn on the Bluetooth, find the Bluetooth named BT06, enter the password, and the lock can be unlocked after successful connection. If it takes too long to push the door and the lock closes, there is no need to reconnect at this time.
Method 2.1: Download or open the Bluetooth serial port assistant, and send the second verification password to BT06 Bluetooth. After the verification is successful, the door lock can be opened again.
Method 2.2: Disconnect the Bluetooth connection directly, or open the door lock again.

摘要：基于STC89C52、AS608、BT06、SG90的指纹蓝牙密码锁，此锁在原门锁的基础上安装，可随时拆卸，在不破坏原锁的基础上增加了部分功能。基于C语言编程，代码原创。截止2020.9.26全网唯一。此项目开源。

重要参数：
工作温度：-30℃～50℃
工作电压：5V

密码锁功能：
1.拥有指纹录入、识别功能，工作期间只能识别原有指纹库
2.拥有蓝牙串口通信功能，蓝牙连接有密码保护
3.拥有电机驱动功能
4.拥有追加其他模块的功能

使用方式及原理：
方式1：将其中一只手指放在指纹模块上方，指纹模块即可开启验证模式，验证成功后会发送信号给舵机，舵机转动开启门锁。
方式2：拿出安卓系统的手机，开启蓝牙，找到名称为BT06的蓝牙，输入密码，连接成功后即可开锁。若太久才推门导致门锁关闭，这时候不需要重新连接。
方式2.1：下载或者打开蓝牙串口助手，向BT06蓝牙发送第二个验证密码，验证成功后即可再次开启门锁。
方式2.2：直接断开蓝牙连接，也可再次开启门锁。
