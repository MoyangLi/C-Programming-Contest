#include "stdio.h"
#include "dos.h"
#include "conio.h"

#include "codraw.h"


void size_control()
{
	int mx,my,mbuttn=-1;
	int i;				//循环语句使用
	int count=0;			//用于记录条件个数
	MX mine;			//记录每个滑动条两边的位置,条件，条件要求
	SIZE *Q=NULL;

	for(i=0;i<3;i++)
	{
		mine.a[i]=0;
		strcpy(mine.lowx[i],"398");
		strcpy(mine.highx[i],"552");			//将每个拖动条滑块位置初始化为两边
	}

	cleardevice();
	draw_();										//初始化界面
	mouseInit(&mx,&my,&mbuttn);

	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		delay(25);

		if(mouse_press(atoi(mine.lowx[0])-1,35,atoi(mine.lowx[0])+2,45,&mx,&my,&mbuttn)&&count>=1)
		{
			move_slidder_11(&mx,&my,&mbuttn,1,&mine);
		}
		else if(mouse_press(atoi(mine.highx[0])-1,35,atoi(mine.highx[0])+2,45,&mx,&my,&mbuttn)&&count>=1)
		{
			move_slidder_11(&mx,&my,&mbuttn,2,&mine);
		}
		
		else if(mouse_press(atoi(mine.lowx[1])-1,35+25,atoi(mine.lowx[1])+2,45+25,&mx,&my,&mbuttn)&&count>=2)
		{
			move_slidder_21(&mx,&my,&mbuttn,1,&mine);
		}
		else if(mouse_press(atoi(mine.highx[1])-1,35+25,atoi(mine.highx[1])+2,45+25,&mx,&my,&mbuttn)&&count>=2)
		{
			move_slidder_21(&mx,&my,&mbuttn,2,&mine);
		}
		
		else if(mouse_press(atoi(mine.lowx[2])-1,35+25*2,atoi(mine.lowx[2])+2,45+25*2,&mx,&my,&mbuttn)&&count>=3)
		{
			move_slidder_31(&mx,&my,&mbuttn,1,&mine);
		}
		
		else if(mouse_press(atoi(mine.highx[2])-1,35+25*2,atoi(mine.highx[2])+2,45+25*2,&mx,&my,&mbuttn)&&count>=3)
		{
			move_slidder_31(&mx,&my,&mbuttn,2,&mine);
		}



		else if(mouse_press(290,183,350,468,&mx,&my,&mbuttn))		//鼠标点击查看条件
		{
			i=(my-179)/17+1;
			show_condition(i);
		}
		else if(mouse_press(360,183,370,468,&mx,&my,&mbuttn))		//鼠标点击加入条件
		{
			i=(my-179)/17+1;
			if(i!=mine.a[0]&&i!=mine.a[1]&&i!=mine.a[2])
			{
			  mine.a[count]=i;
			  add_condition(i,count,&mine);
			  count++;
			}
		}
		else if(mouse_press(510,120,580,150,&mx,&my,&mbuttn))		//鼠标点击开始筛选
		{
			choose(&mine,Q);
		}
		else if(mouse_press(610,0,640,20,&mx,&my,&mbuttn))		//鼠标点击退出
		{
			free(Q);
			break;
		}
	}
}

