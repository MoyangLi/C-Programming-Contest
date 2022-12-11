#include "dos.h"
#include "graphics.h"
#include "stdio.h"
#include "mouse.h"
union REGS regs;
int arrowMousePixSave[16][10];	  //用于保存鼠标即将覆盖的区域
int JtMouseDraw[16][10]={	 //设计鼠标的形状,其中1:表示鼠标的边界,2:表示鼠标边界所包围的区域,3:表示鼠标以外的区域
	{1,1,3,3,3,3,3,3,3,3},
	{1,2,1,3,3,3,3,3,3,3},
	{1,2,2,1,3,3,3,3,3,3},
	{1,2,2,2,1,3,3,3,3,3},
	{1,2,2,2,2,1,3,3,3,3},
	{1,2,2,2,2,2,1,3,3,3},
	{1,2,2,2,2,2,2,1,3,3},
	{1,2,2,2,2,2,2,2,1,3},
	{1,2,2,2,2,2,2,2,2,1},
	{1,2,2,2,2,2,2,1,3,3},
	{1,2,2,2,2,2,1,3,3,3},
	{1,2,1,3,1,2,2,1,3,3},
	{1,1,3,3,1,2,2,1,3,3},
	{3,3,3,3,3,1,2,2,1,3},
	{3,3,3,3,3,1,2,2,1,3},
	{3,3,3,3,3,3,1,2,2,1}  };
int HandMouseDraw[16][10]={	   //设计鼠标的形状,其中1:表示鼠标的边界,2:表示鼠标边界所包围的区域,3:表示鼠标以外的区域
	{3,3,1,1,1,3,3,3,3,3},
	{3,3,1,2,1,3,3,3,3,3},
	{3,3,1,2,1,3,3,3,3,3},
	{3,3,1,2,1,3,1,3,3,3},
	{3,3,1,2,1,1,1,1,1,3},
	{1,1,1,2,2,2,1,2,1,1},
	{1,2,1,2,2,2,2,2,1,1},
	{1,2,2,2,2,2,2,2,2,1},
	{1,1,2,2,2,2,2,2,2,1},
	{3,3,1,2,2,2,2,2,2,1},
	{3,3,1,2,2,2,2,2,1,1},
	{3,3,1,2,2,2,2,2,1,3},
	{3,3,3,1,2,2,2,2,1,3},
	{3,3,3,1,2,2,2,1,1,3},
	{3,3,3,1,2,2,1,3,3,3},
	{3,3,3,1,1,1,1,3,3,3} };
