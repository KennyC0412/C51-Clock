#include <REGX52.H>
#define uchar unsigned char
#define uint unsigned int

#include "pre.h"


 //共阳数码管笔段
uchar code segcode[14]={0xc0,0xf9,0xa4,0xb0,		//0,1,2,3	
						0x99,0x92,0x82,0xf8,	    //4,5,6,7
						0x80,0x90,0xbf,0xff,			//8,9,-,空
						0xc6,0xc7};			//C,L

uchar dispBuf[4];//mode;

enum MODE{HM,DATE,SEC,COUNT,CLOCK,SET}mode;	//功能对应时分、日期、秒显示、计时、设置时间

uchar hour=12,min=12,sec=0;		   //存放时分秒
uint year=2021,mon=1,day=8;			//存放年月日

uint time,t;//毫秒计时变量
uint count,count_ms;//秒表时间变量
uchar clock[3];//元素0：是否开启闹钟（0：关  1：开）    元素1：小时变量    元素2：分钟变量 
uchar mode_4,mode_5,mode5_set;

bit point; //小数点控制位
bit mode_1;//控制日期显示年还是月日
bit mode_3;//控制计时开始和暂停
bit key_lock; //键盘标志
bit mode4_lock,mode5_lock;	//闹钟和设置时间闪烁控制位
