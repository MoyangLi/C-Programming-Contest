#include "trade.h"

/*************************************************
  Copyright (C),Moyang LI
  File name:			trade.c
  Author:       		��ī��
  Version:				1.0 
  Date:					18/11/05
  Description:  		��Ʊ���׽��溯��
  Function List:  
    add_dalegate		���ί�й�Ʊ
	find_hold			���ҳֲֹ�Ʊ
	write_delegate		�û�ί���ļ�����
	delet_pre_delegate	ɾ���ǽ��յ�ί����Ϣ
	show_delegate_data	ί�н���������ʾ
	show_recall_data	��������������ʾ
	show_his_deal		չʾ��ʷ�ɽ�
	show_tod_deal		չʾ���ճɽ�
	show_balance_data	չʾ�ʽ��������ˮ
	recall_num			�ж�ѡ�г����Ĺ�Ʊ
	delet_delegate		����
	free_all			�ͷ���������ڵ�
	get_recall_num		��ȡ����������ʾ������
	get_today_deal		��ȡ���ճɽ�����
	page_up_down		���¼��л�����ҳ
	rewrite_own			�����û�own�ļ�	
	renew_own			��own���ݵĸ���
	rewrite_balance		�û�����ļ�����
	rewrite_hold		�û��ֲ��ļ�����
	rewrite_deal		�û������ļ�����
	balance_new_add		�������ˮ��¼
	deal_new_add		����½��׼�¼
	hold_new_add		����³ֲּ�¼
	delet_hold			ɾ��ĳ�ֲּ�¼
	judge_deal			�ж�ĳֻ��Ʊ�Ƿ�ɽ�
	get_now_price		��ȡ��Ʊ�ּ�
	test_balance		�ɽ��ܿغ���
	recharge			��ֵ�ܿ��ƺ���
	judge_rech			�ж��Ƿ��ֵ�ɹ�
  History:      
	<author>  <time>   <version >   <desc>
	��ī��    18/11/05     1.0     build this moudle  
*************************************************/

/*************************************************
  Function:			add_dalegate	
  Description:   	���ί�й�Ʊ
  Input:          	own			�����û���Ϣ
					phead		����ί������ͷ���
					time_p		����ί��ʱ��
					length		����ί����Ϣ����
					hold		�޸ĳֲ���Ϣ�ж����Ʊ
  Return:         	void
*************************************************/

Delegate *add_dalegate(Own *own,Delegate *phead,struct tm time_p,int *length,Hold *hold)
{
	Delegate *temp,*delegate;
	Hold *temp_hold;
	if((delegate=(Delegate *)malloc(sizeof(Delegate)))==NULL)
	{
		printf("Allocation of delegate failed!!!");
		getch();
		exit(1);
	}
	length[0]++;
	length[4]++;
	strcpy(delegate->stockname,own->stockname);
	strcpy(delegate->stockcode,own->stockcode);
	delegate->dele_amount=own->num_own;
	delegate->dele_price=own->price_own;
	delegate->date=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1)*100+(long)time_p.tm_mday;
	delegate->time=100*(time_p.tm_hour)+time_p.tm_min;
	delegate->flag=own->flag;
	delegate->flag_=0;
	delegate->delet_flag=0;
	if(own->flag==0)
	{
		own->balance[2]+=1.003*(double)(delegate->dele_amount*delegate->dele_price);
		own->balance[0]=own->balance[1]-own->balance[2];	//���ý��=�ʽ����-������
	}
	else if(own->flag==1)	//����������Ļ�����Ҫ���˻����
	{
		temp_hold=find_hold(hold,length[1],own->stockcode);
		temp_hold->amount_blocked+=own->num_own;
		temp_hold->amount_avail=temp_hold->amount_real-temp_hold->amount_blocked;
	}
	rewrite_own(own);					//����д��own
	rewrite_hold(own,hold,length[1]);	//����д��hold
	strcpy(own->stockcode,"");
	if(phead==NULL)
	{
		phead=delegate;
		phead->pre=NULL;
		phead->next=NULL;
	}
	else if(phead->next==NULL)
	{
		phead->next=delegate;
		phead->pre=delegate;
		delegate->next=phead;
		delegate->pre=phead;
	}
	else
	{
		temp=phead->pre;		//��temp���浱ǰ���һ���ڵ�
		temp->next=delegate;	//����ǰ���һ���ڵ�ĺ��ָ��delegate������ӵĽڵ�
		delegate->next=phead;	//���½ڵ�ĺ��ָ��ͷ�ڵ�
		delegate->pre=temp;		//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
		phead->pre=delegate;	//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
	}
	write_delegate(own,phead,length[0]);
	return phead;
}

/*************************************************
  Function:			find_hold	
  Description:   	ȷ���ֲ����Ƿ��Ѿ����иù�Ʊ�ڵ�
  Input:          	hold		���ݳֲ�����
					length		���ݳֲֽڵ�����
					stockcode	���жϹ�Ʊ����
  Return:         	Hold *
*************************************************/

Hold *find_hold(Hold *hold,int length,char stockcode[7])	//���ҳֲ����Ƿ��и�֧��Ʊ
{
	Hold *temp;
	int i;
	temp=hold;
	for(i=0;i<length;i++)
	{
		if(strcmp(temp->stockcode,stockcode)==0)
			return temp;
		temp=temp->next;
	}
	temp=NULL;
	return temp;
}

/**Delegate *del_dalegate(Delegate *phead,int del_num,int length)		//ɾ�����ص�һ����Ϣ
{
	Delegate *temp,*pn;
	if(phead==NULL||del_num>length)
	{
		return phead;
	}
	else if(length==1)			//�ڵ���Ϊ1
	{
		free(phead);
		return(NULL);
	}
	else if(del_num==1&&length>2)//���ɾ��ͷ��㲢�ҽڵ������������
	{
		temp=phead;				//temp��Ϊ��ʱҪɾ���Ľڵ�
		phead=phead->next;
		phead->pre=temp->pre;
		temp->pre->next=phead;
		free(temp);
		return(phead);
	}
	else if(length==2)			//�ڵ���Ϊ2	
	{
		temp=phead;
		for(;del_num>1;del_num--)
		{
			temp=temp->next;
		}
		phead=temp->next;		//phead�Ƶ�Ҫɾ���Ľڵ�ĺ��λ��,��Ϊ����Ҫɾ���Ľڵ�ʣ�µĽڵ������һ��phead
		free(temp);
		phead->next=NULL;
		phead->pre=NULL;
		return(phead);
	}
	else
	{
		temp=phead;
		for(;del_num>1;del_num--)
		{
			pn=temp;
			temp=temp->next;
		}
		pn->next=temp->next;
		temp->next->pre=pn;
		free(temp);
		return(phead);
	}
}**/

/*************************************************
  Function:			delet_pre_delegate	
  Description:   	�ж�Ŀǰί����Ϣ�Ƿ�ʧЧ
  Input:          	own			�����û���Ϣ
					phead		����ί��������Ϣ
					time_p		���ݵ�ǰ������ʱ��
					length		����ί�нڵ������
  Return:         	Delegate *
*************************************************/

Delegate *delet_pre_delegate(Own *own,Delegate *phead,struct tm time_p,int *length)	//��Ϊֻ����ɵ���ί�еĸ���֮����ܽ����µ�ί�У�����ί��Ҫôȫ��Ϊ֮ǰί��Ҫôȫ��Ϊ����ί��
{
	Delegate *temp;
	int i;
	long date_temp;
	temp=phead;
	date_temp=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1)*100+(long)time_p.tm_mday;
	if(temp->date==date_temp)
		//return phead;
		;
	else if(temp->date!=date_temp)
	{
		free_delegate(phead,length[0]);
		length[0]=0;
		length[4]=0;
		write_delegate(own,phead,length[0]);
		//return phead;
	}
	return phead;
}

/*************************************************
  Function:			write_delegate
  Description:   	�������ļ���д��ί����Ϣ������ί���ļ�
  Input:          	own			�����û���Ϣ
					phead		����ί��������Ϣ
					length		����ί�нڵ������
  Return:         	void
*************************************************/

