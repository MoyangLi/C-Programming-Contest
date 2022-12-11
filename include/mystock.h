#ifndef _LINE_h_
#define _LINE_h_
#include "head.h"
#include "KLINE.h"
#include "deal.h"
#include "tradere.h"
#include "detail.h"
void add_mystock(INFO *info,STOINFO *stoinfo);
void draw_mystock(void);
void show_mystock(INFO *info,STOINFO *stoinfo,int *,int *,int *);
void present(mySTOCK *own_stock,int length,int offset);
mySTOCK *init_mystock(INFO *info,mySTOCK *own_stock,int *length);
void free_stock(int length,mySTOCK *own_stock);
mySTOCK *delet_mystock(INFO *info,STOINFO *stoinfo,mySTOCK *own_stock,int *length,int offset,int position);
void rewrite_stock(INFO *info,STOINFO *stoinfo,mySTOCK *own_stock,int length,int flag);
void back(mySTOCK *own_stock,int offset,int position,STOINFO *stoinfo);
void find_stockpress_(STOINFO *stoinfo);
void stock_multied(mySTOCK *own_stock,int length,STOINFO *stoinfo,INFO *info);
void draw_multied(void);
void line_switch(int index,mySTOCK *own_stock,int column,STOINFO *stoinfo);
void right_press(INFO *info,STOINFO *stoinfo,int mx_,int my_);
#endif