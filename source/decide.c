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
Description：	投资决策界面相关函数

Function List：	decide_control			决策界面主函数
				

				deicde_choose_draw		画投资决策界面
				deicde_choose_anal

				decide_compare_draw		加入股票对比的股票进行对比
				decide_add				将目标股票加入分析篮中（同时进行数据导入计算）
				decide_delate			将目标股票从分析篮中删除（同时进行数据导入计算）

				make_chart				画条形统计图
				make_bar				*被封装

需要控制的值有：
**********************************************************/

/**********************************************************
decide主函数
	鼠标点击管理  点击进入对比界面
				  点击进入分析界面
				  点击删除对比股票
				  点击股票加入对比
				  点击选择投资风格
				  点击开始分析

**********************************************************/


void control_decide(INFO *info,STOINFO *stoinfo,int *mx,int *my,int *mbtn)
{
	if(info->layout==9)
	{
		if(mouse_press(5,470-17,5+53,470,mx,my,mbtn))		//点击进入股票对比界面
		{
			info->layout_last=info->layout;
			info->layout=8;
			layout_change(info,stoinfo);
			decide_compare_draw(stoinfo);
		}


		if(mouse_press(10,80,130,100,mx,my,mbtn))		//选择高受益型
		{
			stoinfo->style=0;
			decide_choose_draw_init();
		}
		if(mouse_press(10,130,130,150,mx,my,mbtn))		//选择低风险型
		{
			stoinfo->style=1;
			decide_choose_draw_init();
		}
		if(mouse_press(10,180,130,200,mx,my,mbtn))	//选择风险收益综合型
		{
			stoinfo->style=2;
			decide_choose_draw_init();
		}
		if(mouse_press(30,250,110,270,mx,my,mbtn))		//开始分析
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
		if(mouse_press(5,470-17,5+53,470,mx,my,mbtn))		//点击进入股票推荐界面
		{
			info->layout_last=info->layout;
			info->layout=9;
			layout_change(info,stoinfo);
			decide_choose_draw_init();
		}
		if(mouse_press(500,402,524,418,mx,my,mbtn))		//删比较股票列表第一个
		{
			decide_delate(stoinfo,stoinfo->choose[0]);
			decide_compare_draw(stoinfo);
		}
		if(mouse_press(500,422,524,438,mx,my,mbtn))		//删比较股票列表第二个
		{
			decide_delate(stoinfo,stoinfo->choose[1]);
			decide_compare_draw(stoinfo);

		}
		if(mouse_press(500,442,524,458,mx,my,mbtn))	//删比较股票列表第三个
		{
			decide_delate(stoinfo,stoinfo->choose[2]);
			decide_compare_draw(stoinfo);
		}
	}
}


 /**********************************************************
decide_choose_anal(STOINFO * stoinfo)
分析出优质股并打印
   调用grade_calculate计算三百支股票的三个得分
   找出相应风格下的最优质四只股票记录其代码至stoinfo_combine
   调用sheet_fill填表，将stoinfo极其分数传入
**********************************************************/

void deicde_choose_anal(STOINFO * stoinfo)            //control_decide传入投资风格
{
	FILE * fsymb;
	FILE * fscore;
	char address[35];
	char pointer[30]="data\\database\\";
	int score[300][3];                         //记录股票三种风格的评分
	char symbol[300][7];                       //记录股票代码
	int iround,jround;
	float data[15];                            //股票的15项指标
	
	int max1,max2,max3,max4;
	int maxj1,maxj2,maxj3,maxj4;
	int combine_score[4][3];		//组合的得分
	
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
			grade_calculate(score[iround],data);  //传入数据data，得到存入score[i]的三个得分
			
		}
		else 
		{
			break;
		}
		temp[0]='\0';
	}                        	
	fclose(fsymb);                                //调用grade_calculate计算各组合得分
	
	max1=max2=max3=max4=score[0][stoinfo->style];	
	maxj1=maxj2=maxj3=maxj4=0;					
	for(jround=0;jround<iround;jround++)
	{
		if(max1<score[jround][stoinfo->style])
		{		
			max4=max3;         //max1更新，各max的值依次向后移动	
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
	}                                        //找到前四只得分最高的股票，要求max1>max2>max3>max4
	
	strcpy(stoinfo->combine[0],symbol[maxj1]);
	strcpy(stoinfo->combine[1],symbol[maxj2]);
	strcpy(stoinfo->combine[2],symbol[maxj3]);
	strcpy(stoinfo->combine[3],symbol[maxj4]);      //将找到的前四名赋值给stoinfo->combine
	
	for(jround=0;jround<3;jround++)		
	{
		combine_score[0][jround]=score[maxj1][jround];
		combine_score[1][jround]=score[maxj2][jround];
		combine_score[2][jround]=score[maxj3][jround];
		combine_score[3][jround]=score[maxj4][jround];
	}                                                         //记录前四名组合的得分

	choose_sheet_fill(stoinfo,185,combine_score);
}

