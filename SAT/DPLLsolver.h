#pragma once
#include"CNFparser.h"
bool is_null_in(Clause* s_clause);
int is_single_in(Clause* s_clause);
bool DPLL(Clause* s_clause, vector<int>& result);
Clause* deepcopy(Clause* s_clause);

bool DPLL(Clause* s_clause,vector<int> &result)//DPLL算法
{
	int value = is_single_in(s_clause);
	while (value)
	{
		result[abs(value)] = value / abs(value);
		Clause* p = s_clause,*q= s_clause;
		while (p)
		{
			if (p->evaluateClause(value))
			{
				if (p == s_clause)
				{
					s_clause = p->next;
					p->destroyClause();
					delete p;
					p = NULL;
					p = s_clause;
					q = p;
				}
				else
				{
					q ->next= p->next;
					p->destroyClause();
					delete p;
					p = NULL;
					p = q->next;
				}
			}
			else
			{
				q = p;
				p = p->next;
				q->removeLiteral(-value);
			}
		}
		if (s_clause == NULL)
			return true;
		if (is_null_in(s_clause))
		{
			while (s_clause)
			{
				Clause* to_delete = s_clause;
				s_clause->destroyClause();
				s_clause = s_clause->next;
				delete to_delete;
			}
			return false;
		}			
		value = is_single_in(s_clause);
	}//while
	value = s_clause->head_node->data;
	vector<int> value1 ;
	value1.push_back(value);
	Clause* s_copy = deepcopy(s_clause);
	Clause* one = s_clause->insertClause(value1);
	value1.pop_back();
	value1.push_back(-value);
	Clause* two = s_copy->insertClause(value1);
	if (DPLL(one,result)) return true;
	return DPLL(two,result);
}

int is_single_in(Clause* s_clause)//寻找单子句并返回单子句变元的值
{
	Clause* a = NULL;
	a=s_clause;
	while (a)
	{
		if (a->isUnitClause())
			return a->isUnitClause();
		a = a->next;
	}
	return 0;
}

bool is_null_in(Clause* s_clause)//判断是否存在空子句
{
	Clause* a = NULL;
	a=s_clause;
	while (a)
	{
		if (a->head_node == NULL)
			return true;
		a = a->next;
	}
	return false;
}

Clause* deepcopy(Clause* s_clause)
{
	Clause* to_copy = s_clause;
	Clause* temp;
	Clause* res = new Clause();
	temp = res;
	while (to_copy->next)
	{
		temp->next = new Clause();
		temp = temp->next;
		to_copy = to_copy->next;
	}
	temp = res;
	to_copy = s_clause;
	while (to_copy)
	{
		Node* node_to_copy = to_copy->head_node;
		Node* newnode = temp->head_node = new Node();
		newnode->data = node_to_copy->data;
		node_to_copy = node_to_copy->next_node;
		while (node_to_copy)
		{
			newnode->next_node = new Node();
			newnode->next_node->data = node_to_copy->data;
			newnode = newnode->next_node;
			node_to_copy = node_to_copy->next_node;
		}
		temp = temp->next;
		to_copy = to_copy->next;
	}
	return res;
}