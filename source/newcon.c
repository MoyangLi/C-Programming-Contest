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
Description��	���غ���

Function List��

��ʼ������
�������룬��굥������Ӧ
����ҳ������˳�
**********************************************************/
void control_main(INFO *info,STOINFO * stoinfo,Linkstock *Q1)      //����������
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
		   puthz12("�ο͵�¼",520,2,BLACK);
		   puthz12("��¼״̬",575,2,BLUE);
		   
	   }
	   else
	   {
		   puthz12("�ο͵�¼",520,2,BLUE);
		   puthz12("��¼״̬",575,2,BLACK);
		   
	   }                                 //״̬��ʾ
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
		}                                      //ҳ����£��չرհ��������Esc��������һ����
	   newmouse(&mx,&my,&mbtn);
	   setmouseshape(1);
	   if(cl>=500)
	   {
		   cl=0;
		  data_updata();         //��ÿ֧��Ʊ��Ӧ�Ķ�д���ļ���ȥ
		  stock_sort(stoinfo);   //��д�µĹ�Ʊ�б�
		  if(stoinfo->sort==0)
		  {
			renewqueue(Q1);
		  }
		  else
		  {
			enqueue(Q1);
		  }                      //���и�ֵ
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
		   info->key.num=bioskey(0);              //���ܼ��̼���ֵ
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
		   control_press(info,stoinfo,Q1,&mx,&my,&mbtn);      //Ӧ�������
	   }
	   
	  
	}

}

