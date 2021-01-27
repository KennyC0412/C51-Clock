#include "pre.h"
#include "key.h"

enum {HM,DATE,SEC,COUNT,CLOCK,SET};

void key()	  //��������
{
	uint dat;
	if(k1 == 1 && k2 == 1 && k3 == 1 && k4 == 1 && k5 == 1 && k6 == 1) 
		key_lock = 1; //ʵ�������ı���	  ����ʵ�ֶ�ʱ����ֻ�㰴��һ�ΰ���
 /***********************************************************************************/
	if(k1 == 0 && key_lock == 1)		 //�� k1 ����������
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
				dat = clock[1]/10%10;		 //��������ʹʱ��Сʱ��ʮλ
				++dat;
				if(dat >= 3)   
					dat = 2;
				clock[1] = dat*10 + clock[1]%10;
			}
			else if(mode_4 == 2)	   //��������ʱ��Сʱ�ĸ�λ
			{
				dat = clock[1]%10;		 //��������ʹʱ��Сʱ�ĸ�λ
				clock[1] /= 10;
				++dat;
				if(dat >= 10)   
					dat = 0;
				clock[1] = clock[1]*10 + dat;				
			}
			else if(mode_4 == 3)	   //��������ʱ����ӵ�ʮλ
			{
				dat = clock[2]/10%10;		 //�������ӷ��ӵ�ʮλ
				++dat;
				if(dat >= 6)   
					dat = 0;
				clock[2] = dat*10 + clock[2]%10;
			}
			else if(mode_4 == 4)	   //��������ʱ����ӵĸ�λ
			{
				dat = clock[2]%10;		 //��������ʹʱ��Сʱ��ʮλ
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
			if(mode_5 == 0)		//��������ܵ�һλ�ϵ�ʱ��
			{
				if(mode5_set == 0)		//�������ǧλ
				{
					dat = year/1000%10;		//ȡ�����ǧλ��ֵ
					year = year - dat*1000;		 //��ȥ��ֵ��ʹǧλ��ֵΪ0
					++dat; 		
					if(dat >= 10)
						dat = 0;
					year = dat*1000 + year; 		 //����ǧλ����ֵ
				}
				else if(mode5_set == 1)	   //�����µ�ʮλ
				{
					dat = mon/10%10;		//ȡ���µ�ʮλ��ֵ
					mon = mon - dat*10;		 //��ȥ��ֵ��ʹʮλ��ֵΪ0
					++dat; 		
					if(dat >= 2)
						dat = 0;
					mon = dat*10 + mon; 		 //����ʮλ����ֵ	
				}
				else if(mode5_set == 2)	   //����ʱ��ʮλ
				{
					dat = hour/10%10;		//ȡ��ʱ��ʮλ��ֵ
					hour = hour - dat*10;		 //��ȥ��ֵ��ʹʮλ��ֵΪ0
					++dat; 	
					if(dat >= 3)
						dat = 0;
					hour = dat*10 + hour; 		 //����ʮλ����ֵ	
				}
			}
			/*************************************************************************************************************************/
			else if(mode_5 == 1)	//��������ܵڶ�λ�ϵ�ʱ��
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
			else if(mode_5 == 2)	//��������ܵ���λ�ϵ�ʱ��
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
			else if(mode_5 == 3)	//��������ܵ���λ�ϵ�ʱ��
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
	if(k2 == 0 && key_lock == 1)	  //�� k2 ����������
	{
		key_lock = 0;
		if(mode == COUNT)	   //��������ģʽ
			mode = HM;	   //�л���ʾʱ��ģʽ
		else if(mode == CLOCK)
		{
			if(mode_4 == 0)
			{
				if(clock[0] == 1)	//�����Ƿ�������
					clock[0] = 0;	
				else 
					clock[0] = 1;
			}
			else if(mode_4 == 1)
			{
				dat = clock[1]/10%10;		 //��������Сʱ��ʮλ
				--dat;
				if(dat >= 3)   
					dat = 2;
				clock[1] = dat*10 + clock[1]%10;
			}
			else if(mode_4 == 2)	   //��������ʱ��Сʱ�ĸ�λ
			{
				dat = clock[1]%10;		 //��������ʹʱ��Сʱ�ĸ�λ
				clock[1] /= 10;
				--dat;
				if(dat >= 10)  
					dat = 9;
				clock[1] = clock[1]*10 + dat;				
			}
			else if(mode_4 == 3)	   //��������ʱ����ӵ�ʮλ
			{
				dat = clock[2]/10%10;		 //�������ӷ��ӵ�ʮλ
				--dat;
				if(dat >= 6)   
					dat = 5;
				clock[2] = dat*10 + clock[2]%10;			
			}
			else if(mode_4 == 4)	   //��������ʱ����ӵĸ�λ
			{
				dat = clock[2]%10;		 //��������ʹʱ��Сʱ��ʮλ
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
			if(mode_5 == 0)		//��������ܵ�һλ�ϵ�ʱ��
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
			else if(mode_5 == 1)	//��������ܵڶ�λ�ϵ�ʱ��
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
			else if(mode_5 == 2)	//��������ܵ���λ�ϵ�ʱ��
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
			else if(mode_5 == 3)	//��������ܵ���λ�ϵ�ʱ��
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
			mode = COUNT;	   //�л������ģʽ

		count = 0;
		t = 0;mode_3=0;
	}
 /***************************** ***********************************************************************/
	if(k3 == 0 && key_lock == 1)	   //�� k3 ����������
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
			mode = CLOCK;	   //�л�����������
		}			   
			
	}
/***************************** ***********************************************************************/
	if(k4 == 0 && key_lock == 1)	//�� k4 ����������
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
 
	 


