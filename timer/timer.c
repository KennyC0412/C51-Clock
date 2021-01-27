#include <REGX52.H>
#include "timer.h"
#include "pre.h"


 enum {HM,DATE,SEC,COUNT,CLOCK,SET};


void Time0_init()		//��ʱ��0��ʼ��
{
	TMOD|=0X01;		 //������16λ��װģʽ
	TH0=(65536-10000)/256;		//����ֵ    10ms��һ���ж�
	TL0=(65536-10000)%256;	
	TR0=1;	   //����ʱ��0����
	ET0=1;	   //�򿪶�ʱ��0�ж�
}


			 
void T00() interrupt 1		  //10ms��һ���ж�
{
	TH0=(65536-10000)/256;	
	TL0=(65536-10000)%256;	
	
	if(mode != SET) 
		time++;
	if(time >= 100)	//100���ж���1s��sec��λ
	{
		sec++;
		time=0;
	}

	if(mode == HM)			 
	{
		t++;
		if(t>=50)
		{
			t=0;
			point = ~point;		 //��������ʾʱ�ֵ�ʱ������ܵĵڶ�λ��С����0.5S����������
		}	
	}
	else if(mode == DATE)
	{
		t++;
		if(t >= 150)		   //1.5s�л�һ����ʾ
		{
			t = 0;
			mode_1 = ~mode_1;	 //	mode_1 ��������ʾ�껹����ʾ����   
		}
	}
	else if(mode == COUNT)
	{
		if(mode_3 == 1) t++;
		if(t >= 100)
		{
			t = 0;
			if(mode == 3)
				count++;	
		}
	}
	else if(mode == CLOCK)
	{
		t++;
		if(t>=30) 		//������ģʽ�����õĶ�Ӧλ��˸  ����300ms
		{
			t=0;
			mode4_lock = ~mode4_lock;  //������˸��ʱ���־λ
		}			
	}
	else if(mode == SET)
	{
		t++;
		if(t>=30) 		//������ģʽ�����õĶ�Ӧλ��˸  ����300ms
		{
			t=0;
			mode5_lock = ~mode5_lock;  //������˸��ʱ���־λ
		}			
	}
}		   


void dealTime()	   //����ʱ��Ľ�λ
{
	//�����
	if(sec >= 60)	
	{
		min++;	//����
		sec=0;
	}
	//�������
	if(min >= 60) 
	{
		hour++;	  //����													   .
		min=0;
	}
	//Сʱ�����һ�������
	if(hour >= 24)	
	{
		hour=0;	  //����
		day++;
	}	
	//���������Ƿ����
	if(mon <= 7 && mon != 2)   //���·ݣ��������£�����31�죬ż��30�죨���³��⣩
	{
		if(day % 2 == 1)  //������˵��������
		{
			if(day > 31)		 //���ڼ�
			{
				day = 1;
				mon++;
			}
		}
		else{	   //û������˵����ż��
			if(day > 30)		 //���ڼ�
			{
				day = 1;
				mon++;
			} 	
		}	
	}
	else if(mon >= 8)	  //���·ݣ��������ϣ�����30�죬ż��31��
	{
		if(day % 2 == 1)  //������˵��������
		{
			if(day > 30)		 //���ڼ�
			{
				day = 1;
				mon++;
			}
		}
		else{	   //û������˵����ż��
			if(day > 31)		 //���ڼ�
			{
				day = 1;
				mon++;
			} 	
		}		
	}
	else if(mon == 2)	//���·�   ������29�죬����28��
	{
		if(year % 4 == 1)	 //û������˵��������
		{
			if(day > 29)		 //���ڼ�
			{
				day = 1;
				mon++;
			} 	
		}	
		else{
			if(day > 28)		 //���ڼ�
			{
				day = 1;
				mon++;
			} 				
		}
	}
	//�����·��Ƿ����
	if(mon > 12)
	{
		mon = 1;
		year++;
	}	
}