void write_delegate(Own *own,Delegate *phead,int length)		//д���Ʊί������
{
	FILE *fp;
	int i;
	char temp[40];
	Delegate *delegate;
	delegate=phead;
	strcpy(temp,"USER\\");
	strcat(temp,own->account);
	strcat(temp,"\\");
	strcat(temp,"delegat.txt");
	if((fp=fopen(temp,"wt"))==NULL)
	{
		printf("can't build the file delegate.txt while write the data of stock!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fprintf(fp,"%d",length);
	fprintf(fp,"%c",'\n');
	//fwrite(&length,sizeof(int),1,fp);
	//fwrite("\n",1,1,fp);
	for(i=0;i<length;i++)
	{
		fprintf(fp,"%s %s %ld %.2f %ld %d %d %d %d",
			   delegate->stockname,delegate->stockcode,delegate->dele_amount,delegate->dele_price,
			   delegate->date,delegate->time,delegate->flag,delegate->flag_,delegate->delet_flag);
		//fwrite("\n",1,1,fp);
		fprintf(fp,"%c",'\n');
		delegate=delegate->next;
	}
	fclose(fp);
}

/*************************************************
  Function:			show_delegate_data
  Description:   	չʾί�н�����Ϣ
  Input:          	phead		����ί��������Ϣ
					length		����ί�нڵ������
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void show_delegate_data(Delegate *phead,int length,int page_pointer)
{
	int i=0;
	Delegate *temp;
	char temp_str[15];
	char time[7];
	temp=phead;
	if(length<=0)
		return;

	while(page_pointer>0)
	{
		temp=temp->next;
		page_pointer--;
		length--;
	}

	while(i<length&&i<14)
	{
		settextstyle(2,0,6);
		settextjustify(CENTER_TEXT,TOP_TEXT);
		setcolor(LIGHTBLUE);
		outtextxy(181,103+20*i,temp->stockcode);
		sprintf(temp_str,"%ld",temp->dele_amount);
		outtextxy(313,103+20*i,temp_str);
		sprintf(temp_str,"%.2f",temp->dele_price);
		outtextxy(379,103+20*i,temp_str);
		sprintf(temp_str,"%d",temp->time/100);
		strcpy(time,temp_str);
		strcat(time,":");
		sprintf(temp_str,"%d",temp->time%100);
		strcat(time,temp_str);
		outtextxy(511,103+20*i,time);
		settextstyle(2,0,5);
		sprintf(temp_str,"%ld",temp->date);
		outtextxy(445,105+20*i,temp_str);
		if(temp->flag==0)
			put_hz(552,105+20*i,"����",LIGHTBLUE,16,2);
		else
			put_hz(552,105+20*i,"����",LIGHTBLUE,16,2);
		
		put_hz(215,105+20*i,temp->stockname,LIGHTBLUE,16,1);
		
		if(temp->flag_==0)
		{
			put_hz(598,104+20*i,"*",BLACK,16,0);
		}
		i++;
		temp=temp->next;
	}
}

/*************************************************
  Function:			show_recall_data
  Description:   	չʾ����������Ϣ
  Input:          	phead		����ί��������Ϣ
					length		����ί�нڵ������
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void show_recall_data(Delegate *phead,int length,int page_pointer)
{
	int i=0;
	Delegate *temp;
	char temp_str[15];
	char time[7];
	temp=phead;
	if(length<=0)
		return;
	while(page_pointer>0)
	{
		length--;
		if(temp->delet_flag==0&&temp->flag_==0)
		{
			page_pointer--;
		}
		temp=temp->next;
	}
	while(length>0&&i<14)
	{
		length--;
		if(temp->delet_flag==1||temp->flag_==1)	//����Ѿ��ɽ������Ѿ�����
		{
			temp=temp->next;
			continue;
		}
		settextstyle(2,0,6);
		settextjustify(CENTER_TEXT,TOP_TEXT);
		setcolor(LIGHTBLUE);
		outtextxy(181,133+20*i,temp->stockcode);
		sprintf(temp_str,"%ld",temp->dele_amount);
		outtextxy(313,133+20*i,temp_str);
		sprintf(temp_str,"%.2f",temp->dele_price);
		outtextxy(379,133+20*i,temp_str);
		sprintf(temp_str,"%d",temp->time/100);
		strcpy(time,temp_str);
		strcat(time,":");
		sprintf(temp_str,"%d",temp->time%100);
		strcat(time,temp_str);
		outtextxy(511,133+20*i,time);
		settextstyle(2,0,5);
		sprintf(temp_str,"%ld",temp->date);
		outtextxy(445,135+20*i,temp_str);
		if(temp->flag==0)
			put_hz(552,135+20*i,"����",LIGHTBLUE,16,2);
		else
			put_hz(552,135+20*i,"����",LIGHTBLUE,16,2);
		
		put_hz(215,135+20*i,temp->stockname,LIGHTBLUE,16,1);
		temp=temp->next;
		i++;
	}
}

/*************************************************
  Function:			show_his_deal
  Description:   	չʾ��ʷ���׽�����Ϣ
  Input:          	phead		���ݽ���������Ϣ
					length		���ݽ�������ڵ������
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void show_his_deal(Deal *phead,int length,int page_pointer)		//��ʾ��ʷ�ɽ�
{
	int i=1;			//��Ϊ��ʷ�ɽ�Ҳ��Ҫ���ճɽ�ʱ��˳�����ŵ����Բ�����ǰ����ֻ���Һ�̣�����ʱ��˳������
	Deal *temp;
	char temp_str[15];
	char time[7];
	temp=phead;
	if(length<=0)
		return;
	while(page_pointer>0)
	{
		page_pointer--;
		temp=temp->next;
		length--;
	}
	while(length>0&&i<=13)
	{
		length--;
		settextstyle(2,0,6);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setcolor(LIGHTBLUE);
		outtextxy(181,97+21*i,temp->stockcode);	//֤ȯ����
		sprintf(temp_str,"%ld",temp->deal_amount);
		outtextxy(379,97+21*i,temp_str);			//�ɽ�����
		sprintf(temp_str,"%.2f",temp->deal_price_ave);
		outtextxy(445,97+21*i,temp_str);			//�ɽ�����
		settextstyle(2,0,5);
		sprintf(temp_str,"%ld",temp->deal_date);
		outtextxy(577,97+21*i,temp_str);			//�ɽ�ʱ��
		sprintf(temp_str,"%.2lf",temp->deal_money);
		outtextxy(511,97+21*i,temp_str);			//�ɽ����
		if(temp->flag==0)
			put_hz(294,92+21*i,"����",LIGHTBLUE,16,2);
		else
			put_hz(294,92+21*i,"����",LIGHTBLUE,16,2);

		put_hz(215,92+21*i,temp->stockname,LIGHTBLUE,16,1);//֤ȯ����
		temp=temp->next;
		i++;
	}
}

/*************************************************
  Function:			show_tod_deal
  Description:   	չʾ���ս��׽�����Ϣ
  Input:          	phead		���ݽ���������Ϣ
					length		���ݽ�������ڵ������
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void show_tod_deal(Deal *phead,int length,int page_pointer,struct tm time_p)	//��ʾ���ճɽ�
{
	int i=1;			//��Ϊ���ճɽ�Ҳ��Ҫ���ճɽ�ʱ��˳�����ŵ����Բ�����ǰ����ֻ���Һ�̣�����ʱ��˳������
	Deal *temp;
	char temp_str[15];
	char time[7];
	long date_temp=((long)(time_p.tm_year+1900)*10000+(long)(time_p.tm_mon+1)*100+(long)time_p.tm_mday);
	temp=phead;
	if(length<=0)
		return;
	while(page_pointer>0)
	{
		if(temp->deal_date==date_temp)
		{
			page_pointer--;
			length--;
		}
		temp=temp->next;
	}
	while(length>0&&i<=13)
	{
		length--;
		if(temp->deal_date!=date_temp)
		{	
			temp=temp->next;
			continue;
		}
		settextstyle(2,0,6);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setcolor(LIGHTBLUE);
		outtextxy(181,97+21*i,temp->stockcode);	//֤ȯ����
		sprintf(temp_str,"%ld",temp->deal_amount);
		outtextxy(379,97+21*i,temp_str);			//�ɽ�����
		sprintf(temp_str,"%.2f",temp->deal_price_ave);
		outtextxy(445,97+21*i,temp_str);			//�ɽ�����
		sprintf(temp_str,"%d",temp->deal_time/100);
		strcpy(time,temp_str);
		strcat(time,":");
		sprintf(temp_str,"%d",temp->deal_time%100);
		strcat(time,temp_str);
		outtextxy(577,97+21*i,time);				//�ɽ�ʱ��
		settextstyle(2,0,5);
		sprintf(temp_str,"%.2lf",temp->deal_money);
		outtextxy(511,97+21*i,temp_str);			//�ɽ����
		if(temp->flag==0)
			put_hz(294,92+21*i,"����",LIGHTBLUE,16,2);
		else
			put_hz(294,92+21*i,"����",LIGHTBLUE,16,2);
		
		put_hz(215,92+21*i,temp->stockname,LIGHTBLUE,16,1);//֤ȯ����
		i++;
		temp=temp->next;
	}
}

/*************************************************
  Function:			show_balance_data
  Description:   	չʾ�ʽ������ˮ������Ϣ
  Input:          	own			�����û���Ϣ
					phead		�����ʽ���ˮ������Ϣ
					length		�����ʽ���ˮ����ڵ�����
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void show_balance_data(Own *own,Balance *phead,int length,int page_pointer)	//��ʾ����ѯ��������
{
	int i=0;
	Balance *temp;
	char temp_str[15];
	char time[7];
	
	temp=phead;
	settextjustify(CENTER_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	setcolor(LIGHTBLUE);
	for(i=0;i<5;i++)
	{
		sprintf(temp_str,"%.2lf",own->balance[i]);
		outtextxy(192+94*i,105,temp_str);
	}
	if(length<=0)
		return;
	while(page_pointer>0)
	{
		page_pointer--;
		length--;
		temp=temp->next;
	}
	i=1;
	while(length>0&&i<=4)
	{
		length--;
		settextstyle(2,0,6);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setcolor(LIGHTBLUE);
		sprintf(temp_str,"%ld",temp->deal_date);
		outtextxy(192+94*i,175,temp_str);			//�ɽ�����		
		sprintf(temp_str,"%d",temp->deal_time/100);
		strcpy(time,temp_str);
		strcat(time,":");
		sprintf(temp_str,"%d",temp->deal_time%100);
		strcat(time,temp_str);
		outtextxy(192+94*i,196,time);				//�ɽ�ʱ��
		outtextxy(192+94*i,217,temp->stockcode);	//֤ȯ����	
		sprintf(temp_str,"%ld",temp->deal_amount);	
		outtextxy(192+94*i,280,temp_str);			//�ɽ�����
		sprintf(temp_str,"%.2f",temp->deal_price_ave);
		outtextxy(192+94*i,301,temp_str);			//�ɽ�����
		sprintf(temp_str,"%.2lf",temp->deal_money);
		outtextxy(192+94*i,322,temp_str);			//�ɽ����
		sprintf(temp_str,"%.2lf",temp->deal_money_real);
		outtextxy(192+94*i,343,temp_str);			//�������
		sprintf(temp_str,"%.2f",temp->service_charge);
		outtextxy(192+94*i,364,temp_str);			//������
		sprintf(temp_str,"%.2f",temp->stamp_tax);
		outtextxy(192+94*i,385,temp_str);			//ӡ��˰
		sprintf(temp_str,"%.2lf",temp->balance_now);
		outtextxy(192+94*i,406,temp_str);			//���ν��		
		if(temp->flag==0)
			put_hz(175+94*i,255,"����",LIGHTBLUE,16,2);
		else
			put_hz(175+94*i,255,"����",LIGHTBLUE,16,2);
		put_hz(157+94*i,234,temp->stockname,LIGHTBLUE,16,1);//֤ȯ����
		temp=temp->next;
		i++;
	}
}


/*************************************************
  Function:			show_hold_data
  Description:   	չʾ�ֲֽ�����Ϣ
  Input:          	phead		���ݳֲ�������Ϣ
					length		���ݳֲ�����ڵ�����
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void show_hold_data(Hold *phead,int length,int page_pointer)
{
	int i=1;
	Hold *temp;
	char temp_str[15];
	char time[7];
	temp=phead;
	if(length<=0)
		return;
	while(page_pointer>0)
	{
		page_pointer--;
		length--;
		temp=temp->next;
	}
	while(length>0&&i<=6)
	{
		length--;
		settextstyle(2,0,6);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		setcolor(LIGHTBLUE);
		outtextxy(184+66*i,97,temp->stockcode);	//֤ȯ����	
		sprintf(temp_str,"%ld",temp->stock_amount);	
		outtextxy(184+66*i,139,temp_str);			//֤ȯ���	
		sprintf(temp_str,"%ld",temp->amount_avail);	
		outtextxy(184+66*i,160,temp_str);			//�������
		sprintf(temp_str,"%ld",temp->amount_blocked);	
		outtextxy(184+66*i,181,temp_str);			//��������	
		sprintf(temp_str,"%ld",temp->amount_real);	
		outtextxy(184+66*i,202,temp_str);			//��Ʊʵ��
		sprintf(temp_str,"%.2f",temp->deal_price);
		outtextxy(184+66*i,223,temp_str);			//�ɱ���
		sprintf(temp_str,"%.2f",temp->now_price);
		outtextxy(184+66*i,244,temp_str);			//�м�
		sprintf(temp_str,"%.2f",temp->profit_loss_);
		outtextxy(184+66*i,286,temp_str);			//����ӯ��
		sprintf(temp_str,"%.2f",temp->profit_loss_percent);
		strcat(temp_str,"%");
		outtextxy(184+66*i,307,temp_str);			//ӯ������
		sprintf(temp_str,"%.2f",temp->position);
		strcat(temp_str,"%");
		outtextxy(184+66*i,328,temp_str);			//��λ	
		settextstyle(2,0,5);
		sprintf(temp_str,"%.2lf",temp->market_value);
		outtextxy(184+66*i,265,temp_str);			//��ֵ
		put_hz(151+66*i,111,temp->stockname,LIGHTBLUE,16,1);//֤ȯ����
		temp=temp->next;
		i++;
	}
}

/*************************************************
  Function:			recall_num
  Description:   	����ɾ���Ľڵ��ñ�־λ
  Input:          	my			���ݵ�ǰ�����λ��
					flag_delet	��ɾ���ڵ��־
					length		����ί������ڵ�����
					page_pointer���ݵ�ǰ��һ������λ��
  Return:         	void
*************************************************/

void recall_num(int my,int *flag_delet,int length,int page_pointer)
{	
	int num;
	num=(my-112)/20;
	if(flag_delet[num-1]==0&&num<=length-page_pointer&&num<=14)
	{
		setfillstyle(1,BLACK);
		bar(596,116+num*20,608,128+num*20);
		flag_delet[num-1]=num;
	}
	else if(flag_delet[num-1]==num&&num<=length-page_pointer&&num<=14)
	{
		setfillstyle(1,WHITE);
		bar(596,116+num*20,608,128+num*20);
		flag_delet[num-1]=0;
	}
}

/*************************************************
  Function:			delet_delegate
  Description:   	����ĳЩ��Ʊ
  Input:          	own			�����û���Ϣ
					flag_delet	��ɾ���ڵ��־
					phead		����ί��������Ϣ
					length		����ί��������
					page_pointer���ݵ�ǰ��һ������λ��
					hold		���ݳֲ�����
  Return:         	void
*************************************************/

void delet_delegate(Own *own,int *flag_delet,Delegate *phead,int *length,int page_pointer,Hold *hold)	//����
{
	Hold *hold_temp;
	int i=0,j,k=0;
	Delegate *pn;
	pn=phead;
	while(page_pointer>0)
	{
		k++;
		if(pn->delet_flag==0&&pn->flag_==0)
		{
			page_pointer--;
		}
		pn=pn->next;
	}
	for(j=0,i=0;j<length[0]-k;j++)
	{
		if(pn->delet_flag==1||pn->flag_==1)				//����ýڵ�֮ǰ�Ѿ��������߳ɽ��򲻼��뱾�γ�����Χ
		{
			pn=pn->next;
			continue;
		}
		else if(flag_delet[i]==0&&pn->delet_flag==0&&pn->flag_==0)//����ýڵ�˴�δ��������֮ǰҲδ��������Ҳδ�ɽ�
		{
			pn=pn->next;
			i++;
		}
		else if(flag_delet[i]==i+1&&pn->delet_flag==0&&pn->flag_==0)//�ýڵ�˴�ɾ����֮ǰδɾ��Ҳδ�ɽ�
		{
			pn->delet_flag=1;       							//��־flag��һ��ʾ�Ѿ�������
			if(pn->flag==0)
			{
				own->balance[2]-=1.003*(double)(pn->dele_amount*pn->dele_price);	//��������ⶳ
				own->balance[0]=own->balance[1]-own->balance[2];	//���ý��=�ʽ����-������
			}
			else if(pn->flag==1)
			{
				hold_temp=find_hold(hold,length[1],pn->stockcode);
				hold_temp->amount_blocked-=pn->dele_amount;
				hold_temp->amount_avail=hold_temp->amount_real-hold_temp->amount_blocked;
			}
			pn=pn->next;
			i++;
		}
	}
	for(i=0;i<14;i++)		//���ڳ�����һ����Ϣ������length��ά��
	{
		if(flag_delet[i]==i+1)
			length[4]--;
		flag_delet[i]=0;
	}
	page2_draw(0);
	setcolor(WHITE);
	line(158,95,256,95);
	line(278,95,329,95);
	put_hz(158,70,"ȫ��ѡ��",WHITE,24,1);
	put_hz(278,70,"����",WHITE,24,4);
	show_recall_data(phead,length[0],page_pointer);
	rewrite_own(own);
	rewrite_hold(own,hold,length[1]);
	write_delegate(own,phead,length[0]);
}

/*************************************************
  Function:			free_all
  Description:   	�ͷ���������ڵ�
  Input:          	phead_1		����ί��������Ϣ
					phead_2		���ݳֲ�������Ϣ
					phead_3		�����ʽ���ˮ������Ϣ
					phead_4		���ݽ���������Ϣ
					length		��������ڵ�����
  Return:         	void
*************************************************/

void free_all(Delegate *phead_1,Hold *phead_2,Balance *phead_3,Deal *phead_4,int *length)//�˳��ý���ʱ�ͷ����нڵ�
{
	free_delegate(phead_1,length[0]);
	free_hold(phead_2,length[1]);
	free_balance(phead_3,length[2]);
	free_deal(phead_4,length[3]);
}

/*************************************************
  Function:			free_delegate
  Description:   	�ͷ�ί������ڵ�
  Input:          	phead		����ί��������Ϣ
					length		��������ڵ�����
  Return:         	void
*************************************************/

void free_delegate(Delegate *phead,int length)
{
	Delegate *pm,*pn;
	pn=phead;
	while(length>0)
	{
		pm=pn;
		pn=pn->next;
		free(pm);
		length--;
	}
}

/*************************************************
  Function:			free_hold
  Description:   	�ͷųֲ�����ڵ�
  Input:          	phead		���ݳֲ�������Ϣ
					length		��������ڵ�����
  Return:         	void
*************************************************/

void free_hold(Hold *phead,int length)
{
	Hold *pm,*pn;
	pn=phead;
	while(length>0)
	{
		pm=pn;
		pn=pn->next;
		free(pm);
		length--;
	}
}

/*************************************************
  Function:			free_balance
  Description:   	�ͷ��ʽ���ˮ����ڵ�
  Input:          	phead		�����ʽ���ˮ������Ϣ
					length		��������ڵ�����
  Return:         	void
*************************************************/

void free_balance(Balance *phead,int length)
{
	Balance *pm,*pn;
	pn=phead;
	while(length>0)
	{
		pm=pn;
		pn=pn->next;
		free(pm);
		length--;
	}
}

/*************************************************
  Function:			free_deal
  Description:   	�ͷŽ�������ڵ�
  Input:          	phead		���ݽ���������Ϣ
					length		��������ڵ�����
  Return:         	void
*************************************************/

void free_deal(Deal *phead,int length)
{
	Deal *pm,*pn;
	pn=phead;
	while(length>0)
	{
		pm=pn;
		pn=pn->next;
		free(pm);
		length--;
	}
}

/*************************************************
  Function:			get_recall_num
  Description:   	��ȡĿǰ�Կ��Խ��г���������ί����Ϣ����
  Input:          	phead			����ί��������Ϣ
					length_all		����ί�нڵ�������
					length_recall	�ɳ���ί�нڵ�����
  Return:         	void
*************************************************/

void get_recall_num(Delegate *phead,int length_all,int *length_recall)			//��ȡ������һ������ʣ������
{
	Delegate *pn;
	pn=phead;
	*length_recall=0;
	while(length_all>0)
	{
		if(pn->delet_flag==0&&pn->flag_==0)				//����ýڵ�֮ǰ�Ѿ��������߳ɽ��򲻼��뱾�γ�����Χ
		{
			(*length_recall)++;
		}
		pn=pn->next;
		length_all--;
	}
}

/*************************************************
  Function:			get_today_deal
  Description:   	��ȡ���ճɽ���Ϣ����
  Input:          	phead			���ݽ���������Ϣ
					length_all		���ݽ��׽ڵ�������
					length_today	���ս��׽ڵ�����
					time_p			�ɽ�ʱ��
  Return:         	void
*************************************************/

void get_today_deal(Deal *phead,int length_all,int *length_today,struct tm time_p)
{
	Deal *pn;
	long time=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1)*100+(long)time_p.tm_mday;
	pn=phead;
	*length_today=0;
	while(length_all>0)
	{
		if(pn->deal_date==time)
		{
			(*length_today)++;
		}
		if(pn->deal_date==time&&pn->pre->deal_time!=time)	//�ýڵ�ʱ��Ϊ���գ�ǰ��ʱ�䲻Ϊ���գ�֤�����ǽ��ճɽ������һ��
		{
			break;
		}
		pn=pn->pre;
		length_all--;
	}
}

/*************************************************
  Function:			page_up_down
  Description:   	������ת��ʾҳ��
  Input:          	info			���ݵ�ǰ����ֵ
					own				�������ʲ���Ϣ
					flag			���ݵ�ǰҳ��ֵ
					time_p			���ݵ�ǰ����
					page_pointer	���ݵ�ǰ��һ������λ��
					all_length		��������ڵ���������
					phead_1			����ί��������Ϣ
					phead_2			���ݳֲ�������Ϣ
					phead_3			�����ʽ���ˮ������Ϣ
					phead_4			���ݽ���������Ϣ
  Return:         	void
*************************************************/

void page_up_down(INFO *info,Own *own,int flag,struct tm time_p,int *page_pointer,int *all_length,Delegate *phead_1,Hold *phead_2,Balance *phead_3,Deal *phead_4)
{
	int differ_pos,length,num;
	if(flag==3)				//����
	{
		differ_pos=14;
		length=all_length[4];
	}
	else if(flag==43)
	{
		differ_pos=14;
		length=all_length[0];
	}
	else if(flag==42)		//���ճɽ�
	{
		differ_pos=13;
		length=all_length[5];
	}
	else if(flag==44)
	{
		differ_pos=13;
		length=all_length[3];
	}
	else if(flag==41)
	{
		differ_pos=4;
		length=all_length[2];
	}
	else if(flag==45)
	{
		differ_pos=6;
		length=all_length[1];
	}
	if(flag==1||flag==2||flag==4||flag==5)
	{
		return;
	}
	else if(info->key.num==UP&&*page_pointer>=differ_pos)		//��һҳ
	{
		*page_pointer-=differ_pos;
	}
	else if(info->key.num==DOWN&&*page_pointer+differ_pos<length)
	{
		*page_pointer+=differ_pos;
	}
	else
	{
		return;
	}
	page_draw(flag);	//�����ǰpage_pointerδ���������Ͳ����л�����
	num=*page_pointer;
	switch(flag)
	{
		case 1:
				break;
		case 2:
				break;
		case 3:show_recall_data(phead_1,all_length[0],num);
				break;
		case 4:
				break;
		case 41:show_balance_data(own,phead_3,all_length[2],num);
				break;
		case 42:show_tod_deal(phead_4,all_length[3],num,time_p);
				break;
		case 43:show_delegate_data(phead_1,all_length[0],num);
				break;
		case 44:show_his_deal(phead_4,all_length[3],num);
				break;
		case 45:show_hold_data(phead_2,all_length[1],num);
				break;
		case 5:
				break;
		case 51:
				break;
		case 52:
				break;
	}
}

/*************************************************
  Function:			rewrite_own
  Description:   	�����û��ļ�
  Input:          	own			�����û���Ϣ
  Return:         	void
*************************************************/

void rewrite_own(Own *own)			//own�ļ�������д��
{
	char temp_str[40];
	double balance_temp[5];
	FILE *fp;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own->account);
	strcat(temp_str,"\\");
	strcat(temp_str,"own.txt");
	if((fp=fopen(temp_str,"rb+"))==NULL)
	{
		printf("can't open the file while rewrite the own.txt!\n");
		getch();
		exit(1);
	}
	fseek(fp,30L,SEEK_SET);
	fread(&balance_temp[0],sizeof(double),1,fp);
	fread(&balance_temp[1],sizeof(double),1,fp);
	fread(&balance_temp[2],sizeof(double),1,fp);
	fread(&balance_temp[3],sizeof(double),1,fp);
	fread(&balance_temp[4],sizeof(double),1,fp);
	fseek(fp,30L,SEEK_SET);
	fwrite(&(own->balance[0]),sizeof(double),1,fp);
	fwrite(&(own->balance[1]),sizeof(double),1,fp);
	fwrite(&(own->balance[2]),sizeof(double),1,fp);
	fwrite(&(own->balance[3]),sizeof(double),1,fp);
	fwrite(&(own->balance[4]),sizeof(double),1,fp);
	fclose(fp);
}

