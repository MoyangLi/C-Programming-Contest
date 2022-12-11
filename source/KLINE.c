#include "KLINE.h"
#include "deal.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:			deal.c
  Author:      	 		李墨洋
  Version:				1.0 
  Date:					18/11/05
  Description: 			股票行情界面函数
  Function List:  
    control_line		各界面切换总控函数		
	Kline_draw_bk		绘制K线图背景菜单栏
	dot_line			背景虚线绘制
	draw_slidder		画拖动条
	move_slidder_1		直接拖动拖动条
	move_slidder_2		用小三角拉拖动条
	data_get			读取股票数据
	trend_draw			K线图总控制函数
	find_max_min		查找数据最大值和最小值
	find_min			查找数据最小值
	find_max			查找数据最大值
	trend_init			处理计算数据并画图
	day_calculate		计算均线数据
	trend_draw_graph	画K线日线
	trend_draw_ave		画K线均线
	draw				成交量或者成交金额总控制函数
	draw_data			画成交量或者成交金额日线图
	draw_ave			画成交量或者成交金额均线图
	show_new			显示拖动条中的五只股票
	press_up			上键放大
	press_down			下键缩小
	press_right			左键左移
	press_left			右键右移
	day_num_stock		计算某只股票一共有多少天的数据
	trend_change		行情界面主控函数
	stock_diff			放缩移动总控制函数
	data_new			更新显示K线图对应数据
	find_stockpress		根据第几只股票查找股票代码和名字
	showstock			K线右上角显示股票和名字
	change_index		切换小窗口股票指标曲线
	show_index			展示小窗口股票指标曲线对应每一日数据
  History:      
	<author>  <time>   <version >   <desc>
	李墨洋    18/11/05     1.0     build this moudle  
*************************************************/

void control_line(INFO *info,STOINFO *stoinfo,Linkstock*Q1,int *mx,int *my,int *mbuttn)
{
	while(1)
	{
		//strcpy(info->account,"lmy4240");
		info->flag=1;
		if(info->layout==6)
		{
			info->layout_last=info->layout;
			trend_change(info,stoinfo,mx,my,mbuttn);	
		}
		else if(info->layout==3||info->layout==4)
		{
			info->layout_last=info->layout;
			trend_change(info,stoinfo,mx,my,mbuttn);
		}
		/**
		else if(info->layout==5)
		{
			info->layout_last=info->layout;
			show_mystock(info,stoinfo,mx,my,mbuttn);
		}**/
		else if(info->layout==5&&info->account_flag==1)		//必须登录以后才能进入自选股		
		{
			info->layout_last=info->layout;
			show_mystock(info,stoinfo,mx,my,mbuttn);
		}
		else if(info->layout==5&&info->account_flag!=1)		//未登录时弹出登录界面
		{
			sign(info);
			if(info->account_flag==1)						//此时如果登录了则直接进入自选股界面
			{
				info->layout_last=info->layout;
				show_mystock(info,stoinfo,mx,my,mbuttn);
			}
			else
			{
				info->layout=info->layout_last;				//此时如果还未登录则返回上一界面
			}
		}
		else if(info->layout==11)
		{
			info->layout_last=info->layout;
			stock_detail(info,stoinfo,mx,my,mbuttn);
		}
		else if(info->layout==12)
		{
			info->layout_last=info->layout;
			Time_sharing(info,stoinfo);
		}
		else if(info->layout==2)
		{
			info->layout_last=info->layout;
			cleardevice();
			menu_create(); 
			sort_menu();
			stock_listdraw(Q1,info);
			*mbuttn=-1;
			control_stock(info,stoinfo,Q1,mx,my,mbuttn);
			break;
		}
		else if(info->layout==8)
		{
			info->layout_last=info->layout;
			decide_compare_draw(stoinfo);
			*mbuttn=-1;
			decide_add(stoinfo,stoinfo->stockpress);
			layout_change(info,stoinfo);
			decide_compare_draw(stoinfo);
			break;
		}
		else if(info->layout==7&&info->account_flag==1)		//必须登录以后才能进入股票交易界面
		{
			info->layout_last=info->layout;
			deal(info,mx,my,mbuttn);
		}
		else if(info->layout==7&&info->account_flag!=1)		//未登录时弹出登录界面
		{
			sign(info);
			if(info->account_flag==1)						//此时如果登录了则直接进入交易界面
			{
				info->layout_last=info->layout;
				deal(info,mx,my,mbuttn);
			}
			else
			{
				info->layout=info->layout_last;				//此时如果还未登录则返回上一界面
			}
		}
		else
		{
			break;
		}

		if(info->flag==0)	//按下了菜单栏
		{
			info->layout_last=info->layout;
			info->flag=1;
			control_menu(info,stoinfo,Q1,mx,my,mbuttn);
			break;
		}
		if(info->flag==2)	//按下了快捷键
		{
			break;
		}
	}
}

