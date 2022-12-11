#include<stdio.h>
#include<string.h>
struct employee
{
	char name[10];
	char sex[2];
	int time;
	long int salary;
	int currency[6];
};
void input(struct employee*p,int n);
void output(struct employee*p,int n);
void main()
{
	int n;
	struct employee pd[20];
	puts("please input the number of employees");
	scanf("%d",&n);
	input(pd,n);
	output(pd,n);
}
void input(struct employee*p,int n)
{
	int i,j,k,m;
	for(i=0;i<n;i++)
	{
		fflush(stdin);
		puts("please input Name");
		gets(p[i].name);
		puts("please input Sex");
		gets(p[i].sex);
		puts("please input Time");
		scanf("%d",&p[i].time);
		puts("please input Salary");
		scanf("%ld",&p[i].salary);
		m=(int)(p[i].salary/100);
		k=(int)(p[i].salary%100);
		p[i].currency[0]=m;
		m=k/50;
		k%=50;
		p[i].currency[1]=m;
		m=k/20;
		k%=20;
		p[i].currency[2]=m;
		m=k/10;
		k%=10;
		p[i].currency[3]=m;
		m=k/5;
		k%=5;
		p[i].currency[4]=m;
		p[i].currency[5]=k;
	}
}
void output(struct employee*p,int n)
{
	int i,j;
	int currency_tap[6]={0,0,0,0,0,0};
	for(i=0;i<6;i++)
	{
		for(j=0;j<n;j++)
			currency_tap[i]+=p[j].currency[i];
		printf("currency%d need %d\n",i+1,currency_tap[i]);
	}
	printf("Name      Sex  Time  Salary    Cur1   Cur2 Cur3 Cur4 Cur5 Cur6\n");
	printf("--------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	  if(p[i].time>20&&p[i].salary>5000&&strcmp(p[i].sex,"M")==0)
	  {
		printf("%-10s%-5s%-6d%-10ld",p[i].name,p[i].sex,p[i].time,p[i].salary);
		for(j=0;j<6;j++)
		  printf("%-6d",p[i].currency[j]);
		printf("\n");
	  }
}
