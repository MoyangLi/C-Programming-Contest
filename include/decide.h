#ifndef _decide_h_
#define _decide_h_
#include "newmenu.h"
#include "mystock.h"
void control_decide(INFO * info,STOINFO * stoinfo,int * mx,int * my,int * mbuttn);


void decide_compare_draw(STOINFO * stoinfo);
void grade_loading(STOINFO * stoinfo,int grade[3][3],char name[3][10]);
void grade_calculate(int * grade,float * data);
void compare_sheet(int grade[3][3],char name[3][10]);
void compare_bar1(int grade[3][3],char name[3][10]);
void compare_line(STOINFO * stoinfo, char name[3][10]);


void decide_choose_draw_init(void);
void deicde_choose_anal(STOINFO * stoinfo);
void choose_sheet(int x,int y,STOINFO *stoinfo);
void choose_button(char *s,int x,int y,int color);
void choose_sheet_fill(STOINFO * stoinfo,int y,int combine_score[4][3]);


void decide_add(STOINFO * stoinfo,char * str);
void decide_delate(STOINFO * stoinfo,char * str);



#endif