void Kline_draw_bk()
{
	setcolor(RED);
	line(75,341,640,341);

	line(0,461,639,461);
	line(0,480,639,480);
	line(0,461,0,479);
	line(639,461,639,479);

	line(40,461,40,479);
	line(80,461,80,479);
	line(120,461,120,479);
	line(160,461,160,479);
	line(200,461,200,479);
	line(240,461,240,479);
	line(280,461,280,479);
	line(320,461,320,479);
	line(360,461,360,479);
	line(400,461,400,479);
	line(440,461,440,479);
	line(480,461,480,479);
	line(520,461,520,479);
	line(560,461,560,479);
	line(600,461,600,479);
	line(640,461,640,479);

	line(0,17,640,17);
	line(75,46,640,46);
	line(639,17,639,46);
	line(0,19,74,19);
	line(0,21,74,21);
	line(0,23,74,23);

	puthz12("指标",9,465,RED);
	puthz12("分时",409,465,RED);

	puthz12("时间：",90,19,WHITE);
	puthz12("开盘：",200,19,WHITE);
	puthz12("最高：",310,19,WHITE);
	puthz12("最低：",420,19,WHITE);
	puthz12("收盘：",530,19,WHITE);
	puthz12("成交量：",90,32,WHITE);
	puthz12("成交额：",200,32,WHITE);
	puthz12("涨幅：",310,32,WHITE);
	puthz12("涨跌：",420,32,WHITE);
	puthz12("振幅：",530,32,WHITE);

	settextjustify(1,1);
	settextstyle(2,0,6);

	outtextxy(60,470,"VOL");
	outtextxy(100,470,"KDJ");
	outtextxy(140,470,"MACD");
	outtextxy(180,470,"AMD");
	outtextxy(220,470,"OBV");
	outtextxy(260,470,"RSI");
	outtextxy(300,470,"PSY");
	outtextxy(340,470,"BIAS");
	outtextxy(380,470,"BOLL");

	settextstyle(2,0,5);
	setcolor(WHITE);
	outtextxy(105,51,"MA5:");
	setcolor(YELLOW);
	outtextxy(206,51,"MA10:");
	setcolor(MAGENTA);
	outtextxy(307,51,"MA20:");
	setcolor(LIGHTGREEN);
	outtextxy(408,51,"MA60:");

	setfillstyle(1,WHITE);
	bar(0,25,74,45);
	bar(0,50,74,70);
	bar(0,75,74,95);
	bar(0,100,74,120);
	bar(0,125,74,145);
	bar(0,150,74,170);
	bar(0,175,74,195);
	bar(0,200,74,220);
	put_hz(2,27,"上证指数",BLACK,16,2);
	put_hz(2,52,"深成指数",BLACK,16,2);
	put_hz(2,77,"深证A股",BLACK,16,2);
	put_hz(2,102,"加入对比",BLACK,16,2);
	put_hz(2,127,"股票财务",BLACK,16,2);
	put_hz(2,152,"股票走势",BLACK,16,2);
	put_hz(7,177,"自选股",BLACK,16,6);
	put_hz(16,202,"交易",BLACK,16,10);
}

void dot_line(int x,int y1,int y2)
{
	int i,j;
	for(j=y2-20;j>y1;j-=40)
	{
		for(i=x;i<639;i+=4)
			putpixel(i,j,RED);
	}
}

void draw_slidder()		//画拖动条
{
	setfillstyle(1,LIGHTGRAY);
	bar(54,225,74,460);
	setcolor(BLACK);
	line(56,235,62,231);
	line(62,231,68,235);
	line(56,236,62,232);
	line(62,232,68,236);
	line(56,237,62,233);
	line(62,233,68,237);

	line(56,450,62,454);
	line(62,454,68,450);
	line(56,451,62,455);
	line(62,455,68,451);
	line(56,452,62,456);
	line(62,456,68,452);
	setfillstyle(1,WHITE);
	bar(0,225,54,460);

	setcolor(BLACK);
	line(0,272,54,272);
	line(0,319,54,319);
	line(0,366,54,366);
	line(0,413,54,413);
}

void move_slidder_1(int *mx,int *my,int *mbuttn,STOINFO *stoinfo)
{
	int region=*my;
	int stock_num=1;
	while(1)
	{
		newmouse(mx,my,mbuttn);
		if(*mbuttn==1&&*my>=241&&*my<=427)
		{
			stoinfo->number_=*my-240;
			if(*my!=region)
			{
				region=*my;
				setfillstyle(1,LIGHTGRAY);
				bar(55,241,68,447);
				setfillstyle(1,DARKGRAY);
				bar(56,(stoinfo->number_)*stock_num+240,68,(stoinfo->number_)*stock_num+260);
				if(stoinfo->number_>2&&stoinfo->number_<187)
				show_new(stoinfo);
			}
		}
		else if(*mbuttn==1&&*my<241&&region!=241)
		{
			region=241;
			setfillstyle(1,LIGHTGRAY);
			bar(55,241,68,447);
			setfillstyle(1,DARKGRAY);
			bar(56,241,68,261);
			stoinfo->number_=1;
			show_new(stoinfo);
		}
		else if(*mbuttn==1&&*my>427&&region!=427)
		{
			region=427;
			setfillstyle(1,LIGHTGRAY);
			bar(55,241,68,447);
			setfillstyle(1,DARKGRAY);
			bar(56,427,68,447);
			stoinfo->number_=187;
			show_new(stoinfo);
		}
		else							//当鼠标状态松开时跳出循环此时的鼠标值就确定了对应的stoinfo->number_
			break;
	}
}

void move_slidder_2(STOINFO *stoinfo)	//如果当前拖动条中显示的第一支股票number小于等于187，则重画拖动条，表示拖动条位置移动
{
	if(stoinfo->number_<=187)
	{
		setfillstyle(1,LIGHTGRAY);
		bar(55,241,68,447);
		setfillstyle(1,DARKGRAY);
		bar(56,stoinfo->number_+240,68,stoinfo->number_+260);
	}
	else 
		;
}

