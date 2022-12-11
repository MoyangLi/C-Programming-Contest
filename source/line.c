#include "line.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:			line.c
  Author:       		李墨洋
  Version:				1.0 
  Date:					18/11/05
  Description:  		小窗口曲线函数
  Function List:  
	line_bk_draw		小窗口曲线函数背景
	draw_KDJ			画KDJ曲线（随机指标）
	calculate_KDJ		计算KDJ曲线数据
	draw_MACD			画MACD曲线（指数平滑异同曲线）
	calculate_MACD		计算MACD曲线
	draw_OBV			画OBV曲线（能量潮）
	calculate_OBV		计算OBV曲线数据
	draw_RSI			画RSI曲线（相对强弱指标）
	draw_PSY			画PSY曲线（心理线）
	draw_BIAS			画BIAS曲线（乖离率）
	draw_BOLL			画BOLL曲线（布林线）
  History:      
	<author>  <time>   <version >   <desc>
	李墨洋    18/11/05     1.0     build this moudle  
*************************************************/

void line_bk_draw(void)
{
	setfillstyle(1,BLACK);
	bar(75,342,639,460);
	dot_line(77,340,460);
	settextjustify(1,1);
	settextstyle(2,0,5);
	setcolor(RED);
	line(90,344,106,344);
	line(90,344,98,356);
	line(98,356,106,344);
}

void draw_KDJ(float *n,int length,float *data1,float *data2,float *data3,int signal,int num)
{
	int x1,x2,y1,y2;
	int width=545/length;
	float height;				//留给K线图的像素点为356~460,342~355用于输出数据
	float ymax,ymin;
	int i;
	int base_x=629;
	int base_y1=102;
	int base_y2=459;
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(160,347,"K:");
		setcolor(YELLOW);
		outtextxy(290,347,"D:");
		setcolor(MAGENTA);
		outtextxy(420,347,"J:");
		setcolor(RED);
		outtextxy(119,347,"KDJ");
	}
	else if(signal==1)
	{
		length=100;
		base_x=((num-1)%3)*215+203;
		base_y1=121;
		base_y2=((num-1)/3+1)*146+15;
		width=2;
	}
	calculate_KDJ(n,length,data1,data2,data3,&ymax,&ymin);
	height=ymax-ymin;
	setcolor(WHITE);
	for(i=0;i<length-1;i++)
	{
		x1=base_x-width*i;
		x2=base_x-width*(i+1);
		y1=(int)(base_y2-((data1[i]-ymin)/height*base_y1));
		y2=(int)(base_y2-((data1[i+1]-ymin)/height*base_y1));
		line(x1,y1,x2,y2);
	}
	setcolor(YELLOW);
	for(i=0;i<length-1;i++)
	{
		x1=base_x-width*i;
		x2=base_x-width*(i+1);
		y1=(int)(base_y2-((data2[i]-ymin)/height*base_y1));
		y2=(int)(base_y2-((data2[i+1]-ymin)/height*base_y1));
		line(x1,y1,x2,y2);
	}
	setcolor(MAGENTA);
	for(i=0;i<length-1;i++)
	{
		x1=base_x-width*i;
		x2=base_x-width*(i+1);
		y1=(int)(base_y2-((data3[i]-ymin)/height*base_y1));
		y2=(int)(base_y2-((data3[i+1]-ymin)/height*base_y1));
		line(x1,y1,x2,y2);
	}
}
void calculate_KDJ(float *price,int length,float *K,float *D,float *J,float *ymax,float *ymin)
{
	int i,j;
	float RSV[140];
	float Hn[140],Ln[140];
	K[length-1+6]=50;
	D[length-1+6]=50;
	J[length-1+6]=50;
	*ymax=50;
	*ymin=50;
	for(i=length+7+6;i>=8;i--)
	{
		Hn[i-8]=price[i-8];
		Ln[i-8]=price[i-8];
		for(j=i-1;j>=i-8;j--)
		{
			if(price[j]>Hn[i-8])
			{
				Hn[i-8]=price[j];
			}
			if(price[j]<Ln[i-8])
			{
				Ln[i-8]=price[j];
			}
		}
		RSV[i-8]=(price[i-8]-Hn[i-8])/(Hn[i-8]-Ln[i-8])*100;
		if(i<length+7+6)
		{
			K[i-8]=K[i-7]*2/3+RSV[i-8]/3;
			if(K[i-8]>*ymax)
			{
				*ymax=K[i-8];
			}
			if(K[i-8]<*ymin)
			{
				*ymin=K[i-8];
			}
			D[i-8]=D[i-7]*2/3+K[i-8]/3;
			if(D[i-8]>*ymax)
			{
				*ymax=D[i-8];
			}
			if(D[i-8]<*ymin)
			{
				*ymin=D[i-8];
			}
			J[i-8]=3*K[i-8]-2*D[i-8];
			if(J[i-8]>*ymax)
			{
				*ymax=J[i-8];
			}
			if(J[i-8]<*ymin)
			{
				*ymin=J[i-8];
			}
		}
	}
}

