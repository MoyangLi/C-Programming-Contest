
#include"head.h"
#include"chinese.h"
#include"tool.h"
#include"stock.h"
#include"queue.h"
#include"newmenu.h"
#include"mouse.h"
#include"kline.h"
#define MAXSIZE 26
/**********************************************************
Function��	stock_manu_draw

Description��  ����Ʊ����

Input��	   ����Q,INFO * info,����int����a

Output��	  

Return��	  ��

Others��	  y��	0-16���˵�
				18-32ΪĿ¼
				35-460Ϊ��Ʊ�б�ÿֻ��Ʊռ15��һ��26ֻ��Ʊ��
				
		   x��	2  number
				30	identifer
				95	name
				150 �ǵ���
				200 �ǵ�
				265 ������
				315 ���̼�
				365 ��߼�
				415 ��ͼ�
				465 ���ռ�
				515 ���
				565 ����
				
			�˺���������ն��к󻭳�ͼ�Σ����漰�Զ��еĳ�ʼ�����κδ���,����info���κδ���
**********************************************************/

void control_stock(INFO * info,STOINFO * stoinfo,Linkstock * Q,int *mx, int *my,int *mbtn)
{
	int present_line;
	int x,y;
	char a[4][4]={"4s","6s","8s","10s"};
	if(mouse_press(395,445,405,455,mx,my,mbtn))
	{
		setcolor(WHITE);
		setlinestyle(0,0,3);
		line(400,450,520,450);
		
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		
		outtextxy(400,430,a[0]);
		outtextxy(435,430,a[1]);
		outtextxy(470,430,a[2]);
		outtextxy(505,430,a[3]);
		
		setcolor(LIGHTRED);
		line(400,445,400,455);  //画横�?
		outtextxy(400,430,a[0]);
		info->time=4;
		setlinestyle(0,0,1);
	}
	else if(mouse_press(435,445,445,455,mx,my,mbtn))
	{
		setcolor(WHITE);
		setlinestyle(0,0,3);
		line(400,450,520,450);
		
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		
		outtextxy(400,430,a[0]);
		outtextxy(435,430,a[1]);
		outtextxy(470,430,a[2]);
		outtextxy(505,430,a[3]);
		
		setcolor(LIGHTRED);
		line(400,450,440,450);
		line(400,445,400,455);
		line(440,445,440,455);//画短竖线

		outtextxy(435,430,a[1]);
		info->time=6;
		setlinestyle(0,0,1);
	}
	else if(mouse_press(475,445,485,455,mx,my,mbtn))
	{
		setcolor(WHITE);
		setlinestyle(0,0,3);
		line(400,450,520,450);
		
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		
		outtextxy(400,430,a[0]);
		outtextxy(435,430,a[1]);
		outtextxy(470,430,a[2]);
		outtextxy(505,430,a[3]);
		
		setcolor(LIGHTRED);
		line(400,450,480,450);  //画横�?

		line(400,445,400,455);
		line(440,445,440,455);
		line(480,445,480,455);//画短竖线
		outtextxy(470,430,a[2]);
		info->time=8;
		setlinestyle(0,0,1);
	}
	else if(mouse_press(515,445,525,455,mx,my,mbtn))
	{
		setcolor(WHITE);
		setlinestyle(0,0,3);
		line(400,450,520,450);
		
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		
		outtextxy(400,430,a[0]);
		outtextxy(435,430,a[1]);
		outtextxy(470,430,a[2]);
		outtextxy(505,430,a[3]);
		
		setcolor(LIGHTRED);
		line(400,450,520,450);  //画横�?

		line(400,445,400,455);
		line(440,445,440,455);
		line(480,445,480,455);
		line(520,445,520,455);//画短竖线
		outtextxy(505,430,a[3]);
		info->time=10;
		setlinestyle(0,0,1);
	}

	if(mouse_press(0,35,640,35+15*MAXSIZE,mx,my,mbtn))		//��Ʊ�б������
	{
		present_line=(*my-35+15)/15;

		if(present_line<=(Q->rear+MAXSIZE+1-Q->front)%(MAXSIZE+1))
		{
			if(stoinfo->listline!=present_line)
			{
				setcolor(BLACK);			//ԭ���İ����ú����ػ�һ��
				line(5,35-15+11+15*stoinfo->listline,630,35-15+11+15*stoinfo->listline);
				setcolor(WHITE);			//��ǰ����Ĺ�Ʊ���»���
				line(5,35-15+11+15*present_line,630,35-15+11+15*present_line);

				stoinfo->listline=present_line;
			}
			else if(stoinfo->listline==present_line)
			{
				setcolor(BLACK);			//ԭ���İ����ú����ػ�һ��
				line(5,35-15+11+15*stoinfo->listline,630,35-15+11+15*stoinfo->listline);
				stoinfo->listline=0;

				info->layout_last=info->layout;
				info->layout=6;
				strcpy(stoinfo->stockpress,Q->base[(Q->front+present_line-1)%(MAXSIZE+1)].identifer);
				find_stockpress_(stoinfo);
				x=*mx;
				y=*my;
				mousehide(x,y);
			}

		}
	}
	else  if(mouse_press(0,480-18,80,480,mx,my,mbtn))		//��������
	{
		stoinfo->sort=0;
		stock_sort(stoinfo);
		enqueue(Q);

		layout_change(info,stoinfo);
		cleardevice();
		menu_create();
		stock_listdraw(Q,info);
		sort_menu();
	}
	else if(mouse_press(80,480-18,80*2,480,mx,my,mbtn))	//�ּ�����
	{
		if(stoinfo->sort==1)
		{
			stoinfo->sort=2;
		}
		else if(stoinfo->sort==2)
		{
			stoinfo->sort=1;
		}
		else
		{
			stoinfo->sort=1;
		}
		stock_sort(stoinfo);
		enqueue(Q);

		layout_change(info,stoinfo);
		cleardevice();
		menu_create();
		stock_listdraw(Q,info);
		sort_menu();
		setfillstyle(1,LIGHTGRAY);
		bar(570,480-18,640,480);
		if(stoinfo->sort%2)
		{
			puthz12("����",590,480-17,BLACK);
		}
		else
		{
			puthz12("����",590,480-17,BLACK);
		}
	}
	else if(mouse_press(80*2,480-18,80*3,480,mx,my,mbtn))	//�ǵ�������
	{
		if(stoinfo->sort==3)
		{
			stoinfo->sort=4;
		}
		else if(stoinfo->sort==4)
		{
			stoinfo->sort=3;
		}
		else
		{
			stoinfo->sort=3;
		}
		stock_sort(stoinfo);
		enqueue(Q);
		layout_change(info,stoinfo);
		cleardevice();
		menu_create();
		stock_listdraw(Q,info);
		sort_menu();
		setfillstyle(1,LIGHTGRAY);
		bar(570,480-18,640,480);
		if(stoinfo->sort%2)
		{
			puthz12("����",590,480-17,BLACK);
		}
		else
		{
			puthz12("����",590,480-17,BLACK);
		}
	}
	else if(mouse_press(80*3,480-18,80*4,480,mx,my,mbtn))	//����������
	{
		if(stoinfo->sort==5)
		{
			stoinfo->sort=6;
		}
		else if(stoinfo->sort==6)
		{
			stoinfo->sort=5;
		}
		else
		{
			stoinfo->sort=5;
		}
		stock_sort(stoinfo);
		enqueue(Q);
		layout_change(info,stoinfo);
		cleardevice();
		menu_create();
		stock_listdraw(Q,info);
		sort_menu();
		setfillstyle(1,LIGHTGRAY);
		bar(570,480-18,640,480);
		if(stoinfo->sort%2)
		{
			puthz12("����",590,480-17,BLACK);
		}
		else
		{
			puthz12("����",590,480-17,BLACK);
		}
	}
	else if(mouse_press(80*4,480-18,80*5,480*5,mx,my,mbtn))	//�������
	{
		if(stoinfo->sort==7)
		{
			stoinfo->sort=8;
		}
		else if(stoinfo->sort==8)
		{
			stoinfo->sort=7;
		}
		else
		{
			stoinfo->sort=7;
		}
		stock_sort(stoinfo);
		enqueue(Q);
		layout_change(info,stoinfo);
		cleardevice();
		menu_create();
		stock_listdraw(Q,info);
		sort_menu();
		setfillstyle(1,LIGHTGRAY);
		bar(570,480-18,640,480);
		if(stoinfo->sort%2)
		{
			puthz12("����",590,480-17,BLACK);
		}
		else
		{
			puthz12("����",590,480-17,BLACK);
		}
	}
}
void stock_listdraw(Linkstock *Q,INFO *info)
{
    int iround,kround=0;
	double temp;
	char temp1[10];
	int length;

	cleardevice();
	menu_create();
	sort_menu();
	time_(info);

	setcolor(WHITE);
	puthz12("����",30,18,WHITE);
	puthz12("����",95,18,WHITE);
	puthz12("�ּ�",150,18,WHITE);
	outtextxy(225,20,"%");
	puthz12("�ǵ�",200,18,WHITE);
	puthz12("������",265,18,WHITE);
	puthz12("���̼�",315,18,WHITE);
	puthz12("��߼�",365,18,WHITE);
	puthz12("��ͼ�",415,18,WHITE);
	puthz12("���ռ�",465,18,WHITE);
	puthz12("���",515,18,WHITE);
	puthz12("����",565,18,WHITE);

	if(Q->front<=Q->rear)
	{
	  length=Q->rear-Q->front;
	}
	else if(Q->front>Q->rear)
	{
	  length=MAXSIZE-(Q->front-Q->rear)+1;
	}

	for(iround=Q->front;kround<length;iround=(iround+1)%(MAXSIZE+1),kround++)
	{
		setcolor(WHITE);				 //��Ʊ���
		itoa(Q->base[iround].number,temp1,10);
		outtextxy(2,35+15*kround,temp1);


		setcolor(YELLOW);				 //��Ʊ����
		outtextxy(30,35+15*kround,Q->base[iround].identifer);


		puthz12(Q->base[iround].name,95,33+15*kround,YELLOW);  //��Ʊ����


		temp=Q->base[iround].sta[0];			   //�ǵ���
		gcvt(temp,4,temp1);
		regu_float(temp1);

		if(fabs(Q->base[iround].sta[2])<1e-2)	//�ǵ���
		{
			setcolor(WHITE);
			line(150,35+6+15*kround,150+5,35+6+15*kround);
		}

		else if(fabs(temp-Q->base[iround].sta[3])<1e-2)
		{
			setcolor(WHITE);
			outtextxy(150,35+15*kround,temp1);
		}
		else if(temp<Q->base[iround].sta[3])
		{
			setcolor(GREEN);
			outtextxy(150,35+15*kround,temp1);
		}
		else if(temp>Q->base[iround].sta[3])
		{
			setcolor(RED);
			outtextxy(150,35+15*kround,temp1);
		}

		temp=Q->base[iround].sta[1];			   //�ǵ�
		gcvt(temp,4,temp1);
		regu_float(temp1);
		temp1[strlen(temp1)+1]='\0';
		temp1[strlen(temp1)]='%';
		
		if(temp<0)
		{
			setcolor(GREEN);
			outtextxy(200,35+15*kround,temp1);
		}
		else if(temp>0)
		{
			setcolor(RED);
			outtextxy(200,35+15*kround,temp1);
		}
		
		else if(fabs(Q->base[iround].sta[2])<1e-6)	
		{
			setcolor(WHITE);
			line(200,35+6+15*kround,200+5,35+6+15*kround);
		}
		else if(fabs(temp)<1e-6)
		{
			setcolor(WHITE);
			outtextxy(200,35+15*kround,temp1);
		}

		temp=Q->base[iround].sta[2];		 	//������	
		gcvt(temp,4,temp1);
		regu_float(temp1);
		if(fabs(temp)<1e-6)
		{
			setcolor(WHITE);
			line(265,35+6+15*kround,265+5,35+6+15*kround);
		}
		else
		{
			setcolor(WHITE);
			outtextxy(265,35+15*kround,temp1);
		}

		temp=Q->base[iround].sta[3];      //���̼�
		gcvt(temp,4,temp1);
		regu_float(temp1);
		
		if(temp>Q->base[iround].sta[6])		   //���̼۾������ռ���ɫ
		{
			setcolor(RED);
			outtextxy(315,35+15*kround,temp1);
		}
		else if(temp<Q->base[iround].sta[6])
		{
			setcolor(GREEN);
			outtextxy(315,35+15*kround,temp1);
		}
		else
		{
			setcolor(WHITE);
			outtextxy(315,35+15*kround,temp1);
		}

		temp=Q->base[iround].sta[4];
		gcvt(temp,4,temp1);
		regu_float(temp1);
		
		if(temp>Q->base[iround].sta[6])			//��߼������ռ۱ȽϾ�����߼���ɫ
		{
			setcolor(RED);
			outtextxy(365,35+15*kround,temp1);
		}
		else if(temp<Q->base[iround].sta[6])
		{
			setcolor(GREEN);
			outtextxy(365,35+15*kround,temp1);
		}
		else if(fabs(Q->base[iround].sta[2])<1e-6)	//������
		{
			setcolor(WHITE);
			line(365,35+6+15*kround,365+5,35+6+15*kround);
		}
		else
		{
			setcolor(WHITE);
			outtextxy(365,35+15*kround,temp1);
		}

		temp=Q->base[iround].sta[5];
		gcvt(temp,4,temp1);
		regu_float(temp1);
		
		if(temp>Q->base[iround].sta[6])  //��ͼ������ռ۱ȽϾ�����ͼ���ɫ
		{
			setcolor(RED);
			outtextxy(415,35+15*kround,temp1);
		}
		else if(temp<Q->base[iround].sta[6])
		{
			setcolor(GREEN);
			outtextxy(415,35+15*kround,temp1);
		}
		else if(fabs(Q->base[iround].sta[2])<1e-6)	//������
		{
			setcolor(WHITE);
			line(415,35+6+15*kround,415+5,35+6+15*kround);
		}
		else
		{
			setcolor(WHITE);
			outtextxy(415,35+15*kround,temp1);
		}

		setcolor(WHITE);				 //������
		temp=Q->base[iround].sta[6];
		gcvt(temp,4,temp1);
		regu_float(temp1);
		
		outtextxy(465,35+15*kround,temp1);

		temp=Q->base[iround].sta[7];	 
		gcvt(temp,4,temp1);
		regu_float(temp1);
		
		if(fabs(temp)<1e-6)           //���
		{
			setcolor(WHITE);
			line(515,35+6+15*kround,515+5,35+6+15*kround);
		}
		else
		{
			setcolor(WHITE);
			outtextxy(515,35+15*kround,temp1);
		}

		temp=Q->base[iround].sta[8];
		gcvt(temp,4,temp1);
		regu_float(temp1);
		
		if(temp>Q->base[iround].sta[6])  //���������ռ۱Ƚ�
		{
			setcolor(RED);
			outtextxy(565,35+15*kround,temp1);
		}
		else if(temp<Q->base[iround].sta[6])
		{
			setcolor(GREEN);
			outtextxy(565,35+15*kround,temp1);
		}
		else if(fabs(Q->base[iround].sta[2])<1e-6)	//������
		{
			setcolor(WHITE);
			line(565,35+6+15*kround,565+5,35+6+15*kround);
		}
		else
		{
			setcolor(WHITE);
			outtextxy(565,35+15*kround,temp1);
		}
	}
}