/*************************************************
  Function:			renew_own
  Description:   	����֤ȯ���
  Input:          	own			�����û���Ϣ
					hold		���ݽ���������Ϣ
					length		���ݽ��׽ڵ�����
  Return:         	void
*************************************************/

void renew_own(Own *own,Hold *hold,int length)
{
	Hold *temp;
	int i;
	own->balance[3]=0;
	temp=hold;
	for(i=0;i<length;i++)
	{
		own->balance[3]+=temp->market_value;
		temp=temp->next;
	}
	own->balance[4]=own->balance[1]+own->balance[3];
	rewrite_own(own);
}

/*************************************************
  Function:			rewrite_balance
  Description:   	�����ʽ���ˮ�ļ�
  Input:          	own			�����û���Ϣ
					phead		�����ʽ���ˮ������Ϣ
					length		�����ʽ���ˮ�ڵ�����
  Return:         	void
*************************************************/

void rewrite_balance(Own *own,Balance *phead,int length)
{
	Balance *balance;
	char temp_str[40];
	int i;
	FILE *fp;
	if(phead->pre!=NULL)
	{
		balance=phead->pre;
	}
	else if(phead->pre==NULL)
	{
		balance=phead;
	}
	
	rewrite_own(own);
	
	balance=phead;									//֮ǰ��balanceָ��ǰ����Ϊ���ҵ����һ�ʳɽ�
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own->account);
	strcat(temp_str,"\\");
	strcat(temp_str,"balance.txt");
	if((fp=fopen(temp_str,"wt"))==NULL)
	{
		printf("can't open the file while renew the balance.txt!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fprintf(fp,"%d",length);
	fprintf(fp,"%c",'\n');
	//fwrite(&length,sizeof(int),1,fp);
	//fwrite("\n",1,1,fp);
	for(i=0;i<length;i++)
	{
		fprintf(fp,"%ld %d %s %s %d %d %ld %.2f %.2lf %.2lf %.2f %.2f %.2lf",
				   balance->deal_date,balance->deal_time,balance->stockname,balance->stockcode,balance->flag,
				   balance->flag_point,balance->deal_amount,balance->deal_price_ave,balance->deal_money,
				   balance->deal_money_real,balance->service_charge,balance->stamp_tax,balance->balance_now);
		//fwrite("\n",1,1,fp);
		fprintf(fp,"%c",'\n');
		balance=balance->next;
	}
	fclose(fp);
}

/*************************************************
  Function:			rewrite_hold
  Description:   	���³ֲ��ļ�
  Input:          	own			�����û���Ϣ
					phead		���ݳֲ�������Ϣ
					length		���ݳֲֽڵ�����
  Return:         	void
*************************************************/

void rewrite_hold(Own *own,Hold *phead,int length)
{
	Hold *hold;
	char temp_str[40];
	int i;
	FILE *fp;
	hold=phead;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own->account);
	strcat(temp_str,"\\");
	strcat(temp_str,"hold.txt");
	if((fp=fopen(temp_str,"wt"))==NULL)
	{
		printf("can't open the file while renew the hold.txt!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fprintf(fp,"%d",length);
	fprintf(fp,"%c",'\n');
	//fwrite(&length,sizeof(int),1,fp);
	//fwrite("\n",1,1,fp);
	for(i=0;i<length;i++)
	{
		fprintf(fp,"%s %s %ld %ld %ld %ld %.2f %.2f %.2lf %.2lf %.2f %.2f %.2f",
				   hold->stockname,hold->stockcode,hold->stock_amount,hold->amount_avail,
				   hold->amount_blocked,hold->amount_real,hold->deal_price,hold->now_price,hold->hold_spend,
				   hold->market_value,hold->profit_loss_,hold->profit_loss_percent,hold->position);
		//fwrite("\n",1,1,fp);
		fprintf(fp,"%c",'\n');
		hold=hold->next;
	}
	fclose(fp);
}

/*************************************************
  Function:			rewrite_deal
  Description:   	���½����ļ�
  Input:          	own			�����û���Ϣ
					phead		���ݽ���������Ϣ
					length		���ݽ��׽ڵ�����
  Return:         	void
*************************************************/

void rewrite_deal(Own *own,Deal *phead,int length)
{
	Deal *deal;
	char temp_str[40];
	int i;
	FILE *fp;
	deal=phead;
	strcpy(temp_str,"USER\\");
	strcat(temp_str,own->account);
	strcat(temp_str,"\\");
	strcat(temp_str,"deal.txt");
	if((fp=fopen(temp_str,"wt"))==NULL)
	{
		printf("can't open the file while rewrite the deal.txt!\n");
		getch();
		exit(1);
	}
	rewind(fp);
	fprintf(fp,"%d",length);
	fprintf(fp,"%c",'\n');
	//fwrite(&length,sizeof(int),1,fp);
	//fwrite("\n",1,1,fp);
	for(i=0;i<length;i++)
	{
		fprintf(fp,"%ld %d %s %s %d %ld %f %lf",
				   deal->deal_date,deal->deal_time,deal->stockname,deal->stockcode,
				   deal->flag,deal->deal_amount,deal->deal_price_ave,deal->deal_money);
		//fwrite("\n",1,1,fp);
		fprintf(fp,"%c",'\n');
		deal=deal->next;
	}
	fclose(fp);
}

/*************************************************
  Function:			test_balance
  Description:   	ʵʱ�����жϺ���
  Input:          	own			�����û���Ϣ
					delegate	����ί��������Ϣ
					phead		�����ʽ���ˮ������Ϣ
					hold		���ݳֲ�������Ϣ
					time_p		���ݵ�ǰ������ʱ��
					length		���ݸ�����ڵ�����
  Return:         	Balance
*************************************************/

Balance *test_balance(Own *own,Delegate *delegate,Balance *phead,Hold *hold,struct tm time_p,int *length)
{
	Delegate *temp;
	int i;
	int time_temp;
	int region_length=length[2];
	temp=delegate;
	for(i=0;i<length[0];i++)	//�ж���û��δ���׵���δ����
	{
		if(temp->flag_==0&&temp->delet_flag==0&&judge_deal(temp,time_p,&time_temp)==1)
		{
			temp->flag_=1;
			phead=balance_new_add(own,temp,phead,time_temp,length,hold);
			++length[2];
			--length[4];
		}
		temp=temp->next;
	}
	if(region_length!=length[2])
	{
		rewrite_balance(own,phead,length[2]);
		write_delegate(own,delegate,length[0]);
		rewrite_own(own);
		rewrite_hold(own,hold,length[1]);
	}
	return phead;
}

/*************************************************
  Function:			balance_new_add
  Description:   	ʵʱ�����жϺ���
  Input:          	own			�����û���Ϣ
					delegate	����ί��������Ϣ
					phead		�����ʽ���ˮ������Ϣ
					hold		���ݳֲ�������Ϣ
					time_p		���ݵ�ǰ������ʱ��
					length		���ݸ�����ڵ�����
  Return:         	Balance
*************************************************/

Balance *balance_new_add(Own *own,Delegate *delegate,Balance *phead,int time_temp,int *length,Hold *hold)
{
	Balance *temp,*balance;
	Hold *temp_hold;
	if((balance=(Balance *)malloc(sizeof(Balance)))==NULL)
	{
		printf("Allocation of balance failed!!!");
		getch();
		exit(1);
	}
	balance->deal_date=delegate->date;
	balance->deal_time=time_temp;
	strcpy(balance->stockname,delegate->stockname);
	strcpy(balance->stockcode,delegate->stockcode);
	balance->flag=delegate->flag;
	balance->flag_point=0;	//�ո��ж����Ƿ�ɽ��ɹ��Ĺ�Ʊ���ǲ���Ծ�����Ʊ
	balance->deal_amount=delegate->dele_amount;
	balance->deal_money=(double)(delegate->dele_amount*delegate->dele_price);
	balance->service_charge=(float)(0.003*balance->deal_money);//��ȡǧ��֮����ӡ��˰
	if(balance->flag==1)	//��������ȡǧ��֮һ��ӡ��˰
	{
		balance->stamp_tax=(float)(0.001*balance->deal_money);
	}
	else if(balance->flag==0)
	{
		balance->stamp_tax=(float)(0.00);
	}
	if(balance->flag==0)
	{
		balance->deal_money_real=balance->deal_money+(double)(balance->service_charge+balance->stamp_tax);
	}
	else if(balance->flag==1)
	{
		balance->deal_money_real=balance->deal_money-(double)(balance->service_charge-balance->stamp_tax);
	}
	balance->deal_price_ave=(float)(balance->deal_money_real/balance->deal_amount);
	if(balance->flag==1)
	{
		own->balance[1]+=balance->deal_money_real;
		temp_hold=find_hold(hold,length[1],balance->stockcode);
		temp_hold->amount_blocked-=balance->deal_amount;
		temp_hold->amount_real-=balance->deal_amount;
		temp_hold->amount_avail=temp_hold->amount_real-temp_hold->amount_blocked;
	}
	else if(balance->flag==0)
	{
		own->balance[1]-=balance->deal_money_real;
		if(fabs(own->balance[2]-balance->deal_money_real)<0.01)
		{
			own->balance[2]=0.00;
		}
		else
		{
			if(fabs(own->balance[2]-balance->deal_money_real)<0.01)
			{
				own->balance[2]=0.00;
			}
			else
			{
				own->balance[2]-=balance->deal_money_real;//��������룬֮ǰ�Ķ�����ⶳ
			}
		}
	}
	own->balance[0]=own->balance[1]-own->balance[2];//�������=�ʽ����-������
	balance->balance_now=own->balance[1];
	if(phead==NULL)
	{
		phead=balance;
		phead->pre=NULL;
		phead->next=NULL;
	}
	else if(phead->next==NULL)
	{
		phead->next=balance;
		phead->pre=balance;
		balance->next=phead;
		balance->pre=phead;
	}
	else
	{
		temp=phead->pre;		//��temp���浱ǰ���һ���ڵ�
		temp->next=balance;		//����ǰ���һ���ڵ�ĺ��ָ��balance������ӵĽڵ�
		balance->next=phead;	//���½ڵ�ĺ��ָ��ͷ�ڵ�
		balance->pre=temp;		//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
		phead->pre=balance;		//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
	}
	return phead;
}

/*************************************************
  Function:			deal_new_add
  Description:   	����½�����Ϣ
  Input:          	own			�����û���Ϣ
					phead		���ݽ���������Ϣ
					balance		�����ʽ���ˮ������Ϣ
					length		��������ڵ�����
					length_pre	����δ�ɽ�֮ǰ���׽ڵ�����
  Return:         	Deal
*************************************************/

Deal *deal_new_add(Own *own,Deal *phead,Balance *pnode,int *length,int length_pre)
{
	Deal *temp,*deal;
	Balance *balance;
	int i;
	balance=pnode;
	for(i=0;i<length_pre;i++)	//��֮ǰ��length_preΪ0ʱ��balance=pnode
		balance=balance->next;
	for(i=length_pre;i<length[2];i++)
	{
		(length[3])++;

		if((deal=(Deal *)malloc(sizeof(Deal)))==NULL)
		{
			printf("Allocation of deal failed!!!!!");
			getch();
			exit(1);
		}
		strcpy(deal->stockname,balance->stockname);
		strcpy(deal->stockcode,balance->stockcode);
		deal->deal_amount=balance->deal_amount;
		deal->deal_money=balance->deal_money;
		deal->deal_price_ave=balance->deal_price_ave;
		deal->deal_date=balance->deal_date;
		deal->deal_time=balance->deal_time;
		deal->flag=balance->flag;
		if(phead==NULL)
		{
			phead=deal;
			phead->pre=NULL;
			phead->next=NULL;
		}
		else if(phead->next==NULL)
		{
			phead->next=deal;
			phead->pre=deal;
			deal->next=phead;
			deal->pre=phead;
		}
		else
		{
			temp=phead->pre;	//��temp���浱ǰ���һ���ڵ�
			temp->next=deal;	//����ǰ���һ���ڵ�ĺ��ָ��deal������ӵĽڵ�
			deal->next=phead;	//���½ڵ�ĺ��ָ��ͷ�ڵ�
			deal->pre=temp;		//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
			phead->pre=deal;	//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
		}
		balance=balance->next;
	}
	rewrite_deal(own,phead,length[3]);
	return phead;
}

/*************************************************
  Function:			delet_hold
  Description:   	���ĳһ֧��Ʊ�ֲ�Ϊ0��ɾ��
  Input:          	length		���ݳֲ�������
					hold		���ݳֲ�������Ϣ
  Return:         	Hold
*************************************************/

Hold *delet_hold(int *length,Hold *hold)
{
	int i=0,j=0,length_pre;
	Hold *temp,*pnode;
	temp=hold;
	length_pre=length[1];
	for(j=0;j<length_pre;j++)
	{
		if(temp->stock_amount==0)
		{
			if(length[1]==1)
			{
				length[1]=0;
				free(temp);
				return hold;
			}
			else if(i==0)
			{
				hold=hold->next;
			}
			
			if(length[1]==2)
			{
				hold->next=NULL;
				hold->pre=NULL;
				free(temp);
				temp=hold;
				--i;
				--length[1];
				continue;
			}
			else if(length[1]!=2)
			{
				pnode=temp->next;
				pnode->pre=temp->pre;
				temp->pre->next=pnode;
				free(temp);
				temp=pnode;
				--i;
				--length[1];
				continue;
			}
		}
		temp=temp->next;
		i++;
	}
	return hold;
}

/*************************************************
  Function:			hold_new_add
  Description:   	����³ֲ���Ϣ
  Input:          	own			�����û���Ϣ
					phead		���ݳֲ�������Ϣ
					pnode		�����ʽ���ˮ������Ϣ
					length		��������ڵ�����
					time_p		���ݵ�ǰ������ʱ��
					length_pre	����δ�ɽ�֮ǰ���׽ڵ�����
  Return:         	Hold
*************************************************/

Hold *hold_new_add(Own *own,Balance *pnode,Hold *phead,int *length,struct tm time_p,int length_pre)
{
	Hold *temp,*hold;
	Balance *balance;
	int i,j,flag=0;
	balance=pnode;
	for(i=0;i<length_pre;i++)	//��֮ǰ��length_preΪ0ʱ��balance=pnode
		balance=balance->next;
	for(i=length_pre;i<length[2];i++)	//��������balance����ӵĽڵ㣬�����н�����Ϣ��ӵ��ֲ���ȥ
	{
		temp=phead;
		for(j=0;j<length[1];j++)		//�������гֲֽڵ㣬����иù�Ʊ�ڵ��ֱ�����û�����½�һ���ڵ�
		{
			if(strcmp(temp->stockcode,balance->stockcode)==0)
			{
				if(balance->flag==0)
				{
					temp->stock_amount+=balance->deal_amount;		//֤ȯ���
					temp->hold_spend+=balance->deal_money;		//�ܻ���
					temp->amount_blocked+=balance->deal_amount;
				}
				else if(balance->flag==1)
				{
					temp->stock_amount-=balance->deal_amount;
					temp->hold_spend-=balance->deal_money;
				}
				temp->amount_avail=temp->stock_amount-temp->amount_blocked;		//��������
				temp->amount_real=temp->stock_amount;							//��Ʊʵ��
				if(temp->stock_amount!=0)
				{
					temp->deal_price=(float)(temp->hold_spend/temp->stock_amount);	//�ɱ���
				}
				else
					temp->deal_price=1e-6;
				temp->now_price=get_now_price(temp->stockcode,time_p);    		//�м�
				temp->market_value=(double)(temp->now_price*temp->stock_amount);//��ֵ
				if(fabs(temp->market_value-temp->hold_spend)<0.01)
				{
					temp->profit_loss_=0.00;
				}
				else
				{
					temp->profit_loss_=(float)(temp->market_value-temp->hold_spend);			//����ӯ��
				}
				temp->profit_loss_percent=(float)((temp->market_value-temp->hold_spend)*100/temp->hold_spend);//ӯ������
				temp->position=(float)(temp->market_value/own->balance[4]);				//��λ
				flag=1;
				break;
			}
			temp=temp->next;
		}
		if(flag==0)	//flagΪ0֤��û���ҵ��ù�Ʊ��hold��
		{
			if((temp=(Hold *)malloc(sizeof(Hold)))==NULL)
			{
				printf("Allocation of hold failed!!!");
				getch();
				exit(1);
			}
			(length[1])++;
			/**����һ���½�����hold�ڵ㲻����֮ǰ�й�Ʊ��������Ҫ�ⶳ��������Բ���Ҫ����**/
			/**�½����Ľڵ�һ����Ϊ�������Ʊ**/
			strcpy(temp->stockname,balance->stockname);
			strcpy(temp->stockcode,balance->stockcode);
			temp->stock_amount=balance->deal_amount;		//֤ȯ���
			temp->hold_spend=balance->deal_money;			//�ܻ���
			temp->amount_blocked=temp->stock_amount;		//��������
			temp->amount_avail=0;							//�������
			temp->amount_real=temp->stock_amount;			//��Ʊʵ��
			temp->deal_price=(float)(balance->deal_money/balance->deal_amount);		//�ɱ���
			temp->now_price=get_now_price(temp->stockcode,time_p);    		//�м�
			temp->market_value=(double)(temp->now_price*temp->stock_amount);//��ֵ
			if(fabs(temp->market_value-temp->hold_spend)<0.01)
			{
				temp->profit_loss_=0.00;
			}
			else
			{
				temp->profit_loss_=(float)(temp->market_value-temp->hold_spend);			//����ӯ��
			}
			temp->profit_loss_percent=(float)((temp->market_value-temp->hold_spend)*100/temp->hold_spend);//ӯ������
			temp->position=(float)(temp->market_value*100/own->balance[4]);	//��λ
			if(phead==NULL)
			{
				phead=temp;
				phead->pre=NULL;
				phead->next=NULL;
			}
			else if(phead->next==NULL)
			{
				phead->next=temp;
				phead->pre=temp;
				temp->next=phead;
				temp->pre=phead;
			}
			else
			{
				hold=phead->pre;	//��temp���浱ǰ���һ���ڵ�
				hold->next=temp;	//����ǰ���һ���ڵ�ĺ��ָ��hold������ӵĽڵ�
				temp->next=phead;	//���½ڵ�ĺ��ָ��ͷ�ڵ�
				temp->pre=hold;		//���½ڵ��ǰ��ָ��֮ǰ��β�ڵ�
				phead->pre=temp;	//��ͷ����ǰ��ָ��ǰ���һ���ڵ�
			}
		}
		balance=balance->next;
	}
	
	balance=pnode;
	if(phead==NULL)
		return phead;
	for(i=0;i<length[2];i++)				//�ȱ�������balance�ڵ��ж��Ƿ��й�Ʊ�Ӷ����ɲ�����
	{
		temp=phead;
		flag=0;
		for(j=0;j<length[1];j++)			//�������гֲֽڵ㣬����иù�Ʊ�ڵ��ֱ�����û�����½�һ���ڵ�
		{
			if(strcmp(temp->stockcode,balance->stockcode)==0)
			{
				if(balance->flag==0&&balance->flag_point==0&&balance->deal_date<((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1)*100+(long)time_p.tm_mday)
				{
					balance->flag_point=1;	//����Ʊ��ɻ�Ծ��Ʊ
					temp->amount_avail+=balance->deal_amount;
					temp->amount_blocked-=balance->deal_amount;//��־λ��ʾ�Ѿ��ҵ�hold���Խ�������ѭ��
				}
				flag=1;
				temp->now_price=get_now_price(temp->stockcode,time_p);    		//�м�
				temp->market_value=(double)(temp->now_price*temp->stock_amount);//��ֵ
				temp->profit_loss_=(float)(temp->market_value-temp->hold_spend);//����ӯ��
				temp->profit_loss_percent=(float)((temp->market_value-temp->hold_spend)*100/temp->hold_spend);//ӯ������
				temp->position=(float)(temp->market_value*100/own->balance[4]);	//��λ
			}

			if(flag==1)
				break;
			temp=temp->next;				//ֱ���ҵ���Ʊ��Ӧ�ֲ�Ϊֹ
		}
		balance=balance->next;
	}	
	phead=delet_hold(length,phead);
	rewrite_balance(own,pnode,length[2]);	//��������Ʊ״̬�ı�
	rewrite_hold(own,phead,length[1]);
	renew_own(own,phead,length[1]);
	return phead;
}

/*************************************************
  Function:			judge_deal
  Description:   	�ж��Ƿ��׳ɹ�
  Input:          	pnode		����ί��������Ϣ
					time_p		���ݵ�ǰ������ʱ��
					time		���سɽ�ʱ��
  Return:         	int
*************************************************/

int judge_deal(Delegate *pnode,struct tm time_p,int *time)		//�ж�Ŀǰ�Ƿ��׳ɹ������׳ɹ�����1�����򷵻�0
{
	char temp_str[40];
	long date_temp=pnode->date;
	int time_temp;
	FILE *fp;
	char time_1[9],time_2[9],kai[7],shou[7],gao[7],di[7],str1[15],str2[20];
	strcpy(temp_str,"data\\MIN\\1MIN\\TXT\\");
	strcat(temp_str,pnode->stockcode);
	strcat(temp_str,".txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file 1MIN.txt of the stock while judge the deal!\n");
		fclose(fp);
		getch();
		exit(1);
	}
	//!!!!!!�ǵø�ʱ��Ŷ
	//time_temp=1500;
	if(date_temp==((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon+1)*100+(long)time_p.tm_mday&&(100*(time_p.tm_hour)+time_p.tm_min)<=1500)	//ί��ʱ��ڵ�ǡ��Ϊ����,����Ŀǰʱ�䲻��������
	{
		time_temp=100*(time_p.tm_hour)+time_p.tm_min;
	}
	else
	{
		time_temp=1500;
	}
	while(1)
	{
		fscanf(fp,"%s %s %s %s %s %s %s %s",time_1,time_2,kai,gao,di,shou,str1,str2);
		if(atol(time_1)>date_temp-197)
		{
			continue;
		}
		else if(atol(time_1)<date_temp-197)
		{
			fclose(fp);
			return(0);
		}
		else if(atol(time_1)==date_temp-197&&atol(time_2)>time_temp)			//��ȡ����ʱ��Ϊ���쵫��Сʱ�����Ѿ�����
		{
			fclose(fp);
			return(0);
		}
		else if(atol(time_1)==date_temp-197&&atoi(time_2)>=901&&atoi(time_2)<=time_temp&&fabs(atof(shou)-pnode->dele_price)<0.01)	//��Ϊbc����洢���ⲻ��������ȫ���
		{
			*time=atoi(time_2);
			fclose(fp);
			return(1);
		}
	}
}

/*************************************************
  Function:			get_now_price
  Description:   	��ȡ�ּ�
  Input:          	str     	���ݹ�Ʊ����
					time_p		���ݵ�ǰ������ʱ��
  Return:         	float 
*************************************************/

float get_now_price(char str[7],struct tm time_p)			//��ȡĿǰ�м�
{
	char temp_str[50],time_1[9],time_2[9],kai[7],shou[7],gao[7],di[7],str1[15],str2[20];
	long date_temp;
	int time_temp=100*(time_p.tm_hour)+time_p.tm_min;
	FILE *fp;
	strcpy(temp_str,"data\\MIN\\1MIN\\TXT\\");
	strcat(temp_str,str);
	strcat(temp_str,".txt");
	if((fp=fopen(temp_str,"rt"))==NULL)
	{
		printf("can't find the file 1MIN.txt of the stock while get the price!\n");
		getch();
		exit(1);
	}
	if(time_temp<=930)
	{
		date_temp=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon)*100+(long)time_p.tm_mday-98;
		time_temp=1500;
	}
	else if(time_temp>1130&&time_temp<=1300)
	{
		date_temp=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon)*100+(long)time_p.tm_mday-98;
		time_temp=1130;
	}
	else if(time_temp>1500)
	{
		date_temp=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon)*100+(long)time_p.tm_mday-97;
		time_temp=1500;
	}
	else
	{
		date_temp=((long)time_p.tm_year+1900)*10000+((long)time_p.tm_mon)*100+(long)time_p.tm_mday-97;
	}
	while(1)
	{
		fscanf(fp,"%s %s %s %s %s %s %s %s",time_1,time_2,kai,gao,di,shou,str1,str2);
		if(atol(time_1)>date_temp)
			continue;
		else if(atol(time_1)<date_temp)
		{
			printf("can not find the date of that day!!!!!!");
			fclose(fp);
			getch();
			//exit(1);
		}
		else if(atol(time_1)==date_temp&&atoi(time_2)==time_temp)
		{
			fclose(fp);
			return(atof(shou));
		}
	}
}

