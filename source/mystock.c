#include "mystock.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:			line.c
  Author:       		李墨洋
  Version:				1.0 
  Date:					18/11/05
  Description:  		小窗口曲线函数
  Function List:  
	add_mystock			添加自选股
	draw_mystock		自选股界面背景
	show_mystock		自选股界面总控制
	present				展示自选股信息
	init_mystock		初始化自选股链表
	free_stock			释放自选股链表
	delet_mystock		删除某个自选股
	rewrite_stock		更新自选股链表
	back				跳转到详情界面
	find_stockpress_	根据股票代码查找股票编号
  History:      
	<author>  <time>   <version >   <desc>
	李墨洋    18/11/05     1.0     build this moudle  
*************************************************/

void add_mystock(INFO *info,STOINFO *stoinfo)
{
	mySTOCK *own_stock;
	int length;
	own_stock=init_mystock(info,own_stock,&length);
	rewrite_stock(info,stoinfo,own_stock,length,1);
	free_stock(length,own_stock);
}

void draw_mystock()
{
	cleardevice();
	detail_draw_bk();
	setfillstyle(1,WHITE);
	bar(100,30,620,460);
	setfillstyle(1,BLACK);
	bar(105,35,615,455);
	setfillstyle(1,WHITE);
	bar(110,40,610,450);
	setcolor(BLACK);
	rectangle(113,43,607,447);
	rectangle(117,47,603,443);
	put_hz(140,67,"股票代码",BLACK,16,2);
	put_hz(220,67,"股票名称",BLACK,16,2);
	put_hz(315,67,"涨幅",BLACK,16,2);
	put_hz(400,67,"现价",BLACK,16,2);
	put_hz(480,67,"多股同列",BLACK,16,2);
}

void show_mystock(INFO *info,STOINFO *stoinfo,int *mx_,int *my_,int *mbutn_)						//自选股界面总控制
{
	int mx,my,mbuttn=-1;
	int length,offset=0;
	int column=0;
	mySTOCK *own_stock;
	draw_mystock();
	own_stock=init_mystock(info,own_stock,&length);
	present(own_stock,length,offset);
	setmouseshape(2);
	mouse_save(mx,my);
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		judge_press(info,stoinfo,&mx,&my,&mbuttn);
		if(mouse_press(460,93,540,417,&mx,&my,&mbuttn)&&(my%30)<=24&&my<=93+(length-offset)*30)
		{
			own_stock=delet_mystock(info,stoinfo,own_stock,&length,offset,(my-93)/30+1);
			present(own_stock,length,offset);
		}
		else if(mouse_press(540,93,582,417,&mx,&my,&mbuttn)&&(my%30)<=24&&my<=93+(length-offset)*30)
		{
			info->layout=6;
			back(own_stock,offset,(my-93)/30+1,stoinfo);
			find_stockpress_(stoinfo);
		}
		else if(mouse_press(480,67,550,83,&mx,&my,&mbuttn))
		{
			stock_multied(own_stock,length,stoinfo,info);
		}
		if(bioskey(1)!=0)
		{
			info->key.num=bioskey(0);
			if(info->key.num==F1||info->key.num==F2||info->key.num==F3
			  ||info->key.num==F4||info->key.num==F5||info->key.num==F6
			  ||info->key.num==F7||info->key.num==F8||info->key.num==F9||info->key.num==F10)
			{
				info->flag=2;
				free_stock(length,own_stock);
				break;
			}
			else if(info->key.num==UP&&offset>=11)		//上一页
			{
				offset-=11;
				present(own_stock,length,offset);
			}
			else if(info->key.num==DOWN&&offset+11<length)
			{
				offset+=11;
				present(own_stock,length,offset);
			}
		}
		if(info->layout_last!=info->layout||info->flag==0)
		{
			free_stock(length,own_stock);
			*mx_=mx;
			*my_=my;
			*mbutn_=mbuttn;
			break;
		}
	}
}