/**********************************************************
grade_calculate(int * grade,float * data)
由data【15】计算所传这只股票的三个分数，存入grade【3】
   
**********************************************************/	

void grade_calculate(int * grade,float * data)
{
	int kround;
	int score[15];
	float temp;
	int temp2;
	
	for(kround=0;kround<15;kround++)
	{
		if(fabs(data[kround])<1e-6)	//如果此项指数为0，则分数直接为0
		{
			score[kround]=0;
		}	
	}
		
	temp=data[0];					//指标1：NPG-TTM（成长因子）
	if(temp>5)
		score[0]=100;
	else if(temp<-5)
		score[0]=0;
	else
		score[0]=(int)((temp+5)*10);
		
	temp=data[1];					//指标2：OPG-TTM（成长因子）
	if(temp>5)
		score[1]=100;
	else if(temp<-1)
		score[1]=0;
	else
		score[1]=(int)((temp+1)/6*100);
		
	temp=data[2];					//指标3：OCFG-TTM（成长因子）
	if(temp>8)
		score[2]=100;
	else if(temp<-8)
		score[2]=0;
	else
		score[2]=(int)((temp+8)/16*100);
		
	temp=data[3];					//指标4：ROEG（成长因子）
	if(temp>2)
		score[3]=100;
	else if(temp<-2)
		score[3]=0;
	else
		score[3]=(int)((temp+2)/4*100);
		
	temp=data[4];					//指标5：ROAG（成长因子）
	if(temp>2)
		score[4]=100;
	else if(temp<-2)
		score[4]=0;
	else
		score[4]=(int)((temp+2)/4*100);
	
	temp=data[5];					//指标6：PE
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
	
	temp=data[6];					//指标7：PB
	if(temp>0&&temp<10)
		score[6]=100-(int)((temp)/10*70);
	else if(temp>15||temp<0)
		score[6]=0;
	else if(temp>10&&temp<15)
		score[6]=30-(int)((temp-10)/5*30);
	
	temp=data[7];					//指标8：PS
	if(temp>0&&temp<10)
		score[7]=100-(int)((temp)/10*75);
	else if(temp>25)
		score[7]=0;
	else if(temp>10&&temp<25)
		score[7]=25-(int)((temp-10)/15*25);

	temp=data[8];					//指标9：PCF
	if(temp>0&&temp<150)
		score[8]=100-(int)((temp)/150*100);
	else if(temp>150||temp<-20)
		score[8]=0;
	else if(temp>-20&&temp<0)
		score[8]=(int)((temp+20)/20*20);
	
	temp=data[9];					//指标10：PEG
	if(temp>0&&temp<500)
		score[9]=100-(int)((temp)/500*80);
	else if(temp>1000||temp<0)
		score[9]=0;
	else if(temp>500&&temp<1000)
		score[9]=20-(int)((temp-500)/500*20);

	temp=data[10];					//指标11：CTAR
	if(temp>0.8)
		score[10]=100;
	else if(temp<-0.5)
		score[10]=0;
	else if(temp>-0.5&&temp<0.8)
		score[10]=100-(int)((temp+0.5)/1.3*100);	
		
	temp=data[11];					//指标12：NPM
	if(temp>1000)
		score[11]=100;
	else if(temp<0)
		score[11]=0;
	else if(temp>0&&temp<1000)
		score[11]=(int)((temp)/1000*100);	
	
	temp=data[12];					//指标13：ROE（质量因子）
	if(temp>15)
		score[12]=100;
	else if(temp<0)
		score[12]=0;
	else if(temp>0&&temp<15)
		score[12]=(int)((temp)/15*100);	
	
	temp=data[13];					//指标14：ROA（质量因子）
	if(temp>8)
		score[13]=100;
	else if(temp<0)
		score[13]=0;
	else if(temp>0&&temp<8)
		score[13]=(int)((temp)/8*100);	
	
	temp=data[14];					//指标15：TAT
	if(temp>0.8)
		score[14]=100;
	else if(temp<0)
		score[14]=0;
	else if(temp>0&&temp<0.8)
		score[14]=(int)((temp)/0.8*100);	
	

		
	temp2=score[0]+score[1]+score[2]+score[3]+score[4];		//成长组合得分
	grade[0]=temp2*0.2;
		
	temp2=score[5]+score[6]+score[7]+score[8]+score[9];		//价值组合得分
	grade[1]=temp2*0.2;
		
	temp2=score[0]*6.5+score[1]*6.5+score[2]*6.5;							//价值成长组合得分
	temp2=temp2+score[3]*7+score[4]*7+score[5]*6.5;
	temp2=temp2+score[6]*7+score[7]*7+score[8]*7;
	temp2=temp2+score[9]*6.5+score[10]*6.5+score[11]*6.5;
	temp2=temp2+score[12]*6.5+score[13]*6.5+score[14]*6.5;
	grade[2]=(int)(temp2*0.01);
	
}

