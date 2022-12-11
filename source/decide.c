#include"head.h"
#include"mouse.h"
#include"newmenu.h"
#include"chinese.h"
#include"decide.h"
#include"tool.h"
#include"line.h"
/**********************************************************
Copyright (C) 
File name:		deicde.c
Author:			
Description��	Ͷ�ʾ��߽�����غ���

Function List��	decide_control			���߽���������
				

				deicde_choose_draw		��Ͷ�ʾ��߽���
				deicde_choose_anal

				decide_compare_draw		�����Ʊ�ԱȵĹ�Ʊ���жԱ�
				decide_add				��Ŀ���Ʊ����������У�ͬʱ�������ݵ�����㣩
				decide_delate			��Ŀ���Ʊ�ӷ�������ɾ����ͬʱ�������ݵ�����㣩

				make_chart				������ͳ��ͼ
				make_bar				*����װ

��Ҫ���Ƶ�ֵ�У�
**********************************************************/

/**********************************************************
decide������
	���������  �������ԱȽ���
				  ��������������
				  ���ɾ���Աȹ�Ʊ
				  �����Ʊ����Ա�
				  ���ѡ��Ͷ�ʷ��
				  �����ʼ����

**********************************************************/


void control_decide(INFO *info,STOINFO *stoinfo,int *mx,int *my,int *mbtn)
{
	if(info->layout==9)
	{
		if(mouse_press(5,470-17,5+53,470,mx,my,mbtn))		//��������Ʊ�ԱȽ���
		{
			info->layout_last=info->layout;
			info->layout=8;
			layout_change(info,stoinfo);
			decide_compare_draw(stoinfo);
		}


		if(mouse_press(10,80,130,100,mx,my,mbtn))		//ѡ���������
		{
			stoinfo->style=0;
			decide_choose_draw_init();
		}
		if(mouse_press(10,130,130,150,mx,my,mbtn))		//ѡ��ͷ�����
		{
			stoinfo->style=1;
			decide_choose_draw_init();
		}
		if(mouse_press(10,180,130,200,mx,my,mbtn))	//ѡ����������ۺ���
		{
			stoinfo->style=2;
			decide_choose_draw_init();
		}
		if(mouse_press(30,250,110,270,mx,my,mbtn))		//��ʼ����
		{
			if(stoinfo->style==0||stoinfo->style==1||stoinfo->style==2)
			{
				deicde_choose_anal(stoinfo);
			}
		}


		if(stoinfo->style==0||stoinfo->style==1||stoinfo->style==2)
		{
		  	if(mouse_press(570,110,600,125,mx,my,mbtn))
			{
				info->layout=6;
				strcpy(stoinfo->stockpress,stoinfo->combine[0]);
				find_stockpress_(stoinfo);
			}
			else if(mouse_press(490,110,490+30,125,mx,my,mbtn))
			{
				info->layout=7;
			}
			else if(mouse_press(530,110,560,125,mx,my,mbtn))
			{
				decide_add(stoinfo,stoinfo->combine[0]);
				info->layout_last=info->layout;
				info->layout=8;
				layout_change(info,stoinfo);
				decide_compare_draw(stoinfo);
			}

			else if(mouse_press(570,110+105,600,125+105,mx,my,mbtn))
			{
				info->layout=6;
				strcpy(stoinfo->stockpress,stoinfo->combine[1]);
				find_stockpress_(stoinfo);
			}
			else if(mouse_press(490,110+105,490+30,125+105,mx,my,mbtn))
			{
				info->layout=7;
			}
			else if(mouse_press(530,110+105,560,125+105,mx,my,mbtn))
			{
				decide_add(stoinfo,stoinfo->combine[1]);
				info->layout_last=info->layout;
				info->layout=8;
				layout_change(info,stoinfo);
				decide_compare_draw(stoinfo);
			}

	  		else if(mouse_press(570,110+105*2,600,125+105*2,mx,my,mbtn))
			{
				info->layout=6;
				strcpy(stoinfo->stockpress,stoinfo->combine[2]);
				find_stockpress_(stoinfo);
			}
			else if(mouse_press(490,110+105*2,490+30,125+105*2,mx,my,mbtn))
			{
				info->layout=7;
			}
			else if(mouse_press(530,110+105*2,560,125+105*2,mx,my,mbtn))
			{
				decide_add(stoinfo,stoinfo->combine[2]);
				info->layout_last=info->layout;
				info->layout=8;
				layout_change(info,stoinfo);
				decide_compare_draw(stoinfo);
			}

			else if(mouse_press(570,110+105*3,600,125+105*3,mx,my,mbtn))
			{
				info->layout=6;
				strcpy(stoinfo->stockpress,stoinfo->combine[3]);
				find_stockpress_(stoinfo);
			}
			else if(mouse_press(490,110+105*3,490+30,125+105*3,mx,my,mbtn))
			{
				info->layout=7;
			}
			else if(mouse_press(530,110+105*3,560,125+105*3,mx,my,mbtn))
			{
				decide_add(stoinfo,stoinfo->combine[3]);
				info->layout_last=info->layout;
				info->layout=8;
				decide_compare_draw(stoinfo);
			}
		}
	}
	else if(info->layout==8)
	{
		if(mouse_press(5,470-17,5+53,470,mx,my,mbtn))		//��������Ʊ�Ƽ�����
		{
			info->layout_last=info->layout;
			info->layout=9;
			layout_change(info,stoinfo);
			decide_choose_draw_init();
		}
		if(mouse_press(500,402,524,418,mx,my,mbtn))		//ɾ�ȽϹ�Ʊ�б��һ��
		{
			decide_delate(stoinfo,stoinfo->choose[0]);
			decide_compare_draw(stoinfo);
		}
		if(mouse_press(500,422,524,438,mx,my,mbtn))		//ɾ�ȽϹ�Ʊ�б�ڶ���
		{
			decide_delate(stoinfo,stoinfo->choose[1]);
			decide_compare_draw(stoinfo);

		}
		if(mouse_press(500,442,524,458,mx,my,mbtn))	//ɾ�ȽϹ�Ʊ�б������
		{
			decide_delate(stoinfo,stoinfo->choose[2]);
			decide_compare_draw(stoinfo);
		}
	}
}


 /**********************************************************
decide_choose_anal(STOINFO * stoinfo)
���������ʹɲ���ӡ
   ����grade_calculate��������֧��Ʊ�������÷�
   �ҳ���Ӧ����µ���������ֻ��Ʊ��¼�������stoinfo_combine
   ����sheet_fill�����stoinfo�����������
**********************************************************/

