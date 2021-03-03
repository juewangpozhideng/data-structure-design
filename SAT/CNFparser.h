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
	int literal_num = 0;//变元个数
	int clause_num = 0;//子句个数
	vector<int> literal_mark;//变元出现次数统计
public:
	Clause* readcnf(string filename);//从文件读取并解析出公式
	void show_the_formula(Clause* cnf);//打印公式
	bool is_null_in();//判断是否含有空子句
};
#endif
