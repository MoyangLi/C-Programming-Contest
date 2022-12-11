#include "input.h"
#include "login.h"
#include "bios.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:	input.c
  Author:       李墨洋
  Version:		1.0 
  Date:			18/11/05
  Description:  输入函数
  Function List: 
	input				输入字符
	clearbuffer			清除键盘缓存区
  History:      
	<author>  <time>   <version >   <desc>
	李墨洋    18/11/05     1.0     build this moudle  
*************************************************/

void input(int x,int y,int num,int size,int color,int bkcolor,char *str,int signal)	//size为放大倍数，color为字体颜色，str为输入的字符串，signal代表阴文阳文
{
	char i, key;
	int x1 = x;
	str[0]='\0';
	clearbuffer();
	settextstyle(2,0,7*size);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	for (i = 0;i < num;i++)
	{
		while(kbhit()==0)			//检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
		{
			setcolor(BLACK);
			line(x1-1,y+4,x1-1,y+20);
			delay(200);
			setcolor(bkcolor);
			line(x1-1,y+4,x1-1,y+20);
			delay(200);
		}
		key = getch();
		if (key == Bksp)
		{
			if(x1>x)
			{
				setcolor(bkcolor);
				x1-=size*8+4;
				bar(x1, y+2, x1+size*8+4, y + 20*size+2);
				setcolor(color);
				str[--i] = '\0';
				--i;
			}
			else  --i;

		}
		else if (key == Enter)
		{
			break;
		}
		else
		{
			setcolor(color);
			str[i] = key;
			str[i + 1]= '\0';
			if (signal == 0)
			{
				outtextxy(x1, y, str + i);
			}
			else if (signal == 1)
			{
				outtextxy(x1, y, "*");
			}

			x1+=size*8+4;
		}
	}
}
//清空键盘缓冲区函数说明：此函数在输入文本，按任意键继续等界面,反复使用防止键盘缓冲区影响输入或者按任意键继续的效果
void clearbuffer(void)
{
	while(kbhit()!=0)	//若按下一个键则返回非零值，否则返回0
	{
		getch();
	}
	return;
}