void deicde_choose_anal(STOINFO * stoinfo)            //control_decide����Ͷ�ʷ��
{
	FILE * fsymb;
	FILE * fscore;
	char address[35];
	char pointer[30]="data\\database\\";
	int score[300][3];                         //��¼��Ʊ���ַ�������
	char symbol[300][7];                       //��¼��Ʊ����
	int iround,jround;
	float data[15];                            //��Ʊ��15��ָ��
	
	int max1,max2,max3,max4;
	int maxj1,maxj2,maxj3,maxj4;
	int combine_score[4][3];		//��ϵĵ÷�
	
	char temp[7];
	
	fsymb=fopen("data\\database\\symbolic.txt","rb");
	for(iround=0;;iround++)
	{
		if(fread(temp,6,1,fsymb)!=0)
		{
			temp[6]='\0';
			strcpy(symbol[iround],temp);
			
			strcpy(address,pointer);
			strcat(address,temp);
			strcat(address,"\\decide.txt");
			
			if((fscore=fopen(address,"rb"))==NULL)  
			{
		        printf("decide_anal: error opening decide.txt(out)\n");
		        getch();
	        }
			fread(data,sizeof(float),15,fscore);
			
			fclose(fscore);
			grade_calculate(score[iround],data);  //��������data���õ�����score[i]�������÷�
			
		}
		else 
		{
			break;
		}
		temp[0]='\0';
	}                        	
	fclose(fsymb);                                //����grade_calculate�������ϵ÷�
	
	max1=max2=max3=max4=score[0][stoinfo->style];	
	maxj1=maxj2=maxj3=maxj4=0;					
	for(jround=0;jround<iround;jround++)
	{
		if(max1<score[jround][stoinfo->style])
		{		
			max4=max3;         //max1���£���max��ֵ��������ƶ�	
			max3=max2;
			max2=max1;
			
			maxj4=maxj3;
			maxj3=maxj2;
			maxj2=maxj1;
		
			max1=score[jround][stoinfo->style];
			maxj1=jround;
		}		
		else if(max2<score[jround][stoinfo->style])
		{
			max4=max3;
			max3=max2;
			
			maxj4=maxj3;
			maxj3=maxj2;
			
			max2=score[jround][stoinfo->style];
			maxj2=jround;
			
		}
		else if(max3<score[jround][stoinfo->style])
		{
			max4=max3;
			
			maxj4=maxj3;
			
			max3=score[jround][stoinfo->style];
			maxj3=jround;
		}
		else if(max4<score[jround][stoinfo->style])
		{
			max4=score[jround][stoinfo->style];
			maxj4=jround;
		}
	}                                        //�ҵ�ǰ��ֻ�÷���ߵĹ�Ʊ��Ҫ��max1>max2>max3>max4
	
	strcpy(stoinfo->combine[0],symbol[maxj1]);
	strcpy(stoinfo->combine[1],symbol[maxj2]);
	strcpy(stoinfo->combine[2],symbol[maxj3]);
	strcpy(stoinfo->combine[3],symbol[maxj4]);      //���ҵ���ǰ������ֵ��stoinfo->combine
	
	for(jround=0;jround<3;jround++)		
	{
		combine_score[0][jround]=score[maxj1][jround];
		combine_score[1][jround]=score[maxj2][jround];
		combine_score[2][jround]=score[maxj3][jround];
		combine_score[3][jround]=score[maxj4][jround];
	}                                                         //��¼ǰ������ϵĵ÷�

	choose_sheet_fill(stoinfo,185,combine_score);
}

/**********************************************************
grade_calculate(int * grade,float * data)
��data��15������������ֻ��Ʊ����������������grade��3��
   
**********************************************************/	

