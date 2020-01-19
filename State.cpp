#include "State.h"
#include <unordered_map>
#include <iostream>
using namespace std;
State::State(int a[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			num[i][j] = a[i][j];
			if (a[i][j] == 0)
			{
				zeroRow = i;
				zeroCol = j;
			}
		}
	}
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->parent = nullptr;
}


State::~State()
{
}

State::State(const State & state)
{
	zeroRow = state.zeroRow;
	zeroCol = state.zeroCol;
	f = state.f;
	g = state.g;
	h = state.h;
	parent = state.parent;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			num[i][j] = state.num[i][j];
}

void State::setH(const State & goal)
{
	unordered_map<int, pair<int, int>> theMap;	//key为元素值，value为该数码的位置
	unordered_map<int, pair<int, int>> goalMap;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			theMap[this->num[i][j]] = pair<int, int>(i, j);
			goalMap[goal.num[i][j]] = pair<int, int>(i, j);
		}
	for (int i = 1; i < 9; i++)
	{
		int dx = abs(theMap[i].first - goalMap[i].first);
		int dy = abs(theMap[i].second - goalMap[i].second);
		h += (dx + dy);
	}
}

void State::setG(int depth)
{
	this->g = depth;
}

void State::setF()
{
	f = g + h;
}

bool State::operator==(const State & state) const
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			if (num[i][j] != state.num[i][j])
				return false;
		}
	return true;
}

std::vector<State> State::getSuccessor()
{
	std::vector<State> ret;
	int direction[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
	for (int i = 0; i < 4; i++)
	{
		int xi = this->zeroRow + direction[i][0];
		int yi = this->zeroCol + direction[i][1];
		if (xi >= 0 && xi < ROW && yi >= 0 && yi < COL)
		{
			int b[COL][ROW];
			//将当前节点的数字信息复制到一个数组中
			for (int j = 0; j < ROW; j++)
				for (int k = 0; k < COL; k++)
					b[j][k] = this->num[j][k];
			
			int tmp = b[xi][yi];
			b[this->zeroRow][this->zeroCol] = tmp;
			b[xi][yi] = 0;
			State succ(b);
			
			succ.setG(this->g + 1);
			succ.setF();
			ret.push_back(succ);
			
		}
	}
	return ret;
}

void State::showState()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (num[i][j] == 0)
				cout << ' ' << ' ';
			else
				cout << num[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int State::getF()
{
	return this->f;
}

int State::getG()
{
	return this->g;
}

int State::getH()
{
	return this->h;
}


