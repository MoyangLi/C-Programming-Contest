#ifndef _detail_h_
#define _detail_h_

#include "login.h"
#include "kline.h"
#include "head.h"
#include "newmenu.h"
#include "chinese.h"
#include "newcon.h"

void detail_draw(STOINFO *stoinfo);
void detail_draw_bk(void);
void stock_detail(INFO *info,STOINFO *stoinfo,int *,int *,int *);
void judge_press(INFO *info,STOINFO *stoinfo,int *mx,int *my,int *mbuttn);
void find(INFO *info,STOINFO *stoinfo);
int strcnmp(char *str1,char *str2,int n);

#endif