/*************************************************
  Function:			recharge
  Description:   	��ֵ�ܿغ���
  Input:          	own			�����û���Ϣ
					flag		�����־λ
					flag_last	��һ�����־
  Return:         	void 
*************************************************/

void recharge(Own *own,int *flag,int *flag_last)
{
	int mx,my,mbuttn,page;
	char password[10]={'\0'},rech_amount[10]={'\0'};
	settextstyle(1,0,3);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setcolor(BLACK);
	outtextxy(320,138,own->account);
	while(1)
	{
		newmouse(&mx,&my,&mbuttn);
		if(*flag==6)
		{
			page_judge_1(flag_last,flag,mx,my,mbuttn);
		}
		else if(*flag==5)
		{
			page_judge_3(flag_last,flag,mx,my,mbuttn);
		}
		else if(*flag==4)
		{
			page_judge_2(flag_last,flag,mx,my,mbuttn);
		}
		else
		{
			mousehide(mx,my);
			break;
		}
		if(*flag_last!=*flag)
		{
			page=*flag;
			page_draw(page);
			*flag_last=*flag;
		}
		if(mouse_press(317,186,550,218,&mx,&my,&mbuttn))
		{
			setfillstyle(1,WHITE);
			bar(318,187,549,217);
			input(320,190,9,1,BLACK,WHITE,password,0);
		}
		else if(mouse_press(317,246,550,278,&mx,&my,&mbuttn))
		{
			setfillstyle(1,WHITE);
			bar(318,247,549,277);
			input(320,250,9,1,BLACK,WHITE,rech_amount,0);
		}
		else if(mouse_press(310,300,368,332,&mx,&my,&mbuttn)&&strcmp(password,"")&&strcmp(rech_amount,""))
		{
			judge_rech(password,rech_amount,own);
			page_draw(6);
			setcolor(BLACK);
			settextstyle(1,0,3);
			settextjustify(LEFT_TEXT,CENTER_TEXT);
			outtextxy(320,138,own->account);
		}
		else if(mouse_press(392,300,450,368,&mx,&my,&mbuttn))
		{
			password[0]='\0';
			rech_amount[0]='\0';
			bar(318,247,549,277);
			bar(318,187,549,217);
		}
		else if(mouse_press(75,30,125,53,&mx,&my,&mbuttn))
		{
			*flag=1;
			mousehide(mx,my);
			break;
		}
	}
}

