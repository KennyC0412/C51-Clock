#include <REGX52.H>
#include "display.h"
#include "delay.h"
#include "pre.h"

enum {HM,DATE,SEC,COUNT,CLOCK,SET};

void dispSet(uchar dispData,uchar _bit)		//控制小数点及LED显示程序
{
	if((mode == HM || mode == SEC || mode == CLOCK) && _bit == 0xfd && point == 1)	//时间、计时模式显示小数点
		P1 = segcode[dispData] & 0x7f;		  
	else if(mode == DATE && _bit == 0xfd  && point == 1)   //日期显示
		P1 = segcode[dispData] & 0x7f;		   
	else if(mode == COUNT && _bit == 0xfd && point == 1)	 //计时模式
		P1 = segcode[dispData] & 0x7f;	 
	else if(mode == SET && mode5_set == 1 && _bit == 0xfd  && point == 1)	 //设置日期时有小数点
		P1 = segcode[dispData] & 0x7f;	
	else if(mode == SET && mode5_set == 2 && _bit == 0xfd && point == 1) //设置时间时有小数点
		P1 = segcode[dispData] & 0x7f;	
	else
		P1 = segcode[dispData];	//无小数点仅显示数值	
	P0 &= _bit;
	delay(100);    //延时
	P0 |= 0x0f;	   //消影
}

void display()
{
	if(mode == DATE)
	{
		if(mode_1 == 0)	  //显示年份
		{
			point = 0;
			dispBuf[0] = year/1000%10;
			dispBuf[1] = year/100%10;
			dispBuf[2] = year/10%10;
			dispBuf[3] = year%10;			
		}
		else{		//显示月和日,有小数点	 
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
	else if(mode == HM)					  //显示时分
	{
		dispBuf[0] = hour/10%10;
		dispBuf[1] = hour%10;
		dispBuf[2] = min/10%10;
		dispBuf[3] = min%10;
	}
	else if(mode == SEC)	 //显示秒和毫秒时间
	{
		point =1;
		dispBuf[0] = sec/10%10;
		dispBuf[1] = sec%10;
		dispBuf[2] = time/10%10;
		dispBuf[3] = time%10;		
	}
	else if(mode == COUNT)		  //计时
	{
		point =1;
		dispBuf[0] = count/10%10;
		dispBuf[1] = count%10;
		dispBuf[2] = t/10%10;
		dispBuf[3] = t %10;	
	}
	else if(mode == CLOCK)	  //闹钟功能显示
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
				dispBuf[3] = clock[0];	//显示是否开启闹钟		
		}
		else{
			point=1;
			if(mode_4 == 1 && mode4_lock == 1) 
				dispBuf[0] = 11;	  	
			else
				dispBuf[0] = clock[1]/10%10;//显示闹钟的时

			if(mode_4 == 2 && mode4_lock == 1) 
				dispBuf[1] = 11;	  
			else 	   				
				dispBuf[1] = clock[1]%10;

			if(mode_4 == 3 && mode4_lock == 1) 
				dispBuf[2] = 11;	  
			else 
				dispBuf[2] = clock[2]/10%10; //显示闹钟的分

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
			dispBuf[0] = 11;	  //灯灭，实现闪烁效果	
		else
		{
			if(mode5_set == 0)			  
				dispBuf[0] = year/1000%10;	 //显示年的千位
			else if(mode5_set == 1)	
				dispBuf[0] = mon/10%10;	//显示月的十位
			else if(mode5_set == 2)
			 	dispBuf[0] = hour/10%10;	   //显示小时的十位
		}
		/*************************************************************************************************************************/
		if(mode_5 == 1 && mode5_lock == 1) 
			dispBuf[1] = 11;	  //灯灭，实现闪烁效果
		else 
		{
			if(mode5_set == 0)			  
				dispBuf[1] = year/100%10;	 //显示年的百位
			else if(mode5_set == 1)	
				dispBuf[1] = mon%10;	//显示月的个位
			else if(mode5_set == 2)
			 	dispBuf[1] = hour%10;	   //显示小时的个位
		}	   	
		/*************************************************************************************************************************/
		if(mode_5 == 2 && mode5_lock == 1) 
			dispBuf[2] = 11;	  //灯灭，实现闪烁效果	
		else 
		{
			if(mode5_set == 0)			  
				dispBuf[2] = year/10%10;	 //显示年的十位
			else if(mode5_set == 1)	
				dispBuf[2] = day/10%10;	//显示日的十位
			else if(mode5_set == 2)
			 	dispBuf[2] = min/10%10;	   //显示分钟的十位
		}	
		/*************************************************************************************************************************/
		if(mode_5 == 3 && mode5_lock == 1) 
			dispBuf[3] = 11;	  //灯灭，实现闪烁效果	
		else 
		{
			if(mode5_set == 0)			  
				dispBuf[3] = year%10;	 //显示年的个位
			else if(mode5_set == 1)	
				dispBuf[3] = day%10;	//显示日的个位
			else if(mode5_set == 2)
			 	dispBuf[3] = min%10;	   //显示分钟的个位
		}			
	}
}