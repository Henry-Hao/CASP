#pragma once
#include "Edge.h"
#include "Vertex.h"
#include <map>
#include <vector>

using namespace std;

class Graph {
private:
	vector <Edge*> edge;
	map <int,Vertex*> vertex;

public:
	Graph() {};
	Graph(string filename,int bound);
	unsigned int bound;
	void build(string filename);
	vector<Edge*>& getAllEdge();
	void addEdge(Edge*);
	Edge* getEdge(int);
	void deleteEdge(int it);
	map <int,Vertex*> getAllVertex();
	bool isVertex(int index);
	Vertex* getVertex(int index);
	void deleteVertex(int index);
	void addVertex(Vertex* v);
	void edgeCoarsening(Edge* e);
	void calculateWANCN();
	void calculateWANCN(Vertex* uu);
	void sortEdge();
	bool isEdge(int, int);
	Vertex* mergeNodes();

};