void time_(INFO * info)
{
	int i;
	char a[4][4]={"4s","6s","8s","10s"};

	puthz16("���ݸ���ʱ��",540,440,16,1,1,WHITE);
	setcolor(WHITE);

	setlinestyle(0,0,3);
	line(400,450,520,450);
	line(400,445,400,455);   //4s
	line(440,445,440,455);   //6s
	line(480,445,480,455);   //8s
	line(520,445,520,455);   //10s
	setlinestyle(0,0,1);

	setcolor(WHITE);
	for(i=0;i<4;i++)
	{
		outtextxy(400+35*i,430,a[i]);
								//打印数字
	}
	if(info->time==4)
	{
		setcolor(WHITE);
		line(400,450,520,450);
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		setlinestyle(0,0,3);
		setcolor(WHITE);
		line(400,450,520,450);			//重画粗线
		setcolor(LIGHTRED);
		line(400,445,400,455);  //画横�?
		outtextxy(400,430,a[0]);
	}
	else if(info->time==6)
	{
		setcolor(WHITE);
		line(400,450,520,450);
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		setlinestyle(0,0,3);
		setcolor(WHITE);
		line(400,450,520,450);			//重画粗线
		setcolor(LIGHTRED);
		line(400,450,440,450);

		line(400,445,400,455);
		line(440,445,440,455);//画短竖线

		outtextxy(435,430,a[1]);
	}
	else if(info->time==8)
	{
		setcolor(WHITE);
		line(400,450,520,450);
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		setlinestyle(0,0,3);
		setcolor(WHITE);
		line(400,450,520,450);		   //重画粗线
		setcolor(LIGHTRED);
		line(400,450,480,450);  //画横�?

		line(400,445,400,455);
		line(440,445,440,455);
		line(480,445,480,455);//画短竖线
		outtextxy(470,430,a[2]);
	}
	else if(info->time==10)
	{
		setcolor(WHITE);
		line(400,450,520,450);
		line(400,445,400,455);   //4s
		line(440,445,440,455);   //6s
		line(480,445,480,455);   //8s
		line(520,445,520,455);   //10s
		setlinestyle(0,0,3);
		setcolor(WHITE);
		line(400,450,520,450);           //重画粗线
		setcolor(LIGHTRED);
		line(400,450,520,450);  //画横�?

		line(400,445,400,455);
		line(440,445,440,455);
		line(480,445,480,455);
		line(520,445,520,455);//画短竖线
		outtextxy(505,430,a[3]);
	}
	setlinestyle(0,0,1);
}

