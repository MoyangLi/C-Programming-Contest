#ifndef _LINE_h_
#define _LINE_h_
#include "head.h"
#include "KLINE.h"

void line_bk_draw(void);
void draw_KDJ(float *n,int length,float *data1,float *data2,float *data3,int signal,int num);
void calculate_KDJ(float *price,int length,float *K,float *D,float *J,float *ymax,float *ymin);
void draw_MACD(float *price,int length,float *DIF,float *DEA,float *MACD,int signal,int num);
void calculate_MACD(float *price,int length,float *MACD,float *DIF,float *DEA,float *ymax,float *ymin);
void draw_OBV(STOCK *stock,int length,float *OBV,float *MAOBV,int signal,int num);
void calculate_OBV(STOCK *stock,int length,float *OBV,float *MAOBV,float *ymax,float *ymin);
void draw_RSI(float *price,int length,float *RSI1,float *RSI2,float *RSI3,int signal,int num);
void draw_PSY(float *price,int length,float *PSY,float *PSYMA,int signal,int num);
void draw_BIAS(float *price,int length,float *BIAS1,float *BIAS2,float *BIAS3,int signal,int num);
void draw_BOLL(float *price,int length,float *BOLL,float *UB,float *LB,int signal,int num);

void Time_sharing(INFO *info,STOINFO *stoinfo);
void show_share(int day,float *price,float *ave_price,float *DIF,float *DEA,float *MACD);
void draw_share(float *min,float *max,float *price,float *ave_price,float *DIF,float *DEA,float *MACD);
void draw_Time_sharing(STOINFO *stoinfo,float *price,float *ave_price,float *ymin,float *ymax);
void calculate_time(float *price,float *DIF,float *DEA,float *MACD,float *ymin,float *ymax);
void bk(void);

#endif