void draw_MACD(float *price,int length,float *DIF,float *DEA,float *MACD,int signal,int num)
{
	int x,y;
	int width=545/length;
	float ymax[2],ymin[2],height;				//留给K线图的像素点为356~460,342~355用于输出数据
	int i;
	int base_x=629;
	int base_y1=40;
	int base_y2=400;
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(160,347,"DIF:");
		setcolor(YELLOW);
		outtextxy(290,347,"DEA:");
		setcolor(MAGENTA);
		outtextxy(420,347,"MACD:");
		setcolor(RED);
		outtextxy(123,347,"MACD");
	}
	else if(signal==1)
	{
		length=100;
		base_x=((num-1)%3)*215+203;
		base_y1=50;
		base_y2=((num-1)/3+1)*146-50;
		width=2;
	}
	calculate_MACD(price,length,MACD,DIF,DEA,ymax,ymin);
	draw_ave(length,ymin[0],ymax[0],DIF,signal,num);
	draw_ave(length,ymin[0],ymax[0],DEA,signal,num);
	if(ymax[1]+ymin[1]>=0.0)
		height=ymax[1];
	else
		height=0-ymin[1];
	for(i=0;i<length;i++)
	{
		x=base_x-width*i-width/2;
		if(MACD[i+1]>=0)
		{
			setcolor(RED);
		}
		else if(MACD[i+1]<0)
		{
			setcolor(LIGHTCYAN);
		}
		y=(int)(base_y2-(MACD[i+1]/height*base_y1));
		line(x,y,x,base_y2);
	}
}

void calculate_MACD(float *price,int length,float *MACD,float *DIF,float *DEA,float *ymax,float *ymin)
{
	int i,j;
	float EMA12[148],EMA26[148];
	DIF[0]=5;
	DEA[0]=10;
	MACD[0]=0;
	EMA12[length+9]=price[length+8];
	EMA26[length+9]=price[length+8];
	ymin[0]=1e-6;
	ymin[1]=1e-6;
	ymax[0]=1e-6;
	ymax[1]=1e-6;
	for(i=length+8;i>0;i--)
	{
		EMA12[i]=11.00*EMA12[i+1]/13.00+2.00*price[i-1]/13.00;
		EMA26[i]=25.00*EMA26[i+1]/27.00+2.00*price[i-1]/27.00;
		DIF[i]=EMA12[i]-EMA26[i];
		if(DIF[i]<ymin[0])
		{
			ymin[0]=DIF[i];
		}
		if(DIF[i]>ymax[0])
		{
			ymax[0]=DIF[i];
		}
		if(i<=length)
		{
			DEA[i]=0.00;
			for(j=i;j<i+9;j++)
			{
				DEA[i]+=DIF[j];
			}
			DEA[i]/=9.00;
			MACD[i]=2*(DIF[i]-DEA[i]);
			if(MACD[i]-ymin[1]<1e-6)
			{
				ymin[1]=MACD[i];
			}
			if(MACD[i]-ymax[1]>1e-6)
			{
				ymax[1]=MACD[i];
			}
		}
	}
}

void draw_OBV(STOCK *stock,int length,float *OBV,float *MAOBV,int signal,int num)
{
	float ymax,ymin;				//留给K线图的像素点为356~460,342~355用于输出数
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(180,347,"OBV:");
		setcolor(YELLOW);
		outtextxy(310,347,"MAOBV:");
		setcolor(RED);
		outtextxy(132,347,"OBV(30)");
	}
	calculate_OBV(stock,length,OBV,MAOBV,&ymax,&ymin);
	draw_ave(length,ymin,ymax,OBV,signal,num);
	draw_ave(length,ymin,ymax,MAOBV,signal,num);
}

