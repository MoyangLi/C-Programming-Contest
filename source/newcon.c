#include "mouse.h"
#include"chinese.h"
#include<bios.h>
#include"newmenu.h"
#include"head.h"
#include"newcon.h"
#include"draw.h"
#include"mouse.h"
#include"queue.h"
#include"stock.h"
#include"tool.h"
#include"decide.h"
#include"login.h"
#include"KLINE.h"
#include"evaluate.h"
#include "codraw.h"
/**********************************************************
Copyright (C)
File name:		control.c
Author:
Description：	主控函数

Function List：

初始化队列
键盘输入，鼠标单击的相应
程序页面管理，退出
**********************************************************/
void control_main(INFO *info,STOINFO * stoinfo,Linkstock *Q1)      //控制主函数
{
	int mx,my,mbtn=-1;
	long int cl=0;
	time_t t;
	srand((unsigned int)(time(&t)));

	initqueue(Q1);
	enqueue(Q1);
	//start=clock();

	sign(info);
	info->layout=0;
	strcpy(stoinfo->stockpress,"000001");
	cleardevice();
	while(1)
	{
	  // pause=clock();
		cl++;
	   if(info->account_flag==0)
	   {
		   puthz12("游客登录",520,2,BLACK);
		   puthz12("登录状态",575,2,BLUE);
		   
	   }
	   else
	   {
		   puthz12("游客登录",520,2,BLUE);
		   puthz12("登录状态",575,2,BLACK);
		   
	   }                                 //状态显示
	   if(info->layout==0)
		{
			if(info->layout_last==2)
			{
				info->layout=2;
				info->layout_last=2;
				
				stock_listdraw(Q1,info);
				menu_create();
			    sort_menu();
			}
			else if(info->layout_last==0)
			{
				info->layout=2;
				info->layout_last=2;
				stock_listdraw(Q1,info);
			    menu_create();			    
			    sort_menu();
			}
			else if(info->layout_last==3)
			{
				info->layout=3;
				info->layout_last=3;
				control_line(info,stoinfo,Q1,&mx,&my,&mbtn);
			}
			else if(info->layout_last==4)
			{
				info->layout=4;
				info->layout_last=4;
				control_line(info,stoinfo,Q1,&mx,&my,&mbtn);
			}
			else if(info->layout==5)
			{
				info->layout=5;
				info->layout_last=5;
				control_line(info,stoinfo,Q1,&mx,&my,&mbtn);
			}
			else if(info->layout_last==6)
			{
				info->layout=6;
				info->layout_last=6;
				control_line(info,stoinfo,Q1,&mx,&my,&mbtn);
			}
			else if(info->layout==7)
			{
				info->layout=7;
				info->layout_last=7;
				control_line(info,stoinfo,Q1,&mx,&my,&mbtn);
			}
			else if(info->layout==11)
			{
				info->layout=11;
				info->layout_last=11;
				control_line(info,stoinfo,Q1,&mx,&my,&mbtn);
			}
			else if(info->layout_last==8)
			{
				info->layout=8;
				info->layout_last=8;
				
				decide_compare_draw(stoinfo);
			}
			else if(info->layout_last==9)
			{
				info->layout=9;
				info->layout_last=9;
				
				decide_choose_draw_init();
			}
			else if(info->layout_last==10)
			{
				info->layout=10;
				info->layout_last=10;
			}
		}                                      //页面更新（刚关闭帮助界面或按Esc键返回上一界面
	   newmouse(&mx,&my,&mbtn);
	   setmouseshape(1);
	   if(cl>=500)
	   {
		   cl=0;
		  data_updata();         //将每支股票相应改动写入文件中去
		  stock_sort(stoinfo);   //重写新的股票列表
		  if(stoinfo->sort==0)
		  {
			renewqueue(Q1);
		  }
		  else
		  {
			enqueue(Q1);
		  }                      //队列赋值
		  if(info->layout==2)
		  {
			layout_change(info,stoinfo);
			cleardevice();
			menu_create();
			sort_menu();
			stock_listdraw(Q1,info);			 
		  } 
	   }
	   if(bioskey(1)!=0)
	   {
		   info->key.num=bioskey(0);              //接受键盘键入值
	   }
	   
		if(info->key.num!=0)
		{
			control_key(info,stoinfo,Q1,&mx,&my,&mbtn);
		}
		
		if(info->flag!=2)
		{
			info->key.num=0;
		}
		else if(info->flag==2)
		{
			info->flag=1;
		}
	   if(mouse_press(0,0,640,480,&mx,&my,&mbtn))
	   {
		   control_press(info,stoinfo,Q1,&mx,&my,&mbtn);      //应对鼠标点击
	   }
	   
	  
	}

}

