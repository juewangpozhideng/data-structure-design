#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<time.h>
#include"DPLLsolver.h"
#define ROW 4
#define COL 4
using namespace std;
vector<vector<int>> initial(int mode);

void question_to_cnf(vector<vector<int>> question, const char* filename)//将初盘转化为cnf文件
{
	ofstream file(filename);
	if (!file)
		cout << "文件打开失败！" << endl;
	file << "p cnf " << 160 << " " << 1330 << endl;
	//单子句
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			if (question[i][j] == 1)
				file << i * COL + j + 1 << " " << 0 << endl;
			if (question[i][j] == 0)
				file << 0 - (i * COL + j + 1) << " " << 0 << endl;
		}
	//行约束2
	for (int i = 0; i < ROW; i++)
		for (int j = 1; j < COL + 1; j++)
			for (int k = j + 1; k < COL + 1; k++)
				for (int l = k + 1; l < COL + 1; l++)
				{
					file << i * COL + j << " " << i * COL + k << " " << i * COL + l << " " << 0 << endl;
					file << -(i * COL + j) << " " << -(i * COL + k) << " " << -(i * COL + l) << " " << 0 << endl;
				}
	//列约束2
	for (int j = 1; j < COL + 1; j++)
		for (int i = 0; i < ROW; i++)
			for (int k = i + 1; k < ROW; k++)
				for (int l = k + 1; l < ROW; l++)
				{
					file << i * COL + j << " " << k * COL + j << " " << l * COL + j << " " << 0 << endl;
					file << -(i * COL + j) << " " << -(k * COL + j) << " " << -(l * COL + j) << " " << 0 << endl;
				}
	//行约束3
	int num_3 = 0;
	int base = ROW * COL;//符加变元基数
	for (int i = 0; i < ROW; i++)
		for (int j = i + 1; j < ROW; j++)
		{
			for (int k = 1; k < COL + 1; k++)
			{
				int add1 = base + num_3 * 3 * ROW + (k - 1) * 3 + 1;
				file << i * COL + k << " " << -add1 << " " << 0 << endl;
				file << j * COL + k << " " << -add1 << " " << 0 << endl;
				file << -(i * COL + k) << " " << -(j * COL + k) << " " << add1 << " " << 0 << endl;
				int add2 = base + num_3 * 3 * ROW + (k - 1) * 3 + 2;
				file << -(i * COL + k) << " " << -add2 << " " << 0 << endl;
				file << -(j * COL + k) << " " << -add2 << " " << 0 << endl;
				file << i * COL + k << " " << j * COL + k << " " << add2 << " " << 0 << endl;
				int add3 = base + num_3 * 3 * ROW + (k - 1) * 3 + 3;
				file << -add1 << " " << add3 << " " << 0 << endl;
				file << -add2 << " " << add3 << " " << 0 << endl;
				file << add1 << " " << add2 << " " << -add3 << " " << 0 << endl;
			}
			for (int m = 0; m < ROW; m++)
			{
				file << -(base + num_3 * 3 * ROW + m * 3 + 3) << " ";
			}
			file << 0 << endl;
			num_3++;
		}
	//列约束3
	for (int i = 1; i < COL + 1; i++)
		for (int j = i + 1; j < COL + 1; j++)
		{
			for (int k = 0; k < ROW; k++)
			{
				int add1 = base + num_3 * 3 * ROW + k * 3 + 1;
				file << k * COL + i << " " << -add1 << " " << 0 << endl;
				file << k * COL + j << " " << -add1 << " " << 0 << endl;
				file << -(k * COL + i) << " " << -(k * COL + j) << " " << add1 << " " << 0 << endl;
				int add2 = base + num_3 * 3 * ROW + k * 3 + 2;
				file << -(k * COL + i) << " " << -add2 << " " << 0 << endl;
				file << -(k * COL + j) << " " << -add2 << " " << 0 << endl;
				file << k * COL + i << " " << k * COL + j << " " << add2 << " " << 0 << endl;
				int add3 = base + num_3 * 3 * ROW + k * 3 + 3;
				file << -add1 << " " << add3 << " " << 0 << endl;
				file << -add2 << " " << add3 << " " << 0 << endl;
				file << add1 << " " << add2 << " " << -add3 << " " << 0 << endl;
			}
			for (int m = 0; m < ROW; m++)
			{
				file << -(base + num_3 * 3 * ROW + m * 3 + 3) << " ";
			}
			file << 0 << endl;
			num_3++;
		}
}

void dighole(vector<vector<int>> &question, int hole_num)//对终盘挖洞
{
	srand((unsigned)time(nullptr));
	while (hole_num)
	{
		int k = rand() % (ROW * COL) ;
		int m = k / ROW;
		k = k % ROW;
		if (question[m][k ] != -1)
		{
			question[m][k ] = -1;
			hole_num--;
		}
	}
	return;
}

vector<vector<int>> initial(int mode)//生成终盘准备
{
	srand((unsigned)time(nullptr));
	vector<vector<int>> res(ROW, vector<int>(COL, -1));
	int i = 0;
	while (mode)
	{
		res[i][rand() % COL] = (i % 2 ? 1 : 0);
		i = (i + 1) % COL;
		mode--;
	}
	return res;
}

void integrated(int mode, int hole_num)//快速生成并打印初盘
{
	vector<vector<int>> question = initial(mode);
	question_to_cnf(question, "001.cnf");
	CNFparser test;
	Clause* test1 = test.readcnf("001.cnf");
	vector<int> result = test.literal_mark;
	DPLL(test1, result);
	vector<vector<int>> res(ROW, vector<int>(COL, -1));
	int m = 1;
	for(int i=0;i<ROW;i++)//终盘生成
		for (int j = 0; j < COL; j++)
		{
			res[i][j] = (result[m++] == 1 ? 1 : 0);
		}
	cout << endl;
	dighole(res, hole_num);//挖洞
	for (int i = 0; i < ROW; i++)//终盘生成
	{
		for (int j = 0; j < COL; j++)
		{
			if (res[i][j] == -1)
				cout << "?" << " ";
			else
				cout << res[i][j] << " ";
		}
		cout << endl;
	}
	cout << "按任意键显示答案" << endl;
	getchar(); getchar();
	question_to_cnf(res, "001.cnf");
    test1 = test.readcnf("001.cnf");
	result = test.literal_mark;
	DPLL(test1, result);
	m = 1;
	for (int i = 0; i < ROW; i++)//终盘生成
	{
		for (int j = 0; j < COL; j++)
		{
			if (result[m] == -1)
				cout << 0 << " ";
			else
				cout << 1 << " ";
			m++;
		}
		cout << endl;
	}
}