void find_stockpress_(STOINFO *stoinfo)
{
	int i=1;
	FILE *fp;
	char str1[7],str2[9],str3[8],str4[8];
	if((fp=fopen("data\\STOCK\\all.txt","rt"))==NULL)
	{
		printf("can not find the file all.txt\n");
		getch();
		exit(1);
	}
	for(;;i++)
	{
		fscanf(fp,"%s%s%s%s",str1,str2,str3,str4);
		if(strcmp(str1,stoinfo->stockpress)==0)
		{
			break;
		}
	}
	strcpy(stoinfo->stockname,str2);
	stoinfo->number=i;
	fclose(fp);
}

void back(mySTOCK *own_stock,int offset,int position,STOINFO *stoinfo)
{
	int i;
	mySTOCK *temp;
	temp=own_stock;
	for(i=1;i<offset+position;i++)
	{
		temp=temp->next;
	}
	strcpy(stoinfo->stockpress,temp->stockcode);
	strcpy(stoinfo->stockname,temp->stockname);
}

void present(mySTOCK *own_stock,int length,int offset)
{
	int i=0,j=0;
	mySTOCK *temp;
	char temp_str1[8],temp_str2[8];
	temp=own_stock;
	draw_mystock();
	for(i=0;i<offset;i++)
	{
		temp=temp->next;
	}
	for(i=0;(i<length-offset)&&j<11;i++,j++)
	{
		sprintf(temp_str1,"%.2f",temp->percent);
		strcat(temp_str1,"%");
		sprintf(temp_str2,"%.2f",temp->price);
		if(temp->percent>0)
		{
			put_hz(140,97+30*i,temp->stockcode,RED,16,2);
			put_hz(220,97+30*i,temp->stockname,RED,16,2);
			put_hz(315,97+30*i,temp_str1,RED,16,2);
			put_hz(400,97+30*i,temp_str2,RED,16,2);
		}
		else if(temp->percent<0)
		{
			put_hz(140,97+30*i,temp->stockcode,GREEN,16,2);
			put_hz(220,97+30*i,temp->stockname,GREEN,16,2);
			put_hz(315,97+30*i,temp_str1,GREEN,16,2);
			put_hz(400,97+30*i,temp_str2,GREEN,16,2);
		}
		else if(fabs(temp->percent)<0.01)
		{
			put_hz(140,97+30*i,temp->stockcode,BLACK,16,2);
			put_hz(220,97+30*i,temp->stockname,BLACK,16,2);
			put_hz(315,97+30*i,temp_str1,BLACK,16,2);
			put_hz(400,97+30*i,temp_str2,BLACK,16,2);
		}
		setfillstyle(1,LIGHTBLUE);
		bar(460,93+30*i,502,117+30*i);
		bar(540,93+30*i,582,117+30*i);
		put_hz(464,97+30*i,"删除",WHITE,16,2);
		put_hz(544,97+30*i,"详情",WHITE,16,2);
		temp=temp->next;
	}
}

mySTOCK *init_mystock(INFO *info,mySTOCK *own_stock,int *length)	//初始化所有自选股信息
{
	FILE *fp;
	int i=0;
	char temp_str[40];
	mySTOCK *temp,*my_stock;
	own_stock=NULL;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,info->account);
	strcat(temp_str,"\\");
	strcat(temp_str,"stock.txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file stock.txt while init the mystock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%d",&i);
	//fread(&i,sizeof(int),1,fp);
	*length=i;
	while(!feof(fp)&&i)
	{
		i--;
		if((my_stock=(mySTOCK *)malloc(sizeof(mySTOCK)))==NULL)
		{
			printf("Allocation of mySTOCK failed!!!");
			getch();
			exit(1);
		}
		fscanf(fp,"%s %s %f %f",my_stock->stockcode,my_stock->stockname,&my_stock->percent,&my_stock->price);
		if(own_stock==NULL)
		{
			own_stock=my_stock;		//my_stock成为自选股第一个节点
			own_stock->pre=NULL;
			own_stock->next=NULL;
		}
		else if(own_stock->next==NULL)
		{
			own_stock->next=my_stock;
			own_stock->pre=my_stock;
			my_stock->next=own_stock;
			my_stock->pre=own_stock;
		}
		else
		{
			temp=own_stock->pre;		//用temp保存当前最后一个节点
			temp->next=my_stock;		//将当前最后一个节点的后继指向my_stock，新添加的节点
			my_stock->next=own_stock;	//将新节点的后继指向头节点
			my_stock->pre=temp;			//将新节点的前驱指向之前的尾节点
			own_stock->pre=my_stock;	//将头结点的前驱指向当前最后一个节点
		}
	}
	fclose(fp);
	return own_stock;
}