void stock_sort(STOINFO * stoinfo)
{
	char address[35];
	char pointer[30]="data\\database\\";
	char sym[35];
	char sor[35];
	FILE * fsymbolic;
	FILE * fstock;
	FILE * fsort;

	char symbolic[300][7];
	long int data[300];
	char temp[7];
	float tempdata;
	
	int iround,kround;
	int target;
	int sortline;
	
	strcpy(sym,"data\\database\\symbolic.txt");
	if((fsymbolic=fopen(sym,"rb"))==NULL)
	{
		printf("stock_sort: error opening list.txt(out)\n");
		getch();
	}
	
	if(stoinfo->sort==0)
	{
		target=-1;
		sortline=1;
	}
	else if(stoinfo->sort==1||stoinfo->sort==2)
	{
		target=0;
		if(stoinfo->sort==1)
		{
			sortline=0;
		}
		else if(stoinfo->sort==2)
		{
			sortline=1;
		}
	}
	else if(stoinfo->sort==3||stoinfo->sort==4)
	{
		target=1;
		if(stoinfo->sort==3)
		{
			sortline=0;
		}
		else if(stoinfo->sort==4)
		{
			sortline=1;
		}
	}
	else if(stoinfo->sort==5||stoinfo->sort==6)
	{
		target=2;
		if(stoinfo->sort==5)
		{
			sortline=0;
		}
		else if(stoinfo->sort==6)
		{
			sortline=1;
		}
	}
	else if(stoinfo->sort==7||stoinfo->sort==8)
	{
		target=7;
		if(stoinfo->sort==7)
		{
			sortline=0;
		}
		else if(stoinfo->sort==8)
		{
			sortline=1;
		}
	}
	
	for(iround=0;;iround++)                       
	{
	
	    if(fread(temp,6,1,fsymbolic)!=0)
		{
			temp[6]='\0';
			strcpy(symbolic[iround],temp);
			
			if(target!=-1)
			{
				strcpy(address,pointer);
				strcat(address,temp);
				strcat(address,"\\list.txt");
				
				if((fstock=fopen(address,"rb"))==NULL)  
				{
					printf("stock_sort: error opening list.txt(out)\n");
					getch();
				}
				fseek(fstock,sizeof(int)+10+6+target*sizeof(float),SEEK_SET);         ///由target值寻找相应的不同种类指标�?
				fread(&tempdata,sizeof(float),1,fstock);
				data[iround]=(long int)(tempdata*100);                                ///将所得指标值赋给data[iround]
				
				fclose(fstock);
			}
			else if(target==-1)
			{
				data[iround]=atol(temp);
			}                                                   ///由target值给data[iround]赋�?
			
		}
		else
		{
			break;
		}
		temp[0]='\0';
	}
	fclose(fsymbolic);
	
	data_sorting(symbolic,data,sortline,iround);              ///对data[300]及symbolic[300][7]排序
	if((fsort=fopen(sym,"wb"))==NULL)
	{
		printf("stock_sort: error opening list.txt(out)\n");
		getch();
	}
	for(kround=0;kround<iround;kround++)
	{
		fwrite(symbolic[kround],6,1,fsort);
	}
	fclose(fsort);
}


