#ifndef _CODRAW_h_
#define _CODRAW_h_
#include "stdio.h"
#include "dos.h"
#include "conio.h"
#include "chinese.h"
#include "graphics.h"
#include "mouse.h"
#include "newmenu.h"
#include "head.h"
# define MAX 24
typedef struct
{
	int a[3];
	char lowx[3][5];
	char highx[3][5];
	char lre[3][10];
	char hre[3][10];	//指示自定义上下限
}MX;

typedef struct SIZE
{
	char num[10];
	char name[10];
	char money[10];
	char up[10];
	struct SIZE *next;
}SIZE;


void add_condition(int condition,int count,MX *mine);
void draw_();
void show_condition(int condition) ;
void choose(MX *mine,SIZE *Q);
void final(SIZE *Q);
void size_control();
void move_slidder_11(int *mx,int *my,int *mbuttn,int flag,MX *mine);
void move_slidder_21(int *mx,int *my,int *mbuttn,int flag,MX *mine);
void move_slidder_31(int *mx,int *my,int *mbuttn,int flag,MX *mine);


#endif