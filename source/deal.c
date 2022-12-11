#include "deal.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:			deal.c
  Author:       		��ī��
  Version:				1.0 
  Date:					18/11/05
  Description:  		��Ʊ���׽��溯��
  Function List: 
    put_point			��Сͼ��	
	deal_draw			�����׽���
	draw_recharge		����ֵ����
	deal				�����ܿ��ƺ���
	deal_press			��ⰴ���ܿغ���
	get_pre_price		��ʼ����Ʊ�۸��������Ϣ
	new_price			�����ּۺ��Ƿ�
	page1_draw			��������������
	page2_draw			������ί�н���
	page3_draw			�ʽ�֤ȯ��ˮ����
	page4_draw			���ճɽ�����ʷ�ɽ�����
	page5_draw			��ѯ�����˵�
	page6_draw			�ֲֽ���
	page7_draw			�м�ί�в˵�
	excel_1				�ֱֲ��
	excel_2				�ɽ����
	draw_tri			��С����
	page_draw			��ͼ�ܿ��ƺ���
	get_time			��ȡʱ��
	change_own			��ѡ���׽���뽻����
	signal_all			��λ���Բ��
	get_data_length		��ȡ���������ݳ���
	init_delegate		��ʼ��ί������
	init_hold			��ʼ���ֲ�����
	init_balance		��ʼ���û��������
	init_deal			��ʼ����������
	init_own			��ʼ���û���Ϣ
	input_deal			�û������Ʊ����
	show_deal_			������ʾ�ܿ��ƺ���
	show_data_1			�������������ʼ������ʾ
	page_judge_1		��һ�ֲ˵������״̬�ж�
	page_judge_2		��һ�ֲ˵������״̬�ж�
	page_judge_3		�����ֲ˵������״̬�ж�
  History:      
	<author>  <time>   <version >   <desc>
	��ī��    18/11/05     1.0     build this moudle  
*************************************************/