void data_sorting(char (*symbolic)[7],long int *data,int sortline,int length)
{
	char tempsym[7];
	char (*point)[7];
	long int most;
	int mostj;

	int iround,kround;
	
	if(sortline==0)
	{
		for(iround=0;iround<length;iround++)
		{
			most=data[iround];
			mostj=iround;
			for(kround=iround+1;kround<length;kround++)
			{
				if(most<data[kround])
				{
					most=data[kround];
					mostj=kround;
				}
			}                                                   
			if(mostj!=iround)
			{
				data[mostj]=data[iround];
				data[iround]=most;                             
				
				strcpy(tempsym,symbolic[iround]);
				strcpy(symbolic[iround],symbolic[mostj]); 
		     	strcpy(symbolic[mostj],tempsym);                
			}
		}
	}
	else if(sortline==1)
	{
		for(iround=0;iround<length;iround++)
		{
			most=data[iround];
			mostj=iround;
			for(kround=iround+1;kround<length;kround++)
			{
				if(most>data[kround])
				{
					most=data[kround];
					mostj=kround;
				}
			}
			
			if(mostj!=iround)
			{
				data[mostj]=data[iround];
				data[iround]=most;
				
				strcpy(tempsym,symbolic[iround]);
				strcpy(symbolic[iround],symbolic[mostj]);
				strcpy(symbolic[mostj],tempsym);
			}
		}
	}
}
