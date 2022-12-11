#include "login.h"
#include "input.h"
#include "head.h"
#include "time.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:			line.c
  Author:       		��ī��
  Version:				1.0 
  Date:					18/11/05
  Description:  		��¼ע����ƺ���
  Function List:  
	sign				��¼���������ƺ���
	draw_sign_in		����¼����
	sign_in				�жϵ�¼״̬
	old_login			�ж����û��Ƿ��½�ɹ�
	draw_new_login		��ע�����
	new_login			���û�ע��
	new_login_			�ж����û��Ƿ�ע��ɹ�
	pass_change			�޸�����
	pass_change_		�ж������Ƿ��޸ĳɹ�
	random_str			���������֤��
  History:      
	<author>  <time>   <version >   <desc>
	��ī��    18/11/05     1.0     build this moudle  
*************************************************/

void sign(INFO *info)
{
	int flag;
	while(1)
	{
		flag=sign_in(info);
		
		if(flag==1)					//��½�ɹ���������ǰѭ���������Ʊ����
		{
			break;
		}
		else if(flag==2)		
		{
			pass_change();
		}
	}
}
int sign_in(INFO *info)
{
	int maxx,maxy;
	int mx,my,mbtn=-1;
	char id[8]="\0",password[10]="\0";
	char rand_str[5]="\0",input_str[5]="\0";


	//user *head,*account;
	//head=Creat();
	//account=head->next;
	maxx=getmaxx();
	maxy=getmaxy();
	random_str(rand_str);

	draw_sign_in();
	setcolor(BLACK);
	settextjustify(1,1);
	settextstyle(2,0,6);
	outtextxy(maxx/2+70,maxy/2+18,rand_str);

	while(1)
	{
		newmouse(&mx,&my,&mbtn);
		if(mbtn==0)
		{
			if(mx>maxx/2-70&&mx<maxx/2+128&&my>maxy/2-53&&my<maxy/2-28)
				setmouseshape(0);													//�����
			else if(mx>maxx/2-70&&mx<maxx/2+128&&my>maxy/2-19&&my<maxy/2+6)
				setmouseshape(0);
			else if(mx>maxx/2+92&&my>maxy/2+50-39&&mx<maxx/2+142&&my<maxy/2+50-21)
				setmouseshape(0);
			else if(mx>maxx/2-56&&mx<maxx/2+56&&my>maxy/2+77&&my<maxy/2+111)		//�ο͵�¼
				setmouseshape(2);
			else if(mx>maxx/2-135&&mx<maxx/2-60&&my>maxy/2+33&&my<maxy/2+67)
				setmouseshape(2);													//С��
			else if(mx>maxx/2-35&&mx<maxx/2+35&&my>maxy/2+33&&my<maxy/2+67)
				setmouseshape(2);
			else if(mx>maxx/2+60&&mx<maxx/2+135&&my>maxy/2+33&&my<maxy/2+67)
				setmouseshape(2);
			else if(mx>maxx/2-100&&mx<maxx/2-30&&my>maxy/2+50-38&&my<maxy/2+50-22)
				setmouseshape(2);
			else
				setmouseshape(1);													//��ͷ
		}
		else if(mbtn==1)
		{
			if(mx>maxx/2+60&&mx<maxx/2+135&&my>maxy/2+33&&my<maxy/2+67)
			{
				delay(100);
				exit(0);
			}
			else if(mx>maxx/2-35&&mx<maxx/2+35&&my>maxy/2+33&&my<maxy/2+67)			//ע��
			{
				setmouseshape(1);
				newmouse(&mx,&my,&mbtn);

				draw_new_login();
				if(new_login(maxx,maxy)==0)											//ע��ɹ�
				{
					return 0;														//���ص�¼����
				}
				else
					continue;
			}
			else if(mx>maxx/2-135&&mx<maxx/2-60&&my>maxy/2+33&&my<maxy/2+67)
			{
				if(old_login(maxx,maxy,id,password,rand_str,input_str)==1)			//��½�ɹ�
				{
					info->account_flag=1;
					strcpy(info->account,id);
					return 1;
				}
				else																//��������µ���֤��
				{
					random_str(rand_str);
					setcolor(BLACK);
					settextjustify(1,1);
					settextstyle(2,0,6);
					outtextxy(maxx/2+70,maxy/2+18,rand_str);
				}
			}
			else if(mx>maxx/2-56&&mx<maxx/2+56&&my>maxy/2+77&&my<maxy/2+111)		//�ο͵�¼
			{
				setmouseshape(2);
				mousehide(mx,my);
				info->account_flag=0;
				return 1;
			}
			else if(mx>maxx/2-100&&mx<maxx/2-30&&my>maxy/2+50-38&&my<maxy/2+50-22)	//��������
			{
				return 2;
			}
			else if(mx>maxx/2-70&&mx<maxx/2+128&&my>maxy/2-53&&my<maxy/2-28)
			{
				mousehide(mx,my);
				bar(maxx/2-70,maxy/2-53,maxx/2+130,maxy/2-26);
				input(maxx/2-65, maxy/2-53,7,1,RED,LIGHTGRAY,id,0);
			}
			else if(mx>maxx/2-70&&mx<maxx/2+128&&my>maxy/2-19&&my<maxy/2+6)
			{
				mousehide(mx,my);
				bar(maxx/2-70,maxy/2-19,maxx/2+130,maxy/2+8);
				input(maxx/2-65, maxy/2-19,9,1,RED,LIGHTGRAY,password,1);
			}
			else if(mx>maxx/2+92&&my>maxy/2+50-39&&mx<maxx/2+142&&my<maxy/2+50-21)
			{
				mousehide(mx,my);
				bar(maxx/2+92,maxy/2+50-39,maxx/2+142,maxy/2+50-19);
				input(maxx/2+94,maxy/2+9,4,1,BLACK,LIGHTGRAY,input_str,0);
			}
		}
	}
}
void draw_sign_in(void)
{
	int maxx,maxy;
	char *string1="��¼";
	char *string2="ע��";
	char *string3="�˳�";
	char *string4="�ο͵�¼";
	char *string5="��������";
	char *string6="�˺�";
	char *string7="����";
	char *string8="֤ȯģ��ϵͳ";

	maxx=getmaxx();
	maxy=getmaxy();

	setfillstyle(1,RED);
	bar(maxx/2-210,maxy/2-160,maxx/2+210,maxy/2+160);
	setfillstyle(1,WHITE);
	bar(maxx/2-200,maxy/2-150,maxx/2+200,maxy/2+150);
	setcolor(BLACK);
	rectangle(maxx/2+50,maxy/2+50-39,maxx/2+90,maxy/2+50-19);

	setfillstyle(1,LIGHTGRAY);
	bar(maxx/2-135,maxy/2+33,maxx/2-60,maxy/2+67);
	bar(maxx/2-35,maxy/2+33,maxx/2+35,maxy/2+67);
	bar(maxx/2+60,maxy/2+33,maxx/2+135,maxy/2+67);
	bar(maxx/2-56,maxy/2+77,maxx/2+56,maxy/2+111);
	bar(maxx/2-70,maxy/2-53,maxx/2+130,maxy/2-26);
	bar(maxx/2-70,maxy/2-19,maxx/2+130,maxy/2+8);
	bar(maxx/2+92,maxy/2+50-39,maxx/2+142,maxy/2+50-19);

	setcolor(DARKGRAY);
	line(maxx/2-59,maxy/2+33,maxx/2-59,maxy/2+68);
	line(maxx/2-135,maxy/2+68,maxx/2-59,maxy/2+68);
	line(maxx/2+36,maxy/2+33,maxx/2+36,maxy/2+68);
	line(maxx/2-35,maxy/2+68,maxx/2+36,maxy/2+68);
	line(maxx/2+136,maxy/2+33,maxx/2+136,maxy/2+68);
	line(maxx/2+60,maxy/2+68,maxx/2+136,maxy/2+68);
	line(maxx/2+57,maxy/2+77,maxx/2+57,maxy/2+112);
	line(maxx/2-56,maxy/2+112,maxx/2+57,maxy/2+112);

	put_hz(maxx/2-130,maxy/2+50-12,string1,RED,24,12);
	put_hz(maxx/2-30,maxy/2+50-12,string2,RED,24,12);
	put_hz(maxx/2+70,maxy/2+50-12,string3,RED,24,12);
	put_hz(maxx/2-51,maxy/2+50+32,string4,RED,24,2);
	put_hz(maxx/2-100,maxy/2+50-38,string5,BLACK,16,2);
	put_hz(maxx/2-2,maxy/2+50-38,"��֤��",BLACK,16,2);

	put_hz(maxx/2-130,maxy/2-50,string6,RED,24,6);
	put_hz(maxx/2-130,maxy/2-16,string7,RED,24,6);
	put_hz(maxx/2-106,maxy/2-120,string8,BLACK,32,4);
}
void draw_new_login(void)
{
	int maxx,maxy;
	
	maxx=getmaxx();
	maxy=getmaxy();
	setfillstyle(1, RED);
	bar(maxx/2-210,maxy/2-160,maxx/2+210,maxy/2+160);
	setfillstyle(1, WHITE);
	bar(maxx/2-200,maxy/2-150,maxx/2+200,maxy/2+150);
	setfillstyle(1, LIGHTGRAY);
	bar(maxx / 2 - 70, maxy / 2 - 104, maxx / 2 + 150, maxy / 2 -80 );
	bar(maxx / 2 - 70, maxy / 2 - 54, maxx / 2 + 150, maxy / 2 - 30);
	bar(maxx / 2 - 70, maxy / 2 - 4, maxx / 2 + 150, maxy / 2 +20 );
	bar(maxx/2-70,maxy/2+46,maxx/2+150,maxy/2+70);
	bar(maxx / 2 +10, maxy / 2 + 80, maxx / 2 + 90, maxy / 2 + 124);
	bar(maxx / 2 - 90, maxy / 2 + 80, maxx / 2 - 10, maxy / 2 + 124);

	put_hz(maxx / 2 - 140, maxy / 2 - 100, "�û��˺�", BLACK, 16, 1);
	put_hz(maxx / 2 - 140, maxy / 2 - 50, "��������",BLACK, 16, 1);
	put_hz(maxx / 2 - 140, maxy / 2, "ȷ������",BLACK, 16, 1);
	put_hz(maxx/2-140,maxy/2+50,"���֤��",BLACK,16,1);
	put_hz(maxx / 2 - 80, maxy / 2 + 90, "ע��", RED, 24, 12);
	put_hz(maxx / 2 + 20, maxy / 2 + 90, "����", BLACK, 24, 12);
}
int new_login(int maxx,int maxy)										//���û�ע��
{
	
	int mx,my,mbtn=-1;
	char account[8] ={'\0'},password_1[10]={'\0'},password_2[10]={'\0'},ID_number[19]={'\0'};
	draw_new_login();
	
	mouse_save(0,0);
	clearbuffer();
	
	while (1)
	{
		newmouse(&mx, &my, &mbtn);
		if (mbtn == 0)
		{
			if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128&& my>maxy / 2 -104 && my < maxy / 2 - 85)
				setmouseshape(0);
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 54 && my < maxy /2- 35)
				setmouseshape(0);
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 +128 && my>maxy / 2 -4 && my < maxy / 2 + 15)
				setmouseshape(0);
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 +128 && my>maxy / 2 +46&& my < maxy / 2 + 65)
				setmouseshape(0);
			else if (mx > maxx / 2 - 90 && mx<maxx / 2 -10 && my>maxy / 2 + 80 && my < maxy / 2 + 124)
				setmouseshape(2);
			else if (mx > maxx / 2 +10 && mx<maxx / 2 + 90 && my>maxy / 2 + 80 && my < maxy / 2 + 124)
				setmouseshape(2);
			else
				setmouseshape(1);
		}
		else if (mbtn == 1)
		{
			if (mx > maxx / 2 + 10 && mx<maxx / 2 + 90 && my>maxy / 2 + 80 && my < maxy / 2 + 124)			//�����˷��ؼ�
			{
				mousehide(mx,my);
				setmouseshape(1);
				delay(100);
				cleardevice();
				return 0;
			}
			else if (mx > maxx/2-90&& mx<maxx/2-10&& my>maxy/2+80&&my<maxy /2+ 124)	//ע��
			{
				mousehide(mx,my);
				setmouseshape(2);
				delay(100);
				if(new_login_(account,password_1,password_2,ID_number)==0)		//ע��ɹ�
				{
					return 0;
				}
			}
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 104 && my < maxy / 2 - 85)
			{
				mousehide(mx, my);
				bar(maxx / 2 - 70, maxy / 2 - 104, maxx / 2 + 130, maxy / 2 -80 );
				input(maxx / 2 - 65, maxy / 2 - 104,7,1,RED,LIGHTGRAY,account,0);
			}
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 54 && my < maxy / 2 - 35)
			{
				mousehide(mx, my);
				bar(maxx / 2 - 70, maxy / 2 - 54, maxx / 2 + 130, maxy / 2 - 30);
				input(maxx / 2 - 65, maxy / 2 - 54, 9,1, RED,LIGHTGRAY,password_1,1);
			}
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 4 && my < maxy / 2 + 15)
			{
				mousehide(mx, my);
				bar(maxx / 2 - 70, maxy / 2 - 4, maxx / 2 + 130, maxy / 2 +20 );
				input(maxx / 2 - 65, maxy / 2 - 4,9,1,RED,LIGHTGRAY,password_2,1);
			}
			else if(mx > maxx / 2 - 70 && mx<maxx / 2 +128 && my>maxy / 2 +46&& my < maxy / 2 + 65)
			{
				mousehide(mx,my);
				bar(maxx/2-70,maxy/2+46,maxx/2+130,maxy/2+70);
				input(maxx/2-65,maxy/2+46,18,1,RED,LIGHTGRAY,ID_number,0);
			}
		}
	}
}
int new_login_(char *id,char *password_1,char *password_2,char *ID_number)	//�ж��Ƿ�ע��ɹ���ע��ɹ�����0
{

	FILE *fp,*fq;
	char flag=0;
	char temp[50]="USER\\";
	char temp_1[30];
	char temp_2[30];
	char temp_3[30];
	char temp_4[30];
	char temp_5[30];
	double balance_sum[5]={200000.0,200000.0,0.0,0.0,200000.0};		//��ʼ���˻����
	int i=0;
	int maxx=getmaxx();
	int maxy=getmaxy();	
	strcat(temp,id);
	if(mkdir(temp))													//ÿһ���û���������һ���ļ��д洢�û���Ϣ
	{
		printf("Unable to create directory\n");
		getch();
		exit(1);
	}
	strcat(temp,"\\");
	strcpy(temp_1,temp);
	strcpy(temp_2,temp);
	strcpy(temp_3,temp);
	strcpy(temp_4,temp);
	strcpy(temp_5,temp);
	strcat(temp,"own.txt");
	
	setfillstyle(1,BLACK);
	bar(maxx/2-113,maxy/2-65,maxx/2+113,maxy/2+65);
	setfillstyle(1,LIGHTGRAY);
	bar(maxx/2-108,maxy/2-60,maxx/2+108,maxy/2+60);
	put_hz(maxx/2-90,maxy/2+6,"����������أ�",RED,24,2);

	if(id[0]=='\0')
		flag=1;
	else if(password_1[0]=='\0')
		flag=2;
	else if(ID_number[0]=='\0')
		flag=3;
	else if(strcmp(password_1,password_2)!=0)
		flag=4;
	else if((fq=fopen(temp,"rt"))!=NULL)
	{
		fclose(fq);
		flag=5;
	}
	else
	{
		if((fp=fopen(temp,"wb"))==NULL)
		{
			printf("can't build the file!\n");
			getch();
			fclose(fp);
			exit(1);
		}
		fwrite(password_1,10,1,fp);
		fwrite(ID_number,20,1,fp);									//ʮ��λ���֤��
		fwrite(&balance_sum[0],sizeof(double),1,fp);
		fwrite(&balance_sum[1],sizeof(double),1,fp);
		fwrite(&balance_sum[2],sizeof(double),1,fp);
		fwrite(&balance_sum[3],sizeof(double),1,fp);
		fwrite(&balance_sum[4],sizeof(double),1,fp);
		fclose(fp);
		
		strcat(temp_1,"Balance.txt");
		if((fp=fopen(temp_1,"wt"))==NULL)
		{
			printf("can not build the Balance.txt\n");
			getch();
			fclose(fp);
			exit(1);
		}
		fprintf(fp,"%d",i);
		fprintf(fp,"%c",'\n');
		//fwrite(&i,sizeof(int),1,fp);
		//fwrite("\n",1,1,fp);
		//fwrite("limoyang\n",10,1,fp);
		//fwrite("limoyang\n",9,1,fp);
		fclose(fp);
		
		strcat(temp_2,"Deal.txt");
		if((fp=fopen(temp_2,"wt"))==NULL)
		{
			printf("can not build the Deal.txt\n");
			getch();
			fclose(fp);
			exit(1);
		}
		fprintf(fp,"%d",i);
		fprintf(fp,"%c",'\n');
		//fwrite(&i,sizeof(int),1,fp);
		//fwrite("\n",1,1,fp);
		fclose(fp);
		
		strcat(temp_3,"Delegat.txt");
		if((fp=fopen(temp_3,"wt"))==NULL)
		{
			printf("can not build the Delegat.txt\n");
			getch();
			fclose(fp);
			exit(1);
		}
		fprintf(fp,"%d",i);
		fprintf(fp,"%c",'\n');
		//fwrite(&i,sizeof(int),1,fp);
		//fwrite("\n",1,1,fp);
		fclose(fp);
		
		strcat(temp_4,"Hold.txt");
		if((fp=fopen(temp_4,"wt"))==NULL)
		{
			printf("can not build the Hold.txt\n");
			getch();
			fclose(fp);
			exit(1);
		}
		fprintf(fp,"%d",i);
		fprintf(fp,"%c",'\n');
		//fwrite(&i,sizeof(int),1,fp);
		//fwrite("\n",1,1,fp);
		fclose(fp);
		
		strcat(temp_5,"stock.txt");
		if((fp=fopen(temp_5,"wt"))==NULL)
		{
			printf("can not build the stock.txt\n");
			getch();
			fclose(fp);
			exit(1);
		}
		fprintf(fp,"%d",i);
		fprintf(fp,"%c",'\n');
		//fwrite(&i,sizeof(int),1,fp);
		//fwrite("\n",1,1,fp);
		fclose(fp);
		
		put_hz(maxx/2-64,maxy/2-30,"ע��ɹ���",RED,24,2);
		clearbuffer();
		getch();
		cleardevice();
		return 0;
	}

	switch(flag)
	{
		case 1:
			put_hz(maxx/2-77,maxy/2-30,"�������˺ţ�",RED,24,2);
			break;
		case 2:
			put_hz(maxx/2-77,maxy/2-30,"���������룡",RED,24,2);
			break;
		case 3:
			put_hz(maxx/2-103,maxy/2-30,"���������֤�ţ�",RED,24,2);
			break;
		case 4:
			put_hz(maxx/2-103,maxy/2-30,"�������벻һ�£�",RED,24,2);
			break;
		case 5:
			put_hz(maxx/2-103,maxy/2-30,"���û����Ѵ��ڣ�",RED,24,2);
	}
	fclose(fp);
	fclose(fq);
	clearbuffer();

	getch();
	draw_new_login();
	return 1;
}
int old_login(int maxx,int maxy,char *id,char *password,char *rand_str,char *input_str)  	//�ж����û���¼�Ƿ�ɹ����ɹ�����1
{
	FILE *fq;
	char temp[30]="USER\\",user_password[10]={'\0'};
	char flag=0;
	char *str1="�������û�����";
	char *str2="���������룡";
	char *str3="���û��������ڣ�";
	char *str4="�������";
	char *str5="����������أ�";
	char *str6="��½�ɹ���";
	//void *buffer;																			//���ѣ�������ʹ��buffer����ͼƬ��������ڴ��������
	//unsigned s;
	strcat(temp,id);
	strcat(temp,"\\");
	strcat(temp,"own.txt");
	fq=fopen(temp,"rt");
	fread(user_password,10,1,fq);
	//s=imagesize(maxx/2-113,maxy/2-65,maxx/2+113,maxy/2+65);
	//if((buffer=malloc(s))==NULL)
	//{
	//	printf("no room");
	//	exit(1);
	//}
	//getimage(maxx/2-113,maxy/2-65,maxx/2+113,maxy/2+65,buffer);
	if(id[0]=='\0')
	{
		flag=1;
	}
	
	else if(password[0]=='\0')
	{
		flag=2;
	}
	else if(input_str[0]=='\0')
	{
		flag=5;
	}
	else if(fq==NULL)
	{
		flag=3;
	}
	else if(strcmp(user_password,password)!=0)
	{
		flag=4;
	}
	else if(strcmp(rand_str,input_str)!=0)
	{
		flag=6;
	}
	
	fclose(fq);
	setfillstyle(1,BLACK);
	bar(maxx/2-113,maxy/2-65,maxx/2+113,maxy/2+65);
	setfillstyle(1,LIGHTGRAY);
	bar(maxx/2-108,maxy/2-60,maxx/2+108,maxy/2+60);
	put_hz(maxx/2-90,maxy/2+6,str5,RED,24,2);
	switch (flag)
	{
		case 0:
			put_hz(maxx/2-64,maxy/2-30,str6,RED,24,2);
			clearbuffer();
			getch();
			return 1;
		case 1:
			put_hz(maxx/2-90,maxy/2-30,str1,RED,24,2);
			break;
		case 2:
			put_hz(maxx/2-77,maxy/2-30,str2,RED,24,2);
			break;
		case 3:
			put_hz(maxx/2-103,maxy/2-30,str3,RED,24,2);
			break;
		case 4:
			put_hz(maxx/2-64,maxy/2-30,str4,RED,24,2);
			break;
		case 5:
			put_hz(maxx/2-90,maxy/2-30,"��������֤��",RED,24,2);
			break;
		case 6:
			put_hz(maxx/2-90,maxy/2-30,"��֤�벻��ȷ",RED,24,2);
			break;	
	}
	
	clearbuffer();
	
	getch();
	draw_sign_in();
	//putimage(maxx/2-113,maxy/2-65,buffer,0);
	//free(buffer);
	return 0;
}
void pass_change(void)				//�޸�����
{
	int mx,my,mbtn=-1,maxx,maxy;
	char account[8] ={'\0'},password_1[10]={'\0'},password_2[10]={'\0'},ID_number[20]={'\0'};
	maxx=getmaxx();
	maxy=getmaxy();
	
	draw_new_login();
	bar(maxx / 2 - 90, maxy / 2 + 80, maxx / 2 - 10, maxy / 2 + 124);
	put_hz(maxx / 2 - 80, maxy / 2 + 90, "�޸�", RED, 24, 12);

	mouse_save(0,0);
	while (1)
	{

		newmouse(&mx, &my, &mbtn);
		if (mbtn == 0)
		{
			if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128&& my>maxy / 2 -104 && my < maxy / 2 - 85)
				setmouseshape(0);
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 54 && my < maxy /2- 35)
				setmouseshape(0);
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 +128 && my>maxy / 2 -4 && my < maxy / 2 + 15)
				setmouseshape(0);
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 +128 && my>maxy / 2 +46&& my < maxy / 2 + 65)
				setmouseshape(0);
			else if (mx > maxx / 2 - 90 && mx<maxx / 2 -10 && my>maxy / 2 + 80 && my < maxy / 2 + 124)
				setmouseshape(2);
			else if (mx > maxx / 2 +10 && mx<maxx / 2 + 90 && my>maxy / 2 + 80 && my < maxy / 2 + 124)
				setmouseshape(2);
			else
				setmouseshape(1);
		}
		else if (mbtn == 1)
		{
			if (mx > maxx / 2 + 10 && mx<maxx / 2 + 90 && my>maxy / 2 + 80 && my < maxy / 2 + 124)		//�����˷��ؼ�
			{
				mousehide(mx,my);
				setmouseshape(1);
				delay(100);
				cleardevice();
				return;
			}
			else if (mx > maxx/2-90&& mx<maxx/2-10&& my>maxy/2+80&&my<maxy /2+ 124)		//�޸�
			{
				mousehide(mx,my);
				setmouseshape(2);
				delay(100);
				if(pass_change_(account,password_1,password_2,ID_number)==0)			//�޸�����ɹ�
				{
					return;
				}
			}
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 104 && my < maxy / 2 - 85)
			{
				mousehide(mx, my);
				bar(maxx / 2 - 70, maxy / 2 - 104, maxx / 2 + 130, maxy / 2 -80 );
				input(maxx / 2 - 65, maxy / 2 - 104,7,1,RED,LIGHTGRAY,account,0);
			}
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 54 && my < maxy / 2 - 35)
			{
				mousehide(mx, my);
				bar(maxx / 2 - 70, maxy / 2 - 54, maxx / 2 + 130, maxy / 2 - 30);
				input(maxx / 2 - 65, maxy / 2 - 54, 9,1, RED,LIGHTGRAY,password_1,1);
			}
			else if (mx > maxx / 2 - 70 && mx<maxx / 2 + 128 && my>maxy / 2 - 4 && my < maxy / 2 + 15)
			{
				mousehide(mx, my);
				bar(maxx / 2 - 70, maxy / 2 - 4, maxx / 2 + 130, maxy / 2 +20 );
				input(maxx / 2 - 65, maxy / 2 - 4,9,1,RED,LIGHTGRAY,password_2,1);
			}
			else if(mx > maxx / 2 - 70 && mx<maxx / 2 +128 && my>maxy / 2 +46&& my < maxy / 2 + 65)
			{
				mousehide(mx,my);
				bar(maxx/2-70,maxy/2+46,maxx/2+130,maxy/2+70);
				input(maxx/2-65,maxy/2+46,18,1,RED,LIGHTGRAY,ID_number,0);
			}
		}
	}
}
int pass_change_(char *id,char *password_1,char *password_2,char *ID_number)//�ж������Ƿ��޸ĳɹ��������޸ĳɹ�����0
{
	FILE *fq;
	char flag=0;
	char temp[30]="USER\\",account[20];										//account�Ƕ�ȡ���Ѿ����ڵ��˻����û�ID_number
	char pass_pre[10];
	int maxx,maxy;
	account[0]='\0';

	maxx=getmaxx();
	maxy=getmaxy();
	strcat(temp,id);
	strcat(temp,"\\");
	strcat(temp,"own.txt");

	setfillstyle(1,BLACK);
	bar(maxx/2-113,maxy/2-65,maxx/2+113,maxy/2+65);
	setfillstyle(1,LIGHTGRAY);
	bar(maxx/2-108,maxy/2-60,maxx/2+108,maxy/2+60);
	put_hz(maxx/2-90,maxy/2+6,"����������أ�",RED,24,2);
	fq=fopen(temp,"rt+");
	fread(pass_pre,10,1,fq);
	fread(account,20,1,fq);

	if(id[0]=='\0')
		flag=1;

	else if(ID_number[0]=='\0')
		flag=3;

	else if(fq==NULL)
	{
		fclose(fq);
		flag=5;
	}

	else if(strcmp(ID_number,account)!=0)
		flag=6;

	else if(password_1[0]=='\0')
		flag=2;

	else if(strcmp(password_1,password_2)!=0)
		flag=4;

	else
	{
		rewind(fq);
		//strcpy(pass_pre,password_1);
		fwrite(password_1,10,1,fq);
		fclose(fq);
		put_hz(maxx/2-90,maxy/2-30,"�����޸ĳɹ���",RED,24,2);
		clearbuffer();
		getch();
		cleardevice();
		return 0;
	}

	switch(flag)
	{
		case 1:
			put_hz(maxx/2-77,maxy/2-30,"�������˺ţ�",RED,24,2);
			break;
		case 2:
			put_hz(maxx/2-77,maxy/2-30,"���������룡",RED,24,2);
			break;
		case 3:
			put_hz(maxx/2-103,maxy/2-30,"���������֤�ţ�",RED,24,2);
			break;
		case 4:
			put_hz(maxx/2-103,maxy/2-30,"�������벻һ�£�",RED,24,2);
			break;
		case 5:
			put_hz(maxx/2-103,maxy/2-30,"���û��������ڣ�",RED,24,2);
			break;
		case 6:
			put_hz(maxx/2-103,maxy/2-30,"�û������Ϣ����",RED,24,2);
			break;
	}
	
	clearbuffer();			//�˴�ʹ��clearbuffer��Ϊ�˷�ֹ������ʱ���������ַ����»������м�ֵ��ʹ��δ�����屨��ͷ���
	getch();
	draw_new_login();
	bar(maxx / 2 - 90, maxy / 2 + 80, maxx / 2 - 10, maxy / 2 + 124);
	put_hz(maxx / 2 - 80, maxy / 2 + 90, "�޸�", RED, 24, 12);
	return 1;
}
void random_str(char *str)
{
	char a,b,i;
	randomize();
	for(i=0;i<4;i++)
	{	
		a=random(26);		//����һ��[0,25]�������
		b=random(2);		//����һ��[0,1]�������
		if(b==0)
			a+=65;
		else if(b==1)
			a+=97;
		str[i]=a;
	}
	str[4]='\0';
}