void grade_calculate(int * grade,float * data)
{
	int kround;
	int score[15];
	float temp;
	int temp2;
	
	for(kround=0;kround<15;kround++)
	{
		if(fabs(data[kround])<1e-6)	//�������ָ��Ϊ0�������ֱ��Ϊ0
		{
			score[kround]=0;
		}	
	}
		
	temp=data[0];					//ָ��1��NPG-TTM���ɳ����ӣ�
	if(temp>5)
		score[0]=100;
	else if(temp<-5)
		score[0]=0;
	else
		score[0]=(int)((temp+5)*10);
		
	temp=data[1];					//ָ��2��OPG-TTM���ɳ����ӣ�
	if(temp>5)
		score[1]=100;
	else if(temp<-1)
		score[1]=0;
	else
		score[1]=(int)((temp+1)/6*100);
		
	temp=data[2];					//ָ��3��OCFG-TTM���ɳ����ӣ�
	if(temp>8)
		score[2]=100;
	else if(temp<-8)
		score[2]=0;
	else
		score[2]=(int)((temp+8)/16*100);
		
	temp=data[3];					//ָ��4��ROEG���ɳ����ӣ�
	if(temp>2)
		score[3]=100;
	else if(temp<-2)
		score[3]=0;
	else
		score[3]=(int)((temp+2)/4*100);
		
	temp=data[4];					//ָ��5��ROAG���ɳ����ӣ�
	if(temp>2)
		score[4]=100;
	else if(temp<-2)
		score[4]=0;
	else
		score[4]=(int)((temp+2)/4*100);
	
	temp=data[5];					//ָ��6��PE
	if(temp>0&&temp<10)
		score[5]=100;
	else if(temp<0||temp>1000)
		score[5]=0;
	else if(temp<1000&&temp>150)
		score[5]=20-(int)((temp-150)/850*20);
	else if(temp<150&&temp>50)
		score[5]=50-(int)((temp-50)/100*30);
	else if(temp<50&&temp>10)
		score[5]=100-(int)((temp)/40*50);
	
	temp=data[6];					//ָ��7��PB
	if(temp>0&&temp<10)
		score[6]=100-(int)((temp)/10*70);
	else if(temp>15||temp<0)
		score[6]=0;
	else if(temp>10&&temp<15)
		score[6]=30-(int)((temp-10)/5*30);
	
	temp=data[7];					//ָ��8��PS
	if(temp>0&&temp<10)
		score[7]=100-(int)((temp)/10*75);
	else if(temp>25)
		score[7]=0;
	else if(temp>10&&temp<25)
		score[7]=25-(int)((temp-10)/15*25);

	temp=data[8];					//ָ��9��PCF
	if(temp>0&&temp<150)
		score[8]=100-(int)((temp)/150*100);
	else if(temp>150||temp<-20)
		score[8]=0;
	else if(temp>-20&&temp<0)
		score[8]=(int)((temp+20)/20*20);
	
	temp=data[9];					//ָ��10��PEG
	if(temp>0&&temp<500)
		score[9]=100-(int)((temp)/500*80);
	else if(temp>1000||temp<0)
		score[9]=0;
	else if(temp>500&&temp<1000)
		score[9]=20-(int)((temp-500)/500*20);

	temp=data[10];					//ָ��11��CTAR
	if(temp>0.8)
		score[10]=100;
	else if(temp<-0.5)
		score[10]=0;
	else if(temp>-0.5&&temp<0.8)
		score[10]=100-(int)((temp+0.5)/1.3*100);	
		
	temp=data[11];					//ָ��12��NPM
	if(temp>1000)
		score[11]=100;
	else if(temp<0)
		score[11]=0;
	else if(temp>0&&temp<1000)
		score[11]=(int)((temp)/1000*100);	
	
	temp=data[12];					//ָ��13��ROE���������ӣ�
	if(temp>15)
		score[12]=100;
	else if(temp<0)
		score[12]=0;
	else if(temp>0&&temp<15)
		score[12]=(int)((temp)/15*100);	
	
	temp=data[13];					//ָ��14��ROA���������ӣ�
	if(temp>8)
		score[13]=100;
	else if(temp<0)
		score[13]=0;
	else if(temp>0&&temp<8)
		score[13]=(int)((temp)/8*100);	
	
	temp=data[14];					//ָ��15��TAT
	if(temp>0.8)
		score[14]=100;
	else if(temp<0)
		score[14]=0;
	else if(temp>0&&temp<0.8)
		score[14]=(int)((temp)/0.8*100);	
	

		
	temp2=score[0]+score[1]+score[2]+score[3]+score[4];		//�ɳ���ϵ÷�
	grade[0]=temp2*0.2;
		
	temp2=score[5]+score[6]+score[7]+score[8]+score[9];		//��ֵ��ϵ÷�
	grade[1]=temp2*0.2;
		
	temp2=score[0]*6.5+score[1]*6.5+score[2]*6.5;							//��ֵ�ɳ���ϵ÷�
	temp2=temp2+score[3]*7+score[4]*7+score[5]*6.5;
	temp2=temp2+score[6]*7+score[7]*7+score[8]*7;
	temp2=temp2+score[9]*6.5+score[10]*6.5+score[11]*6.5;
	temp2=temp2+score[12]*6.5+score[13]*6.5+score[14]*6.5;
	grade[2]=(int)(temp2*0.01);
	
}

/**********************************************************
choose_sheet_fill(stoinfo,x,y,combine_score[4][3])
���ʹ�Ʊ��Ϣ���
  ��ӡÿֻ���ƴ���÷�
  ��ÿֻ��Ʊ����������ѡ��������
   
**********************************************************/	

