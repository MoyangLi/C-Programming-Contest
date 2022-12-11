#include "stdio.h"
#include "stdio.h"
#include "dos.h"
#include "conio.h"
#include "chinese.h"
#include "graphics.h"
#include "mouse.h"
#include "newmenu.h"
#include "newcon.h"
#include "head.h"
#include "login.h"

void main()
{
	int gdriver=VGA;
	int gmode=VGAHI;
	int mx,my,mbuttn=-1;
	INFO info;
	Linkstock Q1;
	STOINFO stoinfo;

	info.account_flag=0;
	info.layout=0;        //info 初始化
	info.layout_last=0;
	info.menu_flag=0;
	info.account_flag=0;
	info.time=4;
	
	stoinfo.sort=0;
	stoinfo.choose[0][0]='k';
	stoinfo.choose[1][0]='k';
	stoinfo.choose[2][0]='k';
	stoinfo.size=1;
	stoinfo.pointer=0;
	stoinfo.number_=1;
	stoinfo.number=1;
	strcpy(stoinfo.stockpress,"000001");
	strcpy(stoinfo.stockpress_,"000001");

	Q1.flag=0;


	initgraph(&gdriver,&gmode,"BORLANDC\\bgi");
	cleardevice();
	mouseInit(&mx,&my,&mbuttn);
	control_main(&info,&stoinfo,&Q1);    //总转入控制函数
	   //closegraph();
}
