#include"head.h"
#include"CHINESE.h"
#include<string.h>
#include<stdlib.h>
#include"tool.h"


void save_picture(int x1,int y1,int x2,int y2)
{
	char address[50]="data\\other\\picture.son";
	FILE * fp;
	int iround,jround;
	int pixel;
	
	if((fp=fopen(address,"wb"))==NULL)
	{
		printf("ERROR OPENING %c.\n");
		getch();
	}
	
	for(iround=y1;iround<=y2;iround++)
	{
		for(jround=x1;jround<=x2;jround++)
		{
			pixel=getpixel(jround,iround);
			fwrite(&pixel,sizeof(int),1,fp);
		}
	}
	
}

void put_picture(int x1,int y1,int x2,int y2)
{
	char address[50]="data\\other\\picture.son";
	FILE * fp;
	int iround,jround;
	int pixel;
	
	if((fp=fopen(address,"rb"))==NULL)
	{
		printf("ERROR OPENING %c.\n");
		getch();
	}
	
	for(iround=y1;iround<=y2;iround++)
	{
		for(jround=x1;jround<=x2;jround++)
		{
			fread(&pixel,sizeof(int),1,fp);
			putpixel(jround,iround,pixel);
		}
	}
	
}

void regu_float(char *a)
{
	int iround,kround;
	int point;
	int length;
	
	if(a[0]=='.')					//小数点前没有整数部分
	{
		for(iround=length;iround>0;iround++)
		{
			a[iround]=a[iround-1];
		}
		a[0]='0';		
	}
	
	for(iround=0;;iround++)			
	{
		if(a[iround]=='.')			//找到小数点位�?
		{
			point=iround+1;
			break;
		}
		else if(a[iround]=='\0')	//没有小数�?
		{
			point=-10;
			break;
		}
	}
	
	length=strlen(a);
	if(point==-10)				//只有整数
	{
		a[length]='.';
		a[length+1]='0';
		a[length+2]='0';
		a[length+3]='\0';
	}
	else if((length-point)>2)			//不止两位小数
	{
		a[point+2]='\0';
	}
	else if((length-point)==1)		//只有一位小�?
	{
		a[length]='0';
		a[length+1]='\0';
	}
	else if((length-point)==0)		//小数点后没位�?
	{
		a[length]='0';
		a[length+1]='0';
		a[length+2]='\0';
	}

	
}


float gauss_rand()
{
	double x1,x2,x3;

	x1=rand()/(RAND_MAX+1.0);
	x2=rand()/(RAND_MAX+1.0);

	x3=sqrt(-2.0*log(x1))*sin(2.0*3.1415926*x2);

	return x3*0.3;
}

/**********************************************************
data_updata()  �������ݸ���
**********************************************************/
void data_updata()                       
{
	float data[9];
	float randnum,calculate1,calculate2,calculate3;
	FILE * fsymbolic;		
	FILE * fstock;			
	
	char address[35];
	char pointer[30]="data\\database\\";
	char temp[7];
	
	int number;
	char symbolic[7];
	char name[10];
	
	int iround,jround,sum;
	
	fsymbolic=fopen("data\\database\\symbolic.txt","rb");

	for(iround=0;;iround++)
	{
		if(fread(temp,6,1,fsymbolic)!=0)
		{
			temp[6]='\0';
			strcpy(address,pointer);
			strcat(address,temp);
			strcat(address,"\\list.txt");
	
            if((fstock=fopen(address,"rb"))==NULL)                ///fstock打开文件data\\database\\000001\\list.txt
			{
		        printf("data_updata: error opening list.txt(out)\n");
		        getch();
	        }
			fread(&number,sizeof(int),1,fstock);         ///股票号码
			fread(symbolic,6,1,fstock);                  
			fread(name,10,1,fstock);                     ///股票名称
			fread(data,sizeof(float),9,fstock);          ///股票数据
		
			fclose(fstock);
			
			if(fabs(data[2])<1e-2)
			{
				continue;
			}
			else
			{
				randnum=gauss_rand();
		
				data[0]=data[0]*(1+0.07*randnum);
				if((data[0]-data[3]*1.15)>0)					//更新现价  data[0]
				{
					data[0]=data[3]*1.15;
				}
				else if((data[0]-data[3]*0.85)<0)
				{
					data[0]=data[3]*0.85;
				}
		
				data[1]=(data[0]-data[3])*100/data[3];		//更新涨跌 data[1]
			
				if((data[0]-data[4])>0)						//更新最高价    data[4]
				{
					data[4]=data[0];
				}
		
				if((data[0]-data[5])<0)						//更新最低价    data[5]
				{
					data[5]=data[0];
				}
		
				if((fstock=fopen(address,"wb"))==NULL) 
				
			    {
					printf("data_updata: error opening list.txt(in)\n");
					getch();
				}
				
				fwrite(&number,sizeof(int),1,fstock);       
				fwrite(symbolic,6,1,fstock);
				fwrite(name,10,1,fstock);
				fwrite(data,sizeof(float),9,fstock);
		
				fclose(fstock);
			}
		}
		else
		{
			break;
		}
	}
	
	fclose(fsymbolic);
	
}

