using namespace std;
#include "Clause.h"
Clause *Clause::createClause(vector<int> literals)
{
	if (literals.size() == 0)//空子句
		return this;
	Node* a = this->head_node=new Node();
	a->data = literals[0];
	num++;
	for (int i = 1; i < literals.size();i++)//子句赋值
	{
		a->next_node = new Node();
		a = a->next_node;
		 a->data = literals[i];	
		 num++;
	}
	return this;
}
void Clause::destroyClause()
{
	if (this == NULL)
		return;
	Node* p, * s;
	p = this->head_node;
	if (this->head_node == NULL)
		return;
	else
	{
		while (p->next_node )
		{
			s = p;
			p = p->next_node;
			delete s;
		}
		delete p;
		this->head_node = NULL;
	}
}
int Clause::isUnitClause()
{
	if (this->head_node == NULL)//空子句
		return false;
	if (this->head_node->next_node == NULL)//单子句
		return this->head_node->data;
	else
		return false;

}
void Clause::removeClause()
{
	if (this == NULL)
		return;
	this->Clause::destroyClause();
	delete this;
}
bool Clause::evaluateClause(int value)
{
	Node* p = this->head_node;
	while (p)
	{
		if (p->data == value)
			return true;
		p = p->next_node;
	}
	return false;
}
void Clause::addClause(vector<int> literals)
{
	this->next = new Clause();
	Clause* to_add = this->next;
	to_add -> createClause(literals);
}
void Clause::removeLiteral(int value)
{
	Node* p = this->head_node,*q=p;
	while (p)
	{
		if (p->data == value)
		{
			num--;
			if (p == this->head_node)
			{
				this->head_node = this->head_node->next_node;
				delete p;
				p = NULL;
				p = this->head_node;
				q = p;
			}
			else
			{
				q->next_node = p->next_node;
				delete p;
				p = NULL;
				p = q->next_node;
			}
		}
		else
		{
			q = p;
			p = p->next_node;
		}
	}
}
Clause* Clause::insertClause(vector<int> literals)
{
	Clause* to_insert = new Clause();
	to_insert->createClause(literals);
	to_insert->next = this;
	return to_insert;
}