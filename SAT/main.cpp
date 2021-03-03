#include <iostream>
#include "DPLLsolver.h"
#include"binary puzzle.h"
#include<time.h>
#pragma warning(disable:4996)
using namespace std;
int main()
{
   //CNFparser test;
    //Clause* test1_head;
    //test1_head = test.readcnf("../qg4-08.cnf");
    //vector<int> literal_mark = test.literal_mark;
    //cout<<DPLL(test1_head, literal_mark);
    //Clause* copyone = deepcopy(test1_head);
    //test.show_the_formula(copyone);
    
   // vector<vector<int>> question(4, vector<int>(4, -1));
    //question[0][1] = 0;
    //question[0][2] = 1;
    //question[1][0] = 1;
    //question[2][1] = 1;
    //question[2][3] = 1;
   // question[3][2] = 0;
   // question_to_cnf(question, "001.cnf");
   // test1_head=test.readcnf("001.cnf");
   // test.show_the_formula(test1_head);
   // vector<int> result(161, 0);
    int op = 1;
    CNFparser test;
    Clause* test1_head;
    string filename;
    vector<int> result;
    clock_t start, finish;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("\t\t\t      Main Menu \n");
        printf("\t\t************************************\n");
        printf("\t\t\t1.  binary puzzle   2.  sat\n");
        printf("\t\t\t0.  Exit\n");
        printf("\t\t************************************\n");
        printf("\t\t\tPlease choose your operation[0--2]:");
       scanf("%d", &op);
        system("cls");
        switch (op) {
        case 1:
            integrated(0, 9);
            getchar(); getchar();
            break;
        case 2:
            cout << "请输入cnf文件路径" << endl;            
            cin >> filename;
            test1_head = test.readcnf(filename);
            cout << "解析如下" << endl;
            test.show_the_formula(test1_head);
            result = test.literal_mark;
            getchar();
            start = clock();
            if (DPLL(test1_head, result))
            {
                finish = clock();
                cout << "计算结果如下" << endl;
                for (int i = 1; i < result.size(); i++)
                    cout << i << ":" << result[i] << endl;
            }
            else
            {
                finish = clock();
                cout << "算例无法满足" << endl;
            }
                cout << "用时" << finish - start << "毫秒" << endl;
                getchar(); getchar();
            break;
        case 0:
            exit(0);
        default:
            printf("\t\t\tPlease choose your operation again[0--2]:");
            scanf("%d", &op);
        }
    }

}
