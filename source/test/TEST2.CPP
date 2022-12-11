#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <stdlib.h>
#include <string.h>
#define N 14
typedef struct
{
	int year;
	int month;
	int day;
}Date;
typedef struct	student
{
	unsigned int number;
	char name[N];
	char sex;
	Date date;
	struct student *next;
}Student;
Student *New_node(Student *head,Student *tail);
void free_all(Student *head);
void main()
{
	char signal;
	Student *head,*tail,*temp;
	if((head=(Student *)malloc(sizeof(Student)))==NULL)
	{
		printf("Allocation failed\n");
		getch();
		exit(1);
	}
	head->next=NULL;
	head->number=0;
	strcpy(head->name,NULL);
	head->sex='0';
	head->date.year=0;
	head->date.month=0;
	head->date.day=0;
	tail=head;
	while(1)
	{
		printf("please input the signal:Y-input/N-exit\n");
		signal=getch();
		if(signal=='N')
		{
			break;
		}
		else if(signal=='Y')
		{
			head=New_node(head,tail);
			tail=tail->next;
		}
		else
		{
			printf("please input the right signal!\n");
		}
	}
	temp=head->next;
	printf("Number----Name----------Sex--Date----\n");
	while(temp!=NULL)
	{
		printf("%-10d%-14s%-5c%d/%d/%d\n",temp->number,temp->name,temp->sex,temp->date.year,temp->date.month,temp->date.day);
		temp=temp->next;
	}
	free_all(head);
}
Student *New_node(Student *head,Student *tail)
{
	Student *temp;
	if((temp=(Student *)malloc(sizeof(Student)))==NULL)
	{
		printf("Allocation failed\n");
		getch();
		exit(1);
	}
	printf("please input the number\n");
	fflush(stdin);
	scanf("%d",&temp->number);
	printf("please input the name\n");
	fflush(stdin);
	gets(temp->name);
	printf("please input the sex\n");
	fflush(stdin);
	temp->sex=getchar();
	printf("please input the year\n");
	fflush(stdin);
	scanf("%d",&(temp->date.year));
	printf("please input the month\n");
	scanf("%d",&(temp->date.month));
	printf("please input the day\n");
	scanf("%d",&(temp->date.day));
	tail->next=temp;
	temp->next=NULL;
	return head;
}
void free_all(Student *head)
{
	Student *temp;
	temp=head;
	{
		while(temp!=NULL)
		{
			head=head->next;
			free(temp);
			temp=head;
		}
	}
}