#pragma once
#include "Vertex.h"

class Edge {
private:
	int id;
	//Æðµã
	Vertex* v1;
	//ÖÕµã
	Vertex* v2;
	//WANCN
	double WANCN;

public:
	Edge() {};
	Edge(int ,Vertex* vv1, Vertex* vv2);
	void init(int,Vertex* vv1, Vertex* vv2);
	void setV1(Vertex* v);
	void setV2(Vertex* v);
	int getId();
	Vertex* getV1();
	Vertex* getV2();
	void setWANCN(double w);
	double getWANCN();

};