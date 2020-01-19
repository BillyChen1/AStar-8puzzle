#pragma once
#include <vector>
#define ROW 3
#define COL 3
class State
{
private:
	int num[ROW][COL];
	int f;	//目标函数值
	int g;	//g函数，初始结点到当前结点的代价
	int h;	//当前节点到目标结点的估计值
public:
	State *parent;	//前驱节点，用于记录路径
	int zeroRow;
	int zeroCol;
	State(int a[ROW][COL]);
	//State();
	~State();
	State(const State &state);	//复制构造函数
	void setH(const State &goal);	//计算当前状态的h，采用曼哈顿距离
	void setG(int depth);	//设置g，即深度
	void setF();		//更新启发函数值f
	bool operator==(const State &state) const;	//重载等于号，状态完全相同时则相等
	std::vector<State> getSuccessor();	//产生当前结点的后继
	void showState();
	int getF();
	int getG();
	int getH();
};