void choose(MX *mine,SIZE *Q)
{
	int i=0,j=0,k=0;
	float l=0.00,h=0.00;
	float ll=0.00,hh=0.00;
	float lll=0.00,hhh=0.00;
	double last;
	char low[10];
	char high[10];
	FILE  *fp;
	char  t[17][15];
	SIZE *front;
	SIZE *temp;
	
	
	while(mine->a[j]!=0)
	{
		i++;
		j++;
		if(j==3)
			break;
	}		//判断有几个条件加入
	fp=fopen("data\\curpri.txt","rt");      //打开文件
	
	if(i==1)
	{
		strcpy(low,mine->lre[0]);
		strcpy(high,mine->hre[0]);
		l=strtod(low,NULL);
		h=strtod(high,NULL);			//设定上下限
			
		
		for(i=0;i<100;i++)//第六组总手除以一万,10,11)第七组总金额除以一亿，第九组涨速0.83,净利润除以一亿，
		{
			fscanf(fp,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
			t[0],t[1],t[2],t[3],t[4],t[5],t[6],t[7],t[8],t[9],t[10],t[11],t[12],t[13],t[14],t[15],t[16]);
			
			last=atol(t[7]);
			last/=10000.0;
			gcvt(last,5,t[7]);
			last=atol(t[8]);
			last/=100000000.0;
			gcvt(last,5,t[8]);
			last=atol(t[15]);
			last/=100000000.0;
			gcvt(last,5,t[15]);
			last=atol(t[16]);
			last/=100000000.0;
			gcvt(last,5,t[16]);
			
			
			if(strtod(t[mine->a[0]+1],NULL)>l&&strtod(t[mine->a[0]+1],NULL)<h)						//满足条件即加入链表
			{
				if(k)
				{	
				temp=(SIZE*)malloc(sizeof(SIZE));
				
				strcpy(temp->num,t[0]);
				strcpy(temp->name,t[1]);
				strcpy(temp->money,t[3]);
				strcpy(temp->up,t[4]);
				temp->next=front->next;
				
				front->next=temp;
				front=temp;
				}
				else
				{
				temp=(SIZE*)malloc(sizeof(SIZE));
				
				strcpy(temp->num,t[0]);
				strcpy(temp->name,t[1]);
				strcpy(temp->money,t[3]);
				strcpy(temp->up,t[4]);
				temp->next=NULL;
				
				front=temp;
				Q=temp;
				k=1;
				}
				
			}			
		}
	}
	else if(i==2)
	{
		strcpy(low,mine->lre[0]);
		strcpy(high,mine->hre[0]);
		l=strtod(low,NULL);
		h=strtod(high,NULL);			//设定上下限
		strcpy(low,mine->lre[1]);
		strcpy(high,mine->hre[1]);
		ll=strtod(low,NULL);
		hh=strtod(high,NULL);			//设定上下限
			
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
			t[0],t[1],t[2],t[3],t[4],t[5],t[6],t[7],t[8],t[9],t[10],t[11],t[12],t[13],t[14],t[15],t[16]);
			
			last=atol(t[7]);
			last/=10000.0;
			gcvt(last,5,t[7]);
			last=atol(t[8]);
			last/=100000000.0;
			gcvt(last,5,t[8]);
			last=atol(t[15]);
			last/=100000000.0;
			gcvt(last,5,t[15]);
			last=atol(t[16]);
			last/=100000000.0;
			gcvt(last,5,t[16]);
			
			if(strtod(t[mine->a[0]+1],NULL)>l&&strtod(t[mine->a[0]+1],NULL)<h&&strtod(t[mine->a[1]+1],NULL)>ll&&strtod(t[mine->a[1]+1],NULL)<hh)						//满足条件即加入链表
			{
				if(k)
				{
				temp=(SIZE*)malloc(sizeof(SIZE));
				
				strcpy(temp->num,t[0]);
				strcpy(temp->name,t[1]);
				strcpy(temp->money,t[3]);
				strcpy(temp->up,t[4]);
				temp->next=front->next;
				
				front->next=temp;
				front=temp;
				}
				else
				{
				temp=(SIZE*)malloc(sizeof(SIZE));
				
				strcpy(temp->num,t[0]);
				strcpy(temp->name,t[1]);
				strcpy(temp->money,t[3]);
				strcpy(temp->up,t[4]);
				temp->next=NULL;
				
				front=temp;
				Q=temp;
				k=1;
				}
				
			}			
		}
	}
	else if(i==3)
	{
		strcpy(low,mine->lre[0]);
		strcpy(high,mine->hre[0]);
		l=strtod(low,NULL);
		h=strtod(high,NULL);			//设定上下限
		strcpy(low,mine->lre[1]);
		strcpy(high,mine->hre[1]);
		ll=strtod(low,NULL);
		hh=strtod(high,NULL);			//设定上下限
		strcpy(low,mine->lre[2]);
		strcpy(high,mine->hre[2]);
		lll=strtod(low,NULL);
		hhh=strtod(high,NULL);			//设定上下限
			
		
		for(i=0;i<100;i++)
		{
			fscanf(fp,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
			t[0],t[1],t[2],t[3],t[4],t[5],t[6],t[7],t[8],t[9],t[10],t[11],t[12],t[13],t[14],t[15],t[16]);
			
			last=atol(t[7]);
			last/=10000.0;
			gcvt(last,5,t[7]);
			last=atol(t[8]);
			last/=100000000.0;
			gcvt(last,5,t[8]);
			last=atol(t[15]);
			last/=100000000.0;
			gcvt(last,5,t[15]);
			last=atol(t[16]);
			last/=100000000.0;
			gcvt(last,5,t[16]);
			
			if(strtod(t[mine->a[0]+1],NULL)>l&&strtod(t[mine->a[0]+1],NULL)<h&&strtod(t[mine->a[1]+1],NULL)>ll&&strtod(t[mine->a[1]+1],NULL)<hh&&strtod(t[mine->a[2]+1],NULL)>lll&&strtod(t[mine->a[2]+1],NULL)<hhh)						//满足条件即加入链表
			{
				if(k)
				{
				temp=(SIZE*)malloc(sizeof(SIZE));
				
				strcpy(temp->num,t[0]);
				strcpy(temp->name,t[1]);
				strcpy(temp->money,t[3]);
				strcpy(temp->up,t[4]);
				temp->next=front->next;
				
				front->next=temp;
				front=temp;
				}
				else
				{
				temp=(SIZE*)malloc(sizeof(SIZE));
				
				strcpy(temp->num,t[0]);
				strcpy(temp->name,t[1]);
				strcpy(temp->money,t[3]);
				strcpy(temp->up,t[4]);
				temp->next=NULL;
				
				front=temp;
				Q=temp;
				k=1;
				}
				
			}			
		}
	}
	fclose(fp);
	final(Q);
}

