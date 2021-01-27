#ifndef _PRE_H_
#define _PRE_H_

#include <REGX52.H>
#define uchar unsigned char
#define uint unsigned int

sbit k1 = P2^0;		//��������
sbit k2 = P2^1;
sbit k3 = P2^2;
sbit k4 = P2^3;
sbit k5 = P2^4;
sbit k6 = P2^7;
sbit beep = P0^4;

 //��������ܱʶ�
extern uchar code segcode[14];		//8,9,-,��

extern uchar dispBuf[4],mode;

extern uchar hour,min,sec;		   //���ʱ����
extern uint year,mon,day;			//���������

extern uint time,t;		//�����ʱ����
extern uint count,count_ms;		//���ʱ�����
extern uchar clock[3];		//���Ӵ洢����		Ԫ��0���Ƿ������ӣ�0����  1������    Ԫ��1��Сʱ����    Ԫ��2�����ӱ��� 
extern uchar mode_4,mode_5,mode5_set;
extern bit point,mode_1,mode_3,key_lock;
extern bit mode4_lock,mode5_lock;
	  
#endif