void data_get(STOCK *stock,STOINFO * stoinfo,int signal)
{
	FILE *fp;
	char address[50];
	char time[10],kai[10],highest[10],lowest[10],shou[10],money_sum[20],amount_sum[15];
	int days_pre[7]={0,134,68,44,34,26,22};
	int length=days_pre[stoinfo->size]+60,i;
	if(signal==1)
	{
		length=160;
	}
	strcpy(address,"data\\TXT\\");
	strcat(address,stoinfo->stockpress);
	strcat(address,".txt");
	if((fp=fopen(address,"rt"))==NULL)
	{
		printf("can not found this stock\n");
		getch();
		exit(-1);
	}
	rewind(fp);
	for(i=0;i<stoinfo->pointer;i++)
	{
		fscanf(fp,"%s %s %s %s %s %s %s",time,kai,highest,lowest,shou,amount_sum,money_sum);
	}
	for(i=0;i<length;i++)
	{
		fscanf(fp,"%s %s %s %s %s %s %s",time,kai,highest,lowest,shou,amount_sum,money_sum);
		stock->date[i]=strtoul(time,NULL,10);
		stock->begin[i]=atof(kai);
		stock->stop[i]=atof(shou);
		stock->zuigao[i]=atof(highest);
		stock->zuidi[i]=atof(lowest);
		stock->sum_money[i]=atof(money_sum);
		stock->sum_amount[i]=atof(amount_sum);
	}
	fclose(fp);
}

void data_get_min(STOCK *stock,STOINFO * stoinfo)
{
	FILE *fp;
	char address[50];
	char date[10],time[6],kai[10],highest[10],lowest[10],shou[10],money_sum[20],amount_sum[15];
	int i,length;
	length=160;
	strcpy(address,"data\\MIN\\1MIN\\TXT\\");
	strcat(address,stoinfo->stockpress);
	strcat(address,".txt");
	if((fp=fopen(address,"rt"))==NULL)
	{
		printf("can not found this stock\n");
		getch();
		exit(-1);
	}
	rewind(fp);
	for(i=0;i<stoinfo->pointer;i++)
	{
		fscanf(fp,"%s %s %s %s %s %s %s %s",date,time,kai,highest,lowest,shou,amount_sum,money_sum);
	}
	for(i=0;i<length;i++)
	{
		fscanf(fp,"%s %s %s %s %s %s %s %s",date,time,kai,highest,lowest,shou,amount_sum,money_sum);
		stock->begin[i]=atof(kai);
		stock->stop[i]=atof(shou);
		stock->zuigao[i]=atof(highest);
		stock->zuidi[i]=atof(lowest);
	}
	fclose(fp);
}

void trend_draw(STOINFO * stoinfo,STOCK *stock,int signal,int num)			//K线图总控制函数
{
	float ymin,ymax;
	int days_pre[7]={0,134,68,44,34,26,22};
	int length=days_pre[stoinfo->size]+60;
	if(signal==1)
	{
		length=160;
	}
	if(signal==0)
	{
		clearbuffer();
		setfillstyle(1,BLACK);
		bar(77,60,639,340);
	}
	find_max(stock->zuigao,&ymax,length);
	find_min(stock->zuidi,&ymin,length);
	trend_init(stock,stoinfo,ymax,ymin,signal,num);
}

void find_max_min(float *n,float *max,float *min,int length)
{
	int i;
	*max=n[0];
	*min=n[0];
	for(i=1;i<length;i++)
	{
		if(*max<n[i])
			*max=n[i];
		if(*min>n[i])
			*min=n[i];
	}
}

void find_max(float *n,float *max,int length)
{
	int i;
	*max=n[0];
	for(i=1;i<length;i++)
	{
		if(*max<n[i])
			*max=n[i];
	}
}

void find_min(float *n,float *min,int length)
{
	int i;
	*min=n[0];
	for(i=1;i<length;i++)
	{
		if(*min>n[i])
			*min=n[i];
	}
}

/**void trend_draw(STAINFO *stainfo)
{
	float day5[137]={5},day10[137]={10},day20[137]={20},day60[137]={60};
	float begin[197],stop[197],zuigao[197],zuidi[197],sum_amount[197],sum_money[197];
	float stock_name[10]={{\0}};
	float ymin,ymax;
	strcpy(stock_name,stainfo->stockpress);
	trend_data_get(stock_name,stainfo,begin,stop,zuigao,zuidi,sum_money,sum_amount,&ymin,&ymax);
	day_calculate(stop,day5,stainfo);
	day_calculate(stop,day10,stainfo);
	day_calculate(stop,day20,stainfo);
	day_calculate(stop,day60,stainfo);
	Kline_draw_bk();

	trend_draw_graph(STOCK,stainfo,ymin,ymax);
	trend_draw_ave(stainfo,ymin,ymax,day5);
	trend_draw_ave(stainfo,ymin,ymax,day10);
	trend_draw_ave(stainfo,ymin,ymax,day20);
	trend_draw_ave(stainfo,ymin,ymax,day60);
}**/

void trend_init(STOCK *stock,STOINFO *stoinfo,float ymax,float ymin,int signal,int num)
{
	int days_pre[7]={0,134,68,44,34,26,22};
	int length=days_pre[stoinfo->size];
	float day5[135]={5},day10[135]={10},day20[135]={20},day60[135]={60};
	if(signal==1)
	{
		length=100;
	}
	day_calculate(stock->stop,day5,length);
	day_calculate(stock->stop,day10,length);
	day_calculate(stock->stop,day20,length);
	day_calculate(stock->stop,day60,length);
	
	if(signal==0)
	{
		dot_line(77,40,340);
	}
	
	trend_draw_graph(stock,stoinfo,ymin,ymax,signal,num);
	trend_draw_ave(stoinfo,ymin,ymax,day5,signal,num);
	trend_draw_ave(stoinfo,ymin,ymax,day10,signal,num);
	trend_draw_ave(stoinfo,ymin,ymax,day20,signal,num);
	trend_draw_ave(stoinfo,ymin,ymax,day60,signal,num);
}

