#ifndef _trade_h_
#define _trade_h_
#include "time.h"
#include "tradere.h"
#include "deal.h"
#include "input.h"
Delegate *add_dalegate(Own *own,Delegate *phead,struct tm time_p,int *length,Hold *hold);
Hold *find_hold(Hold *hold,int length,char stockcode[7]);
void write_delegate(Own *own,Delegate *phead,int length);
//Delegate *del_dalegate(Delegate *phead,int del_num,int length);
Delegate *delet_pre_delegate(Own *own,Delegate *phead,struct tm time_p,int *length);
void show_delegate_data(Delegate *phead,int length,int page_pointer);
void show_recall_data(Delegate *phead,int length,int page_pointer);
void show_his_deal(Deal *phead,int length,int page_pointer);
void show_tod_deal(Deal *phead,int length,int page_pointer,struct tm time_p);
void show_balance_data(Own *own,Balance *phead,int length,int page_pointer);
void show_hold_data(Hold *phead,int length,int page_pointer);
void recall_num(int my,int *flag_delet,int length,int page_pointer);
void delet_delegate(Own *own,int *flag_delet,Delegate *phead,int *length,int page_pointer,Hold *hold);

void free_all(Delegate *phead_1,Hold *phead_2,Balance *phead_3,Deal *phead_4,int *length);
void free_delegate(Delegate *phead,int length);
void free_hold(Hold *phead,int length);
void free_balance(Balance *phead,int length);
void free_deal(Deal *phead,int length);

void get_recall_num(Delegate *phead,int length_all,int *length_recall);
void get_today_deal(Deal *phead,int length_all,int *length_today,struct tm time_p);
void page_up_down(INFO *info,Own *own,int flag,struct tm time_p,int *page_pointer,int *all_length,Delegate *phead_1,Hold *phead_2,Balance *phead_3,Deal *phead_4);

void rewrite_own(Own *own);
void renew_own(Own *own,Hold *hold,int length);
void rewrite_balance(Own *own,Balance *phead,int length);
void rewrite_hold(Own *own,Hold *phead,int length);
void rewrite_deal(Own *own,Deal *phead,int length);
//Deal *add_deal(Own *own,Delegate *phead_1,Hold *phead_2,Balance *phead_3,Deal *phead_4,int *length,struct tm time_p);
Balance *balance_new_add(Own *own,Delegate *delegate,Balance *phead,int time_temp,int *length,Hold *hold);
Deal *deal_new_add(Own *own,Deal *phead,Balance *pnode,int *length,int length_pre);
Hold *delet_hold(int *length,Hold *hold);
Hold *hold_new_add(Own *own,Balance *pnode,Hold *phead,int *length,struct tm time_p,int length_pre);
int judge_deal(Delegate *pnode,struct tm time_p,int *time);
float get_now_price(char str[7],struct tm time_p);
Balance *test_balance(Own *own,Delegate *delegate,Balance *phead,Hold *hold,struct tm time_p,int *length);
void recharge(Own *own,int *flag,int *flag_last);
int judge_rech(char *password,char *rech_amount,Own *own);
#endif