void final(SIZE *Q)
{
	int kround=0;
	SIZE *temp=Q;
	
	setcolor(BLACK);
	rectangle(0,30,275,480);
	setfillstyle(SOLID_FILL,BLACK);
	bar3d(0,30,275,480,0,0);
	
	
	if(!Q)
		return;

	while(temp->next)
	{
		setcolor(YELLOW);
		outtextxy(20,35+15*kround-5,temp->num);
		puthz12(temp->name,95,33+15*kround,YELLOW);
		outtextxy(150,35+15*kround-5,temp->money);
		outtextxy(200,35+15*kround-5,temp->up);
		temp=temp->next;
		kround++;
	}
}

void move_slidder_11(int *mx,int *my,int *mbuttn,int flag,MX * mine)
{
	char temp[10];			//记录目前鼠标按键下的数值并打印
	float flow;
	float fhigh;						//此处需修改
	float fnow=0.0;
	char *record[]={"k","-3.09","5.97","1.94","44.89","-0.45","0.89","5.65","44.81","1.95","44.9","13.6111","6861.8415","0.02662815",
					"13.83050600","100","81200","-0.83","0.36","0.03","14.08","-1.11","0.61","0.24","3.43","1.61","3206","-67","204.56000000","13.9317","2903"};
	
	if(flag==1)
	{
		setcolor(LIGHTRED);
		setlinestyle(0,0,3);
		line(atoi(mine->lowx[0]),35,atoi(mine->lowx[0]),45);
		setlinestyle(0,0,1);
	}
	else if(flag==2)
	{
		setcolor(LIGHTRED);
		setlinestyle(0,0,3);
		line(atoi(mine->highx[0]),35,atoi(mine->highx[0]),45);
		setlinestyle(0,0,1);
	}													//点击上哪个滑块就将其变红

	if(flag==1)
	{
	  while(1)
	  {
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*mx>=398&&*mx<=552)
		{
			if(*mx!=atoi(mine->lowx[0]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->lowx[0]),35,atoi(mine->lowx[0]),45);//覆盖旧滑块

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40,555,40);//重画横线

				setcolor(LIGHTRED);
				line(*mx,35,*mx,45);//重画滑块

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(340,30,390,50,0,0);//重画最小框

				setcolor(BLACK);
				itoa(*mx,mine->lowx[0],10);
				
				
				if(mine->a[0]==1||mine->a[0]==2||mine->a[0]==3||mine->a[0]==4||mine->a[0]==5||mine->a[0]==6||mine->a[0]==7||mine->a[0]==8||mine->a[0]==9||mine->a[0]==10)
				{
					flow=strtod(record[2*mine->a[0]-1],NULL);//较小数值
					fhigh=strtod(record[2*mine->a[0]],NULL);//较大数值
				}
				else if(mine->a[0]==12||mine->a[0]==13||mine->a[0]==14||mine->a[0]==15||mine->a[0]==16)
				{
					flow=strtod(record[2*(mine->a[0]-2)-1],NULL);//较小数值
					fhigh=strtod(record[2*(mine->a[0]-2)],NULL);//较大数值
				}
				else if(mine->a[0]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				
				fnow=flow+(((float)*mx-398.0)*(fhigh-flow)/(552.0-398.0));
				gcvt(fnow,4,temp);
				outtextxy(345,35,temp);//重填数值
			}

		}

		if(*mbuttn!=1)
		{
			strcpy(mine->lre[0],temp);
			break;
		}
	  }
	}
	else if(flag==2)
	{
	  while(1)
	  {
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*mx>=398&&*mx<=552)                //此处需要后期补上数值
		{
			if(*mx!=atoi(mine->highx[0]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->highx[0]),35,atoi(mine->highx[0]),45);//覆盖旧滑块

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40,555,40);//重画横线

				setcolor(LIGHTRED);
				line(*mx,35,*mx,45);//重画滑块

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(560,30,610,50,0,0);    //重画最大框

				setcolor(BLACK);
				itoa(*mx,mine->highx[0],10);
				
				if(mine->a[0]==1||mine->a[0]==2||mine->a[0]==3||mine->a[0]==4||mine->a[0]==5||mine->a[0]==6||mine->a[0]==7||mine->a[0]==8||mine->a[0]==9||mine->a[0]==10)
				{
					flow=strtod(record[2*mine->a[0]-1],NULL);//较小数值
					fhigh=strtod(record[2*mine->a[0]],NULL);//较大数值
				}
				else if(mine->a[0]==12||mine->a[0]==13||mine->a[0]==14||mine->a[0]==15||mine->a[0]==16)
				{
					flow=strtod(record[2*(mine->a[0]-2)-1],NULL);//较小数值
					fhigh=strtod(record[2*(mine->a[0]-2)],NULL);//较大数值
				}
				else if(mine->a[0]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				fnow=flow+(*mx-398)*(fhigh-flow)/(552-398);
				gcvt(fnow,5,temp);
				outtextxy(565,35,temp);//重填数值
			}

		}

		if(*mbuttn!=1)
		{
			strcpy(mine->hre[0],temp);
			break;
		}
	  }
	}
	
	setcolor(LIGHTGRAY);
	setlinestyle(0,0,3);
	line(atoi(mine->lowx[0]),35,atoi(mine->lowx[0]),45);
	line(atoi(mine->highx[0]),35,atoi(mine->highx[0]),45);
	setlinestyle(0,0,1);
}


