using namespace std;
#include "CNFparser.h"
Clause* CNFparser::readcnf(string filename)
{
	Clause* formula = new Clause(),*formula_head=NULL;
	ifstream file(filename);
	if (!file)
		cout << "文件打开失败！" << endl;
	while (true)
	{
		string word;
		getline(file, word);
		if (word[0] == 'p')
		{
			string temp;
			vector<int> formula_head;
			for (int i = 6; i < word.size(); i++)
			{
				if (word[i] != ' ')
					temp.push_back(word[i]);
				else
				{
					formula_head.push_back(stoi(temp));
					temp = {};
				}
			}
			formula_head.push_back(stoi(temp));
			literal_num = formula_head[0];
			clause_num = formula_head[1];
			break;
		}
	}
	literal_mark.resize(literal_num+1,0);
	while (true)
	{
		string word;
		getline(file, word);
		if (word == "")
			break;
		if (word[0] != 'c'&& word[0] != 'p')
		{
			string temp;
			vector<int> literals;
			for (auto w : word)
			{
				if (w != ' ')
					temp.push_back(w);
				else
				{
					int tem = stoi(temp);
					literal_mark[abs(tem)]++;
					literals.push_back(tem);
					temp = {};
				}
			}
			if (literals.size() == 0)
				mark = 1;
			if (formula_head == NULL)
			{
				formula_head = formula;
				formula->createClause(literals);	
			}
			else
			{
				formula->addClause(literals);
                formula = formula->next;
			}

		}
	}
	file.close();
	return formula_head;
}
void CNFparser::show_the_formula(Clause* cnf)
{
	while (cnf)
	{
		Node* readcnf = cnf->head_node;
		if (readcnf)
		{
			cout << readcnf->data;
			readcnf = readcnf->next_node;
		}
		while (readcnf)
		{
			cout << "V" << readcnf->data;
			readcnf = readcnf->next_node;
		}
		cout << "A"<<endl;
		cnf = cnf->next;
	}
}
bool CNFparser::is_null_in()
{
	return this->mark == 1;
}