void calculate_OBV(STOCK *stock,int length,float *OBV,float *MAOBV,float *ymax,float *ymin)
{
	int i,j;
	float max=1e-6;
	float min=1e-6;
	OBV[length+32]=stock->sum_amount[length+31]/100.00;
	OBV[0]=5;
	MAOBV[0]=10;
	for(i=length-1+32;i>0;i--)
	{
		if(stock->stop[i-1]>stock->stop[i])
		{
			OBV[i]=OBV[i+1]+stock->sum_amount[i-1]/100.00;
		}
		else if(stock->stop[i-1]<stock->stop[i])
		{
			OBV[i]=OBV[i+1]-stock->sum_amount[i-1]/100.00;
		}
		else
		{
			OBV[i]=OBV[i+1];
		}
		/**if(stock->zuigao[i-1]!=stock->zuidi[i-1])
		{
			OBV[i]=OBV[i]*((stock->stop[i-1]-stock->zuidi[i-1])-(stock->zuigao[i-1]-stock->stop[i-1]))/(stock->zuigao[i-1]-stock->zuidi[i-1]);	//澶氱┖姣旂巼鍑�棰濇硶
		}
		else
		{
			;
		}**/
		if(OBV[i]>max)
		{
			max=OBV[i];
		}
		if(OBV[i]<min)
		{
			min=OBV[i];
		}
		if(i<=length+1)
		{
			MAOBV[i]=0.00;
			for(j=i;j<i+30;j++)
			{
				MAOBV[i]+=(OBV[j]/30.00);
			}
		}
	}
	*ymax=max;
	*ymin=min;
}

void draw_RSI(float *price,int length,float *RSI1,float *RSI2,float *RSI3,int signal,int num)
{
	float max=-1e-6,min=100.0;
	//float RSI[172]={0.0};
	int i,j;
	float up,down;
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(230,347,"RSI1:");
		setcolor(YELLOW);
		outtextxy(360,347,"RSI2:");
		setcolor(MAGENTA);
		outtextxy(490,347,"RSI3:");
		setcolor(RED);
		outtextxy(155,347,"RSI(6,12,24)");
	}
	RSI1[0]=5;
	RSI2[0]=10;
	RSI3[0]=20;
	for(i=length;i>0;i--)
	{
		up=15e-6,down=1e-6;
		for(j=i;j<i+6;j++)
		{
			if(price[j-1]>price[j])
				up+=price[j-1]-price[j];
			else if(price[j-1]<price[j])
				down+=price[j]-price[j-1];
		}
		if(fabs(up+down)<16e-6)
			RSI1[i]=1e-6;
		else
		{
			RSI1[i]=100*up/(up+down);
		}
		up=15e-6,down=1e-6;
		for(j=i;j<i+12;j++)
		{
			if(price[j-1]>price[j])
				up+=price[j-1]-price[j];
			else if(price[j-1]<price[j])
				down+=price[j]-price[j-1];
		}
		if(fabs(up+down)<16e-6)
			RSI2[i]=1e-6;
		else
		{
			RSI2[i]=100*up/(up+down);
		}
		up=15e-6,down=1e-6;
		for(j=i;j<i+24;j++)
		{
			if(price[j-1]>price[j])
				up+=price[j-1]-price[j];
			else if(price[j-1]<price[j])
				down+=price[j]-price[j-1];
		}
		if(fabs(up+down)<16e-6)
			RSI3[i]=1e-6;
		else
		{
			RSI3[i]=100*up/(up+down);
		}
		if(RSI1[i]>max)
			max=RSI1[i];
		if(RSI1[i]<min)
			min=RSI1[i];
		if(RSI2[i]>max)
			max=RSI2[i];
		if(RSI2[i]<min)
			min=RSI2[i];
		if(RSI3[i]>max)
			max=RSI3[i];
		if(RSI3[i]<min)
			min=RSI3[i];
	}
	draw_ave(length,min,max,RSI1,signal,num);
	draw_ave(length,min,max,RSI2,signal,num);
	draw_ave(length,min,max,RSI3,signal,num);
}