/**********************************************************
choose_sheet_fill(stoinfo,x,y,combine_score[4][3])
优质股票信息填表
  打印每只名称代码得分
  由每只股票的三个分数选择建议填入
   
**********************************************************/	

void choose_sheet_fill(STOINFO * stoinfo,int y,int combine_score[4][3])
{
	int iround;
	char name[10];
	char temp[10];
	char num[10];
	char other[10];
	int flag1,flag2,flag3;		//记录各个股得分的评价

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
		puthz12(name,203,y+10,YELLOW);				//打印出名字

		setcolor(YELLOW);
		outtextxy(260,y+10,stoinfo->combine[iround]);	//打印出代码

		setcolor(WHITE);
		itoa(combine_score[iround][stoinfo->style],temp,10);
		outtextxy(324,y+10,temp);						//打印出得分


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


		if((flag1+flag2+flag3)==3||			//组合得分为1,1,1
				(flag1+flag2+flag3)==4)		//或者组合得分为1,1,2(2任意位置)
		{
			puthz12("股票各指标均较差，建议减持",350,y+10,WHITE);
		}
		else if((flag1+flag2+flag3==5&&flag1!=3&&flag1!=3&&flag1!=3)	//组合得分为1,2,2(1任意位置)
				||(flag1==2&&flag1==2&&flag1==2))	//或者组合得分为2,2,2
		{
			puthz12("股票各指标表现平庸，保留减仓建议",350,y+10,WHITE);
		}
		else if(flag1==3&&(flag1+flag2+flag3)==5)	//组合得分为3,1,1
		{
			puthz12("股票弱项明显，成长组合平庸，保留减仓建议",350,y+10,WHITE);
		}
		else if(flag2==3&&(flag1+flag2+flag3)==5)	//组合得分为1,3,1
		{
			puthz12("股票弱项明显，价值组合平庸，保留减仓建议",350,y+10,WHITE);
		}
		else if(flag3==3&&(flag1+flag2+flag3)==5)	//组合得分为1,1,3
		{
			puthz12("股票弱项明显，价值成长组合平庸，保留减仓建议",350,y+10,WHITE);
		}
		else if(flag1==3&&(flag1+flag2+flag3)==6)	//组合得分为3,(2,1/1,2)
		{
			puthz12("股票弱项明显，成长组合平庸，建议保持或减仓",350,y+10,WHITE);
		}
		else if(flag2==3&&(flag1+flag2+flag3)==6)	//组合得分为(2/1),3,(1/2)
		{
			puthz12("股票弱项明显，价值组合平庸，建议保持或减仓",350,y+10,WHITE);
		}
		else if(flag3==3&&(flag1+flag2+flag3)==6)	//组合得分为(2,1/1,2),3
		{
			puthz12("股票弱项明显，价值成长组合平庸，建议保持或减仓",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==2&&flag3==2)		//组合得分为3,2,2
		{
			puthz12("股票表现良好，高于平均水平，保留增持建议",350,y+10,WHITE);
		}
		else if(flag1==2&&flag2==3&&flag3==2)		//组合得分为2,3,2
		{
			puthz12("股票表现良好，高于平均水平，保留增持建议",350,y+10,WHITE);
		}
		else if(flag1==2&&flag2==2&&flag3==3)		//组合得分为2,2,3
		{
			puthz12("股票表现良好，高于平均水平，保留增持建议",350,y+10,WHITE);
		}
		else if(flag1==1&&flag2==3&&flag3==3)		//组合得分为1,3,3
		{
			puthz12("股票有明显弱项，成长组合得分较低，保留增持建议",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==1&&flag3==3)		//组合得分为3,1,3
		{
			puthz12("股票有明显弱项，价值组合得分较低，保留增持建议",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==3&&flag3==1)		//组合得分为3,3,1
		{
			puthz12("股票有明显弱项，价值成长组合得分较低，保留增持建议",350,y+10,WHITE);
		}
		else if(flag1==2&&flag2==3&&flag3==3)		//组合得分为2,3,3
		{
			puthz12("股票表现优秀，除成长组合外得分均较高，建议增持",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==2&&flag3==3)		//组合得分为3,2,3
		{
			puthz12("股票表现优秀，除价值组合外得分均较高，建议增持",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==3&&flag3==2)		//组合得分为3,3,2
		{
			puthz12("股票表现优秀，除价值成长组合外得分均较高，建议增持",350,y+10,WHITE);
		}
		else if(flag1==3&&flag2==3&&flag3==3)		//组合得分为3,3,3
		{
			puthz12("股票综合表现优秀，各组合得分均较高，建议增持",350,y+10,WHITE);
		}
		y+=35*3;
	}
}


/**********************************************************
decide_compare_draw(STOINFO * stoinfo)
绘制对比界面
  清除屏幕
  生成主菜单
  调用grade_loading计算对比的几个股票的分数
  调用compare_sheet填对比表
  调用compare_bar1绘制柱状图
  调用compare_line绘制折线图
**********************************************************/

void decide_compare_draw(STOINFO * stoinfo)   //绘制对比界面
{
	int grade[3][3];
	char name[3][10];

	cleardevice();
	menu_create();

	grade_loading(stoinfo,grade,name);

	setcolor(WHITE);
	rectangle(5,470-17,5+53,470);
	puthz12("股票推荐",5+3,480-10-15,RED);         //返回分析界面按钮

	compare_sheet(grade,name);
	compare_bar1(grade,name);
	compare_line(stoinfo,name);
}

/**********************************************************
grade_loading(STOINFO * stoinfo,int grade[3][3],char name[3][10])
对比股票数据生成
   根据stoinfo所记代码打开文件，记录名称，15个数据
   调用grade_calculate计算这几个股票的三个得分记入grade

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

		if((fp=fopen(address,"rb"))==NULL)		//读取股票15个财务数据
	
		{
		    printf("grade_loading: error opening decide.txt(out)\n");
		    getch();
	    }
		for(kround=0;kround<15;kround++)
		{
			fread(&data[iround][kround],sizeof(float),1,fp);
		}
		fclose(fp);

		strcpy(address,pointer);				//读取股票简称
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
加入股票对比函数
  判断所选股票是否已经加入
  若有空位则将该支股票加入对比（股票代码存入stoinfo）
  若对比股票已满，显示该信息
**********************************************************/


void decide_add(STOINFO * stoinfo,char * str)
{
	int tround;

	for(tround=0;tround<3;tround++)
	{
		if(strcmp(str,stoinfo->choose[tround])==0)	//已添加过此股票
		{
			break;
		}
		if(stoinfo->choose[tround][0]=='k')
		{
			strcpy(stoinfo->choose[tround],str);
			break;
		}
	}
	if(tround==3)		//对比列表满了，没有加入
	{
		//save_picture(320-100,240-60,320+100,240+60);

		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		bar(320-100,240-60,320+100,240+60);
		puthz16("列表已满",320-32,240-18,16,1,1,BLACK);

		delay(1000);
		//put_picture(320-100,240-60,320+100,240+60);
		decide_compare_draw(stoinfo);

	}

}



/**********************************************************
decide_delate(STOINFO * stoinfo,char * str)
股票对比删除函数
  判断所选股票是对比列表的第几个
  若非第三个则需做股票移动（改变stoinfo）
**********************************************************/	

void decide_delate(STOINFO * stoinfo,char * str)
{
	int iround,kround;
	int flag=0;
	
	for(iround=0;iround<3;iround++)
	{
		if(strcmp(str,stoinfo->choose[iround])==0)	//判断是不是要删除的股票
		{
			flag=1;
			
			if(iround!=2)
			{
				for(kround=iround+1;kround<3;kround++)	//所有后面的股票前移
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
	
	if(flag==0)		//没找到要删除的股票代码
	{
		
	}
		
}


/**********************************************************
decide_choose_draw_init() 
绘制分析界面函数
  清除屏幕
  生成主菜单
  绘制所有按钮及表格
**********************************************************/	


void decide_choose_draw_init()      //绘制分析界面
{
	int i;
	cleardevice();
	menu_create();

	setcolor(WHITE);
	rectangle(5,470-17,5+53,470);
	puthz12("股票对比",5+3,480-10-15,RED);         //返回对比界面按钮
	
	
	for(i=0;i<12;i++)                     
	 line(200,30+35*i,200+430,30+35*i);
    i=0;
	do
	{
       line(200,30+35*i,200,30+35*(i+2));
	   line(200+430,30+35*i,200+430,30+35*(i+2));
       i+=3;
	}while(i<10);                                           //表格绘制完成
    
	setfillstyle(SOLID_FILL,WHITE);
	puthz16("投资风格选择",20,40,16,1,1,RED);
	bar3d(10,80,10+120,80+20,0,0);
	puthz16("高收益型",38,82,16,1,1,RED);
	bar3d(10,130,10+120,130+20,0,0);
	puthz16("低风险型",38,132,16,1,1,RED);
	bar3d(10,180,10+120,180+20,0,0);
	puthz16("风险收益综合型",15,182,16,1,1,RED);
	bar3d(30,250,110,250+20,0,0);
	puthz16("开始分析",40,252,16,1,1,RED);            //投资风格按钮绘制
	
	setcolor(LIGHTRED);
	line(200+400-30,30+35*2+25,200+400,30+35*2+25);
	puthz12("详情",600-25,30+35*2+12,LIGHTRED);
	line(200+400-30,30+35*5+25,200+400,30+35*5+25);
	puthz12("详情",600-25,30+35*5+12,LIGHTRED);
	line(200+400-30,30+35*8+25,200+400,30+35*8+25);
	puthz12("详情",600-25,30+35*8+12,LIGHTRED);
	line(200+400-30,30+35*11+25,200+400,30+35*11+25);
	puthz12("详情",600-25,30+35*11+12,LIGHTRED);

	setcolor(BLUE);
	line(200+400-110,30+35*2+25,200+400-80,30+35*2+25);
	puthz12("交易",600-105,30+35*2+12,BLUE);
	line(200+400-110,30+35*5+25,200+400-80,30+35*5+25);
	puthz12("交易",600-105,30+35*5+12,BLUE);
	line(200+400-110,30+35*8+25,200+400-80,30+35*8+25);
	puthz12("交易",600-105,30+35*8+12,BLUE);
	line(200+400-110,30+35*11+25,200+400-80,30+35*11+25);
	puthz12("交易",600-105,30+35*11+12,BLUE);

	setcolor(RED);
	line(200+400-70,30+35*2+25,200+400-40,30+35*2+25);
	puthz12("对比",600-65,30+35*2+12,RED);
	line(200+400-70,30+35*5+25,200+400-40,30+35*5+25);
	puthz12("对比",600-65,30+35*5+12,RED);
	line(200+400-70,30+35*8+25,200+400-40,30+35*8+25);
	puthz12("对比",600-65,30+35*8+12,RED);
	line(200+400-70,30+35*11+25,200+400-40,30+35*11+25);
	puthz12("对比",600-65,30+35*11+12,RED);
	 
    puthz12("名称",212,355,YELLOW);
	puthz12("代码",273,355,YELLOW);
	puthz12("组合得分",310,355,YELLOW);
	puthz12("评价",480,355,YELLOW);

	puthz12("名称",212,250,YELLOW);
	puthz12("代码",273,250,YELLOW);
	puthz12("组合得分",310,250,YELLOW);
	puthz12("评价",480,250,YELLOW);

	puthz12("名称",212,145,YELLOW);
	puthz12("代码",273,145,YELLOW);
	puthz12("组合得分",310,145,YELLOW);
	puthz12("评价",480,145,YELLOW);

	puthz12("名称",212,40,YELLOW);
	puthz12("代码",273,40,YELLOW);
	puthz12("组合得分",310,40,YELLOW);
	puthz12("评价",480,40,YELLOW);

    
}



	/*line(200,30,200,30+35*2);
	line(200,30+35*3,200,30+35*5);
	line(200,30+35*6,200,30+35*8);
	line(200,30+35*9,200,30+35*11);
	line(200+405,30,200+405,30+35*2);
	line(200+405,30+35*3,200+405,30+35*5);
	line(200+405,30+35*6,200+405,30+35*8);
	line(200+405,30+35*9,200+405,30+35*11);             //分析界面表格竖线，表格完成      */

/**********************************************************
compare_sheet(int grade[3][3],char name[3][10])
绘制对比表格函数
  绘制表格，写表头
  将股票名称得分建议填入表格，绘制删除按钮
**********************************************************/	
	
void compare_sheet(int grade[3][3],char name[3][10])		
{	
    int iround;
	int xp,yp,width,num;
	int k=20,h=10;						//k,h为数据的长度(高度)
	char str[5];
	int average;

	width=(12*4+24)*4+(12*6+24)+48;			//删除按钮长宽确定
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

	puthz12("成长组合",104+72+72/2-12*2,380+20/2-12/2,YELLOW);
	puthz12("价值组合",104+72*2+72/2-12*2,380+20/2-12/2,YELLOW);
	puthz12("成长价值组合",104+72*3+96/2-12*3,380+20/2-12/2,YELLOW);
	puthz12("建议",104+72*3+96+72/2-12,380+20/2-12/2,YELLOW);    	//对比界面表格绘制完成
		
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,WHITE);

	for(iround=0;iround<3;iround++)
	{
		setcolor(WHITE);
		if(grade[iround][0]!=-1)
		{
			puthz12(name[iround],(640-width)/2+72/2-12*2,380+20*(iround+1)+20/2-12/2,WHITE);		//输出名字
			
			itoa(grade[iround][0],str,10);	 					//grade[iround]中的数据转化为字符串
			outtextxy((640-width)/2+72+72/2-k/2,380+20*(iround+1)+10-h/2,str);		//输出成长组合得分

			itoa(grade[iround][1],str,10);	   
			outtextxy((640-width)/2+72*2+72/2-k/2,380+20*(iround+1)+10-h/2,str);   //输出价值组合得分

			itoa(grade[iround][2],str,10);	  
			outtextxy((640-width)/2+72*3+96/2-k/2,380+20*(iround+1)+10-h/2,str);  	//输出价值成长组合得分
			
			average=(grade[iround][0]+grade[iround][1]+grade[iround][2])/3;//输出系统推荐
			
			if(average<25)
			{
				puthz12("建议减持",(640-width)/2+72*3+96+72/2-12*2,380+20*(iround+1)+10-h/2,WHITE);
			}
			else if(average>45)
			{
				puthz12("建议增持",(640-width)/2+72*3+96+72/2-12*2,380+20*(iround+1)+10-h/2,WHITE);
			}
			else
			{
				puthz12("建议观望",(640-width)/2+72*3+96+72/2-12*2,380+20*(iround+1)+10-h/2,WHITE);
			}
			
			xp=(640-width)/2+72*3+96+72+48/2;		//计算按钮位置
			yp=380+20*(iround+2)-20/2;
			
			bar3d(xp-25/2,yp-16/2,xp+25/2,yp+16/2,0,0);	//画删除按钮
			
			puthz12("删除",xp-12/2*num,yp-12/2,BLACK);
			
		}
		else
		{
			break;
		}
		
	}
		
} 

/**********************************************************
compare_bar1(int grade[3][3], char name[3][10])
绘制柱状图函数
  计算对比股票数目
  将grade中数据存入data【9】
  找出data数组的最大值
  计算每个柱子高度
  绘制柱子，打印名字
  
**********************************************************/	
	

void compare_bar1(int grade[3][3], char name[3][10])							//画左上角条形统计图
{	

	int x,y;								//x,y条形统计图原点位置
	int maxx,maxy;							//maxx,maxy条形统计图x，y轴长度
	int iround,jround,k;
	unsigned int color[3]={RED,YELLOW,LIGHTRED};		//自定义一个颜色数组
	char temp[5];
	int data[9];							//将二维数组转化为一维数组
	int bar_high[9]={0};					//每个柱子的高度（像素值）
	int bar_width;							//每个柱子的宽度（像素值）
	
	int bar_num;
	int x_num;
	int max;								//数值最大的柱子的值（不是像素点最高）
	maxx=275;
	maxy=285;
	x=5;
	y=350;
	bar_width=22;

	for(bar_num=0;bar_num<3;bar_num++)		//找到对比列表中有多少股票
	{
		if(grade[bar_num][0]==-1)
		{
			break;
		}
	}

	setcolor(WHITE);
	line(x,y,x+maxx,y);
	line(x,y,x,y-maxy);
	setcolor(WHITE);        //设置边框颜色为白色
	puthz12("各组合得分情况",x+maxx/2-3*12-3,y-maxy-48,WHITE);

	setfillstyle(SOLID_FILL,RED);
	bar3d(x+5,y-maxy-30,x+5+30,y-maxy-30+12,0,0);
	puthz12("成长组合",x+5+30+6,y-maxy-30,WHITE);

	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(x+5+30+60,y-maxy-30,x+5+30+60+30,y-maxy-30+12,0,0);
	puthz12("价值组合",x+5+30+60+30+6,y-maxy-30,WHITE);

	setfillstyle(SOLID_FILL,LIGHTRED);
	bar3d(x+5+(30+60)*2,y-maxy-30,x+5+(30+60)*2+30,y-maxy-30+12,0,0);
	puthz12("成长价值组合",x+5+(30+60)*2+30+6,y-maxy-30,WHITE);  	//柱状图空表绘制完成

	jround=0;
	for(iround=0;iround<bar_num;iround++)	//把传入的二维数组转化为一维数组bar_high
	{
		data[jround++]=grade[iround][0];
		data[jround++]=grade[iround][1];
		data[jround++]=grade[iround][2];

	}

	max=data[0];							//找出a数组中的最大值
	for(iround=1;iround<bar_num*3;iround++)
	{
		if(max<data[iround])
			 max=data[iround];
	}

	for(iround=0;iround<bar_num*3;iround++)	//求出每个柱子的高度（像素值）
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
				setfillstyle(SOLID_FILL,color[jround]) ;		/*设置条形图填充颜色*/
				bar3d(x+bar_width*x_num,y-bar_high[jround+3*iround],x+bar_width*(x_num+1),y,0,0);	  /*heng表示从左往右数的第几个宽*/
				setcolor(WHITE);			   /*输出数据的颜色*/
				gcvt(data[jround+3*iround],3,temp);		  /*把a数组中的浮点数数据转化为字符串*/
				outtextxy(x+bar_width*x_num+4,y-bar_high[jround+3*iround]-15,temp);	/*输出数据*/
				x_num++;
			}
			x_num+=1;		 //每三个条形图为一大块，中间再空一个宽
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
				setfillstyle(SOLID_FILL,color[jround]) ;		/*设置条形图填充颜色*/
				bar3d(x+bar_width*x_num,y-bar_high[jround+3*iround],x+bar_width*(x_num+1),y,0,0);	  /*heng表示从左往右数的第几个宽*/
				setcolor(WHITE);			   /*输出数据的颜色*/
				gcvt(data[jround+3*iround],3,temp);		  /*把a数组中的浮点数数据转化为字符串*/
				outtextxy(x+bar_width*x_num+4,y-bar_high[jround+3*iround]-15,temp);	/*输出数据*/
				x_num++;
			}
		x_num+=2;		 //每三个条形图为一大块，中间再空两个宽
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
				setfillstyle(SOLID_FILL,color[jround]) ;		/*设置条形图填充颜色*/
				bar3d(x+bar_width*x_num,y-bar_high[jround+3*iround],x+bar_width*(x_num+1),y,0,0);	  /*heng表示从左往右数的第几个宽*/
				setcolor(WHITE);			   /*输出数据的颜色*/
				gcvt(data[jround+3*iround],3,temp);		  /*把a数组中的浮点数数据转化为字符串*/
				outtextxy(x+bar_width*x_num+4,y-bar_high[jround+3*iround]-15,temp);	/*输出数据*/
				x_num++;
			}
		}

	}

}

/**********************************************************
compare_line(stoinfo, char name[3][10])
绘制折线图函数
  将stoinfo中代码打开文件读取存入data【3】【5】
  找出data数组的最大值
  计算每个数据高度，并存入yplace【3】【5】
  绘制折线图，打印名字
  绘制图例，坐标轴

**********************************************************/

void compare_line(STOINFO * stoinfo,char name[3][10])									//画右上角折线统计图
{

	int x,y;								//x,y条形统计图原点位置
	int maxx,maxy;							//maxx,maxy条形统计图x，y轴长度
	int num=0;
	int iround,jround,kround;
	FILE * fp;
	char pointer[]="data\\database\\";
	char filename[35];
	float data[3][5];						//储存15个数据
	int yplace[3][5];						//9个数据的y坐标（像素点坐标）
	float ymax,ymin,ywidth;
	int temp;                //纵坐标的间隔
	char str[6];
	unsigned int color[3]={RED,YELLOW,LIGHTRED};//自定义一个颜色数组

	maxx=265;
	maxy=285;
	x=360;
	y=350;
  //	puthz12("近5个月股票走势",370,25,WHITE);
	setcolor(WHITE);
	line(x,y,x+maxx,y);
	line(x,y,x,y-maxy);
	puthz12("5月",x+10+maxx*1/6,y+2,WHITE);
	puthz12("6月",x+10+maxx*2/6,y+2,WHITE);
	puthz12("7月",x+10+maxx*3/6,y+2,WHITE);
	puthz12("8月",x+10+maxx*4/6,y+2,WHITE);
	puthz12("9月",x+10+maxx*5/6,y+2,WHITE);
	//主标题
	puthz12("近5个月股票走势",x+maxx/2-4*12,y-maxy-48,WHITE);
																 //折线图背景绘制
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
			break;				//留下iround数据
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
				yplace[jround][kround]=(int)(y-((data[jround][kround]-ymin)/ywidth*maxy*0.9))-10;  //整体往上移10像素
			}
		}

		for(jround=0;jround<iround;jround++)
		{
			setcolor(color[jround]);
			setfillstyle(SOLID_FILL,color[jround]);
			//图例部分
			pieslice(x-20+96*jround,y-maxy-24,0,360,2);
			line(x-20+96*jround,y-maxy-24,x-20+96*jround+30,y-maxy-24);
			pieslice(x-20+96*jround+30,y-maxy-24,0,360,2);
			puthz12(name[jround],x-20+96*jround+30+6,y-maxy-24-6,WHITE);
			//折线图部分
			setcolor(color[jround]);
			setfillstyle(SOLID_FILL,color[jround]);          //再写一遍是为了防止上一步输出汉字时夹杂着字母重新setcolor
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

		//纵坐标
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
		//横坐标
		puthz12("5月",x+10+maxx*1/6,y+2,WHITE);
		puthz12("6月",x+10+maxx*2/6,y+2,WHITE);
		puthz12("7月",x+10+maxx*3/6,y+2,WHITE);
		puthz12("8月",x+10+maxx*4/6,y+2,WHITE);
		puthz12("9月",x+10+maxx*5/6,y+2,WHITE);
	}
}