void day_calculate(float *n1,float *day,int length)
{
	float days_num=day[0];
	double sum;
	int i,j;
	
	for(i=0;i<length;i++)
	{
		sum=1e-6;
		for(j=i;j<i+(int)days_num;j++)
		{
			sum+=n1[j];
		}
		sum/=days_num;
		day[i+1]=(float)sum;
	}
}

void trend_draw_graph(STOCK *stock,STOINFO *stoinfo,float ymin,float ymax,int signal,int num)
{
	int days_pre[7]={0,134,68,44,34,26,22};
	int width=4*stoinfo->size;
	float height=ymax-ymin;					//留给K线图的像素点为61-340
	int length=days_pre[stoinfo->size];
	int i;
	int x1,x2,x_mid,y1,y2,bottom,top;
	int base_x=629;
	int base_y1=280;
	int base_y2=340;
	if(signal==1)
	{
		length=100;
		base_x=((num-1)%3)*215+203;
		base_y1=121;
		base_y2=((num-1)/3+1)*146+15;
		width=2;
	}
	for(i=0;i<length;i++)
	{
		x1=base_x-width*i;
		if(signal==0)
			x2=base_x-width*(i+1)+width/4;
		else 
			x2=x1;
		x_mid=(int)((x1+x2)/2);
		y1=(int)(base_y2-(stock->begin[i]-ymin)/height*base_y1);
		y2=(int)(base_y2-(stock->stop[i]-ymin)/height*base_y1);
		bottom=(int)(base_y2-(stock->zuidi[i]-ymin)/height*base_y1);
		top=(int)(base_y2-(stock->zuigao[i]-ymin)/height*base_y1);

		if(stock->stop[i]>stock->begin[i])
		{
			setcolor(RED);
			rectangle(x2,y2,x1,y1);
			line(x_mid,y2,x_mid,top);
			line(x_mid,y1,x_mid,bottom);
		}
		else if(stock->stop[i]<stock->begin[i])
		{
			setcolor(LIGHTCYAN);
			setfillstyle(1,LIGHTCYAN);
			bar(x2,y1,x1,y2);
			line(x_mid,y1,x_mid,top);
			line(x_mid,y2,x_mid,bottom);
		}
		else
		{
			setcolor(WHITE);
			line(x1,y1,x2,y1);
			line(x_mid,top,x_mid,bottom);
		}
	}
}

void trend_draw_ave(STOINFO *stoinfo,float ymin,float ymax,float *day,int signal,int num)
{
	int x1,x2,y1,y2;
	int days_pre[7]={0,134,68,44,34,26,22};
	int width=4*(stoinfo->size);
	float height=ymax-ymin;					//留给K线图的像素点为61-340
	int length=days_pre[stoinfo->size];
	int base_x=629;
	int base_y1=280;
	int base_y2=340;
	int i;
	if(signal==1)
	{
		length=100;
		base_x=((num-1)%3)*215+203;
		base_y1=121;
		base_y2=((num-1)/3+1)*146+15;
		width=2;
	}
	if(day[0]==5)
	{                                
		setcolor(WHITE);
	}
	else if(day[0]==10)
		setcolor(YELLOW);
	else if(day[0]==20)
		setcolor(MAGENTA);
	else if(day[0]==60)
		setcolor(LIGHTGREEN);
	for(i=0;i<length-1;i++)					//因为均线是两点之间连线所以是length-1项
	{
		x1=base_x-width*i;
		x2=base_x-width*(i+1);
		y1=(int)(base_y2-((day[i+1]-ymin)/height*base_y1));
		y2=(int)(base_y2-((day[i+2]-ymin)/height*base_y1));
		line(x1,y1,x2,y2);
	}
}

void draw(STOCK *stock,float *n,int length,float *data1,float *data2,int signal,int num)				//成交量或者成交金额
{
	float ymin,ymax;
	data1[0]=5;
	data2[0]=10;
	if(signal==0)
	{
		setfillstyle(1,BLACK);
		bar(75,342,639,460);
		dot_line(77,340,460);
		settextjustify(1,1);
		settextstyle(2,0,5);
		setcolor(WHITE);
		outtextxy(160,347,"MA5:");
		setcolor(YELLOW);
		outtextxy(290,347,"MA10:");
		setcolor(RED);
		line(90,344,106,344);
		line(90,344,98,356);
		line(98,356,106,344);
	}
	find_max_min(n,&ymax,&ymin,length+10);
	day_calculate(n,data1,length);
	day_calculate(n,data2,length);
	draw_data(length,stock,ymin,ymax,n,signal,num);
	draw_ave(length,ymin,ymax,data1,signal,num);
	draw_ave(length,ymin,ymax,data2,signal,num);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,5);
	setcolor(RED);
}
void draw_data(int length,STOCK *stock,float ymin,float ymax,float *sum,int signal,int num)
{
	int width=545/length;
	float height=ymax-ymin;
	int x1,x2,y;
	int i;
	int base_x=629;
	int base_y1=103;
	int base_y2=460;
	if(signal==1)
	{
		length=100;
		base_x=((num-1)%3)*215+203;
		base_y1=121;
		base_y2=((num-1)/3+1)*146+15;
		width=2;
	}

	for(i=0;i<length;i++)
	{
		x1=base_x-width*i;
		if(signal==0)
			x2=base_x-width*(i+1)+width/4;
		else
			x2=x1;
		y=(int)(base_y2-(sum[i]-ymin)/height*base_y1);

		if(stock->stop[i]>=stock->begin[i])
		{
			setcolor(RED);
			rectangle(x2,y,x1,base_y2);
		}
		else
		{
			setfillstyle(1,LIGHTCYAN);
			bar(x2,y,x1,base_y2);
		}
	}
}
void draw_ave(int length,float ymin,float ymax,float *day,int signal,int num)
{
	int x1,x2,y1,y2;
	int width=545/length;
	float height=ymax-ymin;					//留给K线图的像素点为356~460,342~355用于输出数据
	int i;

	int base_x=629;
	int base_y1=103;
	int base_y2=458;
	if(signal==1)
	{
		length=100;
		base_x=((num-1)%3)*215+203;
		base_y1=121;
		base_y2=((num-1)/3+1)*146+15;
		width=2;
	}
	
	if(day[0]==5)
	{
		setcolor(WHITE);
	}
	else if(day[0]==10)
		setcolor(YELLOW);
	else if(day[0]==20)
		setcolor(MAGENTA);
	for(i=0;i<length-1;i++)
	{
		x1=base_x-width*i;
		x2=base_x-width*(i+1);
		y1=(int)(base_y2-((day[i+1]-ymin)/height*base_y1));
		y2=(int)(base_y2-((day[i+2]-ymin)/height*base_y1));
		line(x1,y1,x2,y2);
	}

}

