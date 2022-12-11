#include "login.h"
#include "chinese.h"
void put_hz(int mx,int my,char *string,int color,char flag,char part)
{

	FILE *hzk_p=NULL;
	unsigned char area_code,bit_code;
	unsigned long offset;
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	char i,j;
	char word[2]={'\0','\0'};
	int pos;
	int maxx=getmaxx();
	switch(flag)
	{
		case 16:
		{
			char hz[32];
			if((hzk_p=fopen("hzk\\HZk16K","rb"))==NULL)
			{
				outtext("Can't open hzk16 file!Press any key to quit");
				getch();
				exit(1);
			}
			settextjustify(LEFT_TEXT,TOP_TEXT);
			settextstyle(2,0,6);
			while(*string!=NULL)
			{
			  while(mx<maxx-flag&&(*string!=NULL))
			  {
				if((int)(*string)>=65&&(int)(*string)<=90)   //大写字母
				{
					word[0]=*string;
					setcolor(color);
					outtextxy(mx+1,my-2,word);
					string+=1;
					mx+=9;
				}
				else if(((int)(*string)>0&&(int)(*string)<65)||((int)(*string)>90&&(int)(*string)<128))  //数字，小写字母及部分特殊符号
				{
					word[0]=*string;
					setcolor(color);
					outtextxy(mx+1,my-2,word);     // 只有一个一个字符输出才不会影响后面的汉字
					string+=1;
					mx+=9;
				}
				else
				{
					area_code=string[0]-0xa0;
					bit_code=string[1]-0xa0;
					offset=(94*(area_code-1)+(bit_code-1))*32L;
					fseek(hzk_p,offset,SEEK_SET);
					fread(hz,32,1,hzk_p);

					for(i=0;i<16;i++)
					{
						pos=2*i;
						for(j=0;j<16;j++)
						{
							if((mask[j%8]&hz[pos+j/8])!=NULL)
							{
								putpixel(mx+j,my+i,color);
							}
						}
					}
					mx+=part+flag;
					string+=2;
				}
			  }
			  my+=10+flag;
			}
			break;
		}
		case 24:
		{
			char hz[72];
			if((hzk_p=fopen("hzk\\HZK24k","rb"))==NULL)
			{
				outtext("Can't open hzk24 file!Press any key to quit");
				getch();
				exit(1);
			}
			settextjustify(LEFT_TEXT,TOP_TEXT);
			settextstyle(1,0,3);
			while(*string!=NULL)
			{
				while (mx<maxx-flag&&(*string!=NULL))
				{
					if((int)(*string)>=65&&(int)(*string)<=90)
					{
						word[0]=*string;
						setcolor(color);
						outtextxy(mx+1,my-4,word);
						string+=1;
						mx+=14;
					}
					else if(((int)(*string)>0&&(int)(*string)<65)||((int)(*string)>90&&(int)(*string)<128))  //数字，小写字母及部分特殊符号
					{
						word[0]=*string;
						setcolor(color);
						outtextxy(mx+1,my-2,word);     // 只有一个一个字符输出才不会影响后面的汉字
						string+=1;
						mx+=12;
					}
					else
					{
						area_code=string[0]-0xa0;
						bit_code=string[1]-0xa0;
						offset=(94*(area_code-1)+(bit_code-1))*72L;
						fseek(hzk_p,offset,SEEK_SET);
						fread(hz,72,1,hzk_p);

						for(i=0;i<24;i++)
						{
							pos=3*i;
							for(j=0;j<24;j++)
							{
								if((mask[j%8]&hz[pos+j/8])!=NULL)
								{
									putpixel(mx+j,my+i,color);
								}
							}
						}
						mx+=part+flag;
						string+=2;
					}
				}
				my+=10+flag;
			}
			break;
		}
		case 32:
		{
			char hz[128];
			if((hzk_p=fopen("hzk\\HZK32","rb"))==NULL)
			{
				outtext("Can't open hzk32 file!Press any key to quit");
				getch();
				exit(1);
			}
			while(*string!=NULL)
			{
				while (mx<maxx-flag&&(*string!=NULL))
				{
					area_code=string[0]-0xa0;
					bit_code=string[1]-0xa0;
					offset=(94*(area_code-1)+(bit_code-1))*128L;
					fseek(hzk_p,offset,SEEK_SET);
					fread(hz,128,1,hzk_p);

					for(i=0;i<32;i++)
					{
						pos=4*i;
						for(j=0;j<32;j++)
						{
							if((mask[j%8]&hz[pos+j/8])!=NULL)
							{
								putpixel(mx+j,my+i,color);
							}
						}
					}
					mx+=part+flag;
					string+=2;
				}
				my+=10+flag;
			}
			break;
		}
		case 40:
		{
			char hz[200];
			if((hzk_p=fopen("hzk\\HZK40T","rb"))==NULL)
			{
				outtext("Can't open hzk40 file!Press any key to quit");
				getch();
				exit(1);
			}
			while(*string!=NULL)
			{
				while (mx<maxx-flag&&(*string!=NULL))
				{
					area_code=string[0]-0xa0;
					bit_code=string[1]-0xa0;
					offset=(94*(area_code-1)+(bit_code-1))*200L;
					fseek(hzk_p,offset,SEEK_SET);
					fread(hz,200,1,hzk_p);

					for(i=0;i<40;i++)
					{
						pos=5*i;
						for(j=0;j<40;j++)
						{
							if((mask[j%8]&hz[pos+j/8])!=NULL)
							{
								putpixel(mx+j,my+i,color);
							}
						}
					}
					mx+=part+flag;
					string+=2;
				}
				my+=10+flag;
			}
			break;
		}
		case 48:
		{
			char hz[288];
			if((hzk_p=fopen("hzk\\Hzk48k","rb"))==NULL)
			{
				outtext("Can't open hzk48 file!Press any key to quit");
				getch();
				exit(1);
			}
			while(*string!=NULL)
			{
				while (mx<maxx-flag&&(*string!=NULL))
				{
					area_code=string[0]-0xa0;
					bit_code=string[1]-0xa0;
					offset=(94*(area_code-1)+(bit_code-1))*288L;
					fseek(hzk_p,offset,SEEK_SET);
					fread(hz,288,1,hzk_p);

					for(i=0;i<48;i++)
					{
						pos=6*i;
						for(j=0;j<48;j++)
						{
							if((mask[j%8]&hz[pos+j/8])!=NULL)
							{
								putpixel(mx+j,my+i,color);
							}
						}
					}
					mx+=part+flag;
					string+=2;
				}
				my+=10+flag;
			}
			break;
		}
		default:
		break;
	}
	fclose(hzk_p);
}
void puthz12(char *s,int x,int y,int color)
{
   FILE *fp;
   char buffer[24],word[2]={'\0','\0'};
   register i,j,k;
   unsigned char qh,wh;
   unsigned long location;
   settextjustify(LEFT_TEXT,TOP_TEXT);
   settextstyle(2,0,5);
   if((fp=fopen("hzk\\hzk12","rb"))==NULL)
   {
       printf("Can't open hzk12!");
	   fclose(fp);
       getch();
       exit(1);
   }
   while(*s)
   {
     if((int)(*s)>=65&&(int)(*s)<=90)   //大写字母
     {
		  word[0]=*s;
		  setcolor(color);
		  outtextxy(x,y-2,word);
          s+=1;
          x+=8;
	 }
	else if(((int)(*s)>0&&(int)(*s)<65)||((int)(*s)>90&&(int)(*s)<128))  //数字，小写字母及部分特殊符号
     {
		  word[0]=*s;
		  setcolor(color);
		  outtextxy(x+1,y-2,word);     // 只有一个一个字符输出才不会影响后面的汉字
          s+=1;
          x+=8;
	 }
     else
     {
          qh=*s-0xa0;
          wh=*(s+1)-0xa0;
          location=(94*(qh-1)+(wh-1))*24L;
          fseek(fp,location,SEEK_SET);
          fread(buffer,24,1,fp);
          for(i=0;i<12;i++)
               for(j=0;j<2;j++)
                	for(k=0;k<8;k++)
                 		if((buffer[i*2+j]>>(7-k))&0x1)
                      		putpixel(x+8*j+k,y+i,color);
          s+=2;
          x+=12;
       }
	}
	fclose(fp);
}
void puthz16(char *s,int x,int y,int wd,int Px,int Py,int color)
{
	FILE *fq=NULL;
	char buffer[32];
	char word[2]={'\0','\0'};
	register m,n,i,j,k;
	unsigned char qh,wh;
	unsigned long offset;
	if((fq=fopen("hzk\\HZK16","rb"))==NULL)     /*可改变打开的汉字库而输出不同字体的汉字*/
	{
		printf("can't open hzk16,please add it");
		getch();
		closegraph();
		exit(0);
	}
	while(*s)
	{
		if((int)(*s)>0&&(int)(*s)<128)
		{
			 word[0]=*s;
			 setcolor(color);
			 //outtextxy(x,y-2,s);
			 settextstyle(0,0,2);
			 outtextxy(x,y+1,word);
			 settextstyle(0,0,0);
			 s+=1;
			 x+=8;
		}
		else
		{
			qh=*s-0xa0;
			wh=*(s+1)-0xa0;
			offset=(94*(qh-1)+(wh-1))*32L;
			fseek(fq,offset,SEEK_SET);
			fread(buffer,32,1,fq);
			for(i=0;i<16;i++)
			for(n=0;n<Px;n++)
			for(j=0;j<2;j++)
			for(k=0;k<8;k++)
			for(m=0;m<Py;m++)
			if((buffer[i*2+j]>>(7-k)&0x1)!=NULL)
				putpixel(x+8*j*Py+k*Py+m,y+i*Px+n,color);
			s+=2;
			x=x+wd;
		}
	}
	fclose(fq);
}
void putnews(char *s,int x,int y,int color,int maxx)  //maxx为绝对最大宽的横坐标
{
	FILE *fp=NULL;
	int start_x=x;
	char buffer[24],word[2]={'\0','\0'};
	register i,j,k;
	unsigned char qh,wh;
	unsigned long location;
	//settextstyle(0,0,1);
	if((fp=fopen("hzk\\hzk12","rb"))==NULL)
	{
		printf("Can't open hzk16!");
		getch();
		exit(0);
	}
	while(*s)
	{
	  if((int)(*s)>0&&(int)(*s)<128)
	  {
		   word[0]=*s;
		   setcolor(color);
		   //outtextxy(x,y-2,s);     用s会导致数字或字母后面的汉子以乱码和正常同时显示在一起
		   outtextxy(x,y+3,word);
		   s+=1;
		   x+=8;
	  }
	  else
	  {
		  if(x>maxx)
		  {
			  y+=16;
			  x=start_x-12*2;       //首行缩进两个汉字

		  }
		   qh=*s-0xa0;
		   wh=*(s+1)-0xa0;
		   location=(94*(qh-1)+(wh-1))*24L;
		   fseek(fp,location,SEEK_SET);
		   fread(buffer,24,1,fp);
		   for(i=0;i<12;i++)
				for(j=0;j<2;j++)
					 for(k=0;k<8;k++)
						  if((buffer[i*2+j]>>(7-k))&0x1)
							   putpixel(x+8*j+k,y+i,color);
		   s+=2;
		   x+=12;
		}
	 }
	 fclose(fp);
}