/**********************************************************
Copyright (C)
File name:		control.c
Author:
Description：	键盘函数

Function List：


按下F2键跳转至主界面
按下UP键股票队列上移
按下DOWM键股票界面下移
按下ESC键退出程序
**********************************************************/
void control_key(INFO *info,STOINFO * stoinfo,Linkstock*Q1,int *mx,int *my,int *mbtn)
{
	if(info->key.num!=0)
	{
		   if(info->key.num==F2)
		   {
			  info->layout_last=info->layout;
			  info->layout=2;
			  layout_change(info,stoinfo);
			  
			  cleardevice();
			  menu_create(); 
			  sort_menu();
			  stock_listdraw(Q1,info);			 
			  *mbtn=-1;
		   }
		   if(info->key.num==F3)
		   {
			  info->layout_last=info->layout;
			  info->layout=3;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			  *mbtn=-1;
		   }
		   if(info->key.num==F4)
		   {
			  info->layout_last=info->layout;
			  info->layout=4;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			  *mbtn=-1;
		   }
		   if(info->key.num==F5)
		   {
			  info->layout_last=info->layout;
			  info->layout=5;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			  *mbtn=-1;
		   }
		   if(info->key.num==F6)
		   {
			  info->layout_last=info->layout;
			  info->layout=6;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			  *mbtn=-1;
		   }
		   if(info->key.num==F7)
		   {
			  info->layout_last=info->layout;
			  info->layout=7;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			  *mbtn=-1;
		   }
		   else if(info->key.num==F8)			//F8股票对比界面
			{
				info->layout_last=info->layout;
				info->layout=8;

				decide_compare_draw(stoinfo);
				layout_change(info,stoinfo);
				*mbtn=-1;
			}
			else if(info->key.num==F9)			//F9量化投资界面
			{
				info->layout_last=info->layout;
				info->layout=9;

				decide_choose_draw_init();
				layout_change(info,stoinfo);
				*mbtn=-1;
			}
			else if(info->key.num==F10)        //F10帮助界面
			{
				info->layout_last=info->layout;
				info->layout=10;
				
				help_draw1(info);
				*mbtn=-1;
			}
		   else if(info->key.num==UP)
			{
					cleardevice();
					frontqueue(Q1);
                    menu_create(); 
					sort_menu();
					stock_listdraw(Q1,info);
					*mbtn=-1;					
			}
			else if(info->key.num==DOWN)
			{
					cleardevice();
					rearqueue(Q1);
					menu_create();
					sort_menu();
					stock_listdraw(Q1,info);
					*mbtn=-1;
					
			}
			else if(info->key.num==F1)
			{
				closegraph();
				free(Q1);
				exit(0);

			}
			else if(info->key.num==ESC)					//esc键
			{
			  info->layout=0;
			  layout_change(info,stoinfo);
			  *mbtn=-1;
			}

	}

}
/**********************************************************
Copyright (C)
File name:		control.c
Author:
Description：	鼠标点击函数

Function List：

当前界面非主界面时 调用菜单控制函数响应点击

**********************************************************/
void control_press(INFO*info,STOINFO * stoinfo,Linkstock * Q,int *mx,int *my,int *mbtn)
{

	  if(info->layout!=1)
	  {
		control_menu(info,stoinfo,Q,mx,my,mbtn);
	  }
	  if(info->layout==8||info->layout==9)
	  {
		if(mouse_press(0,18,640,480,mx,my,mbtn))		//量化投资界面鼠标点击
		{
			control_decide(info,stoinfo,mx,my,mbtn);
		}
	  }
	  else if(info->layout==2)
	  {
			control_stock(info,stoinfo,Q,mx,my,mbtn);
	  }
	  else if(info->layout==10)
	  {
		if(mouse_press(0,18,640,480,mx,my,mbtn))		//帮助界面鼠标点击
		{
			help_control(info,stoinfo,mx,my,mbtn);
			
		}
	  }
	  
	if(info->layout==6||info->layout==3||info->layout==4||info->layout==5||info->layout==11||info->layout==7)
	{
		control_line(info,stoinfo,Q,mx,my,mbtn);
	}
	
}
/**********************************************************
Copyright (C)
File name:		control.c
Author:			
Description：	菜单点击函数

Function List：



**********************************************************/
void control_menu(INFO * info,STOINFO * stoinfo,Linkstock*Q1,int *mx,int *my,int *mbtn)
{
   int t=1;
   if(mouse_press(0,0,42*7,16,mx,my,mbtn))                                                      //点击父菜单项
	{
		if(info->menu_flag!=0)	       //已显示下拉菜单状态
		{
		   if(mouse_press(0,0,42,16,mx,my,mbtn))                //点击了父菜单第一项
			{
				changesubmenu(info,1,Q1,stoinfo);
				info->menu_flag=1;
			}
			else if(mouse_press(42,0,42*2,16,mx,my,mbtn))       //点击了父菜单第二项
			{
				changesubmenu(info,2,Q1,stoinfo);
				info->menu_flag=2;
			}
			else if(mouse_press(42*2,0,42*3,16,mx,my,mbtn))	//点击了父菜单第三项
			{
				info->menu_flag=3;
			}
			else if(mouse_press(42*3,0,42*4,16,mx,my,mbtn))	//点击了父菜单第四项
			{
				info->menu_flag=4;
			}
			else if(mouse_press(42*4,0,42*5,16,mx,my,mbtn))	//点击了父菜单第五项
			{

				changesubmenu(info,5,Q1,stoinfo);
				info->menu_flag=5;

			}
			else if(mouse_press(42*5,0,42*6,16,mx,my,mbtn))	//点击了父菜单第六项
			{
				//endsubmenu(info->menu_flag);
				info->menu_flag=0;

				info->layout_last=info->layout;
				info->layout=10;
				help_draw1(info);

			}
			else if(mouse_press(42*6,0,42*7,16,mx,my,mbtn))	//点击了父菜单第六项
			{
				//endsubmenu(info->menu_flag);
				info->menu_flag=0;

				 size_control() ;

			}
		}


		else if(info->menu_flag==0)		//未显示下拉菜单状态
		{
			if(mouse_press(0,0,42,16,mx,my,mbtn))				//显示第一个父菜单项
			{
			  DisplaySubMenu(1);
			  info->menu_flag=1;
			}
			 else if(mouse_press(42,0,42*2,16,mx,my,mbtn))				//显示第二个父菜单项
			{
			  DisplaySubMenu(2);
			  info->menu_flag=2;
			}
			else if(mouse_press(42*2,0,42*3,16,mx,my,mbtn))	//点击了父菜单第三项
			{
				info->menu_flag=3;

			}
			else if(mouse_press(42*3,0,42*4,16,mx,my,mbtn))	//点击了父菜单第四项
			{
				info->menu_flag=4;

			}
			else if(mouse_press(42*4,0,42*5,16,mx,my,mbtn))	//点击了父菜单第五项
			{
				DisplaySubMenu(5);
				info->menu_flag=5;
			}
			else if(mouse_press(42*5,0,42*6,16,mx,my,mbtn))	//点击了父菜单第六项
			{
				info->menu_flag=0;

				info->layout_last=info->layout;
				info->layout=10;
				help_draw1();
			}
			else if(mouse_press(42*6,0,42*7,16,mx,my,mbtn))	//点击了父菜单第六项
			{
				//endsubmenu(info->menu_flag);
				info->menu_flag=0;

				 size_control();

			}

		}
	}                                                                                             //点击下拉菜单项
	if(info->menu_flag==1)		//第一个父菜单项下
	{
		if(mouse_press(0,17,70,17+15,mx,my,mbtn))				   //点击”登陆“键
		{
			//endsubmenu(info->menu_flag);
			if(info->account_flag==0)
			{
				cleardevice();
				info->layout_last=info->layout;
				sign(info);
				cleardevice();
				if(info->layout==2)
				{
					stock_listdraw(Q1,info);
					menu_create();
					sort_menu();
				}
				else if(info->layout==0)
				{
					stock_listdraw(Q1,info);
					menu_create();
					sort_menu();
				}

				else if(info->layout==8)
				{
					decide_compare_draw(stoinfo);
				}
				else if(info->layout==9)
				{
					decide_choose_draw_init();
				}
				else if(info->layout==10)
				{
					help_draw1();
				}
			}
			info->menu_flag=0;
			*mx=0;
		}
		else if(mouse_press(0,17+15,70,17+15*2,mx,my,mbtn))		   //点击”退出登录“键
		{
			//endsubmenu(info->menu_flag);
			info->account_flag=0;
			if(info->layout==5||info->layout==7)
			{
				info->layout=6;
			}
			info->menu_flag=0;
			*mx=0;

		}
		else if(mouse_press(0,17+15*2,70,17+15*3,mx,my,mbtn))	   //点击”退出“键
		{
			//endsubmenu(info->menu_flag);
			info->menu_flag=0;
			*mx=0;
			t=0;
		}
		else if(mouse_press(0,17+15*3,640,480,mx,my,mbtn)||
						mouse_press(70,17,640,480,mx,my,mbtn))	//点击任意别处,退出菜单
		{

			//endsubmenu(info->menu_flag);
			if(info->layout==2)
			{
				stock_listdraw(Q1,info);
			}
			else if(info->layout==8)
			{
				decide_compare_draw(stoinfo);
			}
			else if(info->layout==9)
			{
				decide_choose_draw_init();
			}
			info->menu_flag=0;
			*mx=0;
		}

	}

	else if(info->menu_flag==2)		//第二个父菜单项下
	{
		if(mouse_press(0+42,17,70+42,17+15,mx,my,mbtn))				  //点击”沪深股票“键
		{
			//endsubmenu(info->menu_flag);
			if(info->layout!=2)
			{
			  info->layout_last=info->layout;
			  info->layout=2;
			  cleardevice();
			  menu_create();
			  sort_menu();
			  stock_listdraw(Q1,info);
			}
			else
				stock_listdraw(Q1,info);
			info->menu_flag=0;
			*mx=0;
		}
		else if(mouse_press(0+42,17+15,70+42,17+15*2,mx,my,mbtn))	  //点击”上证指数“键
		{
			//endsubmenu(info->menu_flag);
			if(info->layout!=3)
			{
			  info->layout_last=info->layout;
			  info->layout=3;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			}
			info->menu_flag=0;
			*mx=0;
		}
		else if(mouse_press(0+42,17+15*2,70+42,17+15*3,mx,my,mbtn)) //点击”深成指数“键
		{

			*mx=0;
			//endsubmenu(info->menu_flag);
			if(info->layout!=4)
			{
			  info->layout_last=info->layout;
			  info->layout=4;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			}
			info->menu_flag=0;
		}
		else if(mouse_press(0+42,17+15*3,70+42,17+15*4,mx,my,mbtn))	//点击自选股”键
		{
			*mx=0;
			//endsubmenu(info->menu_flag);
			if(info->layout!=5)
			{
			  info->layout_last=info->layout;
			  info->layout=5;
			  control_line(info,stoinfo,Q1,mx,my,mbtn);
			}
			info->menu_flag=0;
		}
		else if(mouse_press(0,17,42,480,mx,my,mbtn)||
						mouse_press(70+42,17,640,480,mx,my,mbtn)||
						mouse_press(0,17+15*5,640,480,mx,my,mbtn))	//点击任意别处,退出菜单
		{

			//endsubmenu(info->menu_flag);
			if(info->layout==2)
			{
				stock_listdraw(Q1,info);
			}
			else if(info->layout==8)
			{
				decide_compare_draw(stoinfo);
			}
			else if(info->layout==9)
			{
				decide_choose_draw_init();
			}
			info->menu_flag=0;
			*mx=0;
		}


	}
	else if(info->menu_flag==3)		//第三个父菜单项下
	{
		info->layout_last=info->layout;
		info->layout=7;
		control_line(info,stoinfo,Q1,mx,my,mbtn);
		*mx=0;
	}

	else if(info->menu_flag==4)		//第四个父菜单项下
	{
		info->layout_last=info->layout;
		info->layout=6;
		control_line(info,stoinfo,Q1,mx,my,mbtn);
		*mx=0;
	}
	else if(info->menu_flag==5)		//第五个父菜单项下
	{
		if(mouse_press(0+42*4,17,70+42*4,17+15,mx,my,mbtn))				//点击子菜单第1个按钮
		{
			//endsubmenu(info->menu_flag);
			*mx=0;
			info->menu_flag=0;         ///留待添加
			info->layout_last=info->layout;						   ///留待添加
			info->layout=8;
			//layout_change(info,stoinfo);
			decide_compare_draw(stoinfo);
		}
		else if(mouse_press(0+42*4,17+15,70+42*4,17+15*2,mx,my,mbtn))		//点击子菜单第2个按钮
		{
			//endsubmenu(info->menu_flag);
			info->menu_flag=0;
			*mx=0;
			info->layout_last=info->layout;						   ///留待添加
			info->layout=9;
			//layout_change(info,stoinfo);
			decide_choose_draw_init();
		}
		else if(mouse_press(0,17,42*4,480,mx,my,mbtn)||
						mouse_press(70+42*4,17,640,480,mx,my,mbtn)||
						mouse_press(0,17+15*2,640,480,mx,my,mbtn))	//点击任意别处,退出菜单
		{
			if(info->layout==2)
	        {
				stock_listdraw(Q1,info);
			}	
			else if(info->layout==8)
			{
				decide_compare_draw(stoinfo);
			}
			else if(info->layout==9)
			{
				decide_choose_draw_init();
			}
			info->menu_flag=0;
			*mx=0;
		}

	}
	else if(info->menu_flag==6)		//第六个父菜单项下
	{
		*mx=0;
	}

	if(t==0)
	{
		//save_picture(160,120,405,225);
		draw_quit();
		while(1)
		{
			newmouse(mx,my,mbtn);
			if(mouse_press(204,178,248,198,mx,my,mbtn))
			{
				evaluate_control(mx,my,mbtn);
				closegraph();
				free(Q1);
				exit(0);
				*mx=0;
			}
			else if(mouse_press(314,178,358,198,mx,my,mbtn)||
						mouse_press(0,0,160,480,mx,my,mbtn)||
						mouse_press(405,0,640,480,mx,my,mbtn)||
						mouse_press(160,0,405,120,mx,my,mbtn)||
						mouse_press(160,225,405,640,mx,my,mbtn))
			{
				//put_picture(160,120,405,225);
				if(info->layout==2)
				{
					stock_listdraw(Q1,info);
				}
				else if(info->layout==8)
				{
					decide_compare_draw(stoinfo);
				}
				else if(info->layout==9)
				{
					decide_choose_draw_init();
				}	
				*mx=0;
				break;
			}
			
			//cleardevice();
		}
		t=1; 
	}	       
}

void draw_quit()
{
	setfillstyle(1,RED);
	bar(160,120,405,225);
	setfillstyle(1,WHITE);
	bar(170,130,395,215);
	puthz16("请问您确定要退出本系统吗",185,146,16,1,1,BLACK);
	setfillstyle(1,LIGHTGRAY);
	bar(204,178,248,198);
	bar(314,178,358,198);
	puthz16("确定",210,180,16,1,1,BLACK);
    puthz16("取消",320,180,16,1,1,BLACK);
}