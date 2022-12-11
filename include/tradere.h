#ifndef _tradereal_h_
#define _tradereal_h_
#include "stdio.h"
typedef struct own
{
	char account[8];
	char stockname[9];
	char stockcode[7];
	float stock_now_price;	//股票现价
	float stock_pre_price;
	long num_max;			//最大可买数量
	double balance[5];		//1可用金额,2资金余额,3冻结余额,4证券市值,5总资产
	float price_own;		//自己选择价格
	long num_own;			//自己选择数量
	int flag;				//仅仅用于判断处于买入、卖出还是委托买入、卖出
	float stock_zuoshou;	//昨日收盘价
	float zhangfu;			//涨幅
}Own;
typedef struct delegate_node
{
	char stockname[9];
	char stockcode[7];
	long dele_amount;
	float dele_price;
	long date;
	int time;
	int flag;				//flag为0：买入，1：卖出
	int flag_;				//0为未成交，1为已经成交
	int delet_flag;			//0为未删除，1为删除
	struct delegate_node *next;
	struct delegate_node *pre;
}Delegate;	//委托
typedef struct hold_node
{
	char stockname[9];
	char stockcode[7];
	long stock_amount;		//证券余额
	long amount_avail;		//可用余额
	long amount_blocked;	//冻结数量
	long amount_real;		//股票实际
	float deal_price;		//成本价
	float now_price;    	//市价
	double hold_spend;		//总花费
	double market_value;	//市值
	float profit_loss_;		//浮动盈亏
	float profit_loss_percent;//盈亏比例
	float position;			//仓位
	struct hold_node *next;
	struct hold_node *pre;
}Hold;		//持仓

typedef struct balance_node
{
	long deal_date;			//成日期
	int deal_time;			//成交时间
	char stockname[9];
	char stockcode[7];
	int flag;				//flag为0：买入，1：卖出
	int flag_point; 		//判断该笔交易是否在一天前完成的，如果在一天内完成的则为冻结股票,flag为0，否则flag为1
	long deal_amount;
	float deal_price_ave;	//成交均价
	double deal_money;		//成交金额
	double deal_money_real;	//发生金额
	float service_charge;	//手续费
	float stamp_tax;		//印花税
	double balance_now;		//本次金额
	
	struct balance_node *next;
	struct balance_node *pre;
}Balance;	//余额流水查询

typedef struct deal_node
{
	long deal_date;			//成交日期
	int deal_time;			//成交时间
	char stockname[9];
	char stockcode[7];
	int flag;				//flag为0：买入，1：卖出
	long deal_amount;		//成交数量
	float deal_price_ave;	//成交均价
	double deal_money;		//成交金额
	struct deal_node *next;
	struct deal_node *pre;
}Deal;		//成交

typedef struct mySTOCK
{
	char stockcode[7];
	char stockname[9];
	float price;
	float percent;
	struct mySTOCK *next;
	struct mySTOCK *pre;
}mySTOCK;
#endif