void press_up(STOINFO *stoinfo)
{
	if(stoinfo->size<6)
	{
		stoinfo->size++;
	}
}

void press_down(STOINFO *stoinfo)
{
	if(stoinfo->size>1)
	{
		stoinfo->size--;
	}
}

void press_right(STOINFO *stoinfo)
{
	if(stoinfo->pointer>0)
	{
		stoinfo->pointer--;
	}
}

void press_left(STOINFO *stoinfo)
{
	if(stoinfo->pointer < stoinfo->stock_day_num-200)
	{
		stoinfo->pointer++;
	}
}

void day_num_stock(STOINFO *stoinfo)			//计算股票一共有多少天的数据
{
	char address[40];
	char time[10],kai[10],highest[10],lowest[10],shou[10],money_sum[20],amount_sum[15];
	int i;
	FILE *fp;
	strcpy(address,"data\\TXT\\");
	strcat(address,stoinfo->stockpress);
	strcat(address,".txt");
	if((fp=fopen(address,"rt"))==NULL)
	{
		printf("can not found this stock while calculate the days of stock\n");
		getch();
		exit(-1);
	}
	rewind(fp);
	for(i=0;;i++)
	{
		fscanf(fp,"%s %s %s %s %s %s %s",time,kai,highest,lowest,shou,amount_sum,money_sum);
		if(feof(fp))
			break;
	}
	fclose(fp);
	stoinfo->stock_day_num=i;
}

void trend_change(INFO *info,STOINFO *stoinfo,int *mx_,int *my_,int *mbutn_)							//切换展示的股票
{
	int mx,my,mbuttn=-1,day,old_day=0;
	int width[7]={0,4,8,12,16,20,24};
	int days_pre[7]={0,134,68,44,34,26,22};
	float day5[135]={5},day10[135]={10},day20[135]={20},day60[135]={60};
	float data1[180]={1e-6},data2[180]={1e-6},data3[180]={1e-6};
	int last_index=1,index=1;
	STOCK stock;
	cleardevice();
	Kline_draw_bk();
	stoinfo->pointer=0;
	if(info->layout==6)						//区别上证指数深成指数与普通股票走势图
	{
		find_stockpress(stoinfo);
		showstock(stoinfo);
		draw_slidder();
		move_slidder_2(stoinfo);
		show_new(stoinfo);
	}
	else if(info->layout==3)
	{
		strcpy(stoinfo->stockpress,"SZ");
		puthz12("上证指数",560,47,RED);
	}
	else if(info->layout==4)
	{
		strcpy(stoinfo->stockpress,"SC");
		puthz12("深成指数",560,47,RED);
	}
	menu_create();
	data_get(&stock,stoinfo,0);
	trend_draw(stoinfo,&stock,0,0);			//画K线图
	change_index(index,&stock,days_pre[stoinfo->size],data1,data2,data3);	//画小窗口曲线
	show_index(index,data1,data2,data3,1);									//展示小窗口股票指标曲线对应每一日数据
	day_calculate(stock.stop,day5,days_pre[stoinfo->size]);
	day_calculate(stock.stop,day10,days_pre[stoinfo->size]);
	day_calculate(stock.stop,day20,days_pre[stoinfo->size]);
	day_calculate(stock.stop,day60,days_pre[stoinfo->size]);
	data_new(&stock,0,day5,day10,day20,day60);								//展示K线每一日数据
	day_num_stock(stoinfo);
	mouse_save(mx,my);
	clearbuffer();
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(mx>=629-width[stoinfo->size]*days_pre[stoinfo->size]&&mx<=629&&my>=77&&my<=460&&mbuttn==0)		//设置鼠标形状
		{
			setmouseshape(3);
			day=(629-mx)/width[stoinfo->size]+1;
			if(day!=old_day)
			{
				old_day=day;
				data_new(&stock,old_day,day5,day10,day20,day60);
				show_index(index,data1,data2,data3,day);
			}
		}
		else if(mx>=55&&mx<=69&&((my>=228&&my<=240)||(my>=447&&my<=459)))
		{
			setmouseshape(1);
		}
		else 
		{
			setmouseshape(2);
		}
		
		if(info->layout==6&&mouse_press(55,228,69,240,&mx,&my,&mbuttn)&&strcmp(stoinfo->stockpress_,"000001")!=0&&stoinfo->number_>1)	//只有当显示的为股票走势才会显示拖动条
		{
			--(stoinfo->number_);
			move_slidder_2(stoinfo);
			show_new(stoinfo);	
		}
		else if(info->layout==6&&mouse_press(55,447,69,459,&mx,&my,&mbuttn)&&strcmp(stoinfo->stockpress_,"000620")!=0&&stoinfo->number_<187)
		{
			++(stoinfo->number_);
			move_slidder_2(stoinfo);
			show_new(stoinfo);
		}
		else if(info->layout==6&&mouse_press(54,230,68,437,&mx,&my,&mbuttn))
		{
			move_slidder_1(&mx,&my,&mbuttn,stoinfo);
			continue;
		}
		else if(info->layout==6&&mouse_press(500,47,512,59,&mx,&my,&mbuttn))
		{
			add_mystock(info,stoinfo);
		}
		else if(info->layout==6&&mouse_press(0,227,52,459,&mx,&my,&mbuttn)&&stoinfo->number_+(my-225)/47!=stoinfo->number)
		{
			stoinfo->number=stoinfo->number_+(my-225)/47;
			find_stockpress(stoinfo);
			showstock(stoinfo);
			stoinfo->pointer=0;
			data_get(&stock,stoinfo,0);
			trend_draw(stoinfo,&stock,0,0);
			change_index(index,&stock,days_pre[stoinfo->size],data1,data2,data3);
			day_calculate(stock.stop,day5,days_pre[stoinfo->size]);
			day_calculate(stock.stop,day10,days_pre[stoinfo->size]);
			day_calculate(stock.stop,day20,days_pre[stoinfo->size]);
			day_calculate(stock.stop,day60,days_pre[stoinfo->size]);
			data_new(&stock,0,day5,day10,day20,day60);
			show_index(index,data1,data2,data3,1);
			day_num_stock(stoinfo);
			continue;
		}
		else if(mouse_press(42,463,398,480,&mx,&my,&mbuttn))	//切换不同的曲线图
		{
			index=mx/40;
			if(last_index!=index)
			{
				last_index=index;
				change_index(index,&stock,days_pre[stoinfo->size],data1,data2,data3);
				show_index(index,data1,data2,data3,1);
				continue;
			}
		}
		else if(info->layout==6&&mouse_press(402,463,438,480,&mx,&my,&mbuttn))
		{
			info->layout=12;
			break;
		}
		else if(bioskey(1)!=0)
		{
			info->key.num=bioskey(0);
			if(info->key.num==F1||info->key.num==F2||info->key.num==F3
			  ||info->key.num==F4||info->key.num==F5||info->key.num==F6
			  ||info->key.num==F7||info->key.num==F8||info->key.num==F9||info->key.num==F10)
			{
				info->flag=2;
				break;
			}
			if(info->key.num==ENTER&&(info->layout==3||info->layout==4))
			{
				mousehide(mx,my);								//按下enter可以调取出来查找股票函数
				find(info,stoinfo);
				mouse_save(mx,my);
				if(info->layout==6)
				{
					find_stockpress(stoinfo);
					break;
				}
			}
			else if(info->key.num==UP||info->key.num==DOWN||info->key.num==LEFT||info->key.num==RIGHT)
			{
				mousehide(mx,my);
				stock_diff(info,stoinfo,&stock,day5,day10,day20,day60,data1,data2,data3,index);
				mouse_save(mx,my);
			}
			clearbuffer();
			continue;
		}
		if(mbuttn==1)
		{
			judge_press(info,stoinfo,&mx,&my,&mbuttn);
		}
		if(info->layout_last!=info->layout||info->flag==0)
		{
			*mx_=mx;
			*my_=my;
			*mbutn_=mbuttn;
			break;
		}
	}
}