void layout_change(INFO * info,STOINFO * stoinfo)
{
	info->menu_flag=0;
	//info->search[0]='\0';
	//info->search_flag=0;
	stoinfo->style=4;
	
}

/**********************************************************
  help_control(INFO *info,STOINFO * stoinfo,int *mx,int *my,int *mbutt)�����������
**********************************************************/
void help_control(INFO *info,STOINFO * stoinfo,int *mx,int *my,int *mbutt)
{   while(1)
    {
        newmouse(mx,my,mbutt);
	if(mouse_press(640/2-66,480-50-12-3-20,640/2-66+24,480-50-12-3-20+2+6,mx,my,mbutt))
	{
		help_draw1();           //helpdraw������Լ����������˵�
		layout_change(info,stoinfo);
	}
	else if(mouse_press(640/2-30,480-50-12-3-20,640/2-30+24,480-50-12-3-20+2+6,mx,my,mbutt))
	{
		help_draw2();
		layout_change(info,stoinfo);
	}
	else if(mouse_press(640/2+6,480-50-12-3-20,640/2+6+24,480-50-12-3-20+2+6,mx,my,mbutt))
	{
		help_draw3();
		layout_change(info,stoinfo);
	}
	else if(mouse_press(640/2+42,480-50-12-3-20,640/2+42+24,480-50-12-3-20+2+6,mx,my,mbutt))
	{
		help_draw4();
		layout_change(info,stoinfo);
	}
	else if(mouse_press(640/2+129,50+12+2,640/2+129+24+1,50+12+2+12+2,mx,my,mbutt))
	{
		cleardevice();
		layout_change(info,stoinfo);

			info->layout=0;

				break;

	}
	}
}

/**********************************************************
  help_draw1(INFO *info)   ������һҳ������
**********************************************************/
void help_draw1()   //������һҳ������
{
	int r=12;
	int dx=160;
	int dy=50;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *str0="����";
	char *page[]={"[1]","[2]","[3]","[4]",0};
	char *str3="�˳�";

	char *simplename[]={
					"��ӭʹ��֤ȯͶ�ʾ��߷���ϵͳ",
					"��ϵͳΪ֤ȯͶ�����ṩ֤ȯ�г��ϵĸ��ֹ�Ʊ�����������û���ѯ��Ʊʵʱ���ơ��������ݡ���ʷ���飬���й�Ʊ���ף�����ϵͳ������Ͷ��ģ�ͶԱȹ�Ʊ���Ƽ�Ͷ����ϣ��������и��ֿ�ݲ�����ʽ�������������ϵĳ���������ơ�ף��ʹ����죡",
					"�����з��գ�Ͷ�����������ϵͳ����������Ͷ�ʼ���ϵͳ���������κ�����������������ʹ�á�",
					"��������ī�� ��˼ܲ 2018.10.10",
					"�ڴ�һ����л���������ǵĸ�λ��ʦ��ͬѧ��",
					0};

	cleardevice();

	setcolor(BLUE);
	rectangle(dx,dy,640-dx,480-dy);

	puthz16(str0,maxx/2-16,dy+24,16,1,1,WHITE);



	putnews(simplename[0],maxx/2-7*12,dy+62,WHITE,maxx-dx-r-12);

	putnews(simplename[1],dx+24+6,dy+62+30,WHITE,maxx-dx-r-12);

	putnews(simplename[2],dx+24+6,dy+62+30+16*6,WHITE,maxx-dx-r-12);

	putnews(simplename[3],dx+24+6,dy+62+30+16*6+16*6,WHITE,maxx-dx-r-12);

	putnews(simplename[4],dx+24+6,dy+62+30+16*6+16*6+16*2,WHITE,maxx-dx-r-12);


	setcolor(LIGHTRED);
	rectangle(maxx/2+129,dy+r+2,maxx/2+129+24+1,dy+r+2+12+2);
	puthz12(str3,maxx/2+130,dy+r+3,LIGHTRED);

	setcolor(LIGHTRED);
	outtextxy(maxx/2-66,maxy-dy-r-3-20+2,page[0]);
	setcolor(YELLOW);
	outtextxy(maxx/2-30,maxy-dy-r-3-20+2,page[1]);
	outtextxy(maxx/2+6,maxy-dy-r-3-20+2,page[2]);
	outtextxy(maxx/2+42,maxy-dy-r-3-20+2,page[3]);
}

