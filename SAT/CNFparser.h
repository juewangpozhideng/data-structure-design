#pragma once
#ifndef CNFPARSER_H
#define CNFPARSER_H
#include"Clause.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
class CNFparser
{
public:
	int mark = 0;
	int literal_num = 0;//��Ԫ����
	int clause_num = 0;//�Ӿ����
	vector<int> literal_mark;//��Ԫ���ִ���ͳ��
public:
	Clause* readcnf(string filename);//���ļ���ȡ����������ʽ
	void show_the_formula(Clause* cnf);//��ӡ��ʽ
	bool is_null_in();//�ж��Ƿ��п��Ӿ�
};
#endif
