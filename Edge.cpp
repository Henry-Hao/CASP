#include "Edge.h"


Edge::Edge(int id,Vertex* vv1,Vertex* vv2){
	this->id = id;
	this->setV1(vv1);
	this->setV2(vv2);
}
void Edge::init(int id,Vertex * vv1, Vertex * vv2)
{
	this->id = id;
	this->setV1(vv1);
	this->setV2(vv2);
}
void Edge::setV1(Vertex* v){
	Edge::v1 = v;
}

void Edge::setV2(Vertex* v){
	Edge::v2 = v;
}

int Edge::getId()
{
	return this->id;
}

Vertex* Edge::getV1() {
	return this->v1;
}

Vertex* Edge::getV2() {
	return this->v2;
}

void Edge::setWANCN(double w) {
	this->WANCN = w;
}
double Edge::getWANCN() {
	return this->WANCN;
}
