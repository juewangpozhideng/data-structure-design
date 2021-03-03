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
	Node* head_node=NULL;//子句的头结点
	Clause* next=NULL;//指向下一个子句
public:
	Clause *createClause(vector<int> literals);//利用数组创建子句
	void destroyClause();//销毁子句
	int isUnitClause();//判断单子句并返回其值
	bool evaluateClause(int value);//判断子句真假
	void removeClause();//移除子句
	void addClause(vector<int> literals);//添加子句
	void removeLiteral(int value);//去掉子句中的某个单字
    Clause* insertClause(vector<int> literals);//插入一个子句
};
#endif

