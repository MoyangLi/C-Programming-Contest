#ifndef _nMOUSE_H_
#define _nMOUSE_H_

void cursor(int x,int y);
int init(int xmi, int xma, int ymi, int yma);  	//鼠标器初始化操作
void getMousebk(int x, int y);					//存储鼠标背后的图案
void mouseInit(int *mx,int *my, int *mbutt);
void mouse_draw(int x, int y);
void mouse_put(int x, int y);
void mouse_save(int x, int y);
void mousehide(int x,int y);

int initmouse(int xmi, int xma, int ymi, int yma);
int mouse_read(int *mx, int *my,int *mbutt);
void newmouse(int *mx, int*my, int*mbutt);
void setmouseshape(int i);

int mouse_press(int x1,int y1,int x2,int y2,int *mx,int *my,int *mbutt);
int mouse_above(int x1,int y1,int x2,int y2,int *mx,int *my,int *mbutt);

#endif