void free_stock(int length,mySTOCK *own_stock)		//free所有自选股占用的内存
{
	mySTOCK *pm,*pn;
	pn=own_stock;
	while(length>0)
	{
		pm=pn;
		pn=pn->next;
		free(pm);
		length--;
	}
}

mySTOCK *delet_mystock(INFO *info,STOINFO *stoinfo,mySTOCK *own_stock,int *length,int offset,int position)//删除某一只自选股
{
	mySTOCK *temp,*pnode;
	int i,j;
	temp=own_stock;
	for(i=1;i<offset+position;i++)
	{
		temp=temp->next;
	}
	pnode=temp;
	if(own_stock->next==NULL)
	{
		free(pnode);
	}
	
	if(offset+position==1)	//如果删除的是头结点
	{
		own_stock=own_stock->next;
		temp=own_stock->pre;
		pnode=temp;
	}
	
	if(*length==2)
	{
		temp->next->next=NULL;
		temp->next->pre=NULL;
		free(pnode);
	}
	else
	{
		temp->next->pre=temp->pre;
		temp->pre->next=temp->next;
		free(pnode);
	}
	--(*length);
	j=*length;
	rewrite_stock(info,stoinfo,own_stock,j,0);
	return own_stock;
}

void rewrite_stock(INFO *info,STOINFO *stoinfo,mySTOCK *own_stock,int length,int flag)
{
	FILE *fp,*fq;
	char string1[7]={'\0'},string2[9]={'\0'},string3[8]={'\0'},string4[8]={'\0'};
	mySTOCK *stock;
	int i=stoinfo->number;
	int j,judge_flag=0;
	char temp_str[40];
	float price,percent;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,info->account);
	strcat(temp_str,"\\");
	strcat(temp_str,"stock.txt");
	stock=own_stock;
	if((fp=fopen(temp_str,"wt"))==NULL)
	{
		printf("can't find the file stock.txt while rewrite the mystock!\n");
		getch();
		fclose(fp);
		exit(1);
	}
	if(flag==1)			//为直接添加
	{
		if((fq=fopen("data\\STOCK\\all.txt","rt"))==NULL)
		{
			printf("can not find the file all_stocks\n");
			getch();
			exit(1);
		}
		for(;i>0;i--)
		{
			fscanf(fq,"%s %s %s %s",string1,string2,string3,string4);
		}
		fclose(fq);

		for(j=0;j<length;j++)		//检验重复
		{
			if(strcmp(stock->stockcode,string1)==0)
			{
				judge_flag=1;
				break;
			}
			stock=stock->next;
		}

		rewind(fp);
		if(judge_flag==0)
		{
			j=length+1;
			fprintf(fp,"%d",j);
			//fwrite(&j,sizeof(int),1,fp);
		}
		else
		{
			fprintf(fp,"%d",length);
			//fwrite(&length,sizeof(int),1,fp);
		}
		fprintf(fp,"%c",'\n');
		//fwrite("\n",1,1,fp);
		stock=own_stock;
		for(j=0;j<length;j++)
		{
			fprintf(fp,"%s %s %.2f %.2f",stock->stockcode,stock->stockname,stock->percent,stock->price);
			stock=stock->next;
			fprintf(fp,"%c",'\n');
			//fwrite("\n",1,1,fp);
		}
		if(judge_flag==0)
		{
			price=atof(string4);
			percent=atof(string3);
			fprintf(fp,"%s %s %.2f %.2f",string1,string2,percent,price);
			fprintf(fp,"%c",'\n');
			//fwrite("\n",1,1,fp);
		}
	}
	else if(flag==0)
	{
		rewind(fp);
		fprintf(fp,"%d",length);
		fprintf(fp,"%c",'\n');
		//fwrite(&length,sizeof(int),1,fp);
		//fwrite("\n",1,1,fp);
		for(;length>0;length--)
		{
			fprintf(fp,"%s %s %.2f %.2f",stock->stockcode,stock->stockname,stock->percent,stock->price);
			fwrite("\n",1,1,fp);
			stock=stock->next;
		}
	}
	fclose(fp);
}