void move_slidder_21(int *mx,int *my,int *mbuttn,int flag,MX * mine)
{
	char temp[10];			//记录目前鼠标按键下的数值并打印
	float flow;
	float fhigh;						//此处需修改
	float fnow=0.0;
	char *record[]={"k","-3.09","5.97","1.94","44.89","-0.45","0.89","5.65","44.81","1.95","44.9","13.6111","6861.8415","0.02662815",
					"13.83050600","100","81200","-0.83","0.36","0.03","14.08","-1.11","0.61","0.24","3.43","1.61","3206","-67","204.56000000","13.9317","2903"};
	
	if(flag==1)
	{
		setcolor(LIGHTRED);
		setlinestyle(0,0,3);
		line(atoi(mine->lowx[1]),35+25,atoi(mine->lowx[1]),45+25);
		setlinestyle(0,0,1);
	}
	else if(flag==2)
	{
		setcolor(LIGHTRED);
		setlinestyle(0,0,3);
		line(atoi(mine->highx[1]),35+25,atoi(mine->highx[1]),45+25);
		setlinestyle(0,0,1);
	}													//点击上哪个滑块就将其变红

	if(flag==1)
	{
	  while(1)
	  {
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*mx>=398&&*mx<=552)
		{
			if(*mx!=atoi(mine->lowx[1]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->lowx[1]),35+25,atoi(mine->lowx[1]),45+25);//覆盖旧滑块

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25,555,40+25);//重画横线

				setcolor(LIGHTRED);
				line(*mx,35+25,*mx,45+25);//重画滑块

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(340,30+25,390,50+25,0,0);//重画最小框

				setcolor(BLACK);
				itoa(*mx,mine->lowx[1],10);
				
				
				if(mine->a[1]==1||mine->a[1]==2||mine->a[1]==3||mine->a[1]==4||mine->a[1]==5||mine->a[1]==6||mine->a[1]==7||mine->a[1]==8||mine->a[1]==9||mine->a[1]==10)
				{
					flow=strtod(record[2*mine->a[1]-1],NULL);//较小数值
					fhigh=strtod(record[2*mine->a[1]],NULL);//较大数值
				}
				else if(mine->a[1]==12||mine->a[1]==13||mine->a[1]==14||mine->a[1]==15||mine->a[1]==16)
				{
					flow=strtod(record[2*(mine->a[1]-2)-1],NULL);//较小数值
					fhigh=strtod(record[2*(mine->a[1]-2)],NULL);//较大数值
				}
				else if(mine->a[1]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				
				fnow=flow+(((float)*mx-398.0)*(fhigh-flow)/(552.0-398.0));
				gcvt(fnow,4,temp);
				outtextxy(345,35+25,temp);//重填数值
			}

		}

		if(*mbuttn!=1)
		{
			strcpy(mine->lre[1],temp);
			break;
		}
	  }
	}
	else if(flag==2)
	{
	  while(1)
	  {
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*mx>=398&&*mx<=552)                //此处需要后期补上数值
		{
			if(*mx!=atoi(mine->highx[1]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->highx[1]),35+25,atoi(mine->highx[1]),45+25);//覆盖旧滑块

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25,555,40+25);//重画横线

				setcolor(LIGHTRED);
				line(*mx,35+25,*mx,45+25);//重画滑块

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(560,30+25,610,50+25,0,0);    //重画最大框

				setcolor(BLACK);
				itoa(*mx,mine->highx[1],10);
				
				if(mine->a[1]==1||mine->a[1]==2||mine->a[1]==3||mine->a[1]==4||mine->a[1]==5||mine->a[1]==6||mine->a[1]==7||mine->a[1]==8||mine->a[1]==9||mine->a[1]==10)
				{
					flow=strtod(record[2*mine->a[1]-1],NULL);//较小数值
					fhigh=strtod(record[2*mine->a[1]],NULL);//较大数值
				}
				else if(mine->a[1]==12||mine->a[1]==13||mine->a[1]==14||mine->a[1]==15||mine->a[1]==16)
				{
					flow=strtod(record[2*(mine->a[1]-2)-1],NULL);//较小数值
					fhigh=strtod(record[2*(mine->a[1]-2)],NULL);//较大数值
				}
				else if(mine->a[1]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				fnow=flow+(*mx-398)*(fhigh-flow)/(552-398);
				gcvt(fnow,5,temp);
				outtextxy(565,35+25,temp);//重填数值
			}

		}

		if(*mbuttn!=1)
		{
			strcpy(mine->hre[1],temp);
			break;
		}
	  }
	}
	
	setcolor(LIGHTGRAY);
	setlinestyle(0,0,3);
	line(atoi(mine->lowx[1]),35+25,atoi(mine->lowx[1]),45+25);
	line(atoi(mine->highx[1]),35+25,atoi(mine->highx[1]),45+25);
	setlinestyle(0,0,1);
}

