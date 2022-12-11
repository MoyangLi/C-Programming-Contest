#ifndef _tool_h_
#define _tool_h_
#include "head.h"
void regu_float(char *a);
float gauss_rand(void);
void data_updata(void);
void layout_change(INFO *info,STOINFO *stoinfo);
void put_picture(int x1,int y1,int x2,int y2);
void save_picture(int x1,int y1,int x2,int y2);

void help_draw1();
void help_draw2();
void help_draw3();
void help_draw4();
void help_control(INFO *info,STOINFO * stoinfo,int *mx,int *my,int *mbutt);

#endif