/**********************************************************
Copyright (C)
File name:		control.c
Author:
Description��	���̺���

Function List��


����F2����ת��������
����UP����Ʊ��������
����DOWM����Ʊ��������
����ESC���˳�����
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
		   else if(info->key.num==F8)			//F8��Ʊ�ԱȽ���
			{
				info->layout_last=info->layout;
				info->layout=8;

				decide_compare_draw(stoinfo);
				layout_change(info,stoinfo);
				*mbtn=-1;
			}
			else if(info->key.num==F9)			//F9����Ͷ�ʽ���
			{
				info->layout_last=info->layout;
				info->layout=9;

				decide_choose_draw_init();
				layout_change(info,stoinfo);
				*mbtn=-1;
			}
			else if(info->key.num==F10)        //F10��������
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
			else if(info->key.num==ESC)					//esc��
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
Description��	���������

Function List��

��ǰ�����������ʱ ���ò˵����ƺ�����Ӧ���

**********************************************************/
void control_press(INFO*info,STOINFO * stoinfo,Linkstock * Q,int *mx,int *my,int *mbtn)
{

	  if(info->layout!=1)
	  {
		control_menu(info,stoinfo,Q,mx,my,mbtn);
	  }
	  if(info->layout==8||info->layout==9)
	  {
		if(mouse_press(0,18,640,480,mx,my,mbtn))		//����Ͷ�ʽ��������
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
		if(mouse_press(0,18,640,480,mx,my,mbtn))		//�������������
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
Description��	�˵��������

Function List��



**********************************************************/
void control_menu(INFO * info,STOINFO * stoinfo,Linkstock*Q1,int *mx,int *my,int *mbtn)
{
   int t=1;
   if(mouse_press(0,0,42*7,16,mx,my,mbtn))                                                      //������˵���
	{
		if(info->menu_flag!=0)	       //����ʾ�����˵�״̬
		{
		   if(mouse_press(0,0,42,16,mx,my,mbtn))                //����˸��˵���һ��
			{
				changesubmenu(info,1,Q1,stoinfo);
				info->menu_flag=1;
			}
			else if(mouse_press(42,0,42*2,16,mx,my,mbtn))       //����˸��˵��ڶ���
			{
				changesubmenu(info,2,Q1,stoinfo);
				info->menu_flag=2;
			}
			else if(mouse_press(42*2,0,42*3,16,mx,my,mbtn))	//����˸��˵�������
			{
				info->menu_flag=3;
			}
			else if(mouse_press(42*3,0,42*4,16,mx,my,mbtn))	//����˸��˵�������
			{
				info->menu_flag=4;
			}
			else if(mouse_press(42*4,0,42*5,16,mx,my,mbtn))	//����˸��˵�������
			{

				changesubmenu(info,5,Q1,stoinfo);
				info->menu_flag=5;

			}
			else if(mouse_press(42*5,0,42*6,16,mx,my,mbtn))	//����˸��˵�������
			{
				//endsubmenu(info->menu_flag);
				info->menu_flag=0;

				info->layout_last=info->layout;
				info->layout=10;
				help_draw1(info);

			}
			else if(mouse_press(42*6,0,42*7,16,mx,my,mbtn))	//����˸��˵�������
			{
				//endsubmenu(info->menu_flag);
				info->menu_flag=0;

				 size_control() ;

			}
		}


		else if(info->menu_flag==0)		//δ��ʾ�����˵�״̬
		{
			if(mouse_press(0,0,42,16,mx,my,mbtn))				//��ʾ��һ�����˵���
			{
			  DisplaySubMenu(1);
			  info->menu_flag=1;
			}
			 else if(mouse_press(42,0,42*2,16,mx,my,mbtn))				//��ʾ�ڶ������˵���
			{
			  DisplaySubMenu(2);
			  info->menu_flag=2;
			}
			else if(mouse_press(42*2,0,42*3,16,mx,my,mbtn))	//����˸��˵�������
			{
				info->menu_flag=3;

			}
			else if(mouse_press(42*3,0,42*4,16,mx,my,mbtn))	//����˸��˵�������
			{
				info->menu_flag=4;

			}
			else if(mouse_press(42*4,0,42*5,16,mx,my,mbtn))	//����˸��˵�������
			{
				DisplaySubMenu(5);
				info->menu_flag=5;
			}
			else if(mouse_press(42*5,0,42*6,16,mx,my,mbtn))	//����˸��˵�������
			{
				info->menu_flag=0;

				info->layout_last=info->layout;
				info->layout=10;
				help_draw1();
			}
			else if(mouse_press(42*6,0,42*7,16,mx,my,mbtn))	//����˸��˵�������
			{
				//endsubmenu(info->menu_flag);
				info->menu_flag=0;

				 size_control();

			}

		}
	}                                                                                             //��������˵���
	if(info->menu_flag==1)		//��һ�����˵�����
	{
		if(mouse_press(0,17,70,17+15,mx,my,mbtn))				   //�������½����
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
		else if(mouse_press(0,17+15,70,17+15*2,mx,my,mbtn))		   //������˳���¼����
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
		else if(mouse_press(0,17+15*2,70,17+15*3,mx,my,mbtn))	   //������˳�����
		{
			//endsubmenu(info->menu_flag);
			info->menu_flag=0;
			*mx=0;
			t=0;
		}
		else if(mouse_press(0,17+15*3,640,480,mx,my,mbtn)||
						mouse_press(70,17,640,480,mx,my,mbtn))	//��������,�˳��˵�
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

	else if(info->menu_flag==2)		//�ڶ������˵�����
	{
		if(mouse_press(0+42,17,70+42,17+15,mx,my,mbtn))				  //����������Ʊ����
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
		else if(mouse_press(0+42,17+15,70+42,17+15*2,mx,my,mbtn))	  //�������ָ֤������
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
		else if(mouse_press(0+42,17+15*2,70+42,17+15*3,mx,my,mbtn)) //��������ָ������
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
		else if(mouse_press(0+42,17+15*3,70+42,17+15*4,mx,my,mbtn))	//�����ѡ�ɡ���
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
						mouse_press(0,17+15*5,640,480,mx,my,mbtn))	//��������,�˳��˵�
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
	else if(info->menu_flag==3)		//���������˵�����
	{
		info->layout_last=info->layout;
		info->layout=7;
		control_line(info,stoinfo,Q1,mx,my,mbtn);
		*mx=0;
	}

	else if(info->menu_flag==4)		//���ĸ����˵�����
	{
		info->layout_last=info->layout;
		info->layout=6;
		control_line(info,stoinfo,Q1,mx,my,mbtn);
		*mx=0;
	}
	else if(info->menu_flag==5)		//��������˵�����
	{
		if(mouse_press(0+42*4,17,70+42*4,17+15,mx,my,mbtn))				//����Ӳ˵���1����ť
		{
			//endsubmenu(info->menu_flag);
			*mx=0;
			info->menu_flag=0;         ///�������
			info->layout_last=info->layout;						   ///�������
			info->layout=8;
			//layout_change(info,stoinfo);
			decide_compare_draw(stoinfo);
		}
		else if(mouse_press(0+42*4,17+15,70+42*4,17+15*2,mx,my,mbtn))		//����Ӳ˵���2����ť
		{
			//endsubmenu(info->menu_flag);
			info->menu_flag=0;
			*mx=0;
			info->layout_last=info->layout;						   ///�������
			info->layout=9;
			//layout_change(info,stoinfo);
			decide_choose_draw_init();
		}
		else if(mouse_press(0,17,42*4,480,mx,my,mbtn)||
						mouse_press(70+42*4,17,640,480,mx,my,mbtn)||
						mouse_press(0,17+15*2,640,480,mx,my,mbtn))	//��������,�˳��˵�
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
	else if(info->menu_flag==6)		//���������˵�����
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
	puthz16("������ȷ��Ҫ�˳���ϵͳ��",185,146,16,1,1,BLACK);
	setfillstyle(1,LIGHTGRAY);
	bar(204,178,248,198);
	bar(314,178,358,198);
	puthz16("ȷ��",210,180,16,1,1,BLACK);
    puthz16("ȡ��",320,180,16,1,1,BLACK);
}