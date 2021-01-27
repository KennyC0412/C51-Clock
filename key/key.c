#include "pre.h"
#include "key.h"

enum {HM,DATE,SEC,COUNT,CLOCK,SET};

void key()	  //按键程序
{
	uint dat;
	if(k1 == 1 && k2 == 1 && k3 == 1 && k4 == 1 && k5 == 1 && k6 == 1) 
		key_lock = 1; //实现自锁的变量	  用于实现短时间内只算按下一次按键
 /***********************************************************************************/
	if(k1 == 0 && key_lock == 1)		 //若 k1 按键被按下
	{
		key_lock = 0;
		if(mode < COUNT)
		{
			t = 0;
		   	++mode;			
			if(mode >= COUNT)
		   		mode = HM;
		}
		else if(mode == COUNT)
		{
			mode_3 = ~mode_3;
			if(mode_3 == 1)
			{
				count = 0;
				t = 0;
			}
		}
		else if(mode == CLOCK)
		{
			if(mode_4 == 0)
			{
				if(clock[0] == 1)
					clock[0] = 0;
				else 
					clock[0] = 1;
			}
			else if(mode_4 == 1)
			{
				dat = clock[1]/10%10;		 //设置闹钟使时间小时的十位
				++dat;
				if(dat >= 3)   
					dat = 2;
				clock[1] = dat*10 + clock[1]%10;
			}
			else if(mode_4 == 2)	   //设置闹钟时间小时的个位
			{
				dat = clock[1]%10;		 //设置闹钟使时间小时的个位
				clock[1] /= 10;
				++dat;
				if(dat >= 10)   
					dat = 0;
				clock[1] = clock[1]*10 + dat;				
			}
			else if(mode_4 == 3)	   //设置闹钟时间分钟的十位
			{
				dat = clock[2]/10%10;		 //设置闹钟分钟的十位
				++dat;
				if(dat >= 6)   
					dat = 0;
				clock[2] = dat*10 + clock[2]%10;
			}
			else if(mode_4 == 4)	   //设置闹钟时间分钟的个位
			{
				dat = clock[2]%10;		 //设置闹钟使时间小时的十位
				clock[2] /= 10;
				++dat;
				if(dat >= 10)   
					dat = 0;
				clock[2] = clock[2]*10 + dat;	
			}
		}
		else if(mode == 5)
		{
			/*************************************************************************************************************************/
			if(mode_5 == 0)		//设置数码管第一位上的时间
			{
				if(mode5_set == 0)		//设置年的千位
				{
					dat = year/1000%10;		//取出年的千位的值
					year = year - dat*1000;		 //减去该值，使千位的值为0
					++dat; 		
					if(dat >= 10)
						dat = 0;
					year = dat*1000 + year; 		 //设置千位的数值
				}
				else if(mode5_set == 1)	   //设置月的十位
				{
					dat = mon/10%10;		//取出月的十位的值
					mon = mon - dat*10;		 //减去该值，使十位的值为0
					++dat; 		
					if(dat >= 2)
						dat = 0;
					mon = dat*10 + mon; 		 //设置十位的数值	
				}
				else if(mode5_set == 2)	   //设置时的十位
				{
					dat = hour/10%10;		//取出时的十位的值
					hour = hour - dat*10;		 //减去该值，使十位的值为0
					++dat; 	
					if(dat >= 3)
						dat = 0;
					hour = dat*10 + hour; 		 //设置十位的数值	
				}
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 1)	//设置数码管第二位上的时间
			{
				if(mode5_set == 0)		
				{
					dat = year/100%10;		  
					year = year - dat*100;		
					++dat; 	
					if(dat >= 10)
						dat = 0;
					year = dat*100 + year; 	   	 
				}
				else if(mode5_set == 1)	   
				{
					dat = mon%10;		
					mon = mon - dat;		 
					++dat; 	
					if(dat >= 10)
						dat = 0;
					mon = dat + mon; 		
				}
				else if(mode5_set == 2)	
				{
					dat = hour%10;	
					hour = hour - dat;		 
					++dat; 	
					if(dat >= 10)
						dat = 0;
					hour = dat + hour; 		 	
				}
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 2)	//设置数码管第三位上的时间
			{
				if(mode5_set == 0)		
				{
					dat = year/10%10;	 
					year = year - dat*10;	
					++dat; 	
					if(dat >= 10)
						dat = 0;
					year = dat*10 + year; 	
				}
				else if(mode5_set == 1)	
				{
					dat = day/10%10;		
					day = day - dat*10;		 
					++dat; 	
					if(dat >= 4)
						dat = 0;
					day = dat*10 + day; 			
				}
				else if(mode5_set == 2)	   
				{
					dat = min/10%10;		
					min = min - dat*10;		 
					++dat; 		
					if(dat >= 6)
						dat = 0;
					min = dat*10 + min; 		 	
				}			
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 3)	//设置数码管第四位上的时间
			{
				if(mode5_set == 0)		
				{
					dat = year%10;	
					year = year - dat;		 
					++dat; 		
					if(dat >= 10)
						dat = 0;
					year = dat + year; 	   
				}
				else if(mode5_set == 1)	   
				{
					dat = day%10;		
					day = day - dat;		 
					++dat; 	
					if(dat >= 10)
						dat = 0;
					day = dat + day; 		 
				} 
				else if(mode5_set == 2)	  
				{
					dat = min%10;		
					min = min - dat;		
					++dat; 	
					if(dat >= 10)
						dat = 0;
					min = dat + min; 		
				} 		
			}
		}
				
	}	
 /*********************************************************************************************/
	if(k2 == 0 && key_lock == 1)	  //若 k2 按键被按下
	{
		key_lock = 0;
		if(mode == COUNT)	   //如果是秒表模式
			mode = HM;	   //切换显示时分模式
		else if(mode == CLOCK)
		{
			if(mode_4 == 0)
			{
				if(clock[0] == 1)	//设置是否开启闹钟
					clock[0] = 0;	
				else 
					clock[0] = 1;
			}
			else if(mode_4 == 1)
			{
				dat = clock[1]/10%10;		 //设置闹钟小时的十位
				--dat;
				if(dat >= 3)   
					dat = 2;
				clock[1] = dat*10 + clock[1]%10;
			}
			else if(mode_4 == 2)	   //设置闹钟时间小时的个位
			{
				dat = clock[1]%10;		 //设置闹钟使时间小时的个位
				clock[1] /= 10;
				--dat;
				if(dat >= 10)  
					dat = 9;
				clock[1] = clock[1]*10 + dat;				
			}
			else if(mode_4 == 3)	   //设置闹钟时间分钟的十位
			{
				dat = clock[2]/10%10;		 //设置闹钟分钟的十位
				--dat;
				if(dat >= 6)   
					dat = 5;
				clock[2] = dat*10 + clock[2]%10;			
			}
			else if(mode_4 == 4)	   //设置闹钟时间分钟的个位
			{
				dat = clock[2]%10;		 //设置闹钟使时间小时的十位
				clock[2] /= 10;
				--dat;
				if(dat >= 10)   
					dat = 9;
				clock[2] = clock[2]*10 + dat;				
			}
		}
		else if(mode == SET)
		{
			/*************************************************************************************************************************/
			if(mode_5 == 0)		//设置数码管第一位上的时间
			{
				if(mode5_set == 0)	
				{
					dat = year/1000%10;	
					year = year - dat*1000;		
					--dat; 		
					if(dat >= 10)
						dat = 9;
					year = dat*1000 + year; 		 
				}
				else if(mode5_set == 1)	  
				{
					dat = mon/10%10;		
					mon = mon - dat*10;		 
					--dat; 	
					if(dat >= 2)
						dat = 1;
					mon = dat*10 + mon; 			
				}
				else if(mode5_set == 2)	   
				{
					dat = hour/10%10;	
					hour = hour - dat*10;	
					--dat; 		
					if(dat >= 3)
						dat = 2;
					hour = dat*10 + hour; 		 	
				}
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 1)	//设置数码管第二位上的时间
			{
				if(mode5_set == 0)	
				{
					dat = year/100%10;		  
					year = year - dat*100;		 
					--dat; 	
					if(dat >= 10)
						dat = 9;
					year = dat*100 + year; 	   	
				}
				else if(mode5_set == 1)	  
				{
					dat = mon%10;	
					mon = mon - dat;		
					--dat; 		
					if(dat >= 10)
						dat = 9;
					mon = dat + mon; 		 	
				}
				else if(mode5_set == 2)	   
				{
					dat = hour%10;		
					hour = hour - dat;		
					--dat; 	
					if(dat >= 10)
						dat = 9;
					hour = dat + hour; 		 	
				}
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 2)	//设置数码管第三位上的时间
			{
				if(mode5_set == 0)	
				{
					dat = year/10%10;	 
					year = year - dat*10;	 
					--dat; 	
					if(dat >= 10)
						dat = 9;
					year = dat*10 + year; 	  
				}
				else if(mode5_set == 1)	  
				{
					dat = day/10%10;	
					day = day - dat*10;		 
					--dat; 	
					if(dat >= 4)
						dat = 3;
					day = dat*10 + day; 			
				}
				else if(mode5_set == 2)	   
				{
					dat = min/10%10;		
					min = min - dat*10;		
					--dat; 		
					if(dat >= 6)
						dat = 5;
					min = dat*10 + min; 		 
				}			
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 3)	//设置数码管第四位上的时间
			{
				if(mode5_set == 0)		
				{
					dat = year%10;		
					year = year - dat;		
					--dat; 		
					if(dat >= 10)
						dat = 9;
					year = dat + year; 	   
				}
				else if(mode5_set == 1)	   
				{
					dat = day%10;		
					day = day - dat;	
					--dat; 		
					if(dat >= 10)
						dat = 9;
					day = dat + day; 		
				} 
				else if(mode5_set == 2)	   
				{
					dat = min%10;	
					min = min - dat;		
					--dat; 		
					if(dat >= 10)
						dat = 9;
					min = dat + min; 		
				} 		
			}
		}	
		else if(mode < COUNT)			 
			mode = COUNT;	   //切换到秒表模式

		count = 0;
		t = 0;mode_3=0;
	}
 /***************************** ***********************************************************************/
	if(k3 == 0 && key_lock == 1)	   //若 k3 按键被按下
	{
		key_lock = 0;
		if(mode == CLOCK)	  
		{
			mode = HM;	  
			mode_4 = 0;
		}	 			
		else if(mode == SET)
		{
			++mode_5 ;
			if(mode_5 >= 4)
			{
				mode_5 = 0;	
				++mode5_set;
				if(mode5_set >= 3)
					mode5_set = 0;
			}
		}
		else if(mode == COUNT)
		{
			mode_3 = ~mode_3;
		}
		else if(mode < COUNT)
		{
			mode = CLOCK;	   //切换到闹钟设置
		}			   
			
	}
/***************************** ***********************************************************************/
	if(k4 == 0 && key_lock == 1)	//若 k4 按键被按下
	{
		key_lock = 0;
		if(mode < COUNT)	 
		{
			mode5_set = 0;
			mode_5 = 0;
			mode = SET;	 
		}	   		 	
		else if(mode == CLOCK)			 
		{
			++mode_4;		
			if(mode_4 >= 5)
			{
				mode_4 = 0;
			}	
		}
		else if(mode == SET)	 
		{
			mode = HM;		   
		}
	}
/***************************** ***********************************************************************/
	if(k5 == 0 && key_lock == 1)
	{
		key_lock = 0;
		if(mode == SET)
		{
			--mode_5;
			if(mode_5 < 0)
			{
				mode_5 = 3;	
				--mode5_set;
				if(mode5_set < 0)
					mode5_set = 2;
				
			}
		}
		else if(mode == CLOCK)		
		{
			--mode_4;		
			if(mode_4 < 0)
			{
				mode_4 = 4;
			}	
		}
	}
/***************************** ***********************************************************************/
	if(k6 == 0 && key_lock == 1){
		mode = HM;
	 }

}
 
	 


