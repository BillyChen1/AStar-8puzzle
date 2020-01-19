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


int findElementFromTable(State &state, vector<State> &table)	//从表中寻找指定元素，找到则返回索引值，没找到返回-1
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


//仿函数，定义优先队列中的大小关系，即以f为标准进行比较
struct cmp {
	bool operator()(State a, State b) {
		return a.getF() > b.getF();
	}
};



bool AStarSearch(State &startSate, State &goalState)
{
	vector<State> openTable, closedTable;	//open表和closed表作用：方便对表中结点进行修改操作
	priority_queue<State, vector<State>, cmp> openQueue;	//优先队列用于从中取最小元素,opentable和openqueue同步操作
	startSate.setH(goalState);
	startSate.setF();
	openTable.push_back(startSate);
	openQueue.push(startSate);
	int direction[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
	while (!openQueue.empty())
	{
		State *curr = new State(openQueue.top());
		openQueue.pop();	
		deleteFromTable(*curr, openTable);	//删除表中该元素
		if (*curr == goalState)
		{
			goalState = *curr;
			return true;
		}
		closedTable.push_back(*curr);
		//产生cuur的后继状态节点
		vector<State> succArray = (*curr).getSuccessor();
		for (auto &i : succArray)
		{
			i.setH(goalState);
			i.setF();
			int index = findElementFromTable(i, openTable);
			if (index != -1)	//如果这个后继结点已经在open表中
			{
				if (i.getG() < openTable[index].getG())	//如果这个结点的代价比原来open表中结点的代价小
				{
					i.parent = curr;
					openTable[index] = i;
				}
			}

			index = findElementFromTable(i, closedTable);
			if (index != -1)	//如果这个后继节点在closed表中
			{
				if (i.getG() < closedTable[index].getG())
				{
					//更新closed
					i.parent = curr;
					closedTable[index] = i;
					//放入open
					openTable.push_back(i);
					openQueue.push(i);
					closedTable.erase(closedTable.begin() + index);
				}
			}
			else	//后继节点既不在open也不再closed中
			{
				//放入open
				i.parent = curr;
				openTable.push_back(i);
				openQueue.push(i);	
			}
		}

	}
	return false;	//open表空退出，则说明无解
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
	cout << "搜索深度为" << ptr->getG() << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}