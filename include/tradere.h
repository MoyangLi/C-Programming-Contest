#ifndef _tradereal_h_
#define _tradereal_h_
#include "stdio.h"
typedef struct own
{
	char account[8];
	char stockname[9];
	char stockcode[7];
	float stock_now_price;	//��Ʊ�ּ�
	float stock_pre_price;
	long num_max;			//����������
	double balance[5];		//1���ý��,2�ʽ����,3�������,4֤ȯ��ֵ,5���ʲ�
	float price_own;		//�Լ�ѡ��۸�
	long num_own;			//�Լ�ѡ������
	int flag;				//���������жϴ������롢��������ί�����롢����
	float stock_zuoshou;	//�������̼�
	float zhangfu;			//�Ƿ�
}Own;
typedef struct delegate_node
{
	char stockname[9];
	char stockcode[7];
	long dele_amount;
	float dele_price;
	long date;
	int time;
	int flag;				//flagΪ0�����룬1������
	int flag_;				//0Ϊδ�ɽ���1Ϊ�Ѿ��ɽ�
	int delet_flag;			//0Ϊδɾ����1Ϊɾ��
	struct delegate_node *next;
	struct delegate_node *pre;
}Delegate;	//ί��
typedef struct hold_node
{
	char stockname[9];
	char stockcode[7];
	long stock_amount;		//֤ȯ���
	long amount_avail;		//�������
	long amount_blocked;	//��������
	long amount_real;		//��Ʊʵ��
	float deal_price;		//�ɱ���
	float now_price;    	//�м�
	double hold_spend;		//�ܻ���
	double market_value;	//��ֵ
	float profit_loss_;		//����ӯ��
	float profit_loss_percent;//ӯ������
	float position;			//��λ
	struct hold_node *next;
	struct hold_node *pre;
}Hold;		//�ֲ�

typedef struct balance_node
{
	long deal_date;			//������
	int deal_time;			//�ɽ�ʱ��
	char stockname[9];
	char stockcode[7];
	int flag;				//flagΪ0�����룬1������
	int flag_point; 		//�жϸñʽ����Ƿ���һ��ǰ��ɵģ������һ������ɵ���Ϊ�����Ʊ,flagΪ0������flagΪ1
	long deal_amount;
	float deal_price_ave;	//�ɽ�����
	double deal_money;		//�ɽ����
	double deal_money_real;	//�������
	float service_charge;	//������
	float stamp_tax;		//ӡ��˰
	double balance_now;		//���ν��
	
	struct balance_node *next;
	struct balance_node *pre;
}Balance;	//�����ˮ��ѯ

typedef struct deal_node
{
	long deal_date;			//�ɽ�����
	int deal_time;			//�ɽ�ʱ��
	char stockname[9];
	char stockcode[7];
	int flag;				//flagΪ0�����룬1������
	long deal_amount;		//�ɽ�����
	float deal_price_ave;	//�ɽ�����
	double deal_money;		//�ɽ����
	struct deal_node *next;
	struct deal_node *pre;
}Deal;		//�ɽ�

typedef struct mySTOCK
{
	char stockcode[7];
	char stockname[9];
	float price;
	float percent;
	struct mySTOCK *next;
	struct mySTOCK *pre;
}mySTOCK;
#endif