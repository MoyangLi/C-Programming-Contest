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
	
	if(a[0]=='.')					//灏忔暟鐐瑰墠娌℃湁鏁存暟閮ㄥ垎
	{
		for(iround=length;iround>0;iround++)
		{
			a[iround]=a[iround-1];
		}
		a[0]='0';		
	}
	
	for(iround=0;;iround++)			
	{
		if(a[iround]=='.')			//鎵惧埌灏忔暟鐐逛綅缃?
		{
			point=iround+1;
			break;
		}
		else if(a[iround]=='\0')	//娌℃湁灏忔暟鐐?
		{
			point=-10;
			break;
		}
	}
	
	length=strlen(a);
	if(point==-10)				//鍙湁鏁存暟
	{
		a[length]='.';
		a[length+1]='0';
		a[length+2]='0';
		a[length+3]='\0';
	}
	else if((length-point)>2)			//涓嶆涓や綅灏忔暟
	{
		a[point+2]='\0';
	}
	else if((length-point)==1)		//鍙湁涓�浣嶅皬鏁?
	{
		a[length]='0';
		a[length+1]='\0';
	}
	else if((length-point)==0)		//灏忔暟鐐瑰悗娌′綅鏁?
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
data_updata()  负责数据更新
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
	
            if((fstock=fopen(address,"rb"))==NULL)                ///fstock鎵撳紑鏂囦欢data\\database\\000001\\list.txt
			{
		        printf("data_updata: error opening list.txt(out)\n");
		        getch();
	        }
			fread(&number,sizeof(int),1,fstock);         ///鑲＄エ鍙风爜
			fread(symbolic,6,1,fstock);                  
			fread(name,10,1,fstock);                     ///鑲＄エ鍚嶇О
			fread(data,sizeof(float),9,fstock);          ///鑲＄エ鏁版嵁
		
			fclose(fstock);
			
			if(fabs(data[2])<1e-2)
			{
				continue;
			}
			else
			{
				randnum=gauss_rand();
		
				data[0]=data[0]*(1+0.07*randnum);
				if((data[0]-data[3]*1.15)>0)					//鏇存柊鐜颁环  data[0]
				{
					data[0]=data[3]*1.15;
				}
				else if((data[0]-data[3]*0.85)<0)
				{
					data[0]=data[3]*0.85;
				}
		
				data[1]=(data[0]-data[3])*100/data[3];		//鏇存柊娑ㄨ穼 data[1]
			
				if((data[0]-data[4])>0)						//鏇存柊鏈�楂樹环    data[4]
				{
					data[4]=data[0];
				}
		
				if((data[0]-data[5])<0)						//鏇存柊鏈�浣庝环    data[5]
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
  help_control(INFO *info,STOINFO * stoinfo,int *mx,int *my,int *mbutt)负责帮助控制
**********************************************************/
void help_control(INFO *info,STOINFO * stoinfo,int *mx,int *my,int *mbutt)
{   while(1)
    {
        newmouse(mx,my,mbutt);
	if(mouse_press(640/2-66,480-50-12-3-20,640/2-66+24,480-50-12-3-20+2+6,mx,my,mbutt))
	{
		help_draw1();           //helpdraw里面会自己清屏，画菜单
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
  help_draw1(INFO *info)   画出第一页的内容
**********************************************************/
void help_draw1()   //画出第一页的内容
{
	int r=12;
	int dx=160;
	int dy=50;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *str0="帮助";
	char *page[]={"[1]","[2]","[3]","[4]",0};
	char *str3="退出";

	char *simplename[]={
					"欢迎使用证券投资决策分析系统",
					"本系统为证券投资者提供证券市场上的各种股票操作，方便用户查询股票实时走势、财务数据、历史行情，进行股票交易，利用系统的量化投资模型对比股票，推荐投资组合，还辅佐有各种快捷操作方式。操作与市面上的炒股软件类似。祝您使用愉快！",
					"股市有风险，投资需谨慎。本系统尤其是量化投资荐股系统不对您的任何收益与亏损负责。请谨慎使用。",
					"制作：李墨洋 焦思懿 2018.10.10",
					"在此一并感谢帮助过我们的各位老师，同学！",
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
  help_draw2(INFO *info)   画出第二页的内容
**********************************************************/
void help_draw2()   //画出第二页的内容
{
	int r=12;
	int dx=160;
	int dy=50;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *page[]={"[1]","[2]","[3]","[4]",0};
	char *str3="退出";

	char *simplename[]={
						"详细说明：",
						"1.系统主要界面：",
						"深证A股界面（F2）",
						"上证指数界面（F3）",
						"深成指数界面（F4）",
						"自选股界面（F5）",
						"股票K线界面（F6）",
						"交易界面（F7）",
						"股票对比界面（F8）",
						"组合推荐界面（F9）",
						"帮助界面（F10）",
						0};
	char *introduction[]={
						"",
						"",
						"：查看深证A股",
						"：查看上证指数",
						"：查看深成指数",
						"：查看自选股",
						"：查看股票K线",
						"：进行股票交易",
						"：对选定的股票进行对比",
						"：量化投资模型为您推荐投资组合",
						"：查看系统使用说明",
						0};
	

	//总的页面背景
	cleardevice();
	setcolor(BLUE);
	rectangle(dx,dy,maxx-dx,maxy-dy);        //画出主要的大矩形


	//输出第二页的内容

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


//到这里以后要改

	//显示退出键
	setcolor(LIGHTRED);
	rectangle(maxx/2+129,dy+r+2,maxx/2+129+24+1,dy+r+2+12+2);
	puthz12(str3,maxx/2+130,dy+r+3,LIGHTRED);   //显示退出

	setcolor(LIGHTRED);
	outtextxy(maxx/2-30,maxy-dy-r-3-20+2,page[1]);
	setcolor(YELLOW);
	outtextxy(maxx/2-66,maxy-dy-r-3-20+2,page[0]);
	outtextxy(maxx/2+6,maxy-dy-r-3-20+2,page[2]);
	outtextxy(maxx/2+42,maxy-dy-r-3-20+2,page[3]);
}

/**********************************************************
  help_draw3(INFO *info)   画出第三页的内容
**********************************************************/
void help_draw3()
{
	int dx=160;
	int dy=50;
	int r=12;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *page[]={"[1]","[2]","[3]","[4]",0};
	//char *str2="下一页";
	char *str3="退出";

	char *simplename[]={
						"2.辅助快捷操作：",
						"股票快速查找：",
						"选定指数排序：",
						"下拉菜单",
						"键盘快捷键",
						0};
	char *introduction[]={
						"",
						"用户可用小键盘输入六位股票代码，系统自动搜索对应的股票，方便用户选定股票查看详细信息",
						"用户可以在沪深300界面点击排序目录，系统会自动进行升序/降序处理，方便用户筛选股票（目前仅限于代码，现价，涨跌幅，换手率，振幅五项指数的排序）",
						"用户可直接在界面点击屏幕上方的菜单选择各种功能",
						"用户可直接在任何界面（除登录界面外）使用键盘的功能键进行各界面的切换，具体快捷键见上方详细说明",
						0};


	//总的页面背景

	cleardevice();
	setcolor(BLUE);
	rectangle(dx,dy,maxx-dx,maxy-dy);        //画出主要的大矩形


	//输出第三页的内容

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
  help_draw4(INFO *info)   画出第四页的内容
**********************************************************/
void help_draw4()
{
	 int dx=160;
	int dy=50;
	int r=12;
	int maxx=getmaxx();
	int maxy=getmaxy();

	char *page[]={"[1]","[2]","[3]","[4]",0};
	char *str3="退出";

	char *simplename[]={
						"3.本系统的特色功能：",
						"实时模拟：",
						"自选股板块：",
						"投资组合推荐：",
						0};
	char *introduction[]={
						"",
						"用户可以选择实时模拟时间，系统根据这个时间进行股价变动模拟",
						"用户可将特定股票加入自选股，将自动提交到自选股列表中，方便用户查看特定（常用）股票",
						"本系统使用量化投资组合中成长组合，价值组合，价值成长组合三个组合模型进行智能选股，并为用户提供股票详细信息",
						0};

	//总的页面背景
	cleardevice();
	setcolor(BLUE);
	rectangle(dx,dy,640-dx,480-dy);
	//输出第四页的内容

	puthz12(simplename[0],dx+12,dy+r+16,WHITE);

	puthz12(simplename[1],dx+18,dy+r+16+30,WHITE);
	putnews(introduction[1],dx+24+6,dy+r+16+30+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[2],dx+18,dy+r+16+30+(16*3+6),WHITE);
	putnews(introduction[2],dx+24+6,dy+r+16+30+(16*3+6)+16,WHITE,maxx-dx-r-12);

	puthz12(simplename[3],dx+18,dy+r+16+30+(16*3+6)+(16*3+6),WHITE);
	putnews(introduction[3],dx+24+6,dy+r+16+30+(16*3+6)+(16*3+6)+16,WHITE,maxx-dx-r-12);

  //	puthz12(simplename[4],dx+18,dy+r+16+30+(16*3+6)+(16*3+6)+(16*4+6),WHITE);
  //	putnews(introduction[4],dx+24+6,dy+r+16+30+(16*3+6)+(16*3+6)+(16*4+6)+16,WHITE,maxx-dx-r-12);
	
	
	//显示退出键
	setcolor(LIGHTRED);
	rectangle(maxx/2+129,dy+r+2,maxx/2+129+24+1,dy+r+2+12+2); 
	puthz12(str3,maxx/2+130,dy+r+3,LIGHTRED);   //显示退出
	//显示页码[1],[2],[3]
	//line(maxx/2,0,maxx/2,480);中线
	
	setcolor(LIGHTRED);
	outtextxy(maxx/2+42,maxy-dy-r-3-20+2,page[3]);
	
	setcolor(YELLOW);
	outtextxy(maxx/2-66,maxy-dy-r-3-20+2,page[0]);
	outtextxy(maxx/2-30,maxy-dy-r-3-20+2,page[1]);
	outtextxy(maxx/2+6,maxy-dy-r-3-20+2,page[2]);
}