void draw_PSY(float *price,int length,float *PSY,float *PSYMA,int signal,int num)
{
	int up_day=0,i,j;
	float max=1e-6,min=100.0;
	PSY[0]=5;
	PSYMA[0]=10;
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(230,347,"PSY:");
		setcolor(YELLOW);
		outtextxy(360,347,"PSYMA:");
		setcolor(RED);
		outtextxy(145,347,"PSY(12,6)");
	}
	for(i=length+5;i>0;i--)
	{
		up_day=0;
		for(j=i;j<i+12;j++)
		{
			if(price[j-1]>price[j])
			{
				up_day++;
			}
		}
		PSY[i]=100*(float)up_day/12;
		if(PSY[i]>max)
		{
			max=PSY[i];
		}
		if(PSY[i]<min)
		{
			min=PSY[i];
		}
		if(i<=length)
		{
			PSYMA[i]=1e-6;
			for(j=i;j<i+6;j++)
			{
				PSYMA[i]+=PSY[j]/6;
			}
		}
	}
	draw_ave(length,min,max,PSY,signal,num);
	draw_ave(length,min,max,PSYMA,signal,num);
}

void draw_BIAS(float *price,int length,float *BIAS1,float *BIAS2,float *BIAS3,int signal,int num)
{
	float max=-1e-6,min=100.0;
	int i,j;
	float shoupan;
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(230,347,"BIAS1:");
		setcolor(YELLOW);
		outtextxy(360,347,"BIAS2:");
		setcolor(MAGENTA);
		outtextxy(490,347,"BIAS3:");
		setcolor(RED);
		outtextxy(156,347,"BIAS(6,12,24)");
	}
	BIAS1[0]=5;
	BIAS2[0]=10;
	BIAS3[0]=20;
	for(i=length;i>0;i--)
	{
		shoupan=1e-6;
		for(j=i;j<i+6;j++)
		{
			shoupan+=price[j-1]/6;
		}
		BIAS1[i]=100*(price[i-1]-shoupan)/shoupan;
		shoupan=1e-6;
		for(j=i;j<i+12;j++)
		{
			shoupan+=price[j-1]/12;
		}
		BIAS2[i]=100*(price[i-1]-shoupan)/shoupan;
		shoupan=1e-6;
		for(j=i;j<i+24;j++)
		{
			shoupan+=price[j-1]/24;
		}
		BIAS3[i]=100*(price[i-1]-shoupan)/shoupan;
		if(BIAS1[i]>max)
		{
			max=BIAS1[i];
		}
		if(BIAS1[i]<min)
		{
			min=BIAS1[i];
		}
		if(BIAS2[i]>max)
		{
			max=BIAS2[i];
		}
		if(BIAS2[i]<min)
		{
			min=BIAS2[i];
		}
		if(BIAS3[i]>max)
		{
			max=BIAS3[i];
		}
		if(BIAS3[i]<min)
		{
			min=BIAS3[i];
		}
	}
	draw_ave(length,min,max,BIAS1,signal,num);
	draw_ave(length,min,max,BIAS2,signal,num);
	draw_ave(length,min,max,BIAS3,signal,num);
}

void draw_BOLL(float *price,int length,float *BOLL,float *UB,float *LB,int signal,int num)
{
	float max=-1e-6,min=100000.0;
	int i,j;
	float sta_deviation;
	if(signal==0)
	{
		line_bk_draw();
		setcolor(WHITE);
		outtextxy(230,347,"BOLL:");
		setcolor(YELLOW);
		outtextxy(360,347,"UB:");
		setcolor(MAGENTA);
		outtextxy(490,347,"LB:");
		setcolor(RED);
		outtextxy(146,347,"BOLL(20)");
	}
	BOLL[0]=5;
	UB[0]=10;
	LB[0]=20;
	for(i=length;i>0;i--)
	{
		BOLL[i]=1e-6;
		for(j=i;j<i+20;j++)
		{
			BOLL[i]+=price[j-1];
		}
		BOLL[i]/=20;
		sta_deviation=1e-6;
		for(j=i;j<i+20;j++)
		{
			sta_deviation+=pow((BOLL[i]-price[j-1]),2);	//求方差
		}
		sta_deviation/=19;
		sta_deviation=sqrt(sta_deviation);
		UB[i]=BOLL[i]+2*sta_deviation;
		LB[i]=BOLL[i]-2*sta_deviation;
		if(UB[i]>max)
		{
			max=UB[i];
		}
		if(LB[i]<min)
		{
			min=LB[i];
		}
	}
	draw_ave(length,min,max,BOLL,signal,num);
	draw_ave(length,min,max,UB,signal,num);
	draw_ave(length,min,max,LB,signal,num);
}

