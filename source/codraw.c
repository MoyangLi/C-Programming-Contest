#include "stdio.h"
#include "dos.h"
#include "conio.h"

#include "codraw.h"


void size_control()
{
	int mx,my,mbuttn=-1;
	int i;				//ѭ�����ʹ��
	int count=0;			//���ڼ�¼��������
	MX mine;			//��¼ÿ�����������ߵ�λ��,����������Ҫ��
	SIZE *Q=NULL;

	for(i=0;i<3;i++)
	{
		mine.a[i]=0;
		strcpy(mine.lowx[i],"398");
		strcpy(mine.highx[i],"552");			//��ÿ���϶�������λ�ó�ʼ��Ϊ����
	}

	cleardevice();
	draw_();										//��ʼ������
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



		else if(mouse_press(290,183,350,468,&mx,&my,&mbuttn))		//������鿴����
		{
			i=(my-179)/17+1;
			show_condition(i);
		}
		else if(mouse_press(360,183,370,468,&mx,&my,&mbuttn))		//�������������
		{
			i=(my-179)/17+1;
			if(i!=mine.a[0]&&i!=mine.a[1]&&i!=mine.a[2])
			{
			  mine.a[count]=i;
			  add_condition(i,count,&mine);
			  count++;
			}
		}
		else if(mouse_press(510,120,580,150,&mx,&my,&mbuttn))		//�������ʼɸѡ
		{
			choose(&mine,Q);
		}
		else if(mouse_press(610,0,640,20,&mx,&my,&mbuttn))		//������˳�
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
	}		//�ж��м�����������
	fp=fopen("data\\curpri.txt","rt");      //���ļ�
	
	if(i==1)
	{
		strcpy(low,mine->lre[0]);
		strcpy(high,mine->hre[0]);
		l=strtod(low,NULL);
		h=strtod(high,NULL);			//�趨������
			
		
		for(i=0;i<100;i++)//���������ֳ���һ��,10,11)�������ܽ�����һ�ڣ��ھ�������0.83,���������һ�ڣ�
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
			
			
			if(strtod(t[mine->a[0]+1],NULL)>l&&strtod(t[mine->a[0]+1],NULL)<h)						//������������������
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
		h=strtod(high,NULL);			//�趨������
		strcpy(low,mine->lre[1]);
		strcpy(high,mine->hre[1]);
		ll=strtod(low,NULL);
		hh=strtod(high,NULL);			//�趨������
			
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
			
			if(strtod(t[mine->a[0]+1],NULL)>l&&strtod(t[mine->a[0]+1],NULL)<h&&strtod(t[mine->a[1]+1],NULL)>ll&&strtod(t[mine->a[1]+1],NULL)<hh)						//������������������
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
		h=strtod(high,NULL);			//�趨������
		strcpy(low,mine->lre[1]);
		strcpy(high,mine->hre[1]);
		ll=strtod(low,NULL);
		hh=strtod(high,NULL);			//�趨������
		strcpy(low,mine->lre[2]);
		strcpy(high,mine->hre[2]);
		lll=strtod(low,NULL);
		hhh=strtod(high,NULL);			//�趨������
			
		
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
			
			if(strtod(t[mine->a[0]+1],NULL)>l&&strtod(t[mine->a[0]+1],NULL)<h&&strtod(t[mine->a[1]+1],NULL)>ll&&strtod(t[mine->a[1]+1],NULL)<hh&&strtod(t[mine->a[2]+1],NULL)>lll&&strtod(t[mine->a[2]+1],NULL)<hhh)						//������������������
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
	char temp[10];			//��¼Ŀǰ��갴���µ���ֵ����ӡ
	float flow;
	float fhigh;						//�˴����޸�
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
	}													//������ĸ�����ͽ�����

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
				line(atoi(mine->lowx[0]),35,atoi(mine->lowx[0]),45);//���Ǿɻ���

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40,555,40);//�ػ�����

				setcolor(LIGHTRED);
				line(*mx,35,*mx,45);//�ػ�����

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(340,30,390,50,0,0);//�ػ���С��

				setcolor(BLACK);
				itoa(*mx,mine->lowx[0],10);
				
				
				if(mine->a[0]==1||mine->a[0]==2||mine->a[0]==3||mine->a[0]==4||mine->a[0]==5||mine->a[0]==6||mine->a[0]==7||mine->a[0]==8||mine->a[0]==9||mine->a[0]==10)
				{
					flow=strtod(record[2*mine->a[0]-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*mine->a[0]],NULL);//�ϴ���ֵ
				}
				else if(mine->a[0]==12||mine->a[0]==13||mine->a[0]==14||mine->a[0]==15||mine->a[0]==16)
				{
					flow=strtod(record[2*(mine->a[0]-2)-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*(mine->a[0]-2)],NULL);//�ϴ���ֵ
				}
				else if(mine->a[0]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				
				fnow=flow+(((float)*mx-398.0)*(fhigh-flow)/(552.0-398.0));
				gcvt(fnow,4,temp);
				outtextxy(345,35,temp);//������ֵ
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
		if(*mbuttn==1&&*mx>=398&&*mx<=552)                //�˴���Ҫ���ڲ�����ֵ
		{
			if(*mx!=atoi(mine->highx[0]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->highx[0]),35,atoi(mine->highx[0]),45);//���Ǿɻ���

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40,555,40);//�ػ�����

				setcolor(LIGHTRED);
				line(*mx,35,*mx,45);//�ػ�����

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(560,30,610,50,0,0);    //�ػ�����

				setcolor(BLACK);
				itoa(*mx,mine->highx[0],10);
				
				if(mine->a[0]==1||mine->a[0]==2||mine->a[0]==3||mine->a[0]==4||mine->a[0]==5||mine->a[0]==6||mine->a[0]==7||mine->a[0]==8||mine->a[0]==9||mine->a[0]==10)
				{
					flow=strtod(record[2*mine->a[0]-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*mine->a[0]],NULL);//�ϴ���ֵ
				}
				else if(mine->a[0]==12||mine->a[0]==13||mine->a[0]==14||mine->a[0]==15||mine->a[0]==16)
				{
					flow=strtod(record[2*(mine->a[0]-2)-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*(mine->a[0]-2)],NULL);//�ϴ���ֵ
				}
				else if(mine->a[0]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				fnow=flow+(*mx-398)*(fhigh-flow)/(552-398);
				gcvt(fnow,5,temp);
				outtextxy(565,35,temp);//������ֵ
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
	char temp[10];			//��¼Ŀǰ��갴���µ���ֵ����ӡ
	float flow;
	float fhigh;						//�˴����޸�
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
	}													//������ĸ�����ͽ�����

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
				line(atoi(mine->lowx[1]),35+25,atoi(mine->lowx[1]),45+25);//���Ǿɻ���

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25,555,40+25);//�ػ�����

				setcolor(LIGHTRED);
				line(*mx,35+25,*mx,45+25);//�ػ�����

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(340,30+25,390,50+25,0,0);//�ػ���С��

				setcolor(BLACK);
				itoa(*mx,mine->lowx[1],10);
				
				
				if(mine->a[1]==1||mine->a[1]==2||mine->a[1]==3||mine->a[1]==4||mine->a[1]==5||mine->a[1]==6||mine->a[1]==7||mine->a[1]==8||mine->a[1]==9||mine->a[1]==10)
				{
					flow=strtod(record[2*mine->a[1]-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*mine->a[1]],NULL);//�ϴ���ֵ
				}
				else if(mine->a[1]==12||mine->a[1]==13||mine->a[1]==14||mine->a[1]==15||mine->a[1]==16)
				{
					flow=strtod(record[2*(mine->a[1]-2)-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*(mine->a[1]-2)],NULL);//�ϴ���ֵ
				}
				else if(mine->a[1]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				
				fnow=flow+(((float)*mx-398.0)*(fhigh-flow)/(552.0-398.0));
				gcvt(fnow,4,temp);
				outtextxy(345,35+25,temp);//������ֵ
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
		if(*mbuttn==1&&*mx>=398&&*mx<=552)                //�˴���Ҫ���ڲ�����ֵ
		{
			if(*mx!=atoi(mine->highx[1]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->highx[1]),35+25,atoi(mine->highx[1]),45+25);//���Ǿɻ���

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25,555,40+25);//�ػ�����

				setcolor(LIGHTRED);
				line(*mx,35+25,*mx,45+25);//�ػ�����

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(560,30+25,610,50+25,0,0);    //�ػ�����

				setcolor(BLACK);
				itoa(*mx,mine->highx[1],10);
				
				if(mine->a[1]==1||mine->a[1]==2||mine->a[1]==3||mine->a[1]==4||mine->a[1]==5||mine->a[1]==6||mine->a[1]==7||mine->a[1]==8||mine->a[1]==9||mine->a[1]==10)
				{
					flow=strtod(record[2*mine->a[1]-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*mine->a[1]],NULL);//�ϴ���ֵ
				}
				else if(mine->a[1]==12||mine->a[1]==13||mine->a[1]==14||mine->a[1]==15||mine->a[1]==16)
				{
					flow=strtod(record[2*(mine->a[1]-2)-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*(mine->a[1]-2)],NULL);//�ϴ���ֵ
				}
				else if(mine->a[1]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				fnow=flow+(*mx-398)*(fhigh-flow)/(552-398);
				gcvt(fnow,5,temp);
				outtextxy(565,35+25,temp);//������ֵ
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
	char temp[10];			//��¼Ŀǰ��갴���µ���ֵ����ӡ
	float flow;
	float fhigh;						//�˴����޸�
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
	}													//������ĸ�����ͽ�����

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
				line(atoi(mine->lowx[2]),35+25*2,atoi(mine->lowx[2]),45+25*2);//���Ǿɻ���

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25*2,555,40+25*2);//�ػ�����

				setcolor(LIGHTRED);
				line(*mx,35+25*2,*mx,45+25*2);//�ػ�����

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(340,30+25*2,390,50+25*2,0,0);//�ػ���С��

				setcolor(BLACK);
				itoa(*mx,mine->lowx[2],10);
				
				
				if(mine->a[2]==1||mine->a[2]==2||mine->a[2]==3||mine->a[2]==4||mine->a[2]==5||mine->a[2]==6||mine->a[2]==7||mine->a[2]==8||mine->a[2]==9||mine->a[2]==10)
				{
					flow=strtod(record[2*mine->a[2]-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*mine->a[2]],NULL);//�ϴ���ֵ
				}
				else if(mine->a[2]==12||mine->a[2]==13||mine->a[2]==14||mine->a[2]==15||mine->a[2]==16)
				{
					flow=strtod(record[2*(mine->a[2]-2)-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*(mine->a[2]-2)],NULL);//�ϴ���ֵ
				}
				else if(mine->a[2]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				
				fnow=flow+(((float)*mx-398.0)*(fhigh-flow)/(552.0-398.0));
				gcvt(fnow,4,temp);
				outtextxy(345,35+25*2,temp);//������ֵ
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
		if(*mbuttn==1&&*mx>=398&&*mx<=552)                //�˴���Ҫ���ڲ�����ֵ
		{
			if(*mx!=atoi(mine->highx[0]))
			{
				setlinestyle(0,0,3);
				setcolor(BLACK);
				line(atoi(mine->highx[2]),35+25*2,atoi(mine->highx[2]),45+25*2);//���Ǿɻ���

				setcolor(LIGHTGRAY);
				setlinestyle(0,0,3);
				line(395,40+25*2,555,40+25*2);//�ػ�����

				setcolor(LIGHTRED);
				line(*mx,35+25*2,*mx,45+25*2);//�ػ�����

				setcolor(WHITE);
				setfillstyle(SOLID_FILL,WHITE);
				bar3d(560,30+25*2,610,50+25*2,0,0);    //�ػ�����

				setcolor(BLACK);
				itoa(*mx,mine->highx[2],10);
				
				if(mine->a[2]==1||mine->a[2]==2||mine->a[2]==3||mine->a[2]==4||mine->a[2]==5||mine->a[2]==6||mine->a[2]==7||mine->a[2]==8||mine->a[2]==9||mine->a[2]==10)
				{
					flow=strtod(record[2*mine->a[2]-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*mine->a[2]],NULL);//�ϴ���ֵ
				}
				else if(mine->a[2]==12||mine->a[2]==13||mine->a[2]==14||mine->a[2]==15||mine->a[2]==16)
				{
					flow=strtod(record[2*(mine->a[2]-2)-1],NULL);//��С��ֵ
					fhigh=strtod(record[2*(mine->a[2]-2)],NULL);//�ϴ���ֵ
				}
				else if(mine->a[2]==17)
				{
					flow=strtod(record[29],NULL);
					fhigh=strtod(record[30],NULL);
				}
				
				fnow=flow+(*mx-398)*(fhigh-flow)/(552-398);
				gcvt(fnow,5,temp);
				outtextxy(565,35+25*2,temp);//������ֵ
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

	char *name[]={"k","�Ƿ�","�ּ�","�ǵ�","���","����","����","�ܽ��",
					"����","����","����","����","����","��������","����",
					"��ӯ��","������","����ֵ"};				//����������������������ֳ���һ��,10,11)�������ܽ�����һ�ڣ��ھ�������0.83,���������һ�ڣ�
	char *record[]={"k","-3.09","5.97","1.94","44.89","-0.45","0.89","5.65","44.81","1.95","44.9","13.6111","6861.8","0.0266",
					"13.830","100","81200","-0.83","0.36","0.03","14.08","-1.11","0.61","0.24","3.43","1.61","3206","-67","204.56","13.93","2903"};

	int address[5][2];
	int i;

	if(count>=3||condition==17||condition==19)
		return;
	else if(condition==11||condition==12)
	{
		puthz16("����",300,110,16,1,1,RED);
		puthz16("����",380,110,16,1,1,RED);
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
		}															//����ø�����λ��
		puthz16(name[condition],address[count][0],address[count][1],16,1,1,LIGHTRED);
		setcolor(BLACK);
		if(condition==1||condition==2||condition==3||condition==4||condition==5||condition==6||condition==7||condition==8||condition==9||condition==10)
		{
			outtextxy(345,35+25*count,record[2*condition-1]);//��С��ֵ
			outtextxy(565,35+25*count,record[2*condition]);//�ϴ���ֵ
			strcpy(mine->lre[count],record[2*condition-1]);
			strcpy(mine->hre[count],record[2*condition]);
			
		}
		else if(condition==12||condition==13||condition==14||condition==15||condition==16)
		{
			outtextxy(345,35+25*count,record[2*(condition-2)-1]);//��С��ֵ
			outtextxy(565,35+25*count,record[2*(condition-2)]);//�ϴ���ֵ
			strcpy(mine->lre[count],record[2*(condition-2)-1]);
			strcpy(mine->hre[count],record[2*(condition-2)]);
		}
		else if(condition==17)
		{
			outtextxy(345,35+25*count,record[29]);//��С��ֵ
			outtextxy(565,35+25*count,record[29]);//�ϴ���ֵ
			strcpy(mine->lre[count],record[29]);
			strcpy(mine->hre[count],record[30]);
		}
		
	}
	
	setcolor(LIGHTRED);
	rectangle(510,120,580,150);
	puthz16("��ʼɸѡ",515,128,16,1,1,LIGHTRED);
	
}


void show_condition(int condition)
{
	setfillstyle(SOLID_FILL,BLACK);
	bar3d(370,190,630,470,0,0);
	if(condition==9)
	{	setlinestyle(0,0,1);
		puthz16("���٣��ǵ�ǰ��Ʊ���������ٶ�",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("���µ����ٶȣ���ָ��λʱ��",390,235,16,1,1,RED);
		puthz16("�ڹ�Ʊ�۸��Ƿ��Ĵ�С��",390,255,16,1,1,RED);
	}
	else if(condition==3)
	{	setlinestyle(0,0,1);
		puthz16("�ǵ����ǵ�ֵ���á�Ԫ������λ",390,215,16,1,1,RED);
		puthz16("�ǵ�",390,215,16,1,1,WHITE);
		puthz16("��ʾ�۸�䶯�����ǵ�=������",390,235,16,1,1,RED);
		puthz16("-�����̻��µ����ٶȣ���ָ��",390,255,16,1,1,RED);  
		puthz16("λʱ���ڹ�Ʊ�۸��Ƿ��Ĵ�С��",390,275,16,1,1,RED);  
	}
	else if(condition==1)
	{	setlinestyle(0,0,1);
		puthz16("�Ƿ�ָĿǰ��ֻ��Ʊ�����Ƿ���",390,215,16,1,1,RED);
		puthz16("�Ƿ�",390,215,16,1,1,WHITE);  
	}
	else if(condition==2)
	{	setlinestyle(0,0,1);
		puthz16("�ּۣ����ǵ�ǰ�ļ۸񣬵��켴",390,215,16,1,1,RED);
		puthz16("�ּ�",390,215,16,1,1,WHITE);  
		puthz16("ʱ�ļ۸񡣹�Ʊ���ּ����ɵ���",390,235,16,1,1,RED);
		puthz16("�ļ��Ͼ��۾����˿��̼ۣ�����",390,255,16,1,1,RED);  
		puthz16("˫����������Ը�����˼۸�",390,275,16,1,1,RED);  
	}
	else if(condition==4)
	{	setlinestyle(0,0,1);			
		puthz16("�����ָ˰�������׼ʹ��",390,215,16,1,1,RED);
		puthz16("���",390,215,16,1,1,WHITE);
		puthz16("���չ�ƾ֤�ϵļۿ����",390,235,16,1,1,RED);
		puthz16("ũҵ�ز�˰������������ֵ",390,255,16,1,1,RED);
		puthz16("˰",390,275,16,1,1,RED);				
	}
	else if(condition==5)
	{	setlinestyle(0,0,1);			
		puthz16("����Ͷ���˽�����ַ�����",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("���𣨹�˾���ļ۸��ڽ�",390,235,16,1,1,RED);
		puthz16("�����ڻ���ĳ֤ȯ����Ʒ",390,255,16,1,1,RED);
		puthz16("�ĳ��ۼۣ�ͨ�����ǽ�����",390,275,16,1,1,RED);				
		puthz16("Ը����������ͼۡ������֡�",390,295,16,1,1,RED);
		puthz16("����ؼۣ�ͨ���൱�ھ�ֵ",390,315,16,1,1,RED);
		puthz16("����������������ѣ�",390,335,16,1,1,RED);
	}
	else if(condition==6)
	{	setlinestyle(0,0,1);			
		puthz16("���֣���������˵�����Ը�",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("���Զ��ɽ����Ǵγɽ�����",390,235,16,1,1,RED);
		puthz16("��С��һ���������ۼ�����",390,255,16,1,1,RED);
		puthz16("����������, ���ɽ���",390,275,16,1,1,RED);				
	}
	else if(condition==7)
	{	setlinestyle(0,0,1);			
		puthz16("�ܽ���Ʊ�ܽ���Ʊ",390,215,16,1,1,RED);
		puthz16("�ܽ��",390,215,16,1,1,WHITE);
		puthz16("����ֵ���ʽ��ܶ� �����ܹ�",390,235,16,1,1,RED);
		puthz16("�ɽ����ٽ��",390,255,16,1,1,RED);			
	}
	else if(condition==8)
	{	setlinestyle(0,0,1);			
		puthz16("���֣�ĳһ��Ʊ��ʱ�ĳɽ���",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("�������ֻ���С��������һ����",390,235,16,1,1,RED);
		puthz16("�൱�ڹ�Ʊ��һ�ɡ��������",390,255,16,1,1,RED);
		puthz16("�ɽ���һ�ʳɽ���Ҳ�����֡�",390,275,16,1,1,RED);				
	}
	else if(condition==10)
	{	setlinestyle(0,0,1);			
		puthz16("���֣�����������һ�������",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("���������һ������ȷݶ��",390,235,16,1,1,RED);
		puthz16("�ڻ����������ɽ��� ֤ȯ��",390,255,16,1,1,RED);
		puthz16("���У���ƾһ���۸�̬����",390,275,16,1,1,RED);	
		puthz16("�г�����Ϣ�Ƿǳ����޵ģ���",390,295,16,1,1,RED);		
		puthz16("����������Ҳ���ǻ������Ƿ�",390,315,16,1,1,RED);
		puthz16("����Ҫ�Ĳο���׼",390,335,16,1,1,RED);
	}
	else if(condition==11)
	{	setlinestyle(0,0,1);			
		puthz16("���ã���������ʹ��Ʊ��������",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("����Ҫԭ������ء����Զ�ͷ��",390,235,16,1,1,RED);
		puthz16("�������ܴ̼��ɼ��������ǣ���",390,255,16,1,1,RED);
		puthz16("��ľ�������繫˾�������ӡ�",390,275,16,1,1,RED);	
		puthz16("��Ϣ���ӣ���˾��Ӫ״����ת��",390,295,16,1,1,RED);		
		puthz16("���ʽ��͵ȡ�",390,315,16,1,1,RED);
	}
	else if(condition==12)
	{	setlinestyle(0,0,1);			
		puthz16("���գ����վ���ָ�ܹ���ʹ�ɼ�",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("�µ�����Ϣ�����Ʊ���й�˾��",390,235,16,1,1,RED);
		puthz16("Ӫҵ���񻯡����н�����������",390,255,16,1,1,RED);
		puthz16("�ʵ��ߡ�����˥�ˡ�ͨ�����͡�",390,275,16,1,1,RED);	
		puthz16("�����˻��ȣ��Լ��������Ρ���",390,295,16,1,1,RED);		
		puthz16("�þ��¡��⽻�ȷ����ʹ�ɼ���",390,315,16,1,1,RED);
		puthz16("���Ĳ�����Ϣ��",390,335,16,1,1,RED);
	}
	else if(condition==13)
	{	setlinestyle(0,0,1);			
		puthz16("��������������������������",390,215,16,1,1,RED);
		puthz16("��������",390,215,16,1,1,WHITE);
		puthz16("��ֵ��",390,235,16,1,1,RED);
	}
	else if(condition==14)
	{	setlinestyle(0,0,1);			
		puthz16("���ȣ������Ǻ�����Գɽ���",390,215,16,1,1,RED);
		puthz16("����",390,215,16,1,1,WHITE);
		puthz16("��ָ�ꡣ����ָ���п��к�ƽ",390,235,16,1,1,RED);
		puthz16("��ÿ���ӵĳɽ������ȥ5����",390,255,16,1,1,RED);
		puthz16("����ƽ��ÿ���ӳɽ���֮�ȡ�",390,275,16,1,1,RED);	
	}
	else if(condition==15)
	{	setlinestyle(0,0,1);			
		puthz16("��ӯ��Ҳ�ơ�����ȡ������ɼ�",390,215,16,1,1,RED);
		puthz16("��ӯ��",390,215,16,1,1,WHITE);
		puthz16("������ʡ���ơ��м�ӯ����",390,235,16,1,1,RED);
		puthz16("�ʣ������ӯ�ʣ�������ӯ����",390,255,16,1,1,RED);
		puthz16("������������ɼ�ˮƽ�Ƿ�",390,275,16,1,1,RED);
		puthz16("�����ָ��֮һ���ɹɼ۳���",390,295,16,1,1,RED);
		puthz16("���ÿ��ӯ��ó����Թ�˾��",390,315,16,1,1,RED);
		puthz16("ֵ������ȹɶ�Ӧռ�������",390,335,16,1,1,RED);
		puthz16("�ó���ͬ�������",390,355,16,1,1,RED); 
	}
	else if(condition==16)
	{	setlinestyle(0,0,1);			
		puthz16("����ֵ������ֵ��ָ��ĳ�ض�",390,215,16,1,1,RED);
		puthz16("����ֵ",390,215,16,1,1,WHITE);
		puthz16("ʱ�����ܹɱ������Ե�ʱ�ɼ�",390,235,16,1,1,RED);
		puthz16("�ó��Ĺ�Ʊ�ܼ�ֵ��",390,255,16,1,1,RED);
	}
	else if(condition==17)
	{	setlinestyle(0,0,1);			
		puthz16("��ͨ��ֵ����ͨ��ֵָ��ĳ��",390,215,16,1,1,RED);
		puthz16("��ͨ��ֵ",390,215,16,1,1,WHITE);
		puthz16("��ʱ���ڵ�ʱ�ɽ��׵���ͨ��",390,235,16,1,1,RED);
		puthz16("�������Ե�ʱ�ɼ۵ó�����ͨ",390,255,16,1,1,RED);
		puthz16("��Ʊ�ܼ�ֵ��",390,275,16,1,1,RED);
	}
}


void draw_()
{
	int i=0;
	
	puthz12("����",30,18,WHITE);
	puthz12("����",95,18,WHITE);
	puthz12("�ּ�",150,18,WHITE);     
	outtextxy(225,20,"%");
	puthz12("�ǵ�",200,18,WHITE);							//ɸѡ���������

	setcolor(LIGHTGRAY);
	setlinestyle(0,0,3);
	line(275,18,275,480);									//�����ɸѡ���

	line(275,160,640,160);
	setcolor(WHITE);
	rectangle(370,190,630,470);								//�������ܿ�
	
	
	i=-1;
	puthz12("�Ƿ�",307,200+i*17,LIGHTGRAY); i++;
	puthz12("�ּ�",307,200+i*17,LIGHTGRAY); i++;
	puthz12("�ǵ�",307,200+i*17,LIGHTGRAY); i++;
	puthz12("���",307,200+i*17,LIGHTGRAY); i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("�ܽ��",300,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("��������",297,200+i*17,LIGHTGRAY);i++;
	puthz12("����",307,200+i*17,LIGHTGRAY);i++;
	puthz12("��ӯ��",300,200+i*17,LIGHTGRAY);i++;
	puthz12("������",300,200+i*17,LIGHTGRAY);i++;
	puthz12("����ֵ",300,200+i*17,LIGHTGRAY);i++;

	for(i=0;i<17;i++)
	{
	   setlinestyle(0,0,1);
	   line(290,196+i*17,350,196+i*17);
	   setlinestyle(0,0,3);
	   rectangle(360,186+i*17,370,186+i*17);
	}														//��������
	
	setcolor(LIGHTGRAY) ;
	line(395,40,555,40);
	line(395,65,555,65);
	line(395,90,555,90);

	for(i=0;i<3;i++)
	{
		line(398,35+i*25,398,45+i*25);
		line(552,35+i*25,552,45+i*25);
	}														//�����߼���������

	setlinestyle(0,0,1);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	bar3d(340,30,390,50,0,0);
	bar3d(340,55,390,75,0,0);
	bar3d(340,80,390,100,0,0);

	bar3d(560,30,610,50,0,0);
	bar3d(560,55,610,75,0,0);
	bar3d(560,80,610,100,0,0);						//�����Ϳ�
	puthz16("���",560,13,16,1,1,YELLOW);
	puthz16("���",340,13,16,1,1,YELLOW) ;
	puthz16("�˳�",610,0,16,1,1,RED) ;

}