int MaskMouseDraw[16][10]={
	{2,2,2,2,2,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{3,3,2,3,3,3,3,3,3,3},
	{2,2,2,2,2,3,3,3,3,3}
};
int CrossMouseDraw[16][10]={
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{2,2,2,2,2,2,2,2,2,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,2,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3},
};
int (*arrowMouseDraw)[10]=JtMouseDraw;

void getMousebk(int x, int y)//存储鼠标背后的图案
{
	int i, j;
	for(i=0;i<10;i++)
		for(j=0;j<16;j++)
			arrowMousePixSave[i][j] = getpixel(x + i, y + j);
}

int init(int xmi, int xma, int ymi, int yma)  //鼠标器初始化操作
{
	int retcode;
	regs.x.ax = 0;
	int86(51, &regs, &regs);
	retcode = regs.x.ax;
	if (retcode == 0)
		return 0;
	regs.x.ax = 7;
	regs.x.cx = xmi;
	regs.x.dx = xma;
	int86(51, &regs, &regs);
	regs.x.ax = 8;
	regs.x.cx = ymi;
	regs.x.dx = yma;
	int86(51, &regs, &regs);
	return retcode;
}
void mouseInit(int *mx,int *my, int *mbutt)
{
	if (init(0, 639, 0, 479) == 0)
	{
		closegraph();
		printf("Mouse or Mouse Driver Absent,Please Install");
		delay(5000);
		exit(1);
	}

	*mx = 3;
	*my = 460;
	*mbutt = 0;

	getMousebk(*mx, *my);
	cursor(*mx, *my);
}

void setmouseshape(int i)
{
   if(i==1)
   {
		arrowMouseDraw=JtMouseDraw;
	}
   else if(i==2)
	{
		arrowMouseDraw=HandMouseDraw;
	}
   else if(i==0)
   {
	   arrowMouseDraw=MaskMouseDraw;	//键入框
   }
   else
	   arrowMouseDraw=CrossMouseDraw;				//十字鼠标
}

void cursor(int x,int y)                 /*画鼠标你怕不怕*/
{
	int i,j;
	int color;
	
		for(i=0;i<16;i++)
			for(j=0;j<10;j++)
			{     
				arrowMousePixSave[i][j]=getpixel(x+j,y+i);
				if(arrowMouseDraw[i][j]==1)
					putpixel(x+j,y+i,0);
				else if(arrowMouseDraw[i][j]==2)    // 画鼠标
					putpixel(x+j,y+i,15);
			}
}

void mouse_draw(int x,int y)		// 画鼠标
{
	int i,j;
	
		for(i=0;i<16;i++)
			for(j=0;j<10;j++)
			{
				if(arrowMouseDraw[i][j]==1)
					putpixel(x+j,y+i,0);
				else if(arrowMouseDraw[i][j]==2)
					putpixel(x+j,y+i,15);
			}
}

void mouse_save(int x,int y)		//保存鼠标
{
	int i,j;
	
		for(i=0;i<16;i++)
			for(j=0;j<10;j++)
			{
				arrowMousePixSave[i][j]=getpixel(x+j,y+i);
			}
}

void mouse_put(int x,int y)			//覆盖原来的鼠标
{
	int i,j;
		for(i=0;i<16;i++)
			for(j=0;j<10;j++)
			{
				putpixel(x+j,y+i,arrowMousePixSave[i][j]);
			}
}

/***调用系统中断得到热键位置和鼠标状态***/
int mouse_read(int *mx, int *my,int *mbutt) //调用这个函数的作用是改变后面调用函数时定义的mosex,mosey,mousekey值
{
	int xnew;
	int ynew;
	*mbutt = 0;
									//如果鼠标位置或按键状态没有改变，就不会改变定义的值，出就是在函数里定义的mosex,mosey,mousekey值
	regs.x.ax = 3;					//调用功能3，读鼠标的位置和状态
	int86(51, &regs, &regs);
	xnew = regs.x.cx;
	ynew = regs.x.dx;
	*mbutt = regs.x.bx;				//鼠标返回当前的状态，检测是否被按下
	*mx = xnew; /*更新后的热键位置*/																			  
	*my = ynew;																				  
	return 0;													   
}


/****newmouse的作用是在得到的新热键处画鼠标并将原来的鼠标异或掉***/	
void newmouse(int *mx, int*my, int*mbutt)						   
{																								  
	int xold = *mx;																				  
	int yold = *my;	

	int xm;																						  
	int ym;	  
	delay(10);	
	
	if((*mbutt==1)||(*mbutt==-1))
	{
		mouse_save(xold, yold);	//保存旧鼠标底色
		mouse_draw(xold,yold);	//画旧鼠标
	}
	
	mouse_read(&xm, &ym, mbutt); /*调用newmouse函数得到新的热键位置和鼠标按钮状态*/
	
	if(xm==xold&&ym==yold&&(*mbutt)==0)	//鼠标没有操作
	{
		mouse_draw(xm,ym);
	}
	else if((*mbutt)==0)     //鼠标未按下，则鼠标位置发生了变化
	{
		mouse_put(xold,yold);	//覆盖原鼠标
		mouse_save(xm, ym);	//保存新鼠标底色
		cursor(xm,ym);	//画新鼠标
		*mx = xm;																					  
		*my = ym;
	}
	else if((*mbutt)==1)     //鼠标已经按下
	{
		delay(150);
		mouse_put(xold,yold);//覆盖原鼠标
		*mx = xm;																					  
		*my = ym;
		
	}	
}

void mousehide(int x,int y)
{
	int i,j,color;
		for(i=0;i<16;i++)
			for(j=0;j<10;j++)
			{
				putpixel(x+j,y+i,arrowMousePixSave[i][j]);// 还原原背景
			}
}

int mouse_press(int x1,int y1,int x2,int y2,int *mx,int *my,int *mbutt)
{
	if(* mx>x1 && *mx<x2 && *my>y1 && *my<y2 && (*mbutt==1))
		return 1;
	else
		return 0;
	
}

int mouse_above(int x1,int y1,int x2,int y2,int *mx,int *my,int *mbutt)
{
	if(* mx>x1 && *mx<x2 && *my>y1 && *my<y2)
		return 1;
	else
		return 0;
	
}