/*************************************************
  Function:			judge_rech
  Description:   	�ж��Ƿ��ֵ�ɹ�
  Input:          	password		�û���������
					rech_amount		��ֵ���
					own				�����û���Ϣ
  Return:         	int
*************************************************/

int judge_rech(char *password,char *rech_amount,Own *own)
{
	FILE *fq;
	char temp[30]="USER\\";
	char money_temp[10];
	char pass_[10];
	int flag=0;
	double money;
	strcpy(money_temp,rech_amount);
	strcat(temp,own->account);
	strcat(temp,"\\");
	strcat(temp,"own.txt");
	if((fq=fopen(temp,"rb"))==NULL)
	{
		printf("can not find the account!!!(while judge the recharge)\n");
		getch();
		exit(1);
	}
	fread(pass_,10,1,fq);
	fclose(fq);
	if(strcmp(pass_,password)!=0)
	{
		flag=1;
	}
	for(;*rech_amount!='\0';rech_amount++)	//ȷ������Ľ��
	{
		if(*rech_amount<'0'||*rech_amount>'9')
		{
			flag=2;
		}
	}
	setfillstyle(1,BLACK);
	bar(237,137,523,314);
	setfillstyle(1,WHITE);
	bar(240,140,520,311);
	setcolor(BLACK);
	rectangle(242,142,518,309);
	rectangle(245,145,515,306);
	switch(flag)
	{
		case 0:put_hz(328,190,"��ֵ�ɹ�",BLACK,24,2);
			   put_hz(315,230,"���������",BLACK,24,2);
			   break;
		case 1:put_hz(328,170,"��ֵʧ��",BLACK,24,2);
			   put_hz(328,210,"�������",BLACK,24,2);
			   put_hz(315,250,"���������",BLACK,24,2);
			   break;
		case 2:put_hz(328,170,"��ֵʧ��",BLACK,24,2);
			   put_hz(289,210,"��������ȷ���",BLACK,24,2);
			   put_hz(315,250,"���������",BLACK,24,2);
			   break;
	}
	if(flag==0)
	{
		own->balance[0]+=strtod(money_temp,NULL);
		own->balance[1]+=strtod(money_temp,NULL);
		own->balance[4]+=strtod(money_temp,NULL);
		rewrite_own(own);
	}
	clearbuffer();
	getch();
	return(flag);
}