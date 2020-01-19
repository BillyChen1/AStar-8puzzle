#pragma once
#include <vector>
#define ROW 3
#define COL 3
class State
{
private:
	int num[ROW][COL];
	int f;	//Ŀ�꺯��ֵ
	int g;	//g��������ʼ��㵽��ǰ���Ĵ���
	int h;	//��ǰ�ڵ㵽Ŀ����Ĺ���ֵ
public:
	State *parent;	//ǰ���ڵ㣬���ڼ�¼·��
	int zeroRow;
	int zeroCol;
	State(int a[ROW][COL]);
	//State();
	~State();
	State(const State &state);	//���ƹ��캯��
	void setH(const State &goal);	//���㵱ǰ״̬��h�����������پ���
	void setG(int depth);	//����g�������
	void setF();		//������������ֵf
	bool operator==(const State &state) const;	//���ص��ںţ�״̬��ȫ��ͬʱ�����
	std::vector<State> getSuccessor();	//������ǰ���ĺ��
	void showState();
	int getF();
	int getG();
	int getH();
};

