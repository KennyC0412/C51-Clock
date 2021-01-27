#include <REGX52.H>
#include "display.h"
#include "delay.h"
#include "pre.h"

enum {HM,DATE,SEC,COUNT,CLOCK,SET};

void dispSet(uchar dispData,uchar _bit)		//����С���㼰LED��ʾ����
{
	if((mode == HM || mode == SEC || mode == CLOCK) && _bit == 0xfd && point == 1)	//ʱ�䡢��ʱģʽ��ʾС����
		P1 = segcode[dispData] & 0x7f;		  
	else if(mode == DATE && _bit == 0xfd  && point == 1)   //������ʾ
		P1 = segcode[dispData] & 0x7f;		   
	else if(mode == COUNT && _bit == 0xfd && point == 1)	 //��ʱģʽ
		P1 = segcode[dispData] & 0x7f;	 
	else if(mode == SET && mode5_set == 1 && _bit == 0xfd  && point == 1)	 //��������ʱ��С����
		P1 = segcode[dispData] & 0x7f;	
	else if(mode == SET && mode5_set == 2 && _bit == 0xfd && point == 1) //����ʱ��ʱ��С����
		P1 = segcode[dispData] & 0x7f;	
	else
		P1 = segcode[dispData];	//��С�������ʾ��ֵ	
	P0 &= _bit;
	delay(100);    //��ʱ
	P0 |= 0x0f;	   //��Ӱ
}

void display()
{
	if(mode == DATE)
	{
		if(mode_1 == 0)	  //��ʾ���
		{
			point = 0;
			dispBuf[0] = year/1000%10;
			dispBuf[1] = year/100%10;
			dispBuf[2] = year/10%10;
			dispBuf[3] = year%10;			
		}
		else{		//��ʾ�º���,��С����	 
			point =1;
			dispBuf[0] = mon/10%10;
			if(dispBuf[0] == 0)
				dispBuf[0] = 11;
			dispBuf[1] = mon%10;
			dispBuf[2] = day/10%10;
			if(dispBuf[2] == 0)
				dispBuf[2] =   11;
			dispBuf[3] = day%10;		
		}		
	}
	else if(mode == HM)					  //��ʾʱ��
	{
		dispBuf[0] = hour/10%10;
		dispBuf[1] = hour%10;
		dispBuf[2] = min/10%10;
		dispBuf[3] = min%10;
	}
	else if(mode == SEC)	 //��ʾ��ͺ���ʱ��
	{
		point =1;
		dispBuf[0] = sec/10%10;
		dispBuf[1] = sec%10;
		dispBuf[2] = time/10%10;
		dispBuf[3] = time%10;		
	}
	else if(mode == COUNT)		  //��ʱ
	{
		point =1;
		dispBuf[0] = count/10%10;
		dispBuf[1] = count%10;
		dispBuf[2] = t/10%10;
		dispBuf[3] = t %10;	
	}
	else if(mode == CLOCK)	  //���ӹ�����ʾ
	{
	 	if(mode_4 == 0)	  
		{
			point=0;
			dispBuf[0] = 12; //C
			dispBuf[1] = 13; //L
			dispBuf[2] = 0; //O
			if(mode4_lock == 1) 
				dispBuf[3] = 11;	  	
			else
				dispBuf[3] = clock[0];	//��ʾ�Ƿ�������		
		}
		else{
			point=1;
			if(mode_4 == 1 && mode4_lock == 1) 
				dispBuf[0] = 11;	  	
			else
				dispBuf[0] = clock[1]/10%10;//��ʾ���ӵ�ʱ

			if(mode_4 == 2 && mode4_lock == 1) 
				dispBuf[1] = 11;	  
			else 	   				
				dispBuf[1] = clock[1]%10;

			if(mode_4 == 3 && mode4_lock == 1) 
				dispBuf[2] = 11;	  
			else 
				dispBuf[2] = clock[2]/10%10; //��ʾ���ӵķ�

			if(mode_4 == 4 && mode4_lock == 1) 
				dispBuf[3] = 11;	  	
			else 
				dispBuf[3] = clock[2]%10;				
		}
	}
	else if(mode == SET)
	{
		if(mode5_set == 0) point = 0;
		else if(mode5_set == 1 || mode5_set == 2) point = 1;
		/*************************************************************************************************************************/
		if(mode_5 == 0 && mode5_lock == 1) 
			dispBuf[0] = 11;	  //����ʵ����˸Ч��	
		else
		{
			if(mode5_set == 0)			  
				dispBuf[0] = year/1000%10;	 //��ʾ���ǧλ
			else if(mode5_set == 1)	
				dispBuf[0] = mon/10%10;	//��ʾ�µ�ʮλ
			else if(mode5_set == 2)
			 	dispBuf[0] = hour/10%10;	   //��ʾСʱ��ʮλ
		}
		/*************************************************************************************************************************/
		if(mode_5 == 1 && mode5_lock == 1) 
			dispBuf[1] = 11;	  //����ʵ����˸Ч��
		else 
		{
			if(mode5_set == 0)			  
				dispBuf[1] = year/100%10;	 //��ʾ��İ�λ
			else if(mode5_set == 1)	
				dispBuf[1] = mon%10;	//��ʾ�µĸ�λ
			else if(mode5_set == 2)
			 	dispBuf[1] = hour%10;	   //��ʾСʱ�ĸ�λ
		}	   	
		/*************************************************************************************************************************/
		if(mode_5 == 2 && mode5_lock == 1) 
			dispBuf[2] = 11;	  //����ʵ����˸Ч��	
		else 
		{
			if(mode5_set == 0)			  
				dispBuf[2] = year/10%10;	 //��ʾ���ʮλ
			else if(mode5_set == 1)	
				dispBuf[2] = day/10%10;	//��ʾ�յ�ʮλ
			else if(mode5_set == 2)
			 	dispBuf[2] = min/10%10;	   //��ʾ���ӵ�ʮλ
		}	
		/*************************************************************************************************************************/
		if(mode_5 == 3 && mode5_lock == 1) 
			dispBuf[3] = 11;	  //����ʵ����˸Ч��	
		else 
		{
			if(mode5_set == 0)			  
				dispBuf[3] = year%10;	 //��ʾ��ĸ�λ
			else if(mode5_set == 1)	
				dispBuf[3] = day%10;	//��ʾ�յĸ�λ
			else if(mode5_set == 2)
			 	dispBuf[3] = min%10;	   //��ʾ���ӵĸ�λ
		}			
	}
}