#include <REGX52.H>
#include "timer.h"
#include "pre.h"


 enum {HM,DATE,SEC,COUNT,CLOCK,SET};


void Time0_init()		//定时器0初始化
{
	TMOD|=0X01;		 //运行在16位重装模式
	TH0=(65536-10000)/256;		//赋初值    10ms进一次中断
	TL0=(65536-10000)%256;	
	TR0=1;	   //允许定时器0运行
	ET0=1;	   //打开定时器0中断
}


			 
void T00() interrupt 1		  //10ms进一次中断
{
	TH0=(65536-10000)/256;	
	TL0=(65536-10000)%256;	
	
	if(mode != SET) 
		time++;
	if(time >= 100)	//100次中断满1s，sec进位
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
			point = ~point;		 //在正常显示时分的时候，数码管的第二位的小数点0.5S的周期亮灭
		}	
	}
	else if(mode == DATE)
	{
		t++;
		if(t >= 150)		   //1.5s切换一次显示
		{
			t = 0;
			mode_1 = ~mode_1;	 //	mode_1 控制着显示年还是显示月日   
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
		if(t>=30) 		//在闹钟模式，设置的对应位闪烁  亮灭300ms
		{
			t=0;
			mode4_lock = ~mode4_lock;  //给出闪烁的时间标志位
		}			
	}
	else if(mode == SET)
	{
		t++;
		if(t>=30) 		//在闹钟模式，设置的对应位闪烁  亮灭300ms
		{
			t=0;
			mode5_lock = ~mode5_lock;  //给出闪烁的时间标志位
		}			
	}
}		   


void dealTime()	   //处理时间的进位
{
	//秒溢出
	if(sec >= 60)	
	{
		min++;	//清零
		sec=0;
	}
	//分钟溢出
	if(min >= 60) 
	{
		hour++;	  //清零													   .
		min=0;
	}
	//小时溢出（一天结束）
	if(hour >= 24)	
	{
		hour=0;	  //清零
		day++;
	}	
	//计算日期是否溢出
	if(mon <= 7 && mon != 2)   //七月份（含）以下，奇数31天，偶数30天（二月除外）
	{
		if(day % 2 == 1)  //有余数说明是奇数
		{
			if(day > 31)		 //日期加
			{
				day = 1;
				mon++;
			}
		}
		else{	   //没有余数说明是偶数
			if(day > 30)		 //日期加
			{
				day = 1;
				mon++;
			} 	
		}	
	}
	else if(mon >= 8)	  //八月份（含）以上，奇数30天，偶数31天
	{
		if(day % 2 == 1)  //有余数说明是奇数
		{
			if(day > 30)		 //日期加
			{
				day = 1;
				mon++;
			}
		}
		else{	   //没有余数说明是偶数
			if(day > 31)		 //日期加
			{
				day = 1;
				mon++;
			} 	
		}		
	}
	else if(mon == 2)	//二月份   闰年是29天，其他28天
	{
		if(year % 4 == 1)	 //没有余数说明是闰年
		{
			if(day > 29)		 //日期加
			{
				day = 1;
				mon++;
			} 	
		}	
		else{
			if(day > 28)		 //日期加
			{
				day = 1;
				mon++;
			} 				
		}
	}
	//计算月份是否溢出
	if(mon > 12)
	{
		mon = 1;
		year++;
	}	
}