#pragma once
#include <map>
class Edge;

using namespace std;

class Vertex {
private:
	//保存顶点的值
	int value;
	//保存w值
	int w;
	//保存顶点的邻居结点
	map <int,int> neighbour;
	//保存合并的顶点
	map <int,int> coarsed;
	//保存包含的边
	map <int, Edge*> savedEdge;

public:
	Vertex() {};
	//构造函数
	Vertex(int v);
	void init(int v);
	//添加一个邻居结点
	void addNeighbour(Vertex* v);
	//删除一个邻居结点
	void deleteNeighbour(Vertex* v);
	//获得邻居结点
	map <int,int> getNeighbour();
	//添加邻居map
	void addsavedEdge(int, Edge*);
	//获得邻居map
	map <int, Edge*> getsavedEdge();
	//删除邻居map
	void deletesavedEdge(int);
	//获得合并的结点
	map <int,int>& getCoarsed();
	//添加合并的结点
	void addCoarsed(map<int,int> s);
	//获得value
	int getValue();
	//获得w值
	int getW();
	//设置w值
	void setW(int ww);
};