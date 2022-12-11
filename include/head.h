#ifndef _head_h_
#define _head_h_

#include<string.h> 
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<bios.h>
#include<dos.h>
#include<conio.h>
#include<process.h>
#include<bios.h>
#include<fcntl.h>
#include<io.h>
#include<math.h>

#include<ctype.h>
#include<graphics.h>
#include<alloc.h>
#include<string.h>
#include<mem.h>

union KEY
{
	int num;
	char ch;
};

//layout界面：0为空界面，1为登陆界面，2为主界面，3为上证界面，4为深成界面，
//5为自选界面，6为股票折线界面，7为交易界面，8为股票对比，9为投资风格界面，10为帮助界面,11为股票财务界面
typedef struct
{
	char account[10];		  		//登陆的账号
	short int account_flag;			//登陆则为1，否则为0
	short int login_flag;			//第一次进入登陆界面为1，否则为0
	char search[7];					//记录需要搜索的股票代码
	int search_flag;				//搜索是否成功 1为成功，0为不成功
	short int tool;					//0全功能关闭，1开启滚动字幕，2开启实时模拟，3全开启
	int deal_flag;
	int time;
	float deal_price;
	float deal_quantum;
	union KEY key;					//键盘键入值
	short int layout;				//目前的界面
	short int layout_last;			//之前的界面
	short int menu_flag;			//标记下拉的子菜单（main中要初始化）
	int flag;
}INFO;

typedef struct				  //每只股票的基本信息
{
	int number;               //股票序号
	char identifer[7];        //股票代码
	char name[10];            //股票名称
	float sta[9];             //股票的基本数据信息
}Stockdata;			

typedef struct				   //股票列表队结构
{
	Stockdata * base;
	int front;				   //front端为屏幕上端，rear端为屏幕下端
	int rear;				   //front指向上端元素的地址，rear指向下端元素的地址
	int flag;
}Linkstock;


typedef struct
{
	char stockpress[7];				//鼠标点击的股票编码（1-300）
	char stockname[9];
	char choose[3][7];				//选择进行对比的股票（最多三只），若某项为空，则首元素赋为k
	int size;						//控制股票折线大小
	int pointer;					//控制股票折线位置
	int style;						//投资风格选择（0为成长，1为价值，2为成长价值）
	char buystock[7];
	char combine[5][7];				//得分靠前的组合
	short int listline;				//划线的股票
	int sort;						//选择的排序
									//0表示按代码正序，1现价降序，2现价升序，3涨跌幅降序，4涨跌幅升序，5换手率降序，6换手率升序，7振幅降幅，8振幅升序
	int number;						//目前K线图正在展示的是哪一只股票		
	int number_;					//控制拖动条中第一支股票是第多少只股票
	char stockpress_[7];			//目前拖动条显示的第一支股票
	int stock_day_num;				//股票一共有多少天的数据
}STOINFO;

typedef struct
{
	unsigned long date[195];
	float begin[195];
	float stop[195];
	float zuigao[195];
	float zuidi[195];
	float sum_amount[195];
	float sum_money[195];
}STOCK;

#endif