void move_slidder_31(int *mx,int *my,int *mbuttn,int flag,MX * mine)
{
	char temp[10];			//记录目前鼠标按键下的数值并打印
	float flow;
	float fhigh;						//此处需修改
	float fnow=0.0;
	char *record[]={"k","-3.09","5.97","1.94","44.89","-0.45","0.89","5.65","44.81","1.95","44.9","13.6111","6861.8415","0.02662815",
					"13.83050600","100","81200","-0.83","0.36","0.03","14.08","-1.11","0.61","0.24","3.43","1.61","3206","-67","204.56000000","13.9317","2903"};
	
	if(flag==1)
	{
		setcolor(LIGHTRED);
		setlinestyle(0,0,3);
		line(atoi(mine->lowx[2]),35+25*2,atoi(mine->lowx[2]),45+25*2);
		setlinestyle(0,0,1);
	}
	else if(flag==2)
	{
		setcolor(LIGHTRED);
		setlinestyle(0,0,3);
		line(atoi(mine->highx[2]),35+25*2,atoi(mine->highx[2]),45+25*2);
		setlinestyle(0,0,1);
	}													//点击上哪个滑块就将其变红

	if(flag==1)
	{
	  while(1)
	  {
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*mx>=398&&*mx<=552)
		{
			if(*mx!=atoi(mine->lowx[2]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->lowx[2]),35+25*2,atoi(mine->lowx[2]),45+25*2);//覆盖旧滑块

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25*2,555,40+25*2);//重画横线

				setcolor(LIGHTRED);
				line(*mx,35+25*2,*mx,45+25*2);//重画滑块

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(340,30+25*2,390,50+25*2,0,0);//重画最小框

				setcolor(BLACK);
				itoa(*mx,mine->lowx[2],10);
				
				
				if(mine->a[2]==1||mine->a[2]==2||mine->a[2]==3||mine->a[2]==4||mine->a[2]==5||mine->a[2]==6||mine->a[2]==7||mine->a[2]==8||mine->a[2]==9||mine->a[2]==10)
				{
					flow=strtod(record[2*mine->a[2]-1],NULL);//较小数值
					fhigh=strtod(record[2*mine->a[2]],NULL);//较大数值
				}
				else if(mine->a[2]==12||mine->a[2]==13||mine->a[2]==14||mine->a[2]==15||mine->a[2]==16)
				{
					flow=strtod(record[2*(mine->a[2]-2)-1],NULL);//较小数值
					fhigh=strtod(record[2*(mine->a[2]-2)],NULL);//较大数值
				}
				else if(mine->a[2]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				
				fnow=flow+(((float)*mx-398.0)*(fhigh-flow)/(552.0-398.0));
				gcvt(fnow,4,temp);
				outtextxy(345,35+25*2,temp);//重填数值
			}

		}

		if(*mbuttn!=1)
		{
			strcpy(mine->lre[2],temp);
			break;
		}
	  }
	}
	else if(flag==2)
	{
	  while(1)
	  {
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*mx>=398&&*mx<=552)                //此处需要后期补上数值
		{
			if(*mx!=atoi(mine->highx[0]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->highx[2]),35+25*2,atoi(mine->highx[2]),45+25*2);//覆盖旧滑块

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25*2,555,40+25*2);//重画横线

				setcolor(LIGHTRED);
				line(*mx,35+25*2,*mx,45+25*2);//重画滑块

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(560,30+25*2,610,50+25*2,0,0);    //重画最大框

				setcolor(BLACK);
				itoa(*mx,mine->highx[2],10);
				
				if(mine->a[2]==1||mine->a[2]==2||mine->a[2]==3||mine->a[2]==4||mine->a[2]==5||mine->a[2]==6||mine->a[2]==7||mine->a[2]==8||mine->a[2]==9||mine->a[2]==10)
				{
					flow=strtod(record[2*mine->a[2]-1],NULL);//较小数值
					fhigh=strtod(record[2*mine->a[2]],NULL);//较大数值
				}
				else if(mine->a[2]==12||mine->a[2]==13||mine->a[2]==14||mine->a[2]==15||mine->a[2]==16)
				{
					flow=strtod(record[2*(mine->a[2]-2)-1],NULL);//较小数值
					fhigh=strtod(record[2*(mine->a[2]-2)],NULL);//较大数值
				}
				else if(mine->a[2]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				fnow=flow+(*mx-398)*(fhigh-flow)/(552-398);
				gcvt(fnow,5,temp);
				outtextxy(565,35+25*2,temp);//重填数值
			}

		}

		if(*mbuttn!=1)
		{
			strcpy(mine->hre[2],temp);
			break;
		}
	  }
	}
	
	setcolor(LIGHTGRAY);
	setlinestyle(0,0,3);
	line(atoi(mine->lowx[2]),35+25*2,atoi(mine->lowx[2]),45+25*2);
	line(atoi(mine->highx[2]),35+25*2,atoi(mine->highx[2]),45+25*2);
	setlinestyle(0,0,1);
}

