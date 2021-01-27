#include <REGX52.H>
#include "pre.h"
#include "display.h"
#include "timer.h"
#include "key.h"

 enum {HM,DATE,SEC,COUNT,CLOCK,SET};


void main()	
{
	uchar i;
	EA=1;
	Time0_init();
	for(;;)
	{
		display();	//根据当前模式设置dispBuf，并由后续函数处理并显示

		for(i=0;i<4;i++)	//显示数码管程序
			dispSet(dispBuf[i],~(0x01 << i));	 //dispBuf数组控制四个二极管的显示和小数点的亮灭
					
		if(mode != SET)  //除设置时间功能，其他功能需要处理时间溢出
			dealTime();		  
				   
		key();	//检测按键

		if(clock[0] == 1 && hour == clock[1] && min == clock[2])//闹钟时间是否到了																				
			beep = 0;	 //蜂鸣器响
		else 
			beep = 1;	//蜂鸣器不响
	}
}	

