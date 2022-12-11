#ifndef _stock_h_
#define _stock_h_
#include"head.h"

void control_stock(INFO * info,STOINFO * stoinfo,Linkstock * Q,int *mx, int *my,int *mbtn);
void stock_listdraw(Linkstock *Q,INFO *info);
void time_(INFO *info);
void stock_sort(STOINFO * stoinfo);
void data_sorting(char (*symbolic)[7],long int *data,int sortline,int length);

#endif