void add_condition(int condition,int count,MX *mine)
{

	char *name[]={"k","涨幅","现价","涨跌","买价","卖价","总手","总金额",
					"现手","涨速","换手","利好","利空","主力净量","量比",
					"市盈率","净利润","总市值"};				//定义好条件名（第六组总手除以一万,10,11)第七组总金额除以一亿，第九组涨速0.83,净利润除以一亿，
	char *record[]={"k","-3.09","5.97","1.94","44.89","-0.45","0.89","5.65","44.81","1.95","44.9","13.6111","6861.8","0.0266",
					"13.830","100","81200","-0.83","0.36","0.03","14.08","-1.11","0.61","0.24","3.43","1.61","3206","-67","204.56","13.93","2903"};

	int address[5][2];
	int i;

	if(count>=3||condition==17||condition==19)
		return;
	else if(condition==11||condition==12)
	{
		puthz16("利多",300,110,16,1,1,RED);
		puthz16("利空",380,110,16,1,1,RED);
		setcolor(WHITE);
		circle(315,140,7);
		circle(395,140,7);
		floodfill(315,140,WHITE);
		floodfill(395,140,WHITE);
	}
	else
	{
		for(i=0;i<3;i++)
		{
			address[i][0]=277;
			address[i][1]=35+25*i;
		}															//定义好各条件位置
		puthz16(name[condition],address[count][0],address[count][1],16,1,1,LIGHTRED);
		setcolor(BLACK);
		if(condition==1||condition==2||condition==3||condition==4||condition==5||condition==6||condition==7||condition==8||condition==9||condition==10)
		{
			outtextxy(345,35+25*count,record[2*condition-1]);//较小数值
			outtextxy(565,35+25*count,record[2*condition]);//较大数值
			strcpy(mine->lre[count],record[2*condition-1]);
			strcpy(mine->hre[count],record[2*condition]);
			
		}
		else if(condition==12||condition==13||condition==14||condition==15||condition==16)
		{
			outtextxy(345,35+25*count,record[2*(condition-2)-1]);//较小数值
			outtextxy(565,35+25*count,record[2*(condition-2)]);//较大数值
			strcpy(mine->lre[count],record[2*(condition-2)-1]);
			strcpy(mine->hre[count],record[2*(condition-2)]);
		}
		else if(condition==17)
		{
			outtextxy(345,35+25*count,record[29]);//较小数值
			outtextxy(565,35+25*count,record[29]);//较大数值
			strcpy(mine->lre[count],record[29]);
			strcpy(mine->hre[count],record[30]);
		}
		
	}
	
	setcolor(LIGHTRED);
	rectangle(510,120,580,150);
	puthz16("开始筛选",515,128,16,1,1,LIGHTRED);
	
}