void choose_sheet_fill(STOINFO * stoinfo,int y,int combine_score[4][3])
{
	int iround;
	char name[10];
	char temp[10];
	char num[10];
	char other[10];
	int flag1,flag2,flag3;		//��¼�����ɵ÷ֵ�����

	FILE * fstock;
	char address[35];
	char pointer[30]="data\\database\\";
	y=65;

	for(iround=0;iround<4;iround++)
	{
		strcpy(address,pointer);
		strcat(address,stoinfo->combine[iround]);
		strcat(address,"\\list.txt");

		if((fstock=fopen(address,"rb"))==NULL)  
		{
		    printf("choose_sheetfill: error opening list.txt(out)\n");
		    getch();
	    }
			
		fread(num,sizeof(int),1,fstock);
		fread(other,6,1,fstock);
		other[6]='\0';
		fread(name,10,1,fstock);
		fclose(fstock);

		name[9]='\0';
		puthz12(name,203,y+10,YELLOW);				//��ӡ������

		setcolor(YELLOW);
		outtextxy(260,y+10,stoinfo->combine[iround]);	//��ӡ������

		setcolor(WHITE);
		itoa(combine_score[iround][stoinfo->style],temp,10);
		outtextxy(324,y+10,temp);						//��ӡ���÷�


		if(combine_score[iround][0]<34)
		{
			flag1=1;
		}
		else if(combine_score[iround][0]<37)
		{
			flag1=2;
		}
		else
		{
			flag1=3;
		}

		if(combine_score[iround][1]<48)
		{
			flag2=1;
		}
		else if(combine_score[iround][1]<66)
		{
			flag2=2;
		}
		else
		{
			flag2=3;
		}

		if(combine_score[iround][2]<34)
		{
			flag3=1;
		}
		else if(combine_score[iround][2]<41)
		{
			flag3=2;
		}
		else
		{
			flag3=3;
		}


		if((flag1+flag2+flag3)==3||			//��ϵ÷�Ϊ1,1,1
				(flag1+flag2+flag3)==4)		//������ϵ÷�Ϊ1,1,2(2����λ��)
		{
			puthz12("��Ʊ��ָ����ϲ�������",350,y+10,WHITE);
		}
		else if((flag1+flag2+flag3==5&&flag1!=3&&flag1!=3&&flag1!=3)	//��ϵ÷�Ϊ1,2,2(1����λ��)
				||(flag1==2&&flag1==2&&flag1==2))	//������ϵ÷�Ϊ2,2,2
		{
			puthz12("��Ʊ��ָ�����ƽӹ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==3&&(flag1+flag2+flag3)==5)	//��ϵ÷�Ϊ3,1,1
		{
			puthz12("��Ʊ�������ԣ��ɳ����ƽӹ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag2==3&&(flag1+flag2+flag3)==5)	//��ϵ÷�Ϊ1,3,1
		{
			puthz12("��Ʊ�������ԣ���ֵ���ƽӹ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag3==3&&(flag1+flag2+flag3)==5)	//��ϵ÷�Ϊ1,1,3
		{
			puthz12("��Ʊ�������ԣ���ֵ�ɳ����ƽӹ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==3&&(flag1+flag2+flag3)==6)	//��ϵ÷�Ϊ3,(2,1/1,2)
		{
			puthz12("��Ʊ�������ԣ��ɳ����ƽӹ�����鱣�ֻ����",350,y+10,WHITE);
		}
		else if(flag2==3&&(flag1+flag2+flag3)==6)	//��ϵ÷�Ϊ(2/1),3,(1/2)
		{
			puthz12("��Ʊ�������ԣ���ֵ���ƽӹ�����鱣�ֻ����",350,y+10,WHITE);
		}
		else if(flag3==3&&(flag1+flag2+flag3)==6)	//��ϵ÷�Ϊ(2,1/1,2),3
		{
			puthz12("��Ʊ�������ԣ���ֵ�ɳ����ƽӹ�����鱣�ֻ����",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==2&&flag3==2)		//��ϵ÷�Ϊ3,2,2
		{
			puthz12("��Ʊ�������ã�����ƽ��ˮƽ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==2&&flag2==3&&flag3==2)		//��ϵ÷�Ϊ2,3,2
		{
			puthz12("��Ʊ�������ã�����ƽ��ˮƽ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==2&&flag2==2&&flag3==3)		//��ϵ÷�Ϊ2,2,3
		{
			puthz12("��Ʊ�������ã�����ƽ��ˮƽ���������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==1&&flag2==3&&flag3==3)		//��ϵ÷�Ϊ1,3,3
		{
			puthz12("��Ʊ����������ɳ���ϵ÷ֽϵͣ��������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==1&&flag3==3)		//��ϵ÷�Ϊ3,1,3
		{
			puthz12("��Ʊ�����������ֵ��ϵ÷ֽϵͣ��������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==3&&flag3==1)		//��ϵ÷�Ϊ3,3,1
		{
			puthz12("��Ʊ�����������ֵ�ɳ���ϵ÷ֽϵͣ��������ֽ���",350,y+10,WHITE);
		}
		else if(flag1==2&&flag2==3&&flag3==3)		//��ϵ÷�Ϊ2,3,3
		{
			puthz12("��Ʊ�������㣬���ɳ������÷־��ϸߣ���������",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==2&&flag3==3)		//��ϵ÷�Ϊ3,2,3
		{
			puthz12("��Ʊ�������㣬����ֵ�����÷־��ϸߣ���������",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==3&&flag3==2)		//��ϵ÷�Ϊ3,3,2
		{
			puthz12("��Ʊ�������㣬����ֵ�ɳ������÷־��ϸߣ���������",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==3&&flag3==3)		//��ϵ÷�Ϊ3,3,3
		{
			puthz12("��Ʊ�ۺϱ������㣬����ϵ÷־��ϸߣ���������",350,y+10,WHITE);
		}
		y+=35*3;
	}
}


/**********************************************************
decide_compare_draw(STOINFO * stoinfo)
���ƶԱȽ���
  �����Ļ
  �������˵�
  ����grade_loading����Աȵļ�����Ʊ�ķ���
  ����compare_sheet��Աȱ�
  ����compare_bar1������״ͼ
  ����compare_line��������ͼ
**********************************************************/

void decide_compare_draw(STOINFO * stoinfo)   //���ƶԱȽ���
{
	int grade[3][3];
	char name[3][10];

	cleardevice();
	menu_create();

	grade_loading(stoinfo,grade,name);

	setcolor(WHITE);
	rectangle(5,470-17,5+53,470);
	puthz12("��Ʊ�Ƽ�",5+3,480-10-15,RED);         //���ط������水ť

	compare_sheet(grade,name);
	compare_bar1(grade,name);
	compare_line(stoinfo,name);
}

/**********************************************************
grade_loading(STOINFO * stoinfo,int grade[3][3],char name[3][10])
�Աȹ�Ʊ��������
   ����stoinfo���Ǵ�����ļ�����¼���ƣ�15������
   ����grade_calculate�����⼸����Ʊ�������÷ּ���grade

**********************************************************/


void grade_loading(STOINFO * stoinfo,int grade[3][3],char name[3][10])
{
	float data[3][15];
	int iround,kround;
	FILE * fp;
	char address[40];
	char pointer[20]="data\\database\\";

	for(iround=0;iround<3;iround++)
	{
		if(stoinfo->choose[iround][0]!='k')
		{
			strcpy(address,pointer);
			strcat(address,stoinfo->choose[iround]);
			strcat(address,"\\decide.txt");
		}
		else
		{
			break;
		}

		if((fp=fopen(address,"rb"))==NULL)		//��ȡ��Ʊ15����������
	
		{
		    printf("grade_loading: error opening decide.txt(out)\n");
		    getch();
	    }
		for(kround=0;kround<15;kround++)
		{
			fread(&data[iround][kround],sizeof(float),1,fp);
		}
		fclose(fp);

		strcpy(address,pointer);				//��ȡ��Ʊ���
		strcat(address,stoinfo->choose[iround]);
		strcat(address,"\\list.txt");
		if((fp=fopen(address,"rb"))==NULL)  
		{
		    printf("grade_loading: error opening list.txt(out)\n");
		    getch();
	    }
		fseek(fp,sizeof(int)+6,SEEK_SET);
		fread(name[iround],10,1,fp);

		fclose(fp);


	}

	for(kround=0;kround<iround;kround++)
	{
		grade_calculate(grade[kround],data[kround]);
	}
	for(;kround<3;kround++)
	{
		grade[kround][0]=-1;
	}

}

/**********************************************************
decide_add(STOINFO * stoinfo,char * str)
�����Ʊ�ԱȺ���
  �ж���ѡ��Ʊ�Ƿ��Ѿ�����
  ���п�λ�򽫸�֧��Ʊ����Աȣ���Ʊ�������stoinfo��
  ���Աȹ�Ʊ��������ʾ����Ϣ
**********************************************************/


void decide_add(STOINFO * stoinfo,char * str)
{
	int tround;

	for(tround=0;tround<3;tround++)
	{
		if(strcmp(str,stoinfo->choose[tround])==0)	//����ӹ��˹�Ʊ
		{
			break;
		}
		if(stoinfo->choose[tround][0]=='k')
		{
			strcpy(stoinfo->choose[tround],str);
			break;
		}
	}
	if(tround==3)		//�Ա��б����ˣ�û�м���
	{
		//save_picture(320-100,240-60,320+100,240+60);

		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		bar(320-100,240-60,320+100,240+60);
		puthz16("�б�����",320-32,240-18,16,1,1,BLACK);

		delay(1000);
		//put_picture(320-100,240-60,320+100,240+60);
		decide_compare_draw(stoinfo);

	}

}



/**********************************************************
decide_delate(STOINFO * stoinfo,char * str)
��Ʊ�Ա�ɾ������
  �ж���ѡ��Ʊ�ǶԱ��б�ĵڼ���
  ���ǵ�������������Ʊ�ƶ����ı�stoinfo��
**********************************************************/	

void decide_delate(STOINFO * stoinfo,char * str)
{
	int iround,kround;
	int flag=0;
	
	for(iround=0;iround<3;iround++)
	{
		if(strcmp(str,stoinfo->choose[iround])==0)	//�ж��ǲ���Ҫɾ���Ĺ�Ʊ
		{
			flag=1;
			
			if(iround!=2)
			{
				for(kround=iround+1;kround<3;kround++)	//���к���Ĺ�Ʊǰ��
				{
					if(stoinfo->choose[iround][0]!='k')
					{
						strcpy(stoinfo->choose[kround-1],stoinfo->choose[kround]);
						stoinfo->choose[kround][0]='k';
					}
				}
			}
			else if(iround==2)
				stoinfo->choose[iround][0]='k';
	
		}
			
	}
	
	if(flag==0)		//û�ҵ�Ҫɾ���Ĺ�Ʊ����
	{
		
	}
		
}


/**********************************************************
decide_choose_draw_init() 
���Ʒ������溯��
  �����Ļ
  �������˵�
  �������а�ť�����
**********************************************************/	


void decide_choose_draw_init()      //���Ʒ�������
{
	int i;
	cleardevice();
	menu_create();

	setcolor(WHITE);
	rectangle(5,470-17,5+53,470);
	puthz12("��Ʊ�Ա�",5+3,480-10-15,RED);         //���ضԱȽ��水ť
	
	
	for(i=0;i<12;i++)                     
	 line(200,30+35*i,200+430,30+35*i);
    i=0;
	do
	{
       line(200,30+35*i,200,30+35*(i+2));
	   line(200+430,30+35*i,200+430,30+35*(i+2));
       i+=3;
	}while(i<10);                                           //���������
    
	setfillstyle(SOLID_FILL,WHITE);
	puthz16("Ͷ�ʷ��ѡ��",20,40,16,1,1,RED);
	bar3d(10,80,10+120,80+20,0,0);
	puthz16("��������",38,82,16,1,1,RED);
	bar3d(10,130,10+120,130+20,0,0);
	puthz16("�ͷ�����",38,132,16,1,1,RED);
	bar3d(10,180,10+120,180+20,0,0);
	puthz16("���������ۺ���",15,182,16,1,1,RED);
	bar3d(30,250,110,250+20,0,0);
	puthz16("��ʼ����",40,252,16,1,1,RED);            //Ͷ�ʷ��ť����
	
	setcolor(LIGHTRED);
	line(200+400-30,30+35*2+25,200+400,30+35*2+25);
	puthz12("����",600-25,30+35*2+12,LIGHTRED);
	line(200+400-30,30+35*5+25,200+400,30+35*5+25);
	puthz12("����",600-25,30+35*5+12,LIGHTRED);
	line(200+400-30,30+35*8+25,200+400,30+35*8+25);
	puthz12("����",600-25,30+35*8+12,LIGHTRED);
	line(200+400-30,30+35*11+25,200+400,30+35*11+25);
	puthz12("����",600-25,30+35*11+12,LIGHTRED);

	setcolor(BLUE);
	line(200+400-110,30+35*2+25,200+400-80,30+35*2+25);
	puthz12("����",600-105,30+35*2+12,BLUE);
	line(200+400-110,30+35*5+25,200+400-80,30+35*5+25);
	puthz12("����",600-105,30+35*5+12,BLUE);
	line(200+400-110,30+35*8+25,200+400-80,30+35*8+25);
	puthz12("����",600-105,30+35*8+12,BLUE);
	line(200+400-110,30+35*11+25,200+400-80,30+35*11+25);
	puthz12("����",600-105,30+35*11+12,BLUE);

	setcolor(RED);
	line(200+400-70,30+35*2+25,200+400-40,30+35*2+25);
	puthz12("�Ա�",600-65,30+35*2+12,RED);
	line(200+400-70,30+35*5+25,200+400-40,30+35*5+25);
	puthz12("�Ա�",600-65,30+35*5+12,RED);
	line(200+400-70,30+35*8+25,200+400-40,30+35*8+25);
	puthz12("�Ա�",600-65,30+35*8+12,RED);
	line(200+400-70,30+35*11+25,200+400-40,30+35*11+25);
	puthz12("�Ա�",600-65,30+35*11+12,RED);
	 
    puthz12("����",212,355,YELLOW);
	puthz12("����",273,355,YELLOW);
	puthz12("��ϵ÷�",310,355,YELLOW);
	puthz12("����",480,355,YELLOW);

	puthz12("����",212,250,YELLOW);
	puthz12("����",273,250,YELLOW);
	puthz12("��ϵ÷�",310,250,YELLOW);
	puthz12("����",480,250,YELLOW);

	puthz12("����",212,145,YELLOW);
	puthz12("����",273,145,YELLOW);
	puthz12("��ϵ÷�",310,145,YELLOW);
	puthz12("����",480,145,YELLOW);

	puthz12("����",212,40,YELLOW);
	puthz12("����",273,40,YELLOW);
	puthz12("��ϵ÷�",310,40,YELLOW);
	puthz12("����",480,40,YELLOW);

    
}



	/*line(200,30,200,30+35*2);
	line(200,30+35*3,200,30+35*5);
	line(200,30+35*6,200,30+35*8);
	line(200,30+35*9,200,30+35*11);
	line(200+405,30,200+405,30+35*2);
	line(200+405,30+35*3,200+405,30+35*5);
	line(200+405,30+35*6,200+405,30+35*8);
	line(200+405,30+35*9,200+405,30+35*11);             //�������������ߣ�������      */

/**********************************************************
compare_sheet(int grade[3][3],char name[3][10])
���ƶԱȱ����
  ���Ʊ��д��ͷ
  ����Ʊ���Ƶ÷ֽ��������񣬻���ɾ����ť
**********************************************************/	
	
void compare_sheet(int grade[3][3],char name[3][10])		
{	
    int iround;
	int xp,yp,width,num;
	int k=20,h=10;						//k,hΪ���ݵĳ���(�߶�)
	char str[5];
	int average;

	width=(12*4+24)*4+(12*6+24)+48;			//ɾ����ť����ȷ��
	num=2;
				
    setcolor(YELLOW);
	for(iround=0;iround<5;iround++)
	  line((640-432)/2,380+20*iround,(640+432)/2,380+20*iround);
	line(104,380,104,380+80);
	line(104+72,380,104+72,380+80);
	line(104+72*2,380,104+72*2,380+80);
	line(104+72*3,380,104+72*3,380+80);
	line(104+72*3+96,380,104+72*3+96,380+80);
	line(104+72*4+96,380,104+72*4+96,380+80);
	line(536,380,536,380+80);                                    

	puthz12("�ɳ����",104+72+72/2-12*2,380+20/2-12/2,YELLOW);
	puthz12("��ֵ���",104+72*2+72/2-12*2,380+20/2-12/2,YELLOW);
	puthz12("�ɳ���ֵ���",104+72*3+96/2-12*3,380+20/2-12/2,YELLOW);
	puthz12("����",104+72*3+96+72/2-12,380+20/2-12/2,YELLOW);    	//�ԱȽ�����������
		
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,WHITE);

	for(iround=0;iround<3;iround++)
	{
		setcolor(WHITE);
		if(grade[iround][0]!=-1)
		{
			puthz12(name[iround],(640-width)/2+72/2-12*2,380+20*(iround+1)+20/2-12/2,WHITE);		//�������
			
			itoa(grade[iround][0],str,10);	 					//grade[iround]�е�����ת��Ϊ�ַ���
			outtextxy((640-width)/2+72+72/2-k/2,380+20*(iround+1)+10-h/2,str);		//����ɳ���ϵ÷�

			itoa(grade[iround][1],str,10);	   
			outtextxy((640-width)/2+72*2+72/2-k/2,380+20*(iround+1)+10-h/2,str);   //�����ֵ��ϵ÷�

			itoa(grade[iround][2],str,10);	  
			outtextxy((640-width)/2+72*3+96/2-k/2,380+20*(iround+1)+10-h/2,str);  	//�����ֵ�ɳ���ϵ÷�
			
			average=(grade[iround][0]+grade[iround][1]+grade[iround][2])/3;//���ϵͳ�Ƽ�
			
			if(average<25)
			{
				puthz12("�������",(640-width)/2+72*3+96+72/2-12*2,380+20*(iround+1)+10-h/2,WHITE);
			}
			else if(average>45)
			{
				puthz12("��������",(640-width)/2+72*3+96+72/2-12*2,380+20*(iround+1)+10-h/2,WHITE);
			}
			else
			{
				puthz12("�������",(640-width)/2+72*3+96+72/2-12*2,380+20*(iround+1)+10-h/2,WHITE);
			}
			
			xp=(640-width)/2+72*3+96+72+48/2;		//���㰴ťλ��
			yp=380+20*(iround+2)-20/2;
			
			bar3d(xp-25/2,yp-16/2,xp+25/2,yp+16/2,0,0);	//��ɾ����ť
			
			puthz12("ɾ��",xp-12/2*num,yp-12/2,BLACK);
			
		}
		else
		{
			break;
		}
		
	}
		
} 

/**********************************************************
compare_bar1(int grade[3][3], char name[3][10])
������״ͼ����
  ����Աȹ�Ʊ��Ŀ
  ��grade�����ݴ���data��9��
  �ҳ�data��������ֵ
  ����ÿ�����Ӹ߶�
  �������ӣ���ӡ����
  
**********************************************************/	
	

void compare_bar1(int grade[3][3], char name[3][10])							//�����Ͻ�����ͳ��ͼ
{	

	int x,y;								//x,y����ͳ��ͼԭ��λ��
	int maxx,maxy;							//maxx,maxy����ͳ��ͼx��y�᳤��
	int iround,jround,k;
	unsigned int color[3]={RED,YELLOW,LIGHTRED};		//�Զ���һ����ɫ����
	char temp[5];
	int data[9];							//����ά����ת��Ϊһά����
	int bar_high[9]={0};					//ÿ�����ӵĸ߶ȣ�����ֵ��
	int bar_width;							//ÿ�����ӵĿ�ȣ�����ֵ��
	
	int bar_num;
	int x_num;
	int max;								//��ֵ�������ӵ�ֵ���������ص���ߣ�
	maxx=275;
	maxy=285;
	x=5;
	y=350;
	bar_width=22;

	for(bar_num=0;bar_num<3;bar_num++)		//�ҵ��Ա��б����ж��ٹ�Ʊ
	{
		if(grade[bar_num][0]==-1)
		{
			break;
		}
	}

	setcolor(WHITE);
	line(x,y,x+maxx,y);
	line(x,y,x,y-maxy);
	setcolor(WHITE);        //���ñ߿���ɫΪ��ɫ
	puthz12("����ϵ÷����",x+maxx/2-3*12-3,y-maxy-48,WHITE);

	setfillstyle(SOLID_FILL,RED);
	bar3d(x+5,y-maxy-30,x+5+30,y-maxy-30+12,0,0);
	puthz12("�ɳ����",x+5+30+6,y-maxy-30,WHITE);

	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(x+5+30+60,y-maxy-30,x+5+30+60+30,y-maxy-30+12,0,0);
	puthz12("��ֵ���",x+5+30+60+30+6,y-maxy-30,WHITE);

	setfillstyle(SOLID_FILL,LIGHTRED);
	bar3d(x+5+(30+60)*2,y-maxy-30,x+5+(30+60)*2+30,y-maxy-30+12,0,0);
	puthz12("�ɳ���ֵ���",x+5+(30+60)*2+30+6,y-maxy-30,WHITE);  	//��״ͼ�ձ�������

	jround=0;
	for(iround=0;iround<bar_num;iround++)	//�Ѵ���Ķ�ά����ת��Ϊһά����bar_high
	{
		data[jround++]=grade[iround][0];
		data[jround++]=grade[iround][1];
		data[jround++]=grade[iround][2];

	}

	max=data[0];							//�ҳ�a�����е����ֵ
	for(iround=1;iround<bar_num*3;iround++)
	{
		if(max<data[iround])
			 max=data[iround];
	}

	for(iround=0;iround<bar_num*3;iround++)	//���ÿ�����ӵĸ߶ȣ�����ֵ��
	{
		bar_high[iround]=((data[iround])*maxy/max)*0.9;
	}

	if(bar_num==3)
	{
		x_num=1;
		for(iround=0;iround<3;iround++)
		{
			puthz12(name[iround],x+bar_width*x_num+bar_width*.6,y+3,WHITE);
			for(jround=0;jround<3;jround++)
			{
				setfillstyle(SOLID_FILL,color[jround]) ;		/*��������ͼ�����ɫ*/
				bar3d(x+bar_width*x_num,y-bar_high[jround+3*iround],x+bar_width*(x_num+1),y,0,0);	  /*heng��ʾ�����������ĵڼ�����*/
				setcolor(WHITE);			   /*������ݵ���ɫ*/
				gcvt(data[jround+3*iround],3,temp);		  /*��a�����еĸ���������ת��Ϊ�ַ���*/
				outtextxy(x+bar_width*x_num+4,y-bar_high[jround+3*iround]-15,temp);	/*�������*/
				x_num++;
			}
			x_num+=1;		 //ÿ��������ͼΪһ��飬�м��ٿ�һ����
		}

	}
	else if(bar_num==2)
	{
		x_num=2;
		for(iround=0;iround<2;iround++)
		{
			puthz12(name[iround],x+bar_width*x_num+bar_width*.6,y+3,WHITE);
			for(jround=0;jround<3;jround++)
			{
				setfillstyle(SOLID_FILL,color[jround]) ;		/*��������ͼ�����ɫ*/
				bar3d(x+bar_width*x_num,y-bar_high[jround+3*iround],x+bar_width*(x_num+1),y,0,0);	  /*heng��ʾ�����������ĵڼ�����*/
				setcolor(WHITE);			   /*������ݵ���ɫ*/
				gcvt(data[jround+3*iround],3,temp);		  /*��a�����еĸ���������ת��Ϊ�ַ���*/
				outtextxy(x+bar_width*x_num+4,y-bar_high[jround+3*iround]-15,temp);	/*�������*/
				x_num++;
			}
		x_num+=2;		 //ÿ��������ͼΪһ��飬�м��ٿ�������
		}

	}
	else if(bar_num==1)
	{
		x_num=5;
		for(iround=0;iround<1;iround++)
		{
			puthz12(name[iround],x+bar_width*x_num+bar_width*.6,y+3,WHITE);
			for(jround=0;jround<3;jround++)
			{
				setfillstyle(SOLID_FILL,color[jround]) ;		/*��������ͼ�����ɫ*/
				bar3d(x+bar_width*x_num,y-bar_high[jround+3*iround],x+bar_width*(x_num+1),y,0,0);	  /*heng��ʾ�����������ĵڼ�����*/
				setcolor(WHITE);			   /*������ݵ���ɫ*/
				gcvt(data[jround+3*iround],3,temp);		  /*��a�����еĸ���������ת��Ϊ�ַ���*/
				outtextxy(x+bar_width*x_num+4,y-bar_high[jround+3*iround]-15,temp);	/*�������*/
				x_num++;
			}
		}

	}

}

/**********************************************************
compare_line(stoinfo, char name[3][10])
��������ͼ����
  ��stoinfo�д�����ļ���ȡ����data��3����5��
  �ҳ�data��������ֵ
  ����ÿ�����ݸ߶ȣ�������yplace��3����5��
  ��������ͼ����ӡ����
  ����ͼ����������

**********************************************************/

void compare_line(STOINFO * stoinfo,char name[3][10])									//�����Ͻ�����ͳ��ͼ
{

	int x,y;								//x,y����ͳ��ͼԭ��λ��
	int maxx,maxy;							//maxx,maxy����ͳ��ͼx��y�᳤��
	int num=0;
	int iround,jround,kround;
	FILE * fp;
	char pointer[]="data\\database\\";
	char filename[35];
	float data[3][5];						//����15������
	int yplace[3][5];						//9�����ݵ�y���꣨���ص����꣩
	float ymax,ymin,ywidth;
	int temp;                //������ļ��
	char str[6];
	unsigned int color[3]={RED,YELLOW,LIGHTRED};//�Զ���һ����ɫ����

	maxx=265;
	maxy=285;
	x=360;
	y=350;
  //	puthz12("��5���¹�Ʊ����",370,25,WHITE);
	setcolor(WHITE);
	line(x,y,x+maxx,y);
	line(x,y,x,y-maxy);
	puthz12("5��",x+10+maxx*1/6,y+2,WHITE);
	puthz12("6��",x+10+maxx*2/6,y+2,WHITE);
	puthz12("7��",x+10+maxx*3/6,y+2,WHITE);
	puthz12("8��",x+10+maxx*4/6,y+2,WHITE);
	puthz12("9��",x+10+maxx*5/6,y+2,WHITE);
	//������
	puthz12("��5���¹�Ʊ����",x+maxx/2-4*12,y-maxy-48,WHITE);
																 //����ͼ��������
	for(iround=0;iround<3;iround++)
	{
		if(stoinfo->choose[iround][0]!='k')
		{
			strcpy(filename,pointer);
			strcat(filename,stoinfo->choose[iround]);
			strcat(filename,"\\line.txt");

			if((fp=fopen(filename,"rb"))==NULL)
			{
		        printf("compare_line: error opening list.txt(out)\n");
		        getch();
	        }

			fseek(fp,10+720*sizeof(float),SEEK_SET);
			fread(&data[iround][4],sizeof(float),1,fp);
			fseek(fp,10+700*sizeof(float),SEEK_SET);
			fread(&data[iround][3],sizeof(float),1,fp);
			fseek(fp,10+680*sizeof(float),SEEK_SET);
			fread(&data[iround][2],sizeof(float),1,fp);
			fseek(fp,10+660*sizeof(float),SEEK_SET);
			fread(&data[iround][1],sizeof(float),1,fp);
			fseek(fp,10+640*sizeof(float),SEEK_SET);
			fread(&data[iround][0],sizeof(float),1,fp);

			fclose(fp);
			num+=1;
		}
		else
		{
			break;				//����iround����
		}
	}
	if(num!=0)
	{
		ymax=data[0][0];
		ymin=data[0][0];

		for(jround=0;jround<iround;jround++)
		{
			for(kround=0;kround<5;kround++)
			{
				if(data[jround][kround]>ymax)
					ymax=data[jround][kround];
				if(data[jround][kround]<ymin)
					ymin=data[jround][kround];
			}

		}
		ywidth=ymax-ymin;

		for(jround=0;jround<iround;jround++)
		{
			for(kround=0;kround<5;kround++)
			{
				yplace[jround][kround]=(int)(y-((data[jround][kround]-ymin)/ywidth*maxy*0.9))-10;  //����������10����
			}
		}

		for(jround=0;jround<iround;jround++)
		{
			setcolor(color[jround]);
			setfillstyle(SOLID_FILL,color[jround]);
			//ͼ������
			pieslice(x-20+96*jround,y-maxy-24,0,360,2);
			line(x-20+96*jround,y-maxy-24,x-20+96*jround+30,y-maxy-24);
			pieslice(x-20+96*jround+30,y-maxy-24,0,360,2);
			puthz12(name[jround],x-20+96*jround+30+6,y-maxy-24-6,WHITE);
			//����ͼ����
			setcolor(color[jround]);
			setfillstyle(SOLID_FILL,color[jround]);          //��дһ����Ϊ�˷�ֹ��һ���������ʱ��������ĸ����setcolor
			pieslice(x+10+maxx*1/6,yplace[jround][0],0,360,2);
			line(x+10+maxx*1/6,yplace[jround][0],x+10+maxx*2/6,yplace[jround][1]);
			pieslice(x+10+maxx*2/6,yplace[jround][1],0,360,2);
			line(x+10+maxx*2/6,yplace[jround][1],x+10+maxx*3/6,yplace[jround][2]);
			pieslice(x+10+maxx*3/6,yplace[jround][2],0,360,2);
			line(x+10+maxx*3/6,yplace[jround][2],x+10+maxx*4/6,yplace[jround][3]);
			pieslice(x+10+maxx*4/6,yplace[jround][3],0,360,2);
			line(x+10+maxx*4/6,yplace[jround][3],x+10+maxx*5/6,yplace[jround][4]);
			pieslice(x+10+maxx*5/6,yplace[jround][4],0,360,2);

		}

		//������
		temp=maxy/6*0.9;
		setcolor(WHITE);
		gcvt(ymin,4,str);
		regu_float(str);
		outtextxy(x-42,y-10,str);

		gcvt(ymin+ywidth*1/6,4,str);
		regu_float(str);
		outtextxy(x-42,y-10-temp*1,str);

		gcvt(ymin+ywidth*2/6,4,str);
		regu_float(str);
		outtextxy(x-42,y-10-temp*2,str);

		gcvt(ymin+ywidth*3/6,4,str);
		regu_float(str);
		outtextxy(x-42,y-10-temp*3,str);

		gcvt(ymin+ywidth*4/6,4,str);
		regu_float(str);
		outtextxy(x-42,y-10-temp*4,str);

		gcvt(ymin+ywidth*5/6,4,str);
		regu_float(str);
		outtextxy(x-42,y-10-temp*5,str);

		gcvt(ymin+ywidth*6/6,4,str);
		regu_float(str);
		outtextxy(x-42,y-10-temp*6,str);
		//������
		puthz12("5��",x+10+maxx*1/6,y+2,WHITE);
		puthz12("6��",x+10+maxx*2/6,y+2,WHITE);
		puthz12("7��",x+10+maxx*3/6,y+2,WHITE);
		puthz12("8��",x+10+maxx*4/6,y+2,WHITE);
		puthz12("9��",x+10+maxx*5/6,y+2,WHITE);
	}
}

