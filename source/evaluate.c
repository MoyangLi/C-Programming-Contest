#include"head.h"
#include<graphics.h>
#include"chinese.h"
#include"tool.h"
#include"mouse.h"
#include"evaluate.h"
void evaluate_control(int *mx,int *my,int *mbtn)
{
	int t_flag=2,i,j;
	int sum,num=0,flag=0;
	float temp;
	FILE * fp=NULL;
	char addresss[40]="data\\other\\evaluate\\sum.txt";
	char addressn[40]="data\\other\\evaluate\\eva.txt";
	char per[20],summ[10];
	int a[5]={240,280,320,360,400};
	
	fp=fopen(addressn,"rt");
	rewind(fp);
	fread(&num,sizeof(int),1,fp);
	fclose(fp);
	
	fp=fopen(addresss,"rt");
	rewind(fp);
	fread(&sum,sizeof(int),1,fp);
	fclose(fp);
	
	temp=((float)num)/((float)sum)*100.0;
	gcvt(temp,4,per);
	regu_float(per);
	j=strlen(per);
	per[j]='%';
	per[j+1]='\0';
	itoa(sum,summ,10);

	draw_evaluate(summ,per);
	while(!flag)
	{
		newmouse(mx,my,mbtn);
		if(mouse_press(240-12+40*4,96,240+12+40*4,116,mx,my,mbtn))
		{
		setcolor(YELLOW);
		for(i=0;i<5;i++)
		{
			setcolor(YELLOW);
			line(a[i]-12,104,a[i]-4,104);
			line(a[i]-4,104,a[i],96);
			line(a[i],96,a[i]+4,104);
			line(a[i]+4,104,a[i]+12,104);
			line(a[i]+12,104,a[i]+6,112);
			line(a[i]+6,112,a[i]+8,124);
			line(a[i]+8,124,a[i],116);
			line(a[i],116,a[i]-8,124);
			line(a[i]-8,124,a[i]-6,112);
			line(a[i]-6,112,a[i]-12,104);             //������
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(a[i],104,YELLOW);
		}
		t_flag=1;
		setcolor(YELLOW);
		circle(470,105,20);           //��Ц��
		arc(470,105,180,360,15);
		rectangle(470-12,100-6,470-4,100-2);
		rectangle(470+12,100-6,470+4,100-2);
		puthz16("�ܺ�",470-18,130,16,1,1,YELLOW);

	}
	else if(mouse_press(240-12+40*3,96,240+12+40*3,116,mx,my,mbtn))
	{
		setcolor(YELLOW);
		for(i=0;i<4;i++)
		{
			line(a[i]-12,104,a[i]-4,104);
			line(a[i]-4,104,a[i],96);
			line(a[i],96,a[i]+4,104);
			line(a[i]+4,104,a[i]+12,104);
			line(a[i]+12,104,a[i]+6,112);
			line(a[i]+6,112,a[i]+8,124);
			line(a[i]+8,124,a[i],116);
			line(a[i],116,a[i]-8,124);
			line(a[i]-8,124,a[i]-6,112);
			line(a[i]-6,112,a[i]-12,104);             //������
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(a[i],104,YELLOW);
		}
		t_flag=1;
		setcolor(YELLOW);
		circle(470,105,20);           //��Ц��
		arc(470,105,180,360,15);
		rectangle(470-12,100-6,470-4,100-2);
		rectangle(470+12,100-6,470+4,100-2);
		puthz16("�Ϻ�",470-18,130,16,1,1,YELLOW);
	}
	else if(mouse_press(240-12+40*2,96,240+12+40*2,116,mx,my,mbtn))
	{
		setcolor(YELLOW);
		for(i=0;i<3;i++)
		{
			line(a[i]-12,104,a[i]-4,104);
			line(a[i]-4,104,a[i],96);
			line(a[i],96,a[i]+4,104);
			line(a[i]+4,104,a[i]+12,104);
			line(a[i]+12,104,a[i]+6,112);
			line(a[i]+6,112,a[i]+8,124);
			line(a[i]+8,124,a[i],116);
			line(a[i],116,a[i]-8,124);
			line(a[i]-8,124,a[i]-6,112);
			line(a[i]-6,112,a[i]-12,104);             //������
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(a[i],104,YELLOW);
		}
		t_flag=1;
		setcolor(YELLOW);
	    circle(470,105,20);           //��Ц��
		arc(470,105,180,360,10);
		rectangle(470-12,100-6,470-4,100-2);
		rectangle(470+12,100-6,470+4,100-2);
		puthz16("һ��",470-18,130,16,1,1,YELLOW);
	}
	else if(mouse_press(240-12+40,96,240+12+40,116,mx,my,mbtn))
	{
		setcolor(YELLOW);
		for(i=0;i<2;i++)
		{
			line(a[i]-12,104,a[i]-4,104);
			line(a[i]-4,104,a[i],96);
			line(a[i],96,a[i]+4,104);
			line(a[i]+4,104,a[i]+12,104);
			line(a[i]+12,104,a[i]+6,112);
			line(a[i]+6,112,a[i]+8,124);
			line(a[i]+8,124,a[i],116);
			line(a[i],116,a[i]-8,124);
			line(a[i]-8,124,a[i]-6,112);
			line(a[i]-6,112,a[i]-12,104);             //������
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(a[i],104,YELLOW);
		}
		t_flag=0;
		setcolor(YELLOW);
	    circle(470,105,20);           //��Ц��
		arc(470,112,0,180,10);
		rectangle(470-12,100-6,470-4,100-2);
		rectangle(470+12,100-6,470+4,100-2);
		puthz16("�ϲ�",470-18,130,16,1,1,YELLOW);
	}
	else if(mouse_press(240-12,96,240+12,116,mx,my,mbtn))
	{
		setcolor(YELLOW);
		for(i=0;i<1;i++)
		{
			line(a[i]-12,104,a[i]-4,104);
			line(a[i]-4,104,a[i],96);
			line(a[i],96,a[i]+4,104);
			line(a[i]+4,104,a[i]+12,104);
			line(a[i]+12,104,a[i]+6,112);
			line(a[i]+6,112,a[i]+8,124);
			line(a[i]+8,124,a[i],116);
			line(a[i],116,a[i]-8,124);
			line(a[i]-8,124,a[i]-6,112);
			line(a[i]-6,112,a[i]-12,104);             //������
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(a[i],104,YELLOW);
		}
		t_flag=0;
		setcolor(YELLOW);
	    circle(470,105,20);           //��Ц��
		arc(470,113,0,180,10);
		rectangle(470-12,100-6,470-4,100-2);
		rectangle(470+12,100-6,470+4,100-2);
		puthz16("�ܲ�",470-18,130,16,1,1,YELLOW);
	}
	
	if(t_flag==1)
	{
		setcolor(LIGHTGRAY);
		rectangle(170,180,240,210);      //���ۿ�
		puthz16("���нϿ�",174,185,16,1,1,LIGHTGRAY);
		rectangle(285,180,355,210);      //���ۿ�
		puthz16("������ȫ",289,185,16,1,1,LIGHTGRAY);
		rectangle(400,180,470,210);      //���ۿ�
		puthz16("��������",404,185,16,1,1,LIGHTGRAY);
		rectangle(200,230,270,260);      //���ۿ�
		puthz16("������ȫ",204,234,16,1,1,LIGHTGRAY);
		rectangle(370,230,440,260);      //���ۿ�
		puthz16("���ڲ���",374,234,16,1,1,LIGHTGRAY);
	}
	else if(t_flag==0)
	{
		setcolor(LIGHTGRAY);
		rectangle(170,180,240,210);      //���ۿ�
		puthz16("���н���",174,185,16,1,1,LIGHTGRAY);
		rectangle(285,180,355,210);      //���ۿ�
		puthz16("���ݲ�ȫ",289,185,16,1,1,LIGHTGRAY);
		rectangle(400,180,470,210);      //���ۿ�
		puthz16("����һ��",404,185,16,1,1,LIGHTGRAY);
		rectangle(200,230,270,260);      //���ۿ�
		puthz16("���ܲ�ȫ",204,234,16,1,1,LIGHTGRAY);
		rectangle(370,230,440,260);      //���ۿ�
		puthz16("���ײ���",374,234,16,1,1,LIGHTGRAY);
	}
	
	if(t_flag==0)
	{
	 while(1)
	 { 		  
      newmouse(mx,my,mbtn);
	  if(mouse_press(170,180,240,210,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(170,180,240,210);      //���ۿ�
		puthz16("���н���",174,185,16,1,1,LIGHTRED); 
	  }
	  if(mouse_press(285,180,355,210,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(285,180,355,210);      //���ۿ�
		puthz16("���ݲ�ȫ",289,185,16,1,1,LIGHTRED); 
	  }
	  if(mouse_press(400,180,470,210,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(400,180,470,210);      //���ۿ�
		puthz16("����һ��",404,185,16,1,1,LIGHTRED);  
	  }
	  if(mouse_press(200,230,270,260,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(200,230,270,260);      //���ۿ�
		puthz16("���ܲ�ȫ",204,234,16,1,1,LIGHTRED);  
	  }
	  if(mouse_press(370,230,440,260,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(370,230,440,260);      //���ۿ�
		puthz16("���ײ���",374,234,16,1,1,LIGHTRED);
	  }

	  if(mouse_press(280,320,360,360,mx,my,mbtn))
	  {
		fp=fopen(addresss,"wt");
		sum+=1;
		fwrite(&sum,sizeof(int),1,fp);
		fclose(fp);
		flag=1;
		break;
	  }
	 }
	}
	else if(t_flag==1)
	{
	 while(1)
	 {
	  newmouse(mx,my,mbtn);
	  if(mouse_press(170,180,240,210,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(170,180,240,210);      //���ۿ�
		puthz16("���нϿ�",174,185,16,1,1,LIGHTRED);
	  }
	  if(mouse_press(285,180,355,210,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(285,180,355,210);      //���ۿ�
		puthz16("������ȫ",289,185,16,1,1,LIGHTRED);
	  }
	  if(mouse_press(400,180,470,210,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(400,180,470,210);      //���ۿ�
		puthz16("��������",404,185,16,1,1,LIGHTRED);
	  }
	  if(mouse_press(370,230,440,260,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(370,230,440,260);      //���ۿ�
		puthz16("���ڲ���",374,234,16,1,1,LIGHTRED);
	  }
	  if(mouse_press(200,230,270,260,mx,my,mbtn))
	  {
		setcolor(LIGHTRED);
		rectangle(200,230,270,260);      //���ۿ�
		puthz16("������ȫ",204,234,16,1,1,LIGHTRED);
	  }

	  if(mouse_press(280,320,360,360,mx,my,mbtn))
	  {

		fp=fopen(addresss,"wt");
		sum+=1;
		fwrite(&sum,sizeof(int),1,fp);
		fclose(fp);

		fp=fopen(addressn,"wt");
		num+=1;
		fwrite(&num,sizeof(int),1,fp);
		fclose(fp);
		flag=1;
		break;
	  }
	 }
	}
	}
	cleardevice();
	put_hz(280,290,"��лʹ��",RED,48,4);
	delay(1000);
	closegraph();
	*mx=0;
}
void draw_evaluate(char *summ,char *per)
{
	int a[5]={240,280,320,360,400};
	int i;
	cleardevice();

	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setcolor(BLUE);
	rectangle(140,60,500,340);
	puthz16("��Ա�ϵͳ��������",250,38,16,1,1,YELLOW);    ///���۱���

	rectangle(200,80,440,150);
	setcolor(LIGHTGRAY);
	for(i=0;i<5;i++)
	{
	 line(a[i]-12,104,a[i]-4,104);
	 line(a[i]-4,104,a[i],96);
	 line(a[i],96,a[i]+4,104);
	 line(a[i]+4,104,a[i]+12,104);
	 line(a[i]+12,104,a[i]+6,112);
	 line(a[i]+6,112,a[i]+8,124);
	 line(a[i]+8,124,a[i],116);
	 line(a[i],116,a[i]-8,124);
	 line(a[i]-8,124,a[i]-6,112);
	 line(a[i]-6,112,a[i]-12,104);             //������
	}
	setfillstyle(SOLID_FILL,RED);
	bar3d(280,320,360,360,0,0);
	puthz16("�ύ",305,332,16,1,1,WHITE);   //�ύ��ť

	puthz16("����",40,400,16,1,1,WHITE);
	setcolor(YELLOW);
	outtextxy(87,405,summ);
	puthz16("�˶Ա�ϵͳ��������",118,400,16,1,1,WHITE);
	puthz16("�����ʴ�",40,430,16,1,1,WHITE);
	setcolor(YELLOW);
	outtextxy(110,435,per);
}
