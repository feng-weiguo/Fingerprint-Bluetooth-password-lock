/************************************************
Ö¸ÎÆÀ¶ÑÀÃÜÂëËø
»ùÓÚ51µ¥Æ¬»ú¡¢BT06À¶ÑÀÄ£¿é¡¢AS608Ö¸ÎÆÄ£¿é¡¢SG90¶æ»ú
×Ü´úÂëÁ¿£ºÔ¼300ĞĞ

¹¦ÄÜ1£º½ÓÊÕÖ¸ÎÆÌØÕ÷ÓëÖ¸ÎÆ¿â¶Ô±È
¹¦ÄÜ2£º½ÓÊÕÀ¶ÑÀ´®¿ÚÍ¨ĞÅ
¹¦ÄÜ3£º¶æ»ú½ÓÊÕĞÅºÅÇı¶
¯
ÖÆ×÷Õß£º·ëì¿¹ú
ÈÕÆÚ£º2020.9.26
************************************************/

#include <reg52.h>
#include "sg90.h"
#include "as608.h"

unsigned char code table0[] = "Warning ";//À¶ÑÀ¿ªÃÅ·´À¡
unsigned char code table1[] = "FBI";//À¶ÑÀ¿ªÃÅÃÜÂë
unsigned char receive[3]={0};//½ÓÊÕÀ¶ÑÀ´®¿ÚÍ¨ĞÅ

int i=0, flag = 0,j=0;
void UsartInit();
void compare(unsigned char *temp);

sbit WAK = P2^4;//Ö¸ÎÆÃÜÂë¸ĞÓ¦Î»
sbit vcc = VCC;

void main()
{
	UsartInit();
	TR0 = 0;
	receive[2] = '\0';
	while(1)
	{	
		if(receive[2] == 'I')//½øÈëÀ¶ÑÀÃÜÂëÆ¥ÅäµÄÌõ¼ş
		{
			compare(receive);//ÈôÆ¥Åä³É¹¦·¢ËÍ
			delay_ms(100);
			motor();//µç»úÔËĞĞ£¬¿ªÃÅ
			TR0 = 0;
			break;
		}
		if(WAK == 1)//Ö¸ÎÆÄ£¿é¸ĞÓ¦
		{	
			ES = 0;
			PS_GetImage();//»ñÈ¡Ö¸ÎÆÍ¼Ïñ
			PS_GenChar(0x01);//ÏÂÔØÖ¸ÎÆÌØÕ÷
			if((PS_Search(0x01)) == 1)//ÓëÖ¸ÎÆ¿â¶Ô±È
			{	
				motor();//¿ªÃÅ
			}
			ES = 1;
			break;
		}
	}		
}


void UsartInit()
{
	EA = 1;
	ES = 1;
	TR1 = 1;
	TMOD = 0x20;
	
	TH1 = 0xfd;//²¨ÌØÂÊ9600£¬¾§Õñ11.0592MHZ
	TL1 = 0xfd;
	
	SCON = 0x50;
	PCON = 0x0;
}

void compare(unsigned char *temp)//À¶ÑÀ»ØÀ¡º¯Êı
{
	ES = 0;
	for(i=0; i<3; i++)
	{
		if(temp[i] == table1[i])
			flag++;			
	}
	if(flag == 3)//½øÈëÆ¥Åä
	{
		for(i=0; i<8; i++)
		{
			SBUF = table0[i];
			while(TI != 1);
			TI = 0;
		}
		receive[2] = '\0';
	}
	receive[2] = '\0';
	flag = 0;
	ES = 1;
}

void usart() interrupt 4  //´®¿ÚÖĞ¶Ïº¯Êı£¬½ÓÊÕ3¸ö×Ö·û
{
	
	receive[j] = SBUF;
	while(RI != 1);
	RI = 0;
	j++;
	if(j == 3)
		j = 0;
}
