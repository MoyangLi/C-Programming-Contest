#include "detail.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:		detail.c
  Author:       	李墨洋
  Version:			1.0 
  Date:				18/11/05
  Description:  	股票财务界面函数
  Function List: 
	detail_draw		画股票财务界面
	detail_draw_bk	画财务背景菜单栏	
	stock_detail	显示特定股票财务
	judge_press		判断当前按键和模块
	find			查找某一只股票
	strcnmp			比较两个字符串的前n个字符  
  History:      
	<author>  <time>   <version >   <desc>
	李墨洋    18/11/05     1.0     build this moudle  
*************************************************/

void detail_draw(STOINFO *stoinfo)		//画股票财务界面
{
	FILE *fp;
	int i;
	char str[20];
	int color;
	detail_draw_bk();
	draw_slidder();
	move_slidder_2(stoinfo);
	if((fp=(fopen("data\\STOCK\\stocks.txt","rt")))==NULL)
	{

		printf("can not open the stock.txt in detail.c\n");
		getch();
		exit(1);
	}
	for(i=0;i<22;i++)
	{
		fscanf(fp,"%s",str);
		strcat(str,":");
		put_hz(120+i%2*250,40+i/2*40,str,BLUE,16,2);
	}
	for(i=0;i<22*(stoinfo->number-1);i++)
		fscanf(fp,"%s",str);
	for(i=0;i<22;i++)
	{
		fscanf(fp,"%s",str);
		if(i==2||i==9||i==10||i==21)
		{
			if(strcmp(str,"--")!=NULL)
				strcat(str,"%");
		}
		if(i==2)
		{
			if(atof(str)>0)
				color=RED;
			else if(atof(str)==0)
				color=WHITE;
			else if(atof(str)<0)
				color=LIGHTGREEN;
		}
		if(i>=2&&i<=14)
		{
			put_hz(198+i%2*250,40+i/2*40,str,color,16,2);
		}
		else
		{
			put_hz(198+i%2*250,40+i/2*40,str,LIGHTBLUE,16,2);
		}
	}
	fclose(fp);
}	
void stock_detail(INFO *info,STOINFO *stoinfo,int *mx_,int *my_,int *mbutn_)
{
	int mx,my,mbuttn;
	detail_draw(stoinfo);
	show_new(stoinfo);
	mouse_save(mx,my);			//防止出现补丁的情况
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(mx>=55&&mx<=69&&((my>=228&&my<=240)||(my>=447&&my<=459)))
		{
			setmouseshape(1);
		}
		else 
		{
			setmouseshape(2);
		}
		if(mouse_press(54,230,68,437,&mx,&my,&mbuttn))
		{
			move_slidder_1(&mx,&my,&mbuttn,stoinfo);
		}
		else if(mouse_press(55,228,69,240,&mx,&my,&mbuttn))
		{
			if(strcmp(stoinfo->stockpress_,"000001")!=0&&stoinfo->number_>1)
			{
				--(stoinfo->number_);
				move_slidder_2(stoinfo);
				show_new(stoinfo);
				continue;
			}
		}
		else if(mouse_press(55,447,69,459,&mx,&my,&mbuttn))
		{
			if(strcmp(stoinfo->stockpress_,"000550")!=0&&stoinfo->number_<187)
			{
				++(stoinfo->number_);
				move_slidder_2(stoinfo);
				show_new(stoinfo);
				continue;
			}
		}
		
		else if(mouse_press(0,227,52,459,&mx,&my,&mbuttn))
		{
			if(stoinfo->number_+(my-225)/47!=stoinfo->number)
			{
				stoinfo->number=stoinfo->number_+(my-225)/47;
				find_stockpress(stoinfo);
				detail_draw(stoinfo);
				show_new(stoinfo);
				continue;
			}
		}
		if(bioskey(1)!=0)
		{
			info->key.num=bioskey(0);
			if(info->key.num==F1||info->key.num==F2||info->key.num==F3
			  ||info->key.num==F4||info->key.num==F5||info->key.num==F6
			  ||info->key.num==F7||info->key.num==F8||info->key.num==F9||info->key.num==F10)
			{
				info->flag=2;
				break;
			}
		}
		judge_press(info,stoinfo,&mx,&my,&mbuttn);
		if(info->layout_last!=info->layout||info->flag==0)
		{
			*mx_=mx;
			*my_=my;
			*mbutn_=mbuttn;
			break;
		}
	}
}

