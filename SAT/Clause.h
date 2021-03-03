#pragma once
#ifndef CLAUSE_H
#define CLAUSE_H
using namespace std;
#include"Node.h"
#include<vector>
class Clause
{
public:
	int num = 0;
	Node* head_node=NULL;//�Ӿ��ͷ���
	Clause* next=NULL;//ָ����һ���Ӿ�
public:
	Clause *createClause(vector<int> literals);//�������鴴���Ӿ�
	void destroyClause();//�����Ӿ�
	int isUnitClause();//�жϵ��Ӿ䲢������ֵ
	bool evaluateClause(int value);//�ж��Ӿ����
	void removeClause();//�Ƴ��Ӿ�
	void addClause(vector<int> literals);//����Ӿ�
	void removeLiteral(int value);//ȥ���Ӿ��е�ĳ������
    Clause* insertClause(vector<int> literals);//����һ���Ӿ�
};
#endif

