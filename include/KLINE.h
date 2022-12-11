#ifndef _KLINE_h_
#define _KLINE_h_
#include "decide.h"
#include "head.h"
#include "detail.h"
#include "tool.h"
#include "newmenu.h"
#include "login.h"
#include "input.h"
#include "line.h"
#include "stock.h"
#include "mystock.h"

void control_line(INFO * info,STOINFO * stoinfo,Linkstock *Q1,int *mx_,int *my_,int *mbutn_);
void Kline_draw_bk(void);
void dot_line(int x,int y1,int y2);
void draw_slidder(void);
void move_slidder_1(int *mx,int *my,int *mbuttn,STOINFO *stoinfo);
void move_slidder_2(STOINFO *stoinfo);
void data_get(STOCK *stock,STOINFO * stoinfo,int signal);
void data_get_min(STOCK *stock,STOINFO * stoinfo);
void trend_draw(STOINFO *stoinfo,STOCK *stock,int signal,int num);
void find_max_min(float *n,float *max,float *min,int length);
void find_min(float *n,float *min,int length);
void find_max(float *n,float *max,int length);
void trend_init(STOCK *stock,STOINFO *stoinfo,float ymax,float ymin,int signal,int num);
void day_calculate(float *n1,float *day,int length);
void trend_draw_graph(STOCK *stock,STOINFO *stoinfo,float ymin,float ymax,int signal,int num);
void trend_draw_ave(STOINFO *stoinfo,float ymin,float ymax,float *day,int signal,int num);
void draw(STOCK *stock,float *n,int length,float *data1,float *data2,int signal,int num);
void draw_data(int length,STOCK *stock,float ymin,float ymax,float *sum,int signal,int num);
void draw_ave(int length,float ymin,float ymax,float *day,int signal,int num);
void show_new(STOINFO *stoinfo);
void press_up(STOINFO * stoinfo);
void press_down(STOINFO * stoinfo);
void press_right(STOINFO * stoinfo);
void press_left(STOINFO * stoinfo);
void day_num_stock(STOINFO *stoinfo);
void trend_change(INFO *info,STOINFO *stoinfo,int *mx_,int *my_,int *mbutn_);
void stock_diff(INFO *info,STOINFO *stoinfo,STOCK *stock,float *day5,float *day10,float *day20,float *day60,float *data1,float *data2,float *data3,int index);
void data_new(STOCK *stock,int day,float *day5,float *day10,float *day20,float *day60);
void find_stockpress(STOINFO *stoinfo);
void showstock(STOINFO *stoinfo);
void change_index(int index,STOCK *stock,int length,float *data1,float *data2,float *data3);
void show_index(int index,float *data1,float *data2,float *data3,int day);
#endif