void deal_draw(void)
{
	char buy[16][20]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0},
					  {0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
					  {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
					  {1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1}};
					  
   char sale[16][20]={{1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
					  {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
					  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
					  {0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0},
					  {0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
					  
	char refund[16][20]={{1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
						 {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
						 {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1},
						 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
						 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
						 {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1},
						 {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
						 {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},};
						 
	char gofind[16][20]={{1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
						 {1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
						 {1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
						 {1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
						 {1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
						 {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
						 {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
						 {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1},
						 {1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},
						 {1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1},
						 {1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1},
						 {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
						 {1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
						 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
						 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
						 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1},};
						 
  char delegate[16][20]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
						 {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
						 {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
						 {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
						 {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},};	  
	menu_create();
	setcolor(WHITE);
	line(10,60,10,470);
	line(10,60,140,60);
	line(140,60,140,21);
	line(140,21,270,21);
	line(270,21,284,60);
	line(284,60,629,60);
	line(629,60,629,470);
	line(10,470,629,470);
	line(13,100,135,100);
	line(13,130,135,130);
	line(13,160,135,160);
	line(13,190,135,190);
	line(13,220,135,220);
	put_point(buy,15,81);
	put_point(sale,15,111);
	put_point(refund,15,141);
	put_point(gofind,15,171);
	put_point(delegate,15,201);
	put_hz(38,75,"����",WHITE,24,2);
	put_hz(38,105,"����",WHITE,24,2);
	put_hz(38,135,"����",WHITE,24,2);
	put_hz(38,165,"��ѯ",WHITE,24,2);
	put_hz(38,195,"�м�ί��",WHITE,24,0);
	put_hz(158,34,"��֤A��",LIGHTBLUE,24,2);
	put_hz(10,30,"�˳�",CYAN,24,2);
	put_hz(75,30,"����",CYAN,24,2);
	put_hz(570,440,"��ֵ",CYAN,24,2);
}

void draw_recharge(void)
{
	cleardevice();
	deal_draw();
	setfillstyle(1,BLACK);
	bar(10,30,60,53);
	setfillstyle(1,WHITE);
	bar(140,80,620,371);
	setcolor(BLACK);
	rectangle(142,82,618,369);
	rectangle(145,85,615,366);
	put_hz(210,130,"�û��˻�",BLACK,24,2);
	put_hz(210,190,"�û�����",BLACK,24,2);
	put_hz(210,250,"��ֵ���",BLACK,24,2);
	rectangle(317,126,550,158);
	rectangle(317,186,550,218);
	rectangle(317,246,550,278);
	//rectangle(270,300,328,332);
	//rectangle(432,300,490,332);
	put_hz(314,304,"��ֵ",BLACK,24,2);
	put_hz(396,304,"����",BLACK,24,2);
}

void put_point(char str[16][20],int x,int y)
{
	int i,j;
	for(i=0;i<16;i++)
	{
		for(j=0;j<20;j++)
		{
			if(str[i][j]==0)
				putpixel(x+j,y+i,WHITE);
		}
	}
}

void page1_draw(void)			//��������������
{
	cleardevice();
	deal_draw();
	setfillstyle(1,WHITE);
	setcolor(BLACK);
	bar(140,80,370,400);
	bar(385,80,620,400);
	put_hz(150,100,"�ɶ�����:",BLACK,16,1);
	rectangle(223,95,350,121);
	
	put_hz(150,136,"֤ȯ����:",BLACK,16,1);
	rectangle(223,131,350,157);
	
	put_hz(150,172,"�����۸�:",BLACK,16,1);
	rectangle(223,167,350,193);		//��/�����۸�
	
	draw_tri(0,143);				//��������������
	put_hz(150,208,"�����ʽ�:",BLACK,16,1);
	rectangle(223,203,350,229);
	
	put_hz(150,244,"�����:",BLACK,16,1);
	rectangle(223,239,300,265);		//������/��
	setfillstyle(1,LIGHTBLUE);
	bar(310,239,350,265);
	put_hz(313,244,"ȷ��",BLACK,16,2);
	circle(160,290,7);
	circle(210,290,7);
	circle(260,290,7);
	circle(310,290,7);
	put_hz(168,282,"1/2",BLACK,16,1);
	put_hz(218,282,"1/3",BLACK,16,1);
	put_hz(268,282,"1/4",BLACK,16,1);
	put_hz(318,282,"1/5",BLACK,16,1);

	put_hz(150,315,"��������:",BLACK,16,1);
	rectangle(223,310,350,336);
	bar(165,346,240,382);
	bar(260,346,335,382);
	put_hz(177,352,"����",BLACK,24,3);
	put_hz(272,352,"�µ�",BLACK,24,3);
	
	put_hz(400,85,"��ǰ����",BLUE,24,0);
	setcolor(DARKGRAY);
	line(395,115,610,115);
	line(395,245,610,245);
	line(395,375,610,375);
	put_hz(400,380,"�ּ�:",BLACK,16,1);
	put_hz(500,380,"�ǵ�:",BLACK,16,1);
	put_hz(400,120,"����",BLACK,16,1);
	put_hz(400,146,"����",BLACK,16,1);
	put_hz(400,172,"����",BLACK,16,1);
	put_hz(400,198,"����",BLACK,16,1);
	put_hz(400,224,"��һ",BLACK,16,1);

	put_hz(400,250,"����",BLACK,16,1);
	put_hz(400,276,"����",BLACK,16,1);
	put_hz(400,302,"����",BLACK,16,1);
	put_hz(400,328,"���",BLACK,16,1);
	put_hz(400,354,"��һ",BLACK,16,1);
	setfillstyle(1,LIGHTCYAN);
	bar(486,120,516,136);
	bar(486,146,516,162);
	bar(486,172,516,188);
	bar(486,198,516,214);
	bar(486,224,516,240);
	setfillstyle(1,RED);
	bar(486,250,516,266);
	bar(486,276,516,292);
	bar(486,302,516,318);
	bar(486,328,516,344);
	bar(486,354,516,370);
	
}
void page2_draw(int my)			//����
{
	int i;
	cleardevice();
	deal_draw();
	put_hz(38,135,"����",BLUE,24,2);
	setfillstyle(1,WHITE);
	bar(140,100+my,620,420+my);
	setcolor(LIGHTBLUE);
	rectangle(143,103+my,617,417+my);
	rectangle(148,108+my,612,412+my);
	for(i=1;i<15;i++)
	{
		line(148,112+20*i+my,612,112+20*i+my);
	}
	for(i=1;i<7;i++)
	{
		line(148+66*i,108+my,148+66*i,412+my);
	}
	line(592,108+my,592,412+my);
	put_hz(149,113+my,"֤ȯ����",BLUE,16,1);
	put_hz(215,113+my,"֤ȯ����",BLUE,16,1);
	put_hz(281,113+my,"ί������",BLUE,16,1);
	put_hz(347,113+my,"ί�м۸�",BLUE,16,1);
	put_hz(413,113+my,"ί������",BLUE,16,1);
	put_hz(478,113+my,"ί��ʱ��",BLUE,16,1);
	put_hz(552,113+my,"����",BLUE,16,2);
}

void page3_draw(void)			//���ʽ�֤ȯ��ˮ����ѯ
{
	int i;
	cleardevice();
	page5_draw();
	setfillstyle(1,WHITE);
	bar(140,80,620,130);	//���ʽ�֤ȯ�����
	bar(140,160,620,422);
	setcolor(BLACK);
	rectangle(142,82,618,128);
	rectangle(145,85,615,125);
	rectangle(142,162,618,420);
	rectangle(145,165,615,417);
	for(i=1;i<=4;i++)
	{
		line(145+i*94,85,145+i*94,125);
		line(145+i*94,165,145+i*94,417);
	}
	line(145,105,615,105);
	for(i=1;i<12;i++)
	{
		line(145,165+21*i,615,165+21*i);
	}
	put_hz(157,87,"�������",BLUE,16,2);
	put_hz(251,87,"�ʽ����",BLUE,16,2);
	put_hz(345,87,"�������",BLUE,16,2);
	put_hz(439,87,"֤ȯ��ֵ",BLUE,16,2);
	put_hz(542,87,"���ʲ�",BLUE,16,2);
	put_hz(20,195,"�����ˮ��ѯ",BLUE,16,0);
	
	put_hz(157,169,"�ɽ�����",BLUE,16,2);
	put_hz(157,190,"�ɽ�ʱ��",BLUE,16,2);
	put_hz(157,211,"֤ȯ����",BLUE,16,2);
	put_hz(157,232,"֤ȯ����",BLUE,16,2);
	put_hz(175,253,"����",BLUE,16,2);
	put_hz(157,274,"�ɽ�����",BLUE,16,2);
	put_hz(157,295,"�ɽ�����",BLUE,16,2);
	put_hz(157,316,"�ɽ����",BLUE,16,2);
	put_hz(157,337,"�������",BLUE,16,2);
	put_hz(166,358,"������",BLUE,16,2);
	put_hz(166,379,"ӡ��˰",BLUE,16,2);
	put_hz(157,400,"���ν��",BLUE,16,2);
}
void page4_draw(void)				//���ճɽ�������ʷ�ɽ�
{
	cleardevice();
	page5_draw();
	excel_2();
}

void page5_draw(void)			//��ѯ�����˵�
{
	void *buffer;
	unsigned s;
	int i;
	deal_draw();
	s=imagesize(15,203,34,216);
	buffer=malloc(s);
	getimage(15,203,34,216,buffer);
	deal_draw();
	setfillstyle(1,BLACK);
	bar(13,195,135,222);	//�����м�ί��
	putimage(15,324,buffer,COPY_PUT);
	free(buffer);
	put_hz(38,316,"�м�ί��",WHITE,24,0);
	
	put_hz(20,195,"�����ˮ��ѯ",WHITE,16,0);
	put_hz(20,220,"���ճɽ�",WHITE,16,0);
	put_hz(20,245,"����ί��",WHITE,16,0);
	put_hz(20,270,"��ʷ�ɽ�",WHITE,16,0);
	put_hz(20,295,"�ֲ�",WHITE,16,0);
	setcolor(WHITE);
	for(i=0;i<5;i++)
	{
		line(20,213+25*i,116,213+25*i);
	}	
	line(13,341,135,341);
	put_hz(38,165,"��ѯ",BLUE,24,2);
}
void page6_draw(void)			//�ֲ�
{
	cleardevice();
	page5_draw();
	put_hz(20,295,"�ֲ�",BLUE,16,0);
	excel_1();
}

void page7_draw(void)
{
	page1_draw();
	put_hz(38,195,"�м�ί��",BLUE,24,0);
	put_hz(38,225,"����",WHITE,16,2);
	put_hz(38,250,"����",WHITE,16,2);
	setcolor(WHITE);
	line(38,243,72,243);
	line(38,268,72,268);
	setfillstyle(1,WHITE);
	bar(150,167,350,193);
	setcolor(BLACK);
	rectangle(150,167,350,193);	
}
void excel_1(void)				//�ֲ��еı��
{
	int i;
	setfillstyle(1,WHITE);
	bar(140,80,620,371);
	setcolor(BLACK);
	rectangle(143,83,617,342);
	rectangle(147,87,613,338);
	for(i=1;i<=6;i++)
		line(151+66*i,87,151+66*i,338);
	for(i=1;i<12;i++)
		line(147,87+21*i,613,87+21*i);
	put_hz(151,90,"֤ȯ����",BLACK,16,0);
	put_hz(151,90+21,"֤ȯ����",BLACK,16,0);
	put_hz(151,90+2*21,"֤ȯ���",BLACK,16,0);
	put_hz(151,90+3*21,"�������",BLACK,16,0);
	put_hz(151,90+4*21,"��������",BLACK,16,0);
	put_hz(151,90+5*21,"��Ʊʵ��",BLACK,16,0);
	put_hz(156,90+6*21,"�ɱ���",BLACK,16,3);
	put_hz(164,90+7*21,"�м�",BLACK,16,3);
	put_hz(164,90+8*21,"��ֵ",BLACK,16,3);
	put_hz(151,90+9*21,"����ӯ��",BLACK,16,0);
	put_hz(151,90+10*21,"ӯ������",BLACK,16,0);
	put_hz(164,90+11*21,"��λ",BLACK,16,3);
	put_hz(161,348,"��һҳ",LIGHTBLUE,16,1);
	put_hz(550,348,"��һҳ",LIGHTBLUE,16,1);
}

void excel_2(void)				//���ճɽ�������ʷ�ɽ��б��
{
	int i;
	setfillstyle(1,WHITE);
	bar(140,80,620,420);	//�����ճɽ�������ʷ�ɽ�
	put_hz(149,90,"֤ȯ����",BLUE,16,0);
	put_hz(215,90,"֤ȯ����",BLUE,16,0);
	put_hz(295,90,"����",BLUE,16,4);
	put_hz(347,90,"�ɽ�����",BLUE,16,0);
	put_hz(413,90,"�ɽ�����",BLUE,16,0);
	put_hz(479,90,"�ɽ����",BLUE,16,0);
	put_hz(544,90,"�ɽ�ʱ��",BLUE,16,0);
	setcolor(BLUE);
	for(i=1;i<=6;i++)
		line(147+66*i,87,147+66*i,381);
	for(i=1;i<14;i++)
		line(147,87+21*i,613,87+21*i);
	rectangle(143,83,617,385);
	rectangle(147,87,613,381);
	put_hz(161,397,"��һҳ",LIGHTBLUE,16,1);
	put_hz(550,397,"��һҳ",LIGHTBLUE,16,1);
}

void draw_tri(int x,int y)
{
	setfillstyle(1,BLACK);
	line(x+337,y+178,x+345,y+178);
	line(x+337,y+178,x+341,y+170);
	line(x+345,y+178,x+341,y+170);
	floodfill(x+341,y+175,BLACK);
	line(x+337,y+183,x+345,y+183);
	line(x+337,y+183,x+341,y+191);
	line(x+341,y+191,x+345,y+183);
	floodfill(x+341,y+186,BLACK);
}
void page_draw(int flag)
{
	setfillstyle(1,BLACK);
	bar(13,190,135,366);
	switch(flag)
	{
		case 1:	page1_draw();
				draw_tri(0,0);
				put_hz(38,75,"����",BLUE,24,2);
				break;
		case 2:	page1_draw();
				draw_tri(0,0);
				put_hz(38,105,"����",BLUE,24,2);
				break;
		case 3:	page2_draw(0);
				setcolor(WHITE);
				line(158,95,256,95);
				line(278,95,329,95);
				put_hz(158,70,"ȫ��ѡ��",WHITE,24,1);
				put_hz(278,70,"����",WHITE,24,4);
				break;
		case 4:	page5_draw();
				break;
		case 41:page3_draw();			//�ʽ�֤ȯ���
				break;
		case 42:page4_draw();
				put_hz(20,220,"���ճɽ�",BLUE,16,0);
				break;
		case 43:page2_draw(-30);
				page5_draw();
				put_hz(20,245,"����ί��",BLUE,16,0);		//����ί��
				break;
		case 44:page4_draw();
				put_hz(20,270,"��ʷ�ɽ�",BLUE,16,0);
				break;
		case 45:page6_draw();						//�ֲ�
				break;
		case 5:	deal_draw();
				put_hz(38,195,"�м�ί��",BLUE,24,0);
				put_hz(38,225,"����",WHITE,16,2);
				put_hz(38,250,"����",WHITE,16,2);
				setcolor(WHITE);
				line(38,243,72,243);
				line(38,268,72,268);
				break;
		case 51:page7_draw();
				put_hz(38,225,"����",BLUE,16,2);		
				break;
		case 52:page7_draw();
				put_hz(38,250,"����",BLUE,16,2);
				break;
		case 6: draw_recharge();
				break;
	}
}
void get_time(struct tm *time_p,int *second)	//ʵʱ����ʱ��
{
	time_t timep;
	struct tm *p;				//�赥������һ��stuct tm time_p�ṹ�����ڴ洢����
	char time_str[50];
	char temp[5][6];
	char week_day[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    timep=time(NULL);
    p=localtime(&timep);

	itoa(1900+p->tm_year,time_str,10);
	strcat(time_str,"-");
	itoa(1+p->tm_mon,temp[0],10);
	strcat(time_str,temp[0]);
	strcat(time_str,"-");
	itoa(p->tm_mday,temp[1],10);
	strcat(time_str,temp[1]);
	strcat(time_str," ");
	strcat(time_str,week_day[p->tm_wday]);
	strcat(time_str," ");
	itoa(p->tm_hour,temp[2],10);
	strcat(time_str,temp[2]);
	strcat(time_str,":");
	itoa(p->tm_min,temp[3],10);
	strcat(time_str,temp[3]);
	strcat(time_str,":");
	itoa(p->tm_sec,temp[4],10);
	strcat(time_str,temp[4]);
	if(*second!=p->tm_sec)
	{
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(2,0,7);
		setfillstyle(1,BLACK);
		bar(290,35,640,55);
		setcolor(WHITE);
		outtextxy(290,30,time_str);
		*second=p->tm_sec;
	}
	time_p->tm_year=p->tm_year;
	time_p->tm_mon=p->tm_mon;
	time_p->tm_mday=p->tm_mday;
	time_p->tm_hour=p->tm_hour;
	time_p->tm_min=p->tm_min;
	//printf("%d\n",p->tm_sec); /*��ȡ��ǰ��*/

	//printf("%d\n",p->tm_min); /*��ȡ��ǰ��*/

	//printf("%d\n",8+p->tm_hour);/*��ȡ��ǰʱ,�����ȡ������ʱ��,�պ����˸�Сʱ*/

	//printf("%d\n",p->tm_mday);/*��ȡ��ǰ�·�����,��Χ��1-31*/

	//printf("%d\n",1+p->tm_mon);/*��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1*/

	//printf("%d\n",1900+p->tm_year);/*��ȡ��ǰ���,��1900��ʼ������Ҫ��1900*/

    //printf("%d\n",p->tm_yday); /*�ӽ���1��1�������������������ΧΪ0-365*/
}

void deal(INFO *info,int *mx_,int *my_,int *mbutn_)
{
	Delegate * delegate_head;
	Hold * hold_head;
	Balance * balance_head;			//��Ϊѭ��˫����������pend�б���ĵ�ַ��Ϣ�ᶪʧ������
	Deal * deal_head;
	int mx,my,mbuttn=-1;
	double balance_last;
	int flag=1,flag_last=1,time_second=0,time_minute=0,page_pointer=0,temp_num=0;//page_pointerָ���ǵ�ǰ��ҳ��ڼ�ҳ
	int length[7]={0,0,0,0,0,0,0};
	int length_pre=0;
	int flag_delet[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct tm time_p;
	Own own;
	strcpy(own.account,info->account);
	page1_draw();
	draw_tri(0,0);
	put_hz(38,75,"����",BLUE,24,2);
	mouse_save(mx,my);
	newmouse(&mx,&my,&mbuttn);
	get_time(&time_p,&time_second);
	/**��ʼ�������û�����**/
	init_own(&own);
	show_data_1(&own);
	delegate_head=init_delegate(own,delegate_head);
	hold_head=init_hold(own,hold_head);
	balance_head=init_balance(own,balance_head);
	deal_head=init_deal(own,deal_head);
	/**��ȡ�û����ݵ����г���**/
	get_data_length(&own,length);
	get_recall_num(delegate_head,length[0],&length[4]);
	get_today_deal(deal_head,length[3],&length[5],time_p);
	setmouseshape(2);
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(balance_last!=own.balance[0]&&(flag==1||flag==2||flag==51||flag==52))
		{
			show_data_1(&own);
			balance_last=own.balance[0];
		}
		
		get_time(&time_p,&time_second);
		if(time_p.tm_min!=time_minute)		//���ʱ�侭��һ���Ӹ���һ�μ۸�
		{
			new_price(&own,time_p);
			time_minute=time_p.tm_min;
			length_pre=length[2];
			balance_head=test_balance(&own,delegate_head,balance_head,hold_head,time_p,length);
			hold_head=hold_new_add(&own,balance_head,hold_head,length,time_p,length_pre);
			if(length[2]>length_pre)
			{
				deal_head=deal_new_add(&own,deal_head,balance_head,length,length_pre);
			}
			delegate_head=delet_pre_delegate(&own,delegate_head,time_p,length);
		}
		if(mouse_press(10,30,60,53,&mx,&my,&mbuttn))
		{
			free_all(delegate_head,hold_head,balance_head,deal_head,length);
			exit(0);
		}
		else if(mouse_press(75,30,125,53,&mx,&my,&mbuttn))
		{
			free_all(delegate_head,hold_head,balance_head,deal_head,length);
			info->layout=6;
			break;
		}
		else if(mouse_press(0,0,640,18,&mx,&my,&mbuttn))
		{
			info->flag=0;
			*mx_=mx;
			*my_=my;
			*mbutn_=mbuttn;
			free_all(delegate_head,hold_head,balance_head,deal_head,length);
			break;
		}
		if(flag==1||flag==2||flag==3||flag==6)
		{
			page_judge_1(&flag_last,&flag,mx,my,mbuttn);
		}
		else if(flag==5||flag==51||flag==52)
		{
			page_judge_3(&flag_last,&flag,mx,my,mbuttn);
		}
		else
		{
			page_judge_2(&flag_last,&flag,mx,my,mbuttn);
		}
		if(flag_last!=flag)
		{
			page_pointer=0;
			page_draw(flag);
			show_deal_(flag,&own,time_p,delegate_head,hold_head,balance_head,deal_head,length,page_pointer);
			flag_last=flag;
		}
		if(mouse_press(588,132,612,422,&mx,&my,&mbuttn)&&flag==3)
		{
			recall_num(my,flag_delet,length[4],page_pointer);
		}
		else if(mouse_press(278,70,328,94,&mx,&my,&mbuttn)&&flag==3)
		{
			delet_delegate(&own,flag_delet,delegate_head,length,page_pointer,hold_head);
		}
		else if(mouse_press(158,70,257,94,&mx,&my,&mbuttn)&&flag==3)
		{
			for(temp_num=0;temp_num<=length[4]-page_pointer,temp_num<=16;temp_num++)
			{
				recall_num(temp_num*20+142,flag_delet,length[4],page_pointer);
			}
		}
		if(mbuttn==1&&flag==1)	//����
		{
			own.flag=0;
			if(mouse_press(260,346,335,382,&mx,&my,&mbuttn)&&strcmp(own.stockcode,"")!=0&&own.num_own>0)	//�µ�
			{
				delegate_head=add_dalegate(&own,delegate_head,time_p,length,hold_head);
			}
			else
				deal_press(mx,my,mbuttn,&own,time_p,hold_head,length[1]);
		}
		else if(mbuttn==1&&flag==2)
		{
			own.flag=1;	//����
			if(mouse_press(260,346,335,382,&mx,&my,&mbuttn)&&strcmp(own.stockcode,"")!=0&&own.num_own>0)	//�µ�
			{
				delegate_head=add_dalegate(&own,delegate_head,time_p,length,hold_head);	
			}
			else
				deal_press(mx,my,mbuttn,&own,time_p,hold_head,length[1]);
		}
		else if(mbuttn==1&&flag==6)
		{
			recharge(&own,&flag,&flag_last);
			show_deal_(flag,&own,time_p,delegate_head,hold_head,balance_head,deal_head,length,page_pointer);
		}
		if(bioskey(1)!=0)
		{
			info->key.num=bioskey(0);
			if(info->key.num==F1||info->key.num==F2||info->key.num==F3
			  ||info->key.num==F4||info->key.num==F5||info->key.num==F6
			  ||info->key.num==F7||info->key.num==F8||info->key.num==F9||info->key.num==F10)
			{
				info->flag=2;
				free_all(delegate_head,hold_head,balance_head,deal_head,length);
				break;
			}
			else if(info->key.num==UP||info->key.num==DOWN)
			{
				page_up_down(info,&own,flag,time_p,&page_pointer,length,delegate_head,hold_head,balance_head,deal_head);
			}
		}
	}
}

void deal_press(int mx,int my,int mbuttn,Own *own,struct tm time_p,Hold *hold,int length)		//���������
{
	if(mouse_press(223,131,350,157,&mx,&my,&mbuttn))
	{
		input_deal(own,time_p,hold,length);
	}
	else if(mouse_press(165,346,240,382,&mx,&my,&mbuttn))	//����
	{
		signal_all(160,WHITE);
		own->stockname[0]='\0';
		own->stockcode[0]='\0';
		own->stock_now_price=0.0;
		own->stock_pre_price=0.0;
		own->num_max=0;
		own->price_own=0.0;
		own->num_own=0;
		own->stock_zuoshou=0.0;
		own->zhangfu=0.0;
		get_pre_price(own,time_p,hold,length);
		input_deal(own,time_p,hold,length);
	}
	else if(strcmp(own->stockcode,"")!=0)
	{
		change_own(own,mx,my,mbuttn);
	}
}

Delegate *init_delegate(Own own,Delegate *phead)
{
	FILE *fp;
	int i;
	char temp_str[40];
	Delegate *temp,*delegate;
	phead=NULL;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own.account);
	strcat(temp_str,"\\");
	strcat(temp_str,"delegat.txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file delegate.txt while init the data of stock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&i);
	//fread(&i,sizeof(int),1,fp);
	if(i<=0)
	{
		fclose(fp);
		return phead;
	}

	while(i>0&&!feof(fp))
	{
		if((delegate=(Delegate *)malloc(sizeof(Delegate)))==NULL)
		{
			printf("Allocation of delegate failed!!!");
			getch();
			exit(1);
		}
		fscanf(fp,"%s %s %ld %f %ld %d %d %d %d",
			   delegate->stockname,delegate->stockcode,&(delegate->dele_amount),&(delegate->dele_price),
			   &(delegate->date),&(delegate->time),&(delegate->flag),&(delegate->flag_),&(delegate->delet_flag));
		if(phead==NULL)
		{
			phead=delegate;
			phead->pre=NULL;
			phead->next=NULL;
		}
		else if(phead->next==NULL)
		{
			phead->next=delegate;
			phead->pre=delegate;
			delegate->next=phead;
			delegate->pre=phead;
		}
		else
		{
			temp=phead->pre;		//��temp���浱ǰ���һ���ڵ�
			temp->next=delegate;	//����ǰ���һ���ڵ�ĺ��ָ��delegate������ӵĽڵ�
			delegate->next=phead;	//���½ڵ�ĺ��ָ��ͷ�ڵ�
			delegate->pre=temp;		//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
			phead->pre=delegate;	//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
		}
		i--;
	}
	fclose(fp);
	return phead;
}
Hold *init_hold(Own own,Hold *phead)
{
	FILE *fp;
	int i;
	char temp_str[40];
	Hold *temp,*hold;
	phead=NULL;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own.account);
	strcat(temp_str,"\\");
	strcat(temp_str,"hold.txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file hold.txt while init the data of stock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&i);
	//fread(&i,sizeof(int),1,fp);
	if(i<=0)
	{
		fclose(fp);
		return phead;
	}
	
	while(i>0&&!feof(fp))
	{
		if((hold=(Hold *)malloc(sizeof(Hold)))==NULL)
		{
			printf("Allocation of hold failed!!!");
			getch();
			exit(1);
		}
		fscanf(fp,"%s %s %ld %ld %ld %ld %f %f %lf %lf %f %f %f",
				   hold->stockname,hold->stockcode,&(hold->stock_amount),&(hold->amount_avail),
				   &(hold->amount_blocked),&(hold->amount_real),&(hold->deal_price),&(hold->now_price),&(hold->hold_spend),
				   &(hold->market_value),&(hold->profit_loss_),&(hold->profit_loss_percent),&(hold->position));
		if(phead==NULL)
		{
			phead=hold;
			phead->pre=NULL;
			phead->next=NULL;
		}
		else if(phead->next==NULL)		//�����һ���ڵ�ʱ��ǰ����̶�ָ���Լ��������ѧ����
		{
			phead->next=hold;
			phead->pre=hold;
			hold->next=phead;
			hold->pre=phead;
		}
		else
		{
			temp=phead->pre;			//��temp���浱ǰ���һ���ڵ�
			temp->next=hold;			//����ǰ���һ���ڵ�ĺ��ָ��delegate������ӵĽڵ�
			hold->next=phead;			//���½ڵ�ĺ��ָ��ͷ�ڵ�
			hold->pre=temp;				//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
			phead->pre=hold;			//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
		}
		i--;
	}
	fclose(fp);
	return phead;
}
Balance *init_balance(Own own,Balance *phead)
{
	FILE *fp;
	int i;
	char temp_str[40];
	Balance *temp,*balance;
	phead=NULL;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own.account);
	strcat(temp_str,"\\");
	strcat(temp_str,"balance.txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file balance.txt while init the data of stock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&i);
	//fread(&i,sizeof(int),1,fp);
	if(i<=0)
	{
		fclose(fp);
		return phead;
	}

	while(i>0&&!feof(fp))
	{
		if((balance=(Balance *)malloc(sizeof(Balance)))==NULL)
		{
			printf("Allocation of balance failed!!!");
			getch();
			exit(1);
		}
		fscanf(fp,"%ld %d %s %s %d %d %ld %f %lf %lf %f %f %lf",
				   &(balance->deal_date),&(balance->deal_time),(balance->stockname),(balance->stockcode),&(balance->flag),
				   &(balance->flag_point),&(balance->deal_amount),&(balance->deal_price_ave),&(balance->deal_money),
				   &(balance->deal_money_real),&(balance->service_charge),&(balance->stamp_tax),&(balance->balance_now));
		if(phead==NULL)
		{
			phead=balance;
			phead->pre=NULL;
			phead->next=NULL;
		}
		else if(phead->next==NULL)		//�����һ���ڵ�ʱ��ǰ����̶�ָ���Լ��������ѧ����
		{
			phead->next=balance;
			phead->pre=balance;
			balance->next=phead;
			balance->pre=phead;
		}
		else
		{
			temp=phead->pre;		//��temp���浱ǰ���һ���ڵ�
			temp->next=balance;		//����ǰ���һ���ڵ�ĺ��ָ��delegate������ӵĽڵ�
			balance->next=phead;	//���½ڵ�ĺ��ָ��ͷ�ڵ�
			balance->pre=temp;		//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
			phead->pre=balance;		//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
		}
		i--;
	}
	fclose(fp);
	return phead;
}
Deal *init_deal(Own own,Deal *phead)
{
	FILE *fp;
	int i;
	char temp_str[40];
	Deal *temp,*deal;
	phead=NULL;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own.account);
	strcat(temp_str,"\\");
	strcat(temp_str,"deal.txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file deal.txt while init the data of stock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&i);
	//fread(&i,sizeof(int),1,fp);
	if(i<=0)
	{
		fclose(fp);
		return phead;
	}
	
	while(i>0&&!feof(fp))
	{
		if((deal=(Deal *)malloc(sizeof(Deal)))==NULL)
		{
			printf("Allocation of deal failed!!!");
			getch();
			exit(1);
		}
		fscanf(fp,"%ld %d %s %s %d %ld %f %lf",
				   &(deal->deal_date),&(deal->deal_time),deal->stockname,deal->stockcode,&(deal->flag),
				   &(deal->deal_amount),&(deal->deal_price_ave),&(deal->deal_money));
		if(phead==NULL)
		{
			phead=deal;
			phead->pre=NULL;
			phead->next=NULL;
		}
		else if(phead->next==NULL)		//�����һ���ڵ�ʱ��ǰ����̶�ָ���Լ��������ѧ����
		{
			phead->next=deal;
			phead->pre=deal;
			deal->next=phead;
			deal->pre=phead;
		}
		else
		{
			temp=phead->pre;			//��temp���浱ǰ���һ���ڵ�
			temp->next=deal;			//����ǰ���һ���ڵ�ĺ��ָ��delegate������ӵĽڵ�
			deal->next=phead;			//���½ڵ�ĺ��ָ��ͷ�ڵ�
			deal->pre=temp;				//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
			phead->pre=deal;			//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
		}
		i--;
	}
	fclose(fp);
	return phead;
}

void get_pre_price(Own *own,struct tm time_p,Hold *hold,int length)		//��ȡ��Ʊ�ּ�
{
	Hold *hold_temp;
	char temp_1[10],temp_2[10];
	setfillstyle(1,WHITE);
	bar(224,168,300,192);
	bar(224,240,299,264);
	bar(224,132,349,156);
	bar(224,168+143,300,192+143);
	//bar(443,380,490,396);
	//bar(543,380,610,396);
	signal_all(160,WHITE);
	new_price(own,time_p);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	setcolor(LIGHTBLUE);
	if(strcmp(own->stockcode,"")==0)
	{
		return;
	}
	else
	{
		own->price_own=own->stock_now_price;
		sprintf(temp_1,"%.2f",own->price_own);
		outtextxy(227,170,temp_1);
		if(own->flag==1&&(hold_temp=find_hold(hold,length,own->stockcode))==NULL)
		{
			own->num_max=0;
		}
		else if(own->flag==1&&(hold_temp=find_hold(hold,length,own->stockcode))!=NULL)
		{
			own->num_max=hold_temp->amount_avail;
		}
		sprintf(temp_2,"%ld",own->num_max);
		outtextxy(227,242,temp_2);
		outtextxy(227,134,own->stockcode);
		put_hz(285,137,own->stockname,BLACK,16,0);
	}
}

void new_price(Own *own,struct tm time_p)
{
	FILE *fp;
	char temp[40];
	char time_1[9],time_2[9],kai[7],shou[7],gao[7],di[7],str1[15],str2[20];
	char date[9],date_last[9],time[5],in_de_[8];
	setfillstyle(1,WHITE);
	setcolor(BLACK);
	if(strcmp(own->stockcode,"")==0)
	{
		return;
	}
	else
	{
		strcpy(temp,"data\\MIN\\1MIN\\TXT\\");
		strcat(temp,own->stockcode);
		strcat(temp,".txt");
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(2,0,6);
	}
	if((fp=fopen(temp,"rt"))==NULL)
	{
		printf("can't find the file 1MIN.txt of the stock!\n");
		getch();
		return;
	}
	sprintf(date_last,"%ld",((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1-1)*100+(long)time_p.tm_mday-98);
	if(100*(time_p.tm_hour)+time_p.tm_min<=930)					//������δ���̣���ʾǰ�����̼�
	{
		sprintf(date,"%ld",((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1-1)*100+(long)time_p.tm_mday-97);
		sprintf(time,"%d",1500);
	}
	else if(100*(time_p.tm_hour)+time_p.tm_min>1500)			//�����Ѿ����̣��������̼�
	{
		sprintf(date,"%ld",((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1-1)*100+(long)time_p.tm_mday-97);
		sprintf(time,"%d",1500);
	}
	else if(100*(time_p.tm_hour)+time_p.tm_min>1130&&100*(time_p.tm_hour)+time_p.tm_min<=1300)
	{
		sprintf(date,"%ld",((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1-1)*100+(long)time_p.tm_mday-97);
		sprintf(time,"%d",1130);
	}
	else
	{
		sprintf(date,"%ld",((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1-1)*100+(long)time_p.tm_mday-97);
		sprintf(time,"%d",time_p.tm_hour*100+time_p.tm_min);
	}
	for(;;)
	{
		if(feof(fp))
		{
			break;
		}
		else
		{
			fscanf(fp,"%s %s %s %s %s %s %s %s",time_1,time_2,kai,gao,di,shou,str1,str2);
			if(strcmp(date,time_1)==0&&strcmp(time,time_2)==0)	//�ж�ʱ��͵�ǰʱ���Ǻ�
			{
				own->stock_now_price=atof(shou);	
				if(own->stock_now_price!=own->stock_pre_price)
				{
					bar(443,380,490,396);
					outtextxy(443,377,shou);		
				}					
			}
			if(strcmp(date_last,time_1)==0&&strcmp("1500",time_2)==0)
			{
				own->stock_zuoshou=atof(shou);
				break;
			}
		}
	}
	if(own->stock_now_price!=own->stock_pre_price)
	{
		own->num_max=100*((long)(own->balance[0]/(110*own->stock_zuoshou)));	//�����������
		own->stock_pre_price=own->stock_now_price;
		own->zhangfu=(own->stock_now_price-own->stock_zuoshou)/own->stock_zuoshou*100;
		sprintf(in_de_,"%.2f",own->zhangfu);
		strcat(in_de_,"%");
		bar(543,380,610,396);
		outtextxy(543,377,in_de_);
	}
	fclose(fp);
}

void change_own(Own *own,int mx,int my,int mbuttn)
{
	char temp[7];
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	setfillstyle(1,WHITE);
	setcolor(LIGHTBLUE);
	if(mouse_press(335,168,347,178,&mx,&my,&mbuttn)&&own->price_own<1.1*own->stock_zuoshou)
	{
		own->price_own+=0.01;
		bar(224,168,300,192);
		sprintf(temp,"%.2f",own->price_own);
		outtextxy(227,170,temp);
	}
	else if(mouse_press(335,183,347,192,&mx,&my,&mbuttn)&&own->price_own>0.9*own->stock_zuoshou)
	{
		own->price_own-=0.01;
		bar(224,168,300,192);
		sprintf(temp,"%.2f",own->price_own);
		outtextxy(227,170,temp);
	}
	
	else if(mouse_press(335,168+143,347,178+143,&mx,&my,&mbuttn)&&own->num_own<own->num_max)
	{
		own->num_own+=100;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
	else if(mouse_press(335,183+143,347,192+143,&mx,&my,&mbuttn)&&own->num_own>=200)
	{
		own->num_own-=100;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
	else if(mouse_press(310,239,350,265,&mx,&my,&mbuttn))			//�������
	{
		signal_all(160,WHITE);
		own->num_own=own->num_max;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
	else if(mouse_press(153,283,167,297,&mx,&my,&mbuttn))			//1/2
	{
		signal_all(160,BLACK);
		own->num_own=((long)((float)own->num_max/200))*100;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
	else if(mouse_press(203,283,217,297,&mx,&my,&mbuttn))			//1/3
	{
		signal_all(210,BLACK);
		own->num_own=((long)((float)own->num_max/300))*100;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
	else if(mouse_press(253,283,267,297,&mx,&my,&mbuttn))			//1/4
	{
		signal_all(260,BLACK);
		own->num_own=((long)((float)own->num_max/400))*100;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
	else if(mouse_press(303,283,317,297,&mx,&my,&mbuttn))			//1/5
	{
		signal_all(310,BLACK);
		own->num_own=((long)((float)own->num_max/500))*100;
		bar(224,168+143,300,192+143);
		sprintf(temp,"%ld",own->num_own);
		outtextxy(227,170+143,temp);
	}
}

void signal_pos(int x,int color)
{
	setcolor(color);
	setfillstyle(1,color);
	circle(x,290,4);
	floodfill(x,290,color);
}
void signal_all(int x,int color)			//�����ʾ��λ
{
	signal_pos(160,WHITE);
	signal_pos(210,WHITE);
	signal_pos(260,WHITE);
	signal_pos(310,WHITE);
	signal_pos(x,color);
	setcolor(LIGHTBLUE);
	setfillstyle(1,WHITE);
}

void get_data_length(Own *own,int *length)			//��ȡÿһ���ļ����ж�������¼����
{
	char temp[40],temp1[40],temp2[40],temp3[40],temp4[40];
	FILE *fp;
	strcpy(temp,"USER\\");
	strcat(temp,own->account);
	strcat(temp,"\\");
	strcpy(temp1,temp);
	strcpy(temp2,temp);
	strcpy(temp3,temp);
	strcpy(temp4,temp);
	strcat(temp1,"delegat.txt");
	strcat(temp2,"hold.txt");
	strcat(temp3,"balance.txt");
	strcat(temp4,"deal.txt");
	if((fp=fopen(temp1,"rt"))==NULL)
	{
		printf("can't find the file delegate.txt while get the length of data!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&length[0]);
	//fread(&length[0],sizeof(int),1,fp);
	fclose(fp);
	
	if((fp=fopen(temp2,"rt"))==NULL)
	{
		printf("can't find the file hold.txt while get the length of data!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&length[1]);
	//fread(&length[1],sizeof(int),1,fp);
	fclose(fp);
	
	if((fp=fopen(temp3,"rt"))==NULL)
	{
		printf("can't find the file balance.txt while get the length of data!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&length[2]);
	//fread(&length[2],sizeof(int),1,fp);
	fclose(fp);
	
	if((fp=fopen(temp4,"rt"))==NULL)
	{
		printf("can't find the file deal.txt while get the length of data!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&length[3]);
	//fread(&length[3],sizeof(int),1,fp);
	fclose(fp);
}
void init_own(Own *own)
{
	char temp[30];
	FILE *fp;
	int i;
	strcpy(temp,"USER\\");
	strcat(temp,own->account);
	strcat(temp,"\\");
	strcat(temp,"own.txt");
	if((fp=fopen(temp,"rb"))==NULL)
	{
		printf("can't find the file own.txt while init the data of stock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	rewind(fp);
	fseek(fp,30,SEEK_SET);
	for(i=0;i<5;i++)
	{
		fread(&(own->balance[i]),sizeof(double),1,fp);
	}
	fclose(fp);
	own->stockname[0]='\0';
	own->stockcode[0]='\0';
	own->stock_now_price=0.0;
	own->stock_pre_price=0.0;
	own->num_max=0;
	own->price_own=0.0;
	own->num_own=0;
	own->stock_zuoshou=0.0;
	own->zhangfu=0.0;
}
void input_deal(Own *own,struct tm time_p,Hold *hold,int length)		//�жϽ����������Ʊ��Ϣ
{
	char temp[7]={'\0'};
	FILE *fp;
	int i;
	char str1[7]={'\0'},str2[9]={'\0'},str3[8],str4[8];
	setfillstyle(1,WHITE);
	bar(224,132,349,156);
	input(227,131,6,1,LIGHTBLUE,WHITE,temp,0);
	if((fp=fopen("data\\STOCK\\all.txt","rt"))==NULL)
	{
		printf("can not find the file all.txt\n");
		fclose(fp);
		getch();
		exit(1);
	}
	for(i=0;i<191;i++)
	{
		fscanf(fp,"%s%s%s%s",str1,str2,str3,str4);
		if(strcmp(str1,temp)==0)
		{
			strcpy(own->stockcode,str1);
			strcpy(own->stockname,str2);
			break;
		}
	}
	if(i>=191)
	{
		own->stockname[0]='\0';
		own->stockcode[0]='\0';
	}
	fclose(fp);
	get_pre_price(own,time_p,hold,length);
}
void show_deal_(int flag,Own *own,struct tm time_p,Delegate *delegate,Hold *hold,Balance *balance,Deal *deal,int *length,int page_pointer)		//�ܿ���չʾ���й�Ʊ��������
{
	switch(flag)
	{
		case 1:show_data_1(own);
				break;
		case 2:show_data_1(own);
				break;
		case 3:show_recall_data(delegate,length[0],page_pointer);
				break;
		case 4:
				break;
		case 41:show_balance_data(own,balance,length[2],page_pointer);
				break;
		case 42:show_tod_deal(deal,length[3],page_pointer,time_p);
				break;
		case 43:show_delegate_data(delegate,length[0],page_pointer);
				break;
		case 44:show_his_deal(deal,length[3],page_pointer);
				break;
		case 45:show_hold_data(hold,length[1],page_pointer);
				break;
		case 5:
				break;
		case 51:show_data_1(own);
				break;
		case 52:show_data_1(own);
				break;
	}
}
void show_data_1(Own *own)			//��ʾ����������������
{
	char str[15];
	setfillstyle(1,WHITE);
	bar(224,96,349,120);
	bar(224,204,349,228);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	setcolor(LIGHTBLUE);
	sprintf(str,"%.2lf",own->balance[0]);
	outtextxy(227,206,str);
	outtextxy(227,98,own->account);
}
/**void page_judge(int *flag,int *flag_last,int mx,int my,int mbuttn)
{
	int temp;
	if(mouse_press(13,71,135,100,&mx,&my,&mbuttn))
	{
		temp=flag;
		flag_last=temp;
		flag=1;
	}
	else if(mouse_press(13,101,135,130,&mx,&my,&mbuttn))
	{
		temp=flag;
		flag_last=temp;
		flag=2;
	}
	else if(mouse_press(13,131,135,160,&mx,&my,&mbuttn))
	{
		temp=flag;
		flag_last=temp;
		flag=3;
	}
}**/
void page_judge_1(int *flag_last,int *flag,int mx,int my,int mbuttn)
{
	//page_judge(flag_last,flag,mx,my,mbuttn);
	if(mouse_press(13,71,135,100,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=1;
	}
	else if(mouse_press(13,101,135,130,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=2;
	}
	else if(mouse_press(13,131,135,160,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=3;
	}
	else if(mouse_press(13,161,135,190,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=4;
	}
	else if(mouse_press(13,191,135,220,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=5;
	}
	else if(mouse_press(570,440,620,464,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=6;
	}
}
void page_judge_2(int *flag_last,int *flag,int mx,int my,int mbuttn)
{
	//page_judge(*flag_last,*flag,mx,my,mbuttn);
	if(mouse_press(13,71,135,100,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=1;
	}
	else if(mouse_press(13,101,135,130,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=2;
	}
	else if(mouse_press(13,131,135,160,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=3;
	}
	else if(mouse_press(20,195,84,212,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=41;
	}
	else if(mouse_press(20,220,84,237,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=42;
	}
	else if(mouse_press(20,245,84,262,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=43;
	}
	else if(mouse_press(20,270,84,287,&mx,&my,&mbuttn))
	{

		*flag_last=*flag;
		*flag=44;
	}
	else if(mouse_press(20,295,84,312,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=45;
	}
	else if(mouse_press(13,316,135,340,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=5;
	}
	else if(mouse_press(570,440,620,464,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=6;
	}
}
void page_judge_3(int *flag_last,int *flag,int mx,int my,int mbuttn)
{
	//page_judge(*flag_last,*flag,mx,my,mbuttn);
	if(mouse_press(13,71,135,100,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=1;
	}
	else if(mouse_press(13,101,135,130,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=2;
	}
	else if(mouse_press(13,131,135,160,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=3;
	}
	else if(mouse_press(13,161,135,190,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=4;
	}
	else if(mouse_press(38,225,74,242,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=51;
	}
	else if(mouse_press(38,250,74,267,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=52;
	}
	else if(mouse_press(570,440,620,464,&mx,&my,&mbuttn))
	{
		*flag_last=*flag;
		*flag=6;
	}
}