void detail_draw_bk()
{
	cleardevice();
	menu_create();
	setfillstyle(1,WHITE);
	bar(0,25,74,45);
	bar(0,50,74,70);
	bar(0,75,74,95);
	bar(0,100,74,120);
	bar(0,125,74,145);
	bar(0,150,74,170);
	bar(0,175,74,195);
	bar(0,200,74,220);
	put_hz(2,27,"上证指数",BLACK,16,2);
	put_hz(2,52,"深成指数",BLACK,16,2);
	put_hz(2,77,"深证A股",BLACK,16,2);
	put_hz(2,102,"加入对比",BLACK,16,2);
	put_hz(2,127,"股票财务",BLACK,16,2);
	put_hz(2,152,"股票走势",BLACK,16,2);
	put_hz(7,177,"自选股",BLACK,16,6);
	put_hz(16,202,"交易",BLACK,16,10);
}
void judge_press(INFO *info,STOINFO *stoinfo,int *mx,int *my,int *mbuttn)
{
	if(mouse_press(0,25,74,45,mx,my,mbuttn))
	{
		strcpy(stoinfo->stockpress,"SZ");
		info->layout_last=info->layout;
		info->layout=3;
	}
	else if(mouse_press(0,50,74,70,mx,my,mbuttn))
	{
		strcpy(stoinfo->stockpress,"SC");
		info->layout_last=info->layout;
		info->layout=4;
	}
	else if(mouse_press(0,75,74,95,mx,my,mbuttn))
	{
		info->layout_last=info->layout;
		info->layout=2;
	}
	else if(mouse_press(0,100,74,120,mx,my,mbuttn))
	{
		info->layout_last=info->layout;
		info->layout=8;
	}
	else if(mouse_press(0,175,74,195,mx,my,mbuttn))
	{
		info->layout_last=info->layout;
		info->layout=5;
	}
	else if(mouse_press(0,150,74,170,mx,my,mbuttn))
	{
		info->layout_last=info->layout;
		info->layout=6;
	}
	else if(mouse_press(0,125,74,145,mx,my,mbuttn))
	{
		info->layout_last=info->layout;
		info->layout=11;
	}
	else if(mouse_press(0,200,74,220,mx,my,mbuttn))
	{
		info->layout_last=info->layout;
		info->layout=7;
	}
	else if(mouse_press(0,0,640,18,mx,my,mbuttn))
	{
		info->flag=0;
	}
}
void find(INFO *info,STOINFO *stoinfo)			//股票搜索
{
	int mx,my,mbuttn;
	FILE *fp;
	char code[5][7],name[5][9],str[7]="000000",str1[6],str2[6];
	char key;
	int number[6];
	int i=0,j=1,k=0;
	if((fp=fopen("data\\STOCK\\all.txt","rt"))==NULL)
	{
		printf("can not find the file all_stocks\n");
		getch();
		exit(1);
	}
	setfillstyle(1,WHITE);
	bar(0,225,74,438);
	setcolor(BLACK);
	rectangle(2,227,72,436);
	line(2,246,72,246);
	line(2,284,72,284);
	line(2,322,72,322);
	line(2,360,72,360);
	line(2,398,72,398);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	setcolor(BLACK);
	setmouseshape(1);
	mouse_save(mx,my);
	clearbuffer();
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(kbhit()!=0)		//k代表输入的字符数目,当前有字符正在输入
		{
			i=0;
			key=getch();
			if(key==Bksp)
			{
				if(k>0)
				{
					setfillstyle(1,WHITE);
					bar(k*9-4,228,5+k*9,245);
					--k;
					str[k] = '\0';
				}
				else
				{
					str[0]='\0';
				}
			}
			else if(k<6&&k!=Bksp)
			{
				setcolor(BLACK);
				str[k] = key;
				++k;
				str[k]= '\0';
				outtextxy(k*9-4,226,str+k-1);
			}
			clearbuffer();
			rewind(fp);
			for(j=1;j<=191;j++)			//j控制查找的股票范围
			{
				fscanf(fp,"%s %s %s %s",code[i],name[i],str1,str2);
				if(strcnmp(str,code[i],k)==0)
				{					
								//i代表符合目前查找条件的股票数目
					number[i]=j;
					i++;
					if(i>=5)
					{
						break;
					}
				}
			}
			setfillstyle(1,WHITE);
			bar(3,246,71,432);
			setcolor(BLACK);
			line(2,246,72,246);
			line(2,284,72,284);
			line(2,322,72,322);
			line(2,360,72,360);
			line(2,398,72,398);
			if(i==0)
			{
				put_hz(2,248,"没有符合",RED,16,1);
				put_hz(2,265,"条件股票",RED,16,1);
			}
			else
			{
				for(j=0;j<i;j++)
				{
					put_hz(3,248+38*j,name[j],BLACK,16,1);
					put_hz(4,265+38*j,code[j],BLACK,16,1);
				}
			}
		}
		if(mbuttn==1)					//如果目前有展示的股票数据被按下
		{
			if((my-246)/36>=0&&(my-246)/36<i)
			{
				stoinfo->number=number[(my-246)/36];
				info->layout=6;
				fclose(fp);
				break;
			}
		}
		if(strcmp(str,"")==0)	
		{
			mousehide(mx,my);
			fclose(fp);
			break;
		}
	}
	setfillstyle(1,BLACK);
	bar(0,225,74,438);
}
int strcnmp(char *str1,char *str2,int n)
{
	int flag=0;
	for(;n>0;n--)
	{
		if(str1[n-1]!=str2[n-1])
		{
			flag=1;
			break;
		}	
	}
	return flag;
}