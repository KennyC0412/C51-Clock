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
		display();	//���ݵ�ǰģʽ����dispBuf�����ɺ�������������ʾ

		for(i=0;i<4;i++)	//��ʾ����ܳ���
			dispSet(dispBuf[i],~(0x01 << i));	 //dispBuf��������ĸ������ܵ���ʾ��С���������
					
		if(mode != SET)  //������ʱ�书�ܣ�����������Ҫ����ʱ�����
			dealTime();		  
				   
		key();	//��ⰴ��

		if(clock[0] == 1 && hour == clock[1] && min == clock[2])//����ʱ���Ƿ���																				
			beep = 0;	 //��������
		else 
			beep = 1;	//����������
	}
}	