/*************************************************
  Function:			stock_pre 
  Description:   	多股并列
  Input:          	own_stock	存储自选股信息的链表
					column		现在显示股票的行
					length		自选股总数量
  Return:         	void
*************************************************/
void stock_multied(mySTOCK *own_stock,int length,STOINFO *stoinfo,INFO *info)
{
	int mx,my,mbuttn;
	int index=0;
	int column=1;
	int i=0;
	mySTOCK *temp;
	mouse_save(mx,my);
	line_switch(index,own_stock,column,stoinfo);
	stoinfo->pointer=0;
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(bioskey(1)!=0)
		{
			info->key.num=bioskey(0);
			if(info->key.num==UP&&column>1)
			{
				column-=1;
				line_switch(index,own_stock,column,stoinfo);
			}
			else if(info->key.num==DOWN&&length-3*column>6)
			{
				column+=1;
				line_switch(index,own_stock,column,stoinfo);
			}
			else if(info->key.num==LEFT&&stoinfo->pointer<100)
			{
				stoinfo->pointer++;
				line_switch(index,own_stock,column,stoinfo);
			}
			else if(info->key.num==RIGHT&&stoinfo->pointer>0)
			{
				stoinfo->pointer--;
				line_switch(index,own_stock,column,stoinfo);
			}
		}
		else if(mbuttn==2)		//判断右键是否按下
		{
			right_press(info,stoinfo,mx,my);
			if(info->layout==11)
			{
				temp=own_stock;
				for(i=0;i<3*(column-1+(my-20)/146)+mx/215;i++)
				{
					temp=temp->next;
				}
				strcpy(stoinfo->stockpress,temp->stockcode);
				find_stockpress_(stoinfo);
				stoinfo->pointer=0;
				break;
			}
			else
			{
				line_switch(index,own_stock,column,stoinfo);
				mouse_save(mx,my);
				newmouse(&mx,&my,&mbuttn);
			}
		}
		else if(mouse_press(0,20,639,460,&mx,&my,&mbuttn)&&(mx+5)%215<210)	//判断左键是否按下
		{
			info->layout=6;
			temp=own_stock;
			for(i=0;i<3*(column-1+(my-20)/146)+mx/215;i++)
			{
				temp=temp->next;
			}
			strcpy(stoinfo->stockpress,temp->stockcode);
			find_stockpress_(stoinfo);
			stoinfo->pointer=0;
			break;
		}
		else if(mouse_press(5,3,39,19,&mx,&my,&mbuttn)&&index!=0)
		{
			index=0;
			line_switch(index,own_stock,column,stoinfo);
		}
		else if(mouse_press(55,3,89,19,&mx,&my,&mbuttn)&&index!=1)
		{
			index=1;
			line_switch(index,own_stock,column,stoinfo);
		}
		else if(mouse_press(40,460,360,479,&mx,&my,&mbuttn)&&index!=mx/40+1)
		{
			index=mx/40+1;
			line_switch(index,own_stock,column,stoinfo);
		}
	}
}

