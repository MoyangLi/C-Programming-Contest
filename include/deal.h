#ifndef _DEAL_h_
#define _DEAL_h_

#include "mouse.h"
#include "head.h"
#include "login.h"
#include "newmenu.h"
#include "newcon.h"
#include "CHINESE.h"
#include "time.h"
#include "trade.h"
#include "tradere.h"
void put_point(char str[16][20],int x,int y);
void deal_draw(void);
void draw_recharge(void);
void deal(INFO *info,int *,int *,int *);
void deal_press(int mx,int my,int mbuttn,Own *own,struct tm timpe_p,Hold *hold,int length);
void get_pre_price(Own *own,struct tm time_p,Hold *hold,int length);
void new_price(Own *own,struct tm time_p);
void page1_draw(void);
void page2_draw(int my);
void page3_draw(void);
void page4_draw(void);
void page5_draw(void);
void page6_draw(void);
void page7_draw(void);
void excel_1(void);
void excel_2(void);
void draw_tri(int x,int y);
void page_draw(int flag);
void get_time(struct tm *time_p,int *second);
void change_own(Own *own,int mx,int my,int mbuttn);
void signal_pos(int x,int color);
void signal_all(int x,int color);
void get_data_length(Own *own,int *length);
Delegate *init_delegate(Own own,Delegate *phead);
Hold *init_hold(Own own,Hold *phead);
Balance *init_balance(Own own,Balance *phead);
Deal *init_deal(Own own,Deal *phead);
void init_own(Own *own);
void input_deal(Own *own,struct tm time_p,Hold *hold,int length);
void show_deal_(int flag,Own *own,struct tm time_p,Delegate *delegate,Hold *hold,Balance *balance,Deal *deal,int *length,int page_pointer);
void show_data_1(Own *own);	//显示买入卖出界面数据
void page_judge(int *flag_last,int *flag,int mx,int my,int mbuttn);
void page_judge_1(int *flag_last,int *flag,int mx,int my,int mbuttn);
void page_judge_2(int *flag_last,int *flag,int mx,int my,int mbuttn);
void page_judge_3(int *flag_last,int *flag,int mx,int my,int mbuttn);
#endif