#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"
#define MAXSIZE  26

void initqueue(Linkstock *Q)     //初始化队列
{
	Q->base=(Stockdata *)malloc((MAXSIZE+1) * (sizeof(Stockdata)));
	if(!Q->base)
		exit(1);
	Q->front=Q->rear=0;
	Q->flag=1;
}



void enqueue(Linkstock *Q)           //队列赋值
{
	FILE  *fp1;
	FILE  *fp2;
	int i;
	char  t[7];
	char save[50]="data\\database\\";       //用于打开所选股票的文件
	fp1=fopen("data\\database\\symbolic.txt","rb");     //打开股票代码文件     
	
	if(Q->flag==1)
	{
		free(Q->base);
		initqueue(Q);
	}
	
	for(i=0;i<MAXSIZE;i++)
	{
	   if(fread(t,1,6,fp1)!=0)
	   {
		  t[6]='\0';
		  strcat(save,t);
		  strcat(save,"\\list.txt");

		  if((fp2=fopen(save,"rb"))==NULL)  
		  {
		     printf("enqueue: error opening list.txt(out)\n");
		     getch();
	      }

		  fread(&(Q->base[Q->rear].number),sizeof(int),1,fp2);
		  Q->base[Q->rear].number=i+1;
		  fread((Q->base[Q->rear].identifer),6,1,fp2);
		  Q->base[Q->rear].identifer[6]='\0';
		  fread((Q->base[Q->rear].name),10,1,fp2);
		  Q->base[Q->rear].name[9]='\0';
		  fread((Q->base[Q->rear].sta),sizeof(float),9,fp2);

		  fclose(fp2);
		  save[14]='\0';

		  Q->rear=(Q->rear+1)%(MAXSIZE+1);
	   }
	   else
	   {
		  break;
	   }
	}
	fclose(fp1);

}

void frontqueue(Linkstock *Q)   //上端插入元素
{
	
	char str2[30]="data\\database\\";
	char address[50];
	FILE * fp1;
	FILE * fp2;
	FILE * fsum;
	int iround,jround;
	char temp[7];
	int sum;
	int frontnum;
	
	if(Q->front-Q->rear==1||Q->rear==Q->front+26)
	{
		
		fp1=fopen("data\\database\\symbolic.TXT","rb");
		fsum=fopen("data\\database\\sum.TXT","rb");
		strcpy(address,str2);
		
		
		fread(&sum,sizeof(int),1,fsum);
		fclose(fsum);
		sum=191;
	
		frontnum=(Q->base[Q->front]).number;
	
		fseek(fp1,6*((frontnum-1+sum-1)%sum),SEEK_SET);
		fread(temp,1,6,fp1);
		fclose(fp1);
	
		temp[6]='\0';
		strcat(address,temp);
		strcat(address,"\\LIST.TXT");

		if((fp2=fopen(address,"rb"))==NULL) 	//股票数据保存的位置
		{
		    printf("frontqueue: error opening list.txt(out)\n");
		    getch();
	    }
		
		Q->front=(Q->front-1+MAXSIZE+1)%(MAXSIZE+1);
	
	
		fread(&(Q->base[Q->front].number),sizeof(int),1,fp2);
		Q->base[Q->front].number=(frontnum-1+sum-1)%sum+1;			//！！！！！！！！！！！！！！！！！！测试一下重新编号码
		fread((Q->base[Q->front].identifer),6,1,fp2);
		Q->base[Q->rear].identifer[6]='\0';
		fread((Q->base[Q->front].name),10,1,fp2);
		Q->base[Q->rear].name[9]='\0';
		fread((Q->base[Q->front].sta),sizeof(float),9,fp2);
		
		Q->rear=(Q->rear-1+MAXSIZE+1)%(MAXSIZE+1);
		fclose(fp2);

	}
	
}	

void rearqueue(Linkstock *Q)    //下端插入元素
{
	char str2[30]="data\\database\\";
	char address[50];
	FILE * fp1;
	FILE * fp2;
	FILE * fsum;
	int iround,jround;
	char temp[6];
	int sum;
	int rearnum;
	
	if(Q->front-Q->rear==1||Q->rear==Q->front+26)
	{
		
		fp1=fopen("data\\database\\symbolic.TXT","rb");
		fsum=fopen("data\\database\\sum.TXT","rb");
		strcpy(address,str2);
		
		fread(&sum,sizeof(int),1,fsum);
		fclose(fsum);
		sum=191;
	
		rearnum=(Q->base[(Q->rear-1+MAXSIZE+1)%(MAXSIZE+1)]).number;
		fseek(fp1,(rearnum%sum)*6,SEEK_SET);
	
		fread(temp,1,6,fp1);
	
		temp[6]='\0';
		strcat(address,temp);
		strcat(address,"\\LIST.TXT");

		if((fp2=fopen(address,"rb"))==NULL)		//股票数据保存的位置
		{
		  printf("rearqueue: error opening list.txt(out)\n");
		  getch();
	    }
		
		fread(&(Q->base[Q->rear].number),sizeof(int),1,fp2);
		Q->base[Q->rear].number=(rearnum+1)%sum;			//！！！！！！！！！！！！！！！！！！测试一下重新编号码
		fread((Q->base[Q->rear].identifer),6,1,fp2);
		Q->base[Q->rear].identifer[6]='\0';
		fread((Q->base[Q->rear].name),10,1,fp2);
		Q->base[Q->rear].name[9]='\0';
		fread((Q->base[Q->rear].sta),sizeof(float),9,fp2);
			
			
		Q->rear=(Q->rear+1)%(MAXSIZE+1);
		Q->front=(Q->front+1)%(MAXSIZE+1);
		fclose(fp2);
		fclose(fp1);
	
	}
}

void renewqueue(Linkstock *Q)
{
	int iround,kround=0;
	int length;
	FILE * fstock;
	char temp[7];
	char address[50];
	char pointer[30]="data\\database\\";
	
	if(Q->front<=Q->rear)
	{
		length=Q->rear-Q->front;
	}
	else if(Q->front>Q->rear)
	{
		length=MAXSIZE-(Q->front-Q->rear)+1;
	}
	
	for(iround=Q->front;kround<length;iround=(iround+1)%(MAXSIZE+1),kround++)
	{
		strcpy(temp,Q->base[iround].identifer);
		strcpy(address,pointer);
		strcat(address,temp);
		strcat(address,"\\list.txt");
		
		if((fstock=fopen(address,"rb"))==NULL)
	    {
		   printf("data_updata: error opening list.txt(out)\n");
		   getch();
	    }
		
		fseek(fstock,sizeof(int)+10+6,SEEK_SET);
		fread(Q->base[iround].sta,sizeof(float),9,fstock);
		
		fclose(fstock);
	}
	
}
	
	
	
	
		