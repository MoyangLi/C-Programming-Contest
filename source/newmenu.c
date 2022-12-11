#include"chinese.h"
#include<bios.h>
#include"head.h"
#include"newcon.h"
#include"draw.h"
#include"mouse.h"
#include"queue.h"
#include"tool.h"


void DisplaySubMenu(int ord)	//开始下下拉菜单
{	
	draw_submenu(ord);	
}

void changesubmenu(INFO *info,int neww,Linkstock *Q1,STOINFO *stoinfo)		//改变子菜�?
{
	  if(info->layout==2)
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
     
	draw_submenu(neww);
}

void endsubmenu(int ord)		//结束子菜
{
	//put_pic_pixel(ord);
}



void save_pic_pixel(int ord)	//存贮被覆盖的图像
{
	int iround,jround;
	int left,top,right,bottom;
	FILE * fp;
	char address[30]="data\\other\\menu\\";
	int pixel;
	
	switch(ord)
	{
		case 1:	
		{
			strcat(address,"menu1.son");
			left=0;
			right=70+left;
			top=17;
			bottom=15*3+top;
			break;
		}
			
						
		case 2:	
		{
			strcat(address,"menu2.son");
			left=42;
			right=70+left;
			top=17;
			bottom=15*4+top;
			break;
		}
		case 3:	
		{
		/*	strcat(address,"menu3.son");
			left=42*2;
			right=70+left;
			top=17;
			bottom=15*2+top;
			break;*/
		}
		case 4:	
		{

			break;
		}
		case 5:	
		{
     		strcat(address,"menu5.son");
			left=42*4;
			right=70+left;
			top=17;
			bottom=15*2+top;		
			break;
		}
		case 6:	
		{
			break;
		}
		
	}	

	if((fp=fopen(address,"wb"))==NULL)
	{
		printf("ERROR OPENING menu.\n");
		getch();
	}
	
	for(iround=top;iround<=bottom+1;iround++)
	{
		for(jround=left;jround<=right;jround++)
		{
			pixel=getpixel(jround,iround);
			fwrite(&pixel,sizeof(int),1,fp);
		}
	}
	
	fclose(fp);
	address[16]='\0';
}


void put_pic_pixel(int ord)
{
	int iround,jround;
	int left,top,right,bottom;
	FILE * fp;
	char address[30]="data\\other\\menu\\";
	int pixel;
	
	switch(ord)
	{
		case 1:	
		{
			strcat(address,"menu1.son");
			left=0;
			right=70+left;
			top=17;
			bottom=15*3+top;
			break;
		}
			
						
		case 2:	
		{
			strcat(address,"menu2.son");
			left=42;
			right=70+left;
			top=17;
			bottom=15*4+top;
			break;
		}
		case 3:	
		{
			break;
		}
		case 4:	
		{
			break;
		}
		case 5:	
		{
      		strcat(address,"menu5.son");
			left=42*4;
			right=70+left;
			top=17;
			bottom=15*2+top;		
			break;
		}
		case 6:	
		{
			break;
		}
		
	}	

	if((fp=fopen(address,"rb"))==NULL)
	{
	//	printf("ERROR OPENING menu.\n");
	//	getch();
	}
	
	for(iround=top;iround<=bottom+1;iround++)
	{
		for(jround=left;jround<=right;jround++)
		{
			fread(&pixel,sizeof(int),1,fp);
			putpixel(jround,iround,pixel);
		}
	}
	
	fclose(fp);
	address[16]='\0';
}


void draw_submenu(int ord)
{
	switch(ord)
	{
		case 1:	
		{
			setcolor(BLUE);
			setfillstyle(SOLID_FILL,WHITE);
			bar3d(0,17,70,17+1+15*3,0,0);
			puthz12("��½",2,17,BLACK);
			puthz12("�˳���¼",2,17+15,BLACK);
			puthz12("�˳�",2,17+15*2,BLACK);
			break;
		}				
		case 2:	
		{
			setcolor(BLUE);
			setfillstyle(SOLID_FILL,WHITE);
			bar3d(42,17,42+70,17+1+15*4,0,0);
			setcolor(WHITE);
			puthz12("��֤A��",2+42,17,BLACK);
			puthz12("��ָ֤��",2+42,17+15,BLACK);
			puthz12("���ָ��",2+42,17+15*2,BLACK);
			puthz12("��ѡ��",2+42,17+15*3,BLACK);
			break;
		}
		case 3:	
		{
			break;
		}
		case 4:	
		{
			break;
		}
		case 5:	
		{	
            setcolor(BLUE);
			setfillstyle(SOLID_FILL,WHITE);
			bar3d(42*4,17,42*4+70,17+1+15*2,0,0);
			puthz12("��Ʊ�Ա�",2+42*4,17,BLACK);
			puthz12("����ѡ��",2+42*4,17+15,BLACK);
			break;
		}
		case 6:	
		{
            
			break;
		}
		
   }
}



void menu_create(void)
{
	setcolor(BLUE);
	setfillstyle(1,LIGHTGRAY);
	bar(0,0,640,16);
	setcolor(RED);
	puthz12("ϵͳ",2+5,1,BLACK);
	setcolor(BLUE);
	line(42,1,42,16);
	puthz12("����",2+42+5,1,BLACK);
	setcolor(BLUE);
	line(42*2,1,42*2,16);
	puthz12("����",2+42*2+5,1,BLACK);
	setcolor(BLUE);
	line(42*3,1,42*3,16);
	puthz12("����",2+42*3+5,1,BLACK);
	setcolor(BLUE);
	line(42*4,1,42*4,16);
	puthz12("����",2+42*4+5,1,BLACK);
	setcolor(BLUE);
	line(42*5,1,42*5,16);
	puthz12("����",2+42*5+5,1,BLACK);
	puthz12("��Ʊɸѡ��",2+42*5+47,1,BLACK);
	setcolor(BLUE);
	line(42*6,1,42*6,16);
	setcolor(BLACK);
    line(570,0,570,16);
}

void sort_menu(void)
{
	setcolor(RED);
	rectangle(0,0,getmaxx(),getmaxy());
	setcolor(BLUE);
	setfillstyle(1,LIGHTGRAY);
	bar(0,480-18,640,480);
	setcolor(RED);
	puthz12("����������",2,480-17,BLACK);
	setcolor(BLUE);
	line(80,480-18,80,480);
	puthz12("���ּ�����",2+2+80,480-17,BLACK);
	setcolor(BLUE);
	line(80*2,480-18,80*2,480);
	puthz12("���ǵ�������",2+80*2,480-17,BLACK);
	setcolor(BLUE);
	line(80*3,480-18,80*3,480);
	puthz12("������������",2+80*3,480-17,BLACK);
	setcolor(BLUE);
	line(80*4,480-18,80*4,480);
	puthz12("���������",2+2+80*4,480-17,BLACK);
	setcolor(BLUE);
	line(80*5,480-18,80*5,480);

}