void show_condition(int condition)
{
	setfillstyle(SOLID_FILL,BLACK);
	bar3d(370,190,630,470,0,0);
	if(condition==9)
	{	setlinestyle(0,0,1);
		puthz16("涨速：是当前股票的增长加速度",390,215,16,1,1,RED);
		puthz16("涨速",390,215,16,1,1,WHITE);
		puthz16("或下跌加速度，是指单位时间",390,235,16,1,1,RED);
		puthz16("内股票价格涨幅的大小。",390,255,16,1,1,RED);
	}
	else if(condition==3)
	{	setlinestyle(0,0,1);
		puthz16("涨跌：涨跌值，用“元”做单位",390,215,16,1,1,RED);
		puthz16("涨跌",390,215,16,1,1,WHITE);
		puthz16("表示价格变动量，涨跌=今收盘",390,235,16,1,1,RED);
		puthz16("-昨收盘或下跌加速度，是指单",390,255,16,1,1,RED);  
		puthz16("位时间内股票价格涨幅的大小。",390,275,16,1,1,RED);  
	}
	else if(condition==1)
	{	setlinestyle(0,0,1);
		puthz16("涨幅指目前这只股票的上涨幅度",390,215,16,1,1,RED);
		puthz16("涨幅",390,215,16,1,1,WHITE);  
	}
	else if(condition==2)
	{	setlinestyle(0,0,1);
		puthz16("现价：就是当前的价格，当天即",390,215,16,1,1,RED);
		puthz16("现价",390,215,16,1,1,WHITE);  
		puthz16("时的价格。股票的现价是由当天",390,235,16,1,1,RED);
		puthz16("的集合竞价决定了开盘价，再由",390,255,16,1,1,RED);  
		puthz16("双方买卖的意愿决定了价格。",390,275,16,1,1,RED);  
	}
	else if(condition==4)
	{	setlinestyle(0,0,1);			
		puthz16("买价是指税务机关批准使用",390,215,16,1,1,RED);
		puthz16("买价",390,215,16,1,1,WHITE);
		puthz16("的收购凭证上的价款，包括",390,235,16,1,1,RED);
		puthz16("农业特产税，但不包括增值",390,255,16,1,1,RED);
		puthz16("税",390,275,16,1,1,RED);				
	}
	else if(condition==5)
	{	setlinestyle(0,0,1);			
		puthz16("卖价投资人将基金持份卖给",390,215,16,1,1,RED);
		puthz16("卖价",390,215,16,1,1,WHITE);
		puthz16("基金（公司）的价格，于交",390,235,16,1,1,RED);
		puthz16("易所内或场外某证券或商品",390,255,16,1,1,RED);
		puthz16("的出售价，通常这是交易商",390,275,16,1,1,RED);				
		puthz16("愿意卖出的最低价。卖价又。",390,295,16,1,1,RED);
		puthz16("称赎回价，通常相当于净值",390,315,16,1,1,RED);
		puthz16("（除非有赎回手续费）",390,335,16,1,1,RED);
	}
	else if(condition==6)
	{	setlinestyle(0,0,1);			
		puthz16("总手：现手数是说明电脑刚",390,215,16,1,1,RED);
		puthz16("总手",390,215,16,1,1,WHITE);
		puthz16("刚自动成交的那次成交量的",390,235,16,1,1,RED);
		puthz16("大小。一天内现手累计起来",390,255,16,1,1,RED);
		puthz16("就是总手数, 即成交量",390,275,16,1,1,RED);				
	}
	else if(condition==7)
	{	setlinestyle(0,0,1);			
		puthz16("总金额：股票总金额即股票",390,215,16,1,1,RED);
		puthz16("总金额",390,215,16,1,1,WHITE);
		puthz16("总市值加资金总额 ，即总共",390,235,16,1,1,RED);
		puthz16("成交多少金额",390,255,16,1,1,RED);			
	}
	else if(condition==8)
	{	setlinestyle(0,0,1);			
		puthz16("现手：某一股票即时的成交量",390,215,16,1,1,RED);
		puthz16("现手",390,215,16,1,1,WHITE);
		puthz16("。电子现货最小交易量是一批，",390,235,16,1,1,RED);
		puthz16("相当于股票的一股。对于最近",390,255,16,1,1,RED);
		puthz16("成交的一笔成交量也称现手。",390,275,16,1,1,RED);				
	}
	else if(condition==10)
	{	setlinestyle(0,0,1);			
		puthz16("换手：用来描述从一个人那里。",390,215,16,1,1,RED);
		puthz16("换手",390,215,16,1,1,WHITE);
		puthz16("买或卖给另一个人相等份额的",390,235,16,1,1,RED);
		puthz16("期货，即买卖成交。 证券交",390,255,16,1,1,RED);
		puthz16("易中，仅凭一个价格动态描述",390,275,16,1,1,RED);	
		puthz16("市场的信息是非常有限的，成",390,295,16,1,1,RED);		
		puthz16("交的数量，也就是换手量是非",390,315,16,1,1,RED);
		puthz16("常重要的参考标准",390,335,16,1,1,RED);
	}
	else if(condition==11)
	{	setlinestyle(0,0,1);			
		puthz16("利好：利多是致使股票行情上涨",390,215,16,1,1,RED);
		puthz16("利好",390,215,16,1,1,WHITE);
		puthz16("的主要原因或因素。它对多头有",390,235,16,1,1,RED);
		puthz16("利，它能刺激股价行市上涨，利",390,255,16,1,1,RED);
		puthz16("多的具体表现如公司利润增加、",390,275,16,1,1,RED);	
		puthz16("股息增加，公司经营状况好转、",390,295,16,1,1,RED);		
		puthz16("利率降低等。",390,315,16,1,1,RED);
	}
	else if(condition==12)
	{	setlinestyle(0,0,1);			
		puthz16("利空：利空就是指能够促使股价",390,215,16,1,1,RED);
		puthz16("利空",390,215,16,1,1,WHITE);
		puthz16("下跌的信息，如股票上市公司经",390,235,16,1,1,RED);
		puthz16("营业绩恶化、银行紧缩、银行利",390,255,16,1,1,RED);
		puthz16("率调高、经济衰退、通货膨胀、",390,275,16,1,1,RED);	
		puthz16("天灾人祸等，以及其他政治、经",390,295,16,1,1,RED);		
		puthz16("济军事、外交等方面促使股价下",390,315,16,1,1,RED);
		puthz16("跌的不利消息。",390,335,16,1,1,RED);
	}
	else if(condition==13)
	{	setlinestyle(0,0,1);			
		puthz16("主力净量：买手量与卖手量的",390,215,16,1,1,RED);
		puthz16("主力净量",390,215,16,1,1,WHITE);
		puthz16("差值。",390,235,16,1,1,RED);
	}
	else if(condition==14)
	{	setlinestyle(0,0,1);			
		puthz16("量比：量比是衡量相对成交量",390,215,16,1,1,RED);
		puthz16("量比",390,215,16,1,1,WHITE);
		puthz16("的指标。它是指股市开市后平",390,235,16,1,1,RED);
		puthz16("均每分钟的成交量与过去5个交",390,255,16,1,1,RED);
		puthz16("易日平均每分钟成交量之比。",390,275,16,1,1,RED);	
	}
	else if(condition==15)
	{	setlinestyle(0,0,1);			
		puthz16("市盈率也称“本益比”、“股价",390,215,16,1,1,RED);
		puthz16("市盈率",390,215,16,1,1,WHITE);
		puthz16("收益比率”或称“市价盈利比",390,235,16,1,1,RED);
		puthz16("率（简称市盈率）”。市盈率是",390,255,16,1,1,RED);
		puthz16("最常用来做评估股价水平是否",390,275,16,1,1,RED);
		puthz16("合理的指标之一，由股价除以",390,295,16,1,1,RED);
		puthz16("年度每股盈余得出（以公司市",390,315,16,1,1,RED);
		puthz16("值除以年度股东应占溢利亦可",390,335,16,1,1,RED);
		puthz16("得出相同结果）。",390,355,16,1,1,RED); 
	}
	else if(condition==16)
	{	setlinestyle(0,0,1);			
		puthz16("总市值：总市值是指在某特定",390,215,16,1,1,RED);
		puthz16("总市值",390,215,16,1,1,WHITE);
		puthz16("时间内总股本数乘以当时股价",390,235,16,1,1,RED);
		puthz16("得出的股票总价值。",390,255,16,1,1,RED);
	}
	else if(condition==17)
	{	setlinestyle(0,0,1);			
		puthz16("流通市值：流通市值指在某特",390,215,16,1,1,RED);
		puthz16("流通市值",390,215,16,1,1,WHITE);
		puthz16("定时间内当时可交易的流通股",390,235,16,1,1,RED);
		puthz16("股数乘以当时股价得出的流通",390,255,16,1,1,RED);
		puthz16("股票总价值。",390,275,16,1,1,RED);
	}
}


