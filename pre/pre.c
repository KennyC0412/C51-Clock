#include <REGX52.H>
#define uchar unsigned char
#define uint unsigned int

#include "pre.h"


 //��������ܱʶ�
uchar code segcode[14]={0xc0,0xf9,0xa4,0xb0,		//0,1,2,3	
						0x99,0x92,0x82,0xf8,	    //4,5,6,7
						0x80,0x90,0xbf,0xff,			//8,9,-,��
						0xc6,0xc7};			//C,L

uchar dispBuf[4];//mode;

enum MODE{HM,DATE,SEC,COUNT,CLOCK,SET}mode;	//���ܶ�Ӧʱ�֡����ڡ�����ʾ����ʱ������ʱ��

uchar hour=12,min=12,sec=0;		   //���ʱ����
uint year=2021,mon=1,day=8;			//���������

uint time,t;//�����ʱ����
uint count,count_ms;//���ʱ�����
uchar clock[3];//Ԫ��0���Ƿ������ӣ�0����  1������    Ԫ��1��Сʱ����    Ԫ��2�����ӱ��� 
uchar mode_4,mode_5,mode5_set;

bit point; //С�������λ
bit mode_1;//����������ʾ�껹������
bit mode_3;//���Ƽ�ʱ��ʼ����ͣ
bit key_lock; //���̱�־
bit mode4_lock,mode5_lock;	//���Ӻ�����ʱ����˸����λ
