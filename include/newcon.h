#ifndef _control_h_
#define _control_h_

#include"head.h"
#include"mouse.h"
#include"newmenu.h"
#include"tool.h"

#define NUM0 0x5230
#define NUM1 0x4f31
#define NUM2 0x5032
#define NUM3 0x5133
#define NUM4 0x4134
#define NUM5 0x4c35
#define NUM6 0x4d36
#define NUM7 0x4737
#define NUM8 0x4838
#define NUM9 0x4939
#define F2 0x3c00
#define F3 0x3d00
#define F4 0x3e00
#define F5 0x3f00
#define F6 0x4000
#define F7 0x4100
#define F8 0x4200
#define F9 0x4300
#define F10 0x4400
#define F1 0x3b00
#define ENTER 0x1c0d
#define BACK 0x0e08
#define ESC 0x011b
#define UP 0x4800
#define DOWN 0x5000
#define RIGHT 0x4d00
#define LEFT 0x4b00


void control_main(INFO * info,STOINFO * stoinfo,Linkstock *Q1);

void control_menu(INFO * info,STOINFO * stoinfo,Linkstock * Q,int *mx,int *my,int *mbtn);

void control_press(INFO * info,STOINFO * stoinfo,Linkstock * Q,int *mx,int *my,int *mbtn);

void control_key(INFO * info,STOINFO * stoinfo,Linkstock *Q1,int *mx,int *my,int *mbtn);

void draw_quit(void);



#endif