void Time_sharing(INFO *info,STOINFO *stoinfo)
{
	float price[240],ave_price[240],min[3],max[3];
	float MACD[240],DIF[240],DEA[240];
	int mx,my,mbuttn=-1;
	int day,day_last=0;
	bk();
	draw_Time_sharing(stoinfo,price,ave_price,min,max);
	calculate_time(price,DIF,DEA,MACD,min,max);
	mouse_save(mx,my);
	draw_share(min,max,price,ave_price,DIF,DEA,MACD);
	setmouseshape(3);
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(mouse_press(4,4,56,28,&mx,&my,&mbuttn))
		{
			info->layout=6;
			break;
		}
		else if(mx>=37&&mx<500&&my>=40)
		{
			day=(mx-20)/2;
			if(day!=day_last)
			{
				show_share(day,price,ave_price,DIF,DEA,MACD);
				day_last=day;
			}
		}
	}
}

void show_share(int day,float *price,float *ave_price,float *DIF,float *DEA,float *MACD)
{
	char str[6];
	char str_[6];
	int time;
	setfillstyle(1,BLACK);
	bar(175,342,250,354);
	bar(305,342,384,354);
	bar(439,342,480,354);
	bar(195,8,265,24);
	bar(315,8,370,24);
	bar(435,8,490,24);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,5);
	setcolor(WHITE);
	sprintf(str,"%.2f",DIF[day]);
	outtextxy(175,341,str);
	setcolor(YELLOW);
	sprintf(str,"%.2f",DEA[day]);
	outtextxy(305,341,str);
	setcolor(MAGENTA);
	sprintf(str,"%.2f",MACD[day]);
	outtextxy(439,341,str);
	settextstyle(2,0,6);
	setcolor(WHITE);
	if(day<120)
	{
		time=(day+31)/60;
		sprintf(str,"%d",time+9);
		strcat(str,":");
		time=(day+31)%60;
		sprintf(str_,"%d",time);
		strcat(str,str_);
	}
	else
	{
		time=(day+1)/60;
		sprintf(str,"%d",time+13);
		strcat(str,":");
		time=(day+1)%60;
		sprintf(str_,"%d",time);
		strcat(str,str_);
	}
	outtextxy(195,6,str);
	setcolor(WHITE);
	sprintf(str,"%.2f",price[day]);
	outtextxy(315,6,str);
	setcolor(YELLOW);
	sprintf(str,"%.2f",ave_price[day]);
	outtextxy(435,6,str);
}

void draw_share(float *min,float *max,float *price,float *ave_price,float *DIF,float *DEA,float *MACD)
{
	int i,x1,x2,y1,y2;
	float height;

	if(max[1]+min[1]>=0.0)
		height=max[1];
	else
		height=0-min[1];
	for(i=8;i<240;i++)
	{
		x1=i*2+20;
		if(MACD[i]>=0)
		{
			setcolor(RED);
		}
		else if(MACD[i]<0)
		{
			setcolor(LIGHTCYAN);
		}
		y1=(int)(420-(MACD[i]/height*55));
		line(x1,y1,x1,420);
	}

	height=max[2]-min[2];
	setcolor(WHITE);
	for(i=8;i<239;i++)
	{
		x1=i*2+20;
		x2=i*2+22;
		y1=(int)(200-((price[i]-min[2])/height*150));
		y2=(int)(200-((price[i+1]-min[2])/height*150));
		line(x1,y1,x2,y2);
	}
	
	height=max[0]-min[0];
	for(i=8;i<239;i++)
	{
		x1=i*2+20;
		x2=i*2+22;
		y1=(int)(475-((DIF[i]-min[0])/height*115));
		y2=(int)(475-((DIF[i+1]-min[0])/height*115));
		line(x1,y1,x2,y2);
	}
	height=max[2]-min[2];
	setcolor(YELLOW);
	for(i=8;i<239;i++)
	{
		x1=i*2+20;
		x2=i*2+22;
		y1=(int)(200-((ave_price[i]-min[2])/height*150));
		y2=(int)(200-((ave_price[i+1]-min[2])/height*150));
		line(x1,y1,x2,y2);
	}
	height=max[0]-min[0];
	for(i=8;i<239;i++)
	{
		x1=i*2+20;
		x2=i*2+22;
		y1=(int)(475-((DEA[i]-min[0])/height*115));
		y2=(int)(475-((DEA[i+1]-min[0])/height*115));
		line(x1,y1,x2,y2);
	}
}

