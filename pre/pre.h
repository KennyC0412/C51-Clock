#ifndef _PRE_H_
#define _PRE_H_

#include <REGX52.H>
#define uchar unsigned char
#define uint unsigned int

sbit k1 = P2^0;		//按键定义
sbit k2 = P2^1;
sbit k3 = P2^2;
sbit k4 = P2^3;
sbit k5 = P2^4;
sbit k6 = P2^7;
sbit beep = P0^4;

 //共阳数码管笔段
extern uchar code segcode[14];		//8,9,-,空

extern uchar dispBuf[4],mode;

extern uchar hour,min,sec;		   //存放时分秒
extern uint year,mon,day;			//存放年月日

extern uint time,t;		//毫秒计时变量
extern uint count,count_ms;		//秒表时间变量
extern uchar clock[3];		//闹钟存储变量		元素0：是否开启闹钟（0：关  1：开）    元素1：小时变量    元素2：分钟变量 
extern uchar mode_4,mode_5,mode5_set;
extern bit point,mode_1,mode_3,key_lock;
extern bit mode4_lock,mode5_lock;
	  
#endif