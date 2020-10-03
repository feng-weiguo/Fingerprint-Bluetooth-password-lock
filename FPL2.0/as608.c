/**************
AS608源文件
制作者：冯炜国
日期：2020.9.26
**************/

#include <reg52.h>
#include "as608.h"

uchar xdata Data_buff[32];//用于接收指纹的数据包


void Send_Bytes(uchar *c,uchar len)//向指纹模块连续发送字节
{
	uchar i = 0;
	for(i=0; i<len; i++)
	{
		SBUF = *(c+i);
		while(!TI);
		TI = 0;
	}
}


void Receive_Bytes(uchar *c,uchar len)//连续接收字节
{
	uchar i = 0;
	for(i=0; i<len; i++)
	{
		while(!RI);
		*(c+i) = SBUF;
		RI = 0;
	}        
}


char PS_GetImage()//发送获取图像的指令
{

	uchar *ps2 = "\xef\x01\xff\xff\xff\xff\x01\x00\x03\x01\x00\x05";//指令包

	Send_Bytes(ps2,12);//发送
	Receive_Bytes(Data_buff,12);//接收数据包
	if(Data_buff[9] == 0x00&&Data_buff[11]==0x0a)//反馈是否获取成功
	{                                                           
		return 1;        
	}
	return (-1);        
}

char PS_GenChar(uchar BufferID)//获取指纹图像特征，并存放到buffer中
{

	uchar *ps1 = "\xef\x01\xff\xff\xff\xff\x01\x00\x04\x02\x01\x00\x08";//存放到buffer1的指令包
	uchar *ps2 = "\xef\x01\xff\xff\xff\xff\x01\x00\x04\x02\x02\x00\x09";//存放到buffer2的指令包
	if(BufferID == 0x01)
	{
		Send_Bytes(ps1,13);
	}
	else
	{
		Send_Bytes(ps2,13);
	}
	Receive_Bytes(Data_buff,12);//接收数据包
	
	if(Data_buff[9]==0x00 && Data_buff[11]==0x0a)//判断特征是否生成且存放成功
	{                                                           
		return 1;        
	}
	return (-1);        
}

char PS_Search(uchar BufferID)//搜索指纹库函数
{

	uchar *ps1 = "\xef\x01\xff\xff\xff\xff\x01\x00\x08\x04\x01\x00\x00\x01\x2b\x00\x3a";//搜索buffer1指令
	uchar *ps2 = "\xef\x01\xff\xff\xff\xff\x01\x00\x08\x04\x02\x00\x00\x01\x2b\x00\x3b";//搜索buffer2指令
	if(BufferID == 0x01)
	{
		Send_Bytes(ps1,17);
	}
	else
	{
		Send_Bytes(ps2,17);
	}   
	Receive_Bytes(Data_buff,16);//接收数据包
	
	if(Data_buff[9] == 0x00)//判断是否与指纹库指纹匹配        
	{                                                           
		return 1;        
	}
	return (-1);        
}