void draw_Time_sharing(STOINFO *stoinfo,float *price,float *ave_price,float *ymin,float *ymax)
{
	char temp[50];
	char time_1[9],time_2[9],kai[7],shou[7],gao[7],di[7],str1[15],str2[20];
	FILE *fp;
	int i,j;
	ymin[2]=100.00;
	ymax[2]=1e-6;

	strcpy(temp,"data\\MIN\\1MIN\\TXT\\");
	strcat(temp,stoinfo->stockpress);
	strcat(temp,".txt");
	if((fp=fopen(temp,"rt"))==NULL)
	{
		printf("can't find the file 1MIN.txt of the stock while drawing the time_sharing!\n");
		getch();
		exit(1);
	}
	for(i=0;i<240;i++)
	{
		fscanf(fp,"%s %s %s %s %s %s %s %s",time_1,time_2,kai,gao,di,shou,str1,str2);
		price[i]=atof(shou);
		if(price[i]>ymax[2])
		{
			ymax[2]=price[i];
		}
		if(price[i]<ymin[2])
		{
			ymin[2]=price[i];
		}

		if(i>=4)
		{
			ave_price[i]=1e-6;
			for(j=0;j<5;j++)
			{
				ave_price[i]+=price[i-j];
			}
			ave_price[i]/=5.0;
		}
	}
	fclose(fp);
}

void calculate_time(float *price,float *DIF,float *DEA,float *MACD,float *ymin,float *ymax)
{
	float EMA12[240],EMA26[240];
	int i,j;
	ymin[1]=1e-6;
	ymax[1]=1e-6;
	EMA12[0]=price[0];
	EMA26[0]=price[0];
	DIF[0]=EMA12[0]-EMA26[0];
	ymin[0]=DIF[0];
	ymax[0]=DIF[0];
	for(i=1;i<240;i++)
	{
		EMA12[i]=(11.00*EMA12[i-1]+2.00*price[i])/13.00;
		EMA26[i]=(25.00*EMA26[i-1]+2.00*price[i])/27.00;
		DIF[i]=EMA12[i]-EMA26[i];
		if(DIF[i]<ymin[0])
		{
			ymin[0]=DIF[i];
		}
		if(DIF[i]>ymax[0])
		{
			ymax[0]=DIF[i];
		}
		if(i>=8)
		{
			DEA[i]=1e-6;
			for(j=i;j>=i-8;j--)
			{
				DEA[i]+=DIF[j];
			}
			DEA[i]/=9.00;
			MACD[i]=2*(DIF[i]-DEA[i]);
			if(MACD[i]-ymin[1]<1e-6)
			{
				ymin[1]=MACD[i];
			}
			if(MACD[i]-ymax[1]>1e-6)
			{
				ymax[1]=MACD[i];
			}
		}
	}
}
void bk(void)
{
	cleardevice();
	setcolor(RED);
	line(0,340,639,340);
	dot_line(0,340,480);
	dot_line(0,20,340);
	put_hz(4,4,"日线",LIGHTBLUE,24,4);
	put_hz(68,8,"分时图",WHITE,16,2);
	settextjustify(1,1);
	settextstyle(2,0,5);
	setcolor(WHITE);
	outtextxy(80,347,"MACD(12,26,9)");
	outtextxy(160,347,"DIF:");
	setcolor(YELLOW);
	outtextxy(290,347,"DEA:");
	setcolor(MAGENTA);
	outtextxy(420,347,"MACD:");
	put_hz(148,8,"时间：",WHITE,16,1);
	put_hz(268,8,"价位：",WHITE,16,1);
	put_hz(388,8,"均价：",YELLOW,16,1);
}