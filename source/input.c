#include "input.h"
#include "login.h"
#include "bios.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:	input.c
  Author:       ��ī��
  Version:		1.0 
  Date:			18/11/05
  Description:  ���뺯��
  Function List: 
	input				�����ַ�
	clearbuffer			������̻�����
  History:      
	<author>  <time>   <version >   <desc>
	��ī��    18/11/05     1.0     build this moudle  
*************************************************/

void input(int x,int y,int num,int size,int color,int bkcolor,char *str,int signal)	//sizeΪ�Ŵ�����colorΪ������ɫ��strΪ������ַ�����signal������������
{
	char i, key;
	int x1 = x;
	str[0]='\0';
	clearbuffer();
	settextstyle(2,0,7*size);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	for (i = 0;i < num;i++)
	{
		while(kbhit()==0)			//��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
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
//��ռ��̻���������˵�����˺����������ı���������������Ƚ���,����ʹ�÷�ֹ���̻�����Ӱ��������߰������������Ч��
void clearbuffer(void)
{
	while(kbhit()!=0)	//������һ�����򷵻ط���ֵ�����򷵻�0
	{
		getch();
	}
	return;
}
