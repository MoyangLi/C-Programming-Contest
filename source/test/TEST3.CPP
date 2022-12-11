#include<stdio.h>
struct Date
{
	int day;
	int month;
	int year;
	int yearday;
	char month_name[4];
};
int day_of_year(struct Date*pd);
void main()
{
	struct Date pd[2];
	int i;
	for(i=0;i<2;i++)
	{
	  puts("please input year");
	  scanf("%d",&pd[i].year);
	  puts("please input month");
	  scanf("%d",&pd[i].month);
	  puts("please input day");
	  scanf("%d",&pd[i].day);
	}
	printf("there are %d days.\n",day_of_year(pd));
}
int day_of_year(struct Date*pd)
{
	int day_tab[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
						{0,31,29,31,30,31,30,31,31,30,31,30,31}};
	int year_tab[2]={365,366};
	int i,j,k,leap;
	int day[2]={0,0};
	for(i=0;i<2;i++)
	{
		day[i]=pd[i].day;
		leap=pd[i].year%4==0&&
			 pd[i].year%100!=0||
			 pd[i].year%400==0;
		for(j=1;j<pd[i].month;j++)
		  day[i]+=day_tab[leap][j];
	}
	for(k=pd[0].year;k<pd[1].year;k++)
	{
		leap=k%4==0&&
			 k%100!=0||
			 k%400==0;
		day[1]+=year_tab[leap];
	}
	return (day[1]-day[0]);
}