/**********************************************************
  help_draw2(INFO *info)   �����ڶ�ҳ������
**********************************************************/
void help_draw2()   //�����ڶ�ҳ������
{
	int r=12;
	int dx=160;
	int dy=50;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *page[]={"[1]","[2]","[3]","[4]",0};
	char *str3="�˳�";

	char *simplename[]={
						"��ϸ˵����",
						"1.ϵͳ��Ҫ���棺",
						"��֤A�ɽ��棨F2��",
						"��ָ֤�����棨F3��",
						"���ָ�����棨F4��",
						"��ѡ�ɽ��棨F5��",
						"��ƱK�߽��棨F6��",
						"���׽��棨F7��",
						"��Ʊ�ԱȽ��棨F8��",
						"����Ƽ����棨F9��",
						"�������棨F10��",
						0};
	char *introduction[]={
						"",
						"",
						"���鿴��֤A��",
						"���鿴��ָ֤��",
						"���鿴���ָ��",
						"���鿴��ѡ��",
						"���鿴��ƱK��",
						"�����й�Ʊ����",
						"����ѡ���Ĺ�Ʊ���жԱ�",
						"������Ͷ��ģ��Ϊ���Ƽ�Ͷ�����",
						"���鿴ϵͳʹ��˵��",
						0};
	

	//�ܵ�ҳ�汳��
	cleardevice();
	setcolor(BLUE);
	rectangle(dx,dy,maxx-dx,maxy-dy);        //������Ҫ�Ĵ����


	//����ڶ�ҳ������

	puthz12(simplename[0],dx+12,dy+r+16,WHITE);

	puthz12(simplename[1],dx+12,dy+r+18+36,WHITE);

	puthz12(simplename[2],dx+12,dy+r+42+24*2,WHITE);
	puthz12(introduction[2],dx+12+124,dy+r+42+24*2,WHITE);

	puthz12(simplename[3],dx+12,dy+r+42+24*3,WHITE);
	puthz12(introduction[3],dx+12+124,dy+r+42+24*3,WHITE);

	puthz12(simplename[4],dx+12,dy+r+42+24*4,WHITE);
	puthz12(introduction[4],dx+12+124,dy+r+42+24*4,WHITE);

	puthz12(simplename[5],dx+12,dy+r+42+24*5,WHITE);
	puthz12(introduction[5],dx+12+124,dy+r+42+24*5,WHITE);

	puthz12(simplename[6],dx+12,dy+r+42+24*6,WHITE);
	puthz12(introduction[6],dx+12+124,dy+r+42+24*6,WHITE);

	puthz12(simplename[7],dx+12,dy+r+42+24*7,WHITE);
	puthz12(introduction[7],dx+12+124,dy+r+42+24*7,WHITE);

	puthz12(simplename[8],dx+12,dy+r+42+24*8,WHITE);
	puthz12(introduction[8],dx+12+124,dy+r+42+24*8,WHITE);

	puthz12(simplename[9],dx+12,dy+r+42+24*9,WHITE);
	puthz12(introduction[9],dx+12+124,dy+r+42+24*9,WHITE);

	puthz12(simplename[10],dx+12,dy+r+42+24*10,WHITE);
	puthz12(introduction[10],dx+12+124,dy+r+42+24*10,WHITE);


/*
	puthz12(simplename[7],dx+12,dy+r+42+24*7,WHITE);
	puthz12(introduction[7],dx+12+124,dy+r+42+24*7,WHITE);

	puthz12(simplename[8],dx+12,dy+r+42+24*8,WHITE);
	puthz12(introduction[8],dx+12+124,dy+r+42+24*8,WHITE);

	puthz12(simplename[9],dx+12,dy+r+42+24*9,WHITE);
	puthz12(introduction[9],dx+12+124,dy+r+42+24*9,WHITE);

	puthz12(simplename[10],dx+12,dy+r+42+24*10,WHITE);
	puthz12(introduction[10],dx+12+124,dy+r+42+24*10,WHITE);

	puthz12(simplename[11],dx+12,dy+r+42+24*11,WHITE);
	puthz12(introduction[11],dx+12+124,dy+r+42+24*11,RED); */


//�������Ժ�Ҫ��

	//��ʾ�˳���
	setcolor(LIGHTRED);
	rectangle(maxx/2+129,dy+r+2,maxx/2+129+24+1,dy+r+2+12+2);
	puthz12(str3,maxx/2+130,dy+r+3,LIGHTRED);   //��ʾ�˳�

	setcolor(LIGHTRED);
	outtextxy(maxx/2-30,maxy-dy-r-3-20+2,page[1]);
	setcolor(YELLOW);
	outtextxy(maxx/2-66,maxy-dy-r-3-20+2,page[0]);
	outtextxy(maxx/2+6,maxy-dy-r-3-20+2,page[2]);
	outtextxy(maxx/2+42,maxy-dy-r-3-20+2,page[3]);
}