void stock_diff(INFO *info,STOINFO *stoinfo,STOCK *stock,float *day5,float *day10,float *day20,float *day60,float *data1,float *data2,float *data3,int index)	//放大缩小总控制函数
{
	int days_pre[7]={0,134,68,44,34,26,22};
	//int flag=0;
	int init_pointer;
	int init_size;
	init_pointer=stoinfo->pointer;
	init_size=stoinfo->size;
	if(info->key.num==UP)
	{
		press_up(stoinfo);
	  //	flag=1;
	}
	else if(info->key.num==DOWN)
	{
		press_down(stoinfo);
		//flag=2;
	}
	else if(info->key.num==LEFT)
	{
		press_left(stoinfo);
	   //	flag=3;
	}
	else if(info->key.num==RIGHT)
	{
		press_right(stoinfo);
	   //	flag=4;
	}
	if(stoinfo->pointer!=init_pointer||stoinfo->size!=init_size)
	{
		data_get(stock,stoinfo,0);
		day_calculate(stock->stop,day5,days_pre[stoinfo->size]);
		day_calculate(stock->stop,day10,days_pre[stoinfo->size]);
		day_calculate(stock->stop,day20,days_pre[stoinfo->size]);
		day_calculate(stock->stop,day60,days_pre[stoinfo->size]);
		trend_draw(stoinfo,stock,0,0);
		change_index(index,stock,days_pre[stoinfo->size],data1,data2,data3);
		data_new(stock,0,day5,day10,day20,day60);
		show_index(index,data1,data2,data3,1);
	}
}

void find_stockpress(STOINFO *stoinfo)								//查找当前数字对应的股票代码
{
	int i;
	FILE *fp;
	char str1[7],str2[9],str3[8],str4[8];
	i=stoinfo->number;
	if((fp=fopen("data\\STOCK\\all.txt","rt"))==NULL)
	{
		printf("can not find the file all.txt\n");
		getch();
		exit(1);
	}
	for(;i>0;i--)
	{
		fscanf(fp,"%s%s%s%s",str1,str2,str3,str4);
	}
	strcpy(stoinfo->stockpress,str1);
	strcpy(stoinfo->stockname,str2);
	fclose(fp);
}

void showstock(STOINFO *stoinfo)
{
	setfillstyle(1,BLACK);
	bar(480,47,639,59);
	puthz12(stoinfo->stockname,580,47,RED);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,5);
	setcolor(RED);
	outtextxy(520,45,stoinfo->stockpress);
	setfillstyle(1,WHITE);
	bar(500,52,512,54);
	bar(505,47,507,59);
}

