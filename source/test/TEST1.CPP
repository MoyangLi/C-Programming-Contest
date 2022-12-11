#include <stdio.h>
#include <alloc.h>
#include <conio.h>
#include <stdlib.h>
#define N 20
typedef struct pnode
{
	int data;
	struct pnode *next;
}Node;
Node *exchange(Node *head);
void free_all(Node *head);

void main()
{
	int i;
	Node *temp,*head,*tail;
	Node *new_head,*new_tail;
	temp=NULL;
	head=NULL;
	tail=NULL;
	if((temp=(Node *)malloc(sizeof(Node)))==NULL)
	{
		printf("Allocation failed\n");
		getch();
		exit(1);
	}
	temp->data=1;
	temp->next=NULL;
	head=temp;
	tail=temp;
	for(i=1;i<N;i++)
	{
		if((temp=(Node *)malloc(sizeof(Node)))==NULL)
		{
			printf("Allocation failed\n");
			getch();
			exit(1);
		}
		temp->data=i+1;
		tail->next=temp;
		temp->next=NULL;
		tail=temp;
	}
	new_tail=head;
	new_head=exchange(head);
	temp=new_head;
	for(i=0;i<N;i++)
	{
		printf("%d\n",temp->data);
		temp=temp->next;
	}
	free_all(new_head);
}
Node *exchange(Node *head)
{
	int i;
	Node *temp,*new_head;
	temp=NULL;
	new_head=NULL;
	for(i=0;i<N;i++)
	{
		new_head=head;
		head=head->next;
		new_head->next=temp;
		temp=new_head;
	}
	return new_head;
}
void free_all(Node *head)
{
	Node *temp;
	int i;
	temp=head;
	for(i=0;i<N;i++)
	{
		temp=temp->next;
		free(head);
		head=temp;
	}
}