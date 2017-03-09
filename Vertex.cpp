#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(int v)
{
	this->value = v;
	this->coarsed[v] = 0;
	this->w = 1;
}
void Vertex::init(int v) {
	this->value = v;
	this->coarsed[v] = 0;
	this->w = 1;
}

void Vertex::addNeighbour(Vertex* v)
{
	this->neighbour[(*v).getValue()] = 0;
}

void Vertex::deleteNeighbour(Vertex* v)
{
	this->neighbour.erase((*v).getValue());
}

map<int,int> Vertex::getNeighbour()
{
	return this->neighbour;
}

map<int,int>& Vertex::getCoarsed()
{
	return this->coarsed;
}

void Vertex::addCoarsed(map<int,int> s)
{
	map<int,int>::iterator cit;
	for (cit = s.begin(); cit != s.end(); cit++) {
		this->coarsed[cit->first] = 0;
	}
}
void Vertex::addsavedEdge(int arg1, Edge* arg2) {
	this->savedEdge[arg1] = arg2;
}

map <int, Edge*> Vertex::getsavedEdge() {
	return this->savedEdge;
}

void Vertex::deletesavedEdge(int arg1) {
	auto it = this->savedEdge.find(arg1);
	if(it!=this->savedEdge.end())
		this->savedEdge.erase(it);
}

int Vertex::getValue()
{
	return this->value;
}

int Vertex::getW()
{
	return this->w;
}
void Vertex::setW(int ww) {
	this->w = ww;
}