/**********************************************************
  help_draw3(INFO *info)   ��������ҳ������
**********************************************************/
void help_draw3()
{
	int dx=160;
	int dy=50;
	int r=12;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *page[]={"[1]","[2]","[3]","[4]",0};
	//char *str2="��һҳ";
	char *str3="�˳�";

	char *simplename[]={
						"2.������ݲ�����",
						"��Ʊ���ٲ��ң�",
						"ѡ��ָ������",
						"�����˵�",
						"���̿�ݼ�",
						0};
	char *introduction[]={
						"",
						"�û�����С����������λ��Ʊ���룬ϵͳ�Զ�������Ӧ�Ĺ�Ʊ�������û�ѡ����Ʊ�鿴��ϸ��Ϣ",
						"�û������ڻ���300����������Ŀ¼��ϵͳ���Զ���������/�����������û�ɸѡ��Ʊ��Ŀǰ�����ڴ��룬�ּۣ��ǵ����������ʣ��������ָ��������",
						"�û���ֱ���ڽ�������Ļ�Ϸ��Ĳ˵�ѡ����ֹ���",
						"�û���ֱ�����κν��棨����¼�����⣩ʹ�ü��̵Ĺ��ܼ����и�������л��������ݼ����Ϸ���ϸ˵��",
						0};


	//�ܵ�ҳ�汳��

	cleardevice();
	setcolor(BLUE);
	rectangle(dx,dy,maxx-dx,maxy-dy);        //������Ҫ�Ĵ����


	//�������ҳ������

	puthz12(simplename[0],dx+12,dy+r+16,WHITE);

	puthz12(simplename[1],dx+18,dy+r+16+30,WHITE);
	putnews(introduction[1],dx+24+6,dy+r+16+30+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[2],dx+18,dy+r+16+30+(16*4+6),WHITE);
	putnews(introduction[2],dx+24+6,dy+r+16+30+(16*4+6)+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[3],dx+18,dy+r+16+30+(16*4+6)+(16*5+6),WHITE);
	putnews(introduction[3],dx+24+6,dy+r+16+30+(16*4+6)+(16*5+6)+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[4],dx+18,dy+r+16+30+(16*4+6)+(16*5+6)+(16*3+6),WHITE);
	putnews(introduction[4],dx+24+6,dy+r+16+30+(16*4+6)+(16*5+6)+(16*3+6)+16,WHITE,maxx-dx-r-12);



	setcolor(LIGHTRED);
	rectangle(maxx/2+129,dy+r+2,maxx/2+129+24+1,dy+r+2+12+2);
	puthz12(str3,maxx/2+130,dy+r+3,LIGHTRED);


	setcolor(LIGHTRED);
	outtextxy(maxx/2+6,maxy-dy-r-3-20+2,page[2]);
	setcolor(YELLOW);
	outtextxy(maxx/2-66,maxy-dy-r-3-20+2,page[0]);
	outtextxy(maxx/2-30,maxy-dy-r-3-20+2,page[1]);
	outtextxy(maxx/2+42,maxy-dy-r-3-20+2,page[3]);
}