void show_new(STOINFO *stoinfo)										//展示新的股票五只股票
{
	FILE *fp;
	int i,j;
	char string1[7]={'\0'},string2[9]={'\0'},string3[8]={'\0'},string4[8]={'\0'};
	i=stoinfo->number_;
	if((fp=fopen("data\\STOCK\\all.txt","rt"))==NULL)
	{
		printf("can not find the file all_stocks\n");
		getch();
		exit(1);
	}
	for(;i>0;i--)
	{
		fscanf(fp,"%s %s %s %s",string1,string2,string3,string4);
	}
	strcpy(stoinfo->stockpress_,string1);
	
	setfillstyle(1,WHITE);
	bar(0,225,54,460);
	setcolor(BLACK);
	line(0,272,54,272);
	line(0,319,54,319);
	line(0,366,54,366);
	line(0,413,54,413);
	
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,5);

	for(j=0;j<5;j++)
	{
		puthz12(string2,3,226+j*47,BLUE);
		setcolor(BLUE);
		outtextxy(3,236+j*47,string1);
		if(atof(string3)>0)
			setcolor(RED);
		else if(atof(string3)==0)
			setcolor(BLACK);
		else if(atof(string3)<0)
			setcolor(GREEN);

		outtextxy(3,247+j*47,string4);
		if(strcmp(string3,"--")!=0)
		{
			strcat(string3,"%");
		}

		outtextxy(3,258+j*47,string3);
		fscanf(fp,"%s %s %s %s",string1,string2,string3,string4);
	}
	fclose(fp);
}

void data_new(STOCK *stock,int day,float *day5,float *day10,float *day20,float *day60)				//更新每一支K线图对应数据
{
	char str[12]={'\0'};
	setfillstyle(1,BLACK);
	bar(126,18,199,31);
	bar(236,18,309,31);
	bar(346,18,419,31);
	bar(456,18,529,31);
	bar(566,18,639,31);
	bar(136,32,199,45);
	bar(246,32,309,45);
	bar(346,32,419,45);
	bar(456,32,529,45);
	bar(566,32,639,45);

	bar(117,47,180,59);
	bar(222,47,285,59);
	bar(323,47,386,59);
	bar(424,47,487,59);

	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,5);
	setcolor(BLUE);
	sprintf(str,"%lu",stock->date[day]);
	outtextxy(126,17,str);
	sprintf(str,"%.2f",stock->begin[day]);
	outtextxy(236,17,str);
	sprintf(str,"%.2f",stock->zuigao[day]);
	outtextxy(346,17,str);
	sprintf(str,"%.2f",stock->zuidi[day]);
	outtextxy(456,17,str);
	sprintf(str,"%.2f",stock->stop[day]);
	outtextxy(566,17,str);
	if(stock->sum_amount[day]>=1.0e8)
	{
		sprintf(str,"%.1f",stock->sum_amount[day]/1.0e6);		//成交量指股票当天成交的总手数，一手等于一百股
		strcat(str,"万");
		puthz12(str,136,32,BLUE);
	}
	else
	{
		sprintf(str,"%.0f",stock->sum_amount[day]/100.0);
		outtextxy(136,30,str);
	}

	if(stock->sum_money[day]>=1.0e8)
	{
		sprintf(str,"%.1f",stock->sum_money[day]/1.0e8);
		strcat(str,"亿");
		puthz12(str,246,32,BLUE);
	}
	else
	{
		sprintf(str,"%.0f",stock->sum_money[day]/1.0e4);
		strcat(str,"万");
		puthz12(str,246,32,BLUE);
	}
	if(stock->stop[day]>stock->stop[day+1])
		setcolor(RED);
	if(stock->stop[day]==stock->stop[day+1])
		setcolor(WHITE);
	if(stock->stop[day]<stock->stop[day+1])
		setcolor(LIGHTGREEN);
	sprintf(str,"%.2f",(stock->stop[day]-stock->stop[day+1])/stock->stop[day]*100.0);	//计算涨幅
	strcat(str,"%");
	outtextxy(346,30,str);
	sprintf(str,"%.2f",stock->stop[day]-stock->stop[day+1]);	//计算涨跌
	outtextxy(456,30,str);
	sprintf(str,"%.2f",(stock->zuigao[day]-stock->zuidi[day])/stock->stop[day+1]*100.0);	//计算振幅
	strcat(str,"%");
	outtextxy(566,30,str);
	setcolor(WHITE);
	sprintf(str,"%.2f",day5[day+1]);
	outtextxy(119,45,str);
	setcolor(YELLOW);
	sprintf(str,"%.2f",day10[day+1]);
	outtextxy(224,45,str);
	setcolor(MAGENTA);
	sprintf(str,"%.2f",day20[day+1]);
	outtextxy(325,45,str);
	setcolor(LIGHTGREEN);
	sprintf(str,"%.2f",day60[day+1]);
	outtextxy(426,45,str);
	delay(100);
}

void change_index(int index,STOCK *stock,int length,float *data1,float *data2,float *data3)
{
	switch(index)
	{
		case 1:
			draw(stock,stock->sum_amount,length,data1,data2,0,0);
			outtextxy(108,342,"VOL");
			break;
		case 2:
			draw_KDJ(stock->stop,length,data1,data2,data3,0,0);
			break;
		case 3:
			draw_MACD(stock->stop,length,data1,data2,data3,0,0);
			break;
		case 4:
			draw(stock,stock->sum_money,length,data1,data2,0,0);
			outtextxy(108,342,"AMD");
			break;
		case 5:
			draw_OBV(stock,length,data1,data2,0,0);
			break;
		case 6:
			draw_RSI(stock->stop,length,data1,data2,data3,0,0);
			break;
		case 7:
			draw_PSY(stock->stop,length,data1,data2,0,0);
			break;
		case 8:
			draw_BIAS(stock->stop,length,data1,data2,data3,0,0);
			break;
		case 9:
			draw_BOLL(stock->stop,length,data1,data2,data3,0,0);
			break;
	}
}