void draw_()
{
	int i=0;
	
	puthz12("代码",30,18,WHITE);
	puthz12("名称",95,18,WHITE);
	puthz12("现价",150,18,WHITE);     
	outtextxy(225,20,"%");
	puthz12("涨跌",200,18,WHITE);							//筛选结果标题栏

	setcolor(LIGHTGRAY);
	setlinestyle(0,0,3);
	line(275,18,275,480);									//左边是筛选结果

	line(275,160,640,160);
	setcolor(WHITE);
	rectangle(370,190,630,470);								//条件介绍框
	
	
	i=-1;
	puthz12("涨幅",307,200+i*17,LIGHTGRAY); i++;
	puthz12("现价",307,200+i*17,LIGHTGRAY); i++;
	puthz12("涨跌",307,200+i*17,LIGHTGRAY); i++;
	puthz12("买价",307,200+i*17,LIGHTGRAY); i++;
	puthz12("卖价",307,200+i*17,LIGHTGRAY);i++;
	puthz12("总手",307,200+i*17,LIGHTGRAY);i++;
	puthz12("总金额",300,200+i*17,LIGHTGRAY);i++;
	puthz12("现手",307,200+i*17,LIGHTGRAY);i++;
	puthz12("涨速",307,200+i*17,LIGHTGRAY);i++;
	puthz12("换手",307,200+i*17,LIGHTGRAY);i++;
	puthz12("利好",307,200+i*17,LIGHTGRAY);i++;
	puthz12("利空",307,200+i*17,LIGHTGRAY);i++;
	puthz12("主力净量",297,200+i*17,LIGHTGRAY);i++;
	puthz12("量比",307,200+i*17,LIGHTGRAY);i++;
	puthz12("市盈率",300,200+i*17,LIGHTGRAY);i++;
	puthz12("净利润",300,200+i*17,LIGHTGRAY);i++;
	puthz12("总市值",300,200+i*17,LIGHTGRAY);i++;

	for(i=0;i<17;i++)
	{
	   setlinestyle(0,0,1);
	   line(290,196+i*17,350,196+i*17);
	   setlinestyle(0,0,3);
	   rectangle(360,186+i*17,370,186+i*17);
	}														//条件罗列
	
	setcolor(LIGHTGRAY) ;
	line(395,40,555,40);
	line(395,65,555,65);
	line(395,90,555,90);

	for(i=0;i<3;i++)
	{
		line(398,35+i*25,398,45+i*25);
		line(552,35+i*25,552,45+i*25);
	}														//滑动线及两个滑块

	setlinestyle(0,0,1);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	bar3d(340,30,390,50,0,0);
	bar3d(340,55,390,75,0,0);
	bar3d(340,80,390,100,0,0);

	bar3d(560,30,610,50,0,0);
	bar3d(560,55,610,75,0,0);
	bar3d(560,80,610,100,0,0);						//最高最低框
	puthz16("最高",560,13,16,1,1,YELLOW);
	puthz16("最低",340,13,16,1,1,YELLOW) ;
	puthz16("退出",610,0,16,1,1,RED) ;

}
