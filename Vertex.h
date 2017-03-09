#pragma once
#include <map>
class Edge;

using namespace std;

class Vertex {
private:
	//���涥���ֵ
	int value;
	//����wֵ
	int w;
	//���涥����ھӽ��
	map <int,int> neighbour;
	//����ϲ��Ķ���
	map <int,int> coarsed;
	//��������ı�
	map <int, Edge*> savedEdge;

public:
	Vertex() {};
	//���캯��
	Vertex(int v);
	void init(int v);
	//���һ���ھӽ��
	void addNeighbour(Vertex* v);
	//ɾ��һ���ھӽ��
	void deleteNeighbour(Vertex* v);
	//����ھӽ��
	map <int,int> getNeighbour();
	//����ھ�map
	void addsavedEdge(int, Edge*);
	//����ھ�map
	map <int, Edge*> getsavedEdge();
	//ɾ���ھ�map
	void deletesavedEdge(int);
	//��úϲ��Ľ��
	map <int,int>& getCoarsed();
	//��Ӻϲ��Ľ��
	void addCoarsed(map<int,int> s);
	//���value
	int getValue();
	//���wֵ
	int getW();
	//����wֵ
	void setW(int ww);
};