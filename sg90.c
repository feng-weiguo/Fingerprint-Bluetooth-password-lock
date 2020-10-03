/**************
SG90舵机 源文件
制作者：冯炜国
日期：2020.9.26
**************/

#include <reg52.h>
#include "sg90.h"

sbit PWM = P2^1;
unsigned char Turn;//速度信号
unsigned char value = 0;

void delay_ms(unsigned int c)//延时1ms，误差0us
{
    unsigned int a,b;
    for(;c>0;c--)
        for(b=102;b>0;b--)
            for(a=3;a>0;a--);
}

void Time0_Init()
{
	TMOD = 0x01;
	EA = 1;
	ET0 = 1;
	TH0 = 0xfe;
	TL0 = 0x33;//11.0592MZ,0.5ms
	TR0 = 1;
}

void motor()//舵机驱动函数
{
	ES = 0;
	Time0_Init();
    PWM = 0;
	value = 0;
	Turn = 2;     //正转
	delay_ms(180);
	TR0 = 0;
	delay_ms(800);
	value = 0;
	Turn = 4;     //反转
	Time0_Init();
	delay_ms(170);
	TR0 = 0;
	PWM = 0;
	value = 0;
	ES = 1;
}

void timer0() interrupt 1  //中断函数，0.5ms
{
    TR0 = 0;
    TH0  = 0xfe;
    TL0  = 0x33;

    if(value <= Turn)
    {
        PWM = 1;
    }
    else
    {
        PWM = 0;
    }
    if(value == 40)//让舵机周期为20ms
    {
        value = 0;
    }
    value ++;
    TR0 = 1;
}