void show_index(int index,float *data1,float *data2,float *data3,int day)		//展示第二区域不同曲线的数据
{
	char str[15];
	setfillstyle(1,BLACK);

	switch(index)
	{
		case 1:
			bar(174,342,250,354);
			bar(309,342,384,354);
			setcolor(WHITE);	
			if(data1[day]>=1.0e8)
			{
				sprintf(str,"%.1f",data1[day]/1.0e6);
				strcat(str,"万");
				puthz12(str,174,343,WHITE);
			}
			else
			{
				sprintf(str,"%.0f",data1[day]/100.0);
				outtextxy(174,341,str);
			}
			setcolor(YELLOW);
			if(data2[day]>=1.0e8)
			{
				sprintf(str,"%.1f",data2[day]/1.0e6);
				strcat(str,"万");
				puthz12(str,309,343,YELLOW);
			}
			else
			{
				sprintf(str,"%.0f",data2[day]/100.0);
				outtextxy(309,341,str);
			}
			break;

		case 2:
			bar(164,342,250,354);
			bar(297,342,384,354);
			bar(427,342,480,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);
			sprintf(str,"%.2f",data1[day-1]);
			outtextxy(167,341,str);
			setcolor(YELLOW);
			sprintf(str,"%.2f",data2[day-1]);
			outtextxy(297,341,str);
			setcolor(MAGENTA);
			sprintf(str,"%.2f",data3[day-1]);
			outtextxy(427,341,str);
			break;

		case 3:
			bar(175,342,250,354);
			bar(305,342,384,354);
			bar(439,342,480,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);
			sprintf(str,"%.2f",data1[day]);
			outtextxy(175,341,str);
			setcolor(YELLOW);
			sprintf(str,"%.2f",data2[day]);
			outtextxy(305,341,str);
			setcolor(MAGENTA);
			sprintf(str,"%.2f",data3[day]);
			outtextxy(439,341,str);
			break;

		case 4:
			bar(174,342,229,354);
			bar(309,342,364,354);	
			setcolor(WHITE);
			if(data1[day]>=1.0e8)
			{
				sprintf(str,"%.2f",data1[day]/1.0e8);
				strcat(str,"亿");
				puthz12(str,174,343,WHITE);
			}
			else
			{
				sprintf(str,"%.0f",data1[day]/1.0e4);
				strcat(str,"万");
				puthz12(str,174,343,WHITE);
			}
			setcolor(YELLOW);
			if(data2[day]>=1.0e8)
			{
				sprintf(str,"%.2f",data2[day]/1.0e8);
				strcat(str,"亿");
				puthz12(str,309,343,YELLOW);
			}
			else
			{
				sprintf(str,"%.0f",data2[day]/1.0e4);
				strcat(str,"万");
				puthz12(str,309,343,YELLOW);
			}
			break;
			
		case 5:
			bar(192,342,280,354);
			bar(332,342,420,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);	
			if(data1[day]>=1.0e6)
			{
				sprintf(str,"%.1f",data1[day]/1.0e4);
				strcat(str,"万");
				puthz12(str,195,343,WHITE);
			}
			else
			{
				sprintf(str,"%.0f",data1[day]);
				outtextxy(195,341,str);
			}
			setcolor(YELLOW);
			if(data2[day]>=1.0e6)
			{
				sprintf(str,"%.1f",data2[day]/1.0e4);
				strcat(str,"万");
				puthz12(str,334,343,YELLOW);
			}
			else
			{
				sprintf(str,"%.0f",data2[day]);
				outtextxy(334,341,str);
			}
			break;
			
		case 6:
			bar(248,342,300,354);
			bar(378,342,430,354);
			bar(508,342,560,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);
			sprintf(str,"%.2f",data1[day]);
			outtextxy(248,341,str);
			setcolor(YELLOW);
			sprintf(str,"%.2f",data2[day]);
			outtextxy(378,341,str);
			setcolor(MAGENTA);
			sprintf(str,"%.2f",data3[day]);
			outtextxy(508,341,str);
			break;
			
		case 7:
			bar(245,342,300,354);
			bar(384,342,430,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);
			sprintf(str,"%.2f",data1[day]);
			outtextxy(245,341,str);
			setcolor(YELLOW);
			sprintf(str,"%.2f",data2[day]);
			outtextxy(384,341,str);
			break;
			
		case 8:
			bar(251,342,300,354);
			bar(381,342,430,354);
			bar(511,342,560,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);
			sprintf(str,"%.2f",data1[day]);
			outtextxy(251,341,str);
			setcolor(YELLOW);
			sprintf(str,"%.2f",data2[day]);
			outtextxy(381,341,str);
			setcolor(MAGENTA);
			sprintf(str,"%.2f",data3[day]);
			outtextxy(511,341,str);
			break;
			
		case 9:
			bar(248,342,300,354);
			bar(375,342,430,354);
			bar(505,342,560,354);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			setcolor(WHITE);
			sprintf(str,"%.2f",data1[day]);
			outtextxy(248,341,str);
			setcolor(YELLOW);
			sprintf(str,"%.2f",data2[day]);
			outtextxy(375,341,str);
			setcolor(MAGENTA);
			sprintf(str,"%.2f",data3[day]);
			outtextxy(505,341,str);
			break;
	}
}