void draw_multied(void)
{
	cleardevice();
	setcolor(RED);
	rectangle(0,0,639,479);
	line(0,20,639,20);
	line(0,460,639,460);
	line(210,20,210,459);
	line(215,20,215,459);
	line(425,20,425,459);
	line(430,20,430,459);
	line(0,166,639,166);
	line(0,313,639,313);
	
	settextjustify(1,1);
	settextstyle(2,0,6);

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
	
	outtextxy(60,468,"VOL");
	outtextxy(100,468,"KDJ");
	outtextxy(140,468,"MACD");
	outtextxy(180,468,"AMD");
	outtextxy(220,468,"RSI");
	outtextxy(260,468,"PSY");
	outtextxy(300,468,"BIAS");
	outtextxy(340,468,"BOLL");
	
	put_hz(5,3,"日线",RED,16,2);
	put_hz(55,3,"1分钟",RED,16,2);
	put_hz(125,3,"MA5",WHITE,16,2);
	put_hz(175,3,"MA10",YELLOW,16,2);
	put_hz(225,3,"MA20",MAGENTA,16,2);
	put_hz(275,3,"MA60",LIGHTGREEN,16,2);
	puthz12("指标",9,465,RED);
}

void line_switch(int index,mySTOCK *own_stock,int column,STOINFO *stoinfo)
{
	STOCK stock;
	float data1[180]={1e-6},data2[180]={1e-6},data3[180]={1e-6};
	int num,base_x,base_y2;
	mySTOCK *temp=own_stock;
	clearbuffer();
	draw_multied();
	for(num=0;num<3*(column-1);num++)
	{
		temp=temp->next;
	}
	for(num=1;num<=9;num++)
	{
		base_x=((num-1)%3*215+203);
		base_y2=((num-1)/3+1)*146+15;
		strcpy(stoinfo->stockpress,temp->stockcode);
		data_get(&stock,stoinfo,0);
		find_stockpress_(stoinfo);
		puthz12(stoinfo->stockname,base_x-165,base_y2-137,RED);
		puthz12(stoinfo->stockpress,base_x-115,base_y2-137,RED);
		switch(index)
		{
			case 0:	trend_draw(stoinfo,&stock,1,num);
					puthz12("日线",base_x-199,base_y2-137,RED);
				break;
			case 1:	data_get_min(&stock,stoinfo);
					puthz12("1分钟",base_x-199,base_y2-137,RED);
					trend_draw(stoinfo,&stock,1,num);
				break;
			case 2:	draw(&stock,stock.sum_amount,100,data1,data2,1,num);
					puthz12("VOL",base_x-199,base_y2-137,RED);
				break;
			case 3:	draw_KDJ(stock.stop,100,data1,data2,data3,1,num);
					puthz12("KDJ",base_x-199,base_y2-137,RED);
				break;
			case 4:	draw_MACD(stock.stop,100,data1,data2,data3,1,num);
					puthz12("MACD",base_x-199,base_y2-137,RED);
				break;
			case 5:	draw(&stock,stock.sum_money,100,data1,data2,1,num);
					puthz12("AMD",base_x-199,base_y2-137,RED);
				break;
			case 6:	draw_RSI(stock.stop,100,data1,data2,data3,1,num);
					puthz12("RSI",base_x-199,base_y2-137,RED);
				break;
			case 7:	draw_PSY(stock.stop,100,data1,data2,1,num);
					puthz12("PSY",base_x-199,base_y2-137,RED);
				break;
			case 8:	draw_BIAS(stock.stop,100,data1,data2,data3,1,num);
					puthz12("BIAS",base_x-199,base_y2-137,RED);
				break;
			case 9:	draw_BOLL(stock.stop,100,data1,data2,data3,1,num);
					puthz12("BOLL",base_x-199,base_y2-137,RED);
				break;
		}
		temp=temp->next;
		if(temp==own_stock)
			break;
	}
}



/*****多股同列界面右键*****/
void right_press(INFO *info,STOINFO *stoinfo,int mx_,int my_)
{
	int mx,my,mbuttn;
	setfillstyle(1,WHITE);
	bar(mx_,my_,mx_+100,my_+20);
	put_hz(mx_+15,my_+2,"股票财务",BLACK,16,2);
	mouse_save(mx_,my_);
	newmouse(&mx,&my,&mbuttn);
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(mouse_press(mx_,my_,mx_+100,my_+20,&mx,&my,&mbuttn))	//跳转到股票财务界面
		{
			info->layout=11;
			break;
		}
		else if(mouse_press(0,0,639,479,&mx,&my,&mbuttn))
		{
			break;
		}
	}
}