/**********************************************************
  help_draw4(INFO *info)   ��������ҳ������
**********************************************************/
void help_draw4()
{
	 int dx=160;
	int dy=50;
	int r=12;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *page[]={"[1]","[2]","[3]","[4]",0};
	char *str3="�˳�";

	char *simplename[]={
						"3.��ϵͳ����ɫ���ܣ�",
						"ʵʱģ�⣺",
						"��ѡ�ɰ�飺",
						"Ͷ������Ƽ���",
						0};
	char *introduction[]={
						"",
						"�û�����ѡ��ʵʱģ��ʱ�䣬ϵͳ�������ʱ����йɼ۱䶯ģ��",
						"�û��ɽ��ض���Ʊ������ѡ�ɣ����Զ��ύ����ѡ���б��У������û��鿴�ض������ã���Ʊ",
						"��ϵͳʹ������Ͷ������гɳ���ϣ���ֵ��ϣ���ֵ�ɳ�����������ģ�ͽ�������ѡ�ɣ���Ϊ�û��ṩ��Ʊ��ϸ��Ϣ",
						0};

	//�ܵ�ҳ�汳��
	cleardevice();
	setcolor(BLUE);
	rectangle(dx,dy,640-dx,480-dy);
	//�������ҳ������

	puthz12(simplename[0],dx+12,dy+r+16,WHITE);

	puthz12(simplename[1],dx+18,dy+r+16+30,WHITE);
	putnews(introduction[1],dx+24+6,dy+r+16+30+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[2],dx+18,dy+r+16+30+(16*3+6),WHITE);
	putnews(introduction[2],dx+24+6,dy+r+16+30+(16*3+6)+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[3],dx+18,dy+r+16+30+(16*3+6)+(16*3+6),WHITE);
	putnews(introduction[3],dx+24+6,dy+r+16+30+(16*3+6)+(16*3+6)+16,WHITE,maxx-dx-r-12);

  //	puthz12(simplename[4],dx+18,dy+r+16+30+(16*3+6)+(16*3+6)+(16*4+6),WHITE);
  //	putnews(introduction[4],dx+24+6,dy+r+16+30+(16*3+6)+(16*3+6)+(16*4+6)+16,WHITE,maxx-dx-r-12);
	
	
	//��ʾ�˳���
	setcolor(LIGHTRED);
	rectangle(maxx/2+129,dy+r+2,maxx/2+129+24+1,dy+r+2+12+2); 
	puthz12(str3,maxx/2+130,dy+r+3,LIGHTRED);   //��ʾ�˳�
	//��ʾҳ��[1],[2],[3]
	//line(maxx/2,0,maxx/2,480);����
	
	setcolor(LIGHTRED);
	outtextxy(maxx/2+42,maxy-dy-r-3-20+2,page[3]);
	
	setcolor(YELLOW);
	outtextxy(maxx/2-66,maxy-dy-r-3-20+2,page[0]);
	outtextxy(maxx/2-30,maxy-dy-r-3-20+2,page[1]);
	outtextxy(maxx/2+6,maxy-dy-r-3-20+2,page[2]);
}