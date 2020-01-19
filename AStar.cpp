#include "State.h"
#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;


void deleteFromTable(State &state, vector<State> &table)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (state == table[i])
		{
			table.erase(table.begin() + i);
			return;
		}
	}
}


int findElementFromTable(State &state, vector<State> &table)	//�ӱ���Ѱ��ָ��Ԫ�أ��ҵ��򷵻�����ֵ��û�ҵ�����-1
{
	for (int i = 0; i < table.size(); i++)
	{
		if (state == table[i])
		{
			return i;
		}
	}
	return -1;
}


//�º������������ȶ����еĴ�С��ϵ������fΪ��׼���бȽ�
struct cmp {
	bool operator()(State a, State b) {
		return a.getF() > b.getF();
	}
};



bool AStarSearch(State &startSate, State &goalState)
{
	vector<State> openTable, closedTable;	//open���closed�����ã�����Ա��н������޸Ĳ���
	priority_queue<State, vector<State>, cmp> openQueue;	//���ȶ������ڴ���ȡ��СԪ��,opentable��openqueueͬ������
	startSate.setH(goalState);
	startSate.setF();
	openTable.push_back(startSate);
	openQueue.push(startSate);
	int direction[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
	while (!openQueue.empty())
	{
		State *curr = new State(openQueue.top());
		openQueue.pop();	
		deleteFromTable(*curr, openTable);	//ɾ�����и�Ԫ��
		if (*curr == goalState)
		{
			goalState = *curr;
			return true;
		}
		closedTable.push_back(*curr);
		//����cuur�ĺ��״̬�ڵ�
		vector<State> succArray = (*curr).getSuccessor();
		for (auto &i : succArray)
		{
			i.setH(goalState);
			i.setF();
			int index = findElementFromTable(i, openTable);
			if (index != -1)	//��������̽���Ѿ���open����
			{
				if (i.getG() < openTable[index].getG())	//���������Ĵ��۱�ԭ��open���н��Ĵ���С
				{
					i.parent = curr;
					openTable[index] = i;
				}
			}

			index = findElementFromTable(i, closedTable);
			if (index != -1)	//��������̽ڵ���closed����
			{
				if (i.getG() < closedTable[index].getG())
				{
					//����closed
					i.parent = curr;
					closedTable[index] = i;
					//����open
					openTable.push_back(i);
					openQueue.push(i);
					closedTable.erase(closedTable.begin() + index);
				}
			}
			else	//��̽ڵ�Ȳ���openҲ����closed��
			{
				//����open
				i.parent = curr;
				openTable.push_back(i);
				openQueue.push(i);	
			}
		}

	}
	return false;	//open����˳�����˵���޽�
}


void showRoute(State *goalState)
{
	if (goalState != NULL)
	{
		showRoute(goalState->parent);
		goalState->showState();
	}
}




int main()
{
	FILE *stream;
	freopen_s(&stream, "input3.txt", "r", stdin);
	freopen_s(&stream, "output.txt", "w", stdout);
	int start = clock();
	int a[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> a[i][j];
	State startState(a);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> a[i][j];
	State goalState(a);
	State *ptr = &goalState;
	bool ret = AStarSearch(startState, goalState);
	if (!ret)	cout << "No Solution" << endl;
	showRoute(ptr);
	cout << "�������Ϊ" << ptr->getG() << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}