#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include <iterator>

Graph::Graph(string filename,int bound) {
	Graph::build(filename);
	Graph::bound = (unsigned int)bound;
}

void Graph::build(string filename) {
	string line;
	ifstream graphfile(filename.c_str());
	int v1, v2;
	if (graphfile.is_open()) {
		int i = 0;
		while (getline(graphfile, line)) {
			Vertex *vv1, *vv2;
			Edge *e1;
			vv1 = new Vertex();
			vv2 = new Vertex();
			e1 = new Edge();
			string from, to;
			istringstream lines(line);
			getline(lines, from, ' ');
			getline(lines, to, ' ');
			//保证没有自己到自己的边
			if (from == to) continue;
			v1 = atoi(from.c_str());
			v2 = atoi(to.c_str());
			//这条边已经出现过
			if (isEdge(v1, v2))
				continue;
			if (Graph::isVertex(v1))
				vv1 = Graph::getVertex(v1);
			else {
				(*vv1).init(v1);
				//37
				Graph::addVertex(vv1);
			}
			if (Graph::isVertex(v2))
				vv2 = Graph::getVertex(v2);
			else {
				(*vv2).init(v2);
				//37
				Graph::addVertex(vv2);
			}

			(*vv1).addsavedEdge(i, e1);
			(*vv2).addsavedEdge(i, e1);
			
			(*vv1).addNeighbour(vv2);
			(*vv2).addNeighbour(vv1);

			(*e1).init(i,vv1, vv2);
			(*e1).setWANCN(0);
			Graph::addEdge(e1);
			i++;
		}
		graphfile.close();
	}
	else
		cout << "Unable to open file " << filename;
}

vector <Edge*>& Graph::getAllEdge() {
	return Graph::edge;
}

void Graph::addEdge(Edge* e) {
	Graph::edge.push_back(e);
}
void Graph::deleteEdge(int id) {
	for (auto it = Graph::edge.begin(); it != Graph::edge.end();) {
		if ((*(*it)).getId() == id) {
			auto it2 = it;
			Graph::edge.erase(it);
			return;
		}
		else {
			it++;
		}
	}
}

Edge* Graph::getEdge(int id) {
	for (auto it = Graph::edge.begin(); it != Graph::edge.end(); it++) {
		if ((*(*(it))).getId() == id)
			return (*it);
	}
}


map <int,Vertex*> Graph::getAllVertex() {
	return Graph::vertex;
}

bool Graph::isVertex(int index)
{
	if (Graph::vertex.find(index) != Graph::vertex.end())
		return true;
	else
		return false;
}

bool Graph::isEdge(int v1, int v2) {
	Vertex* x;
	if (Graph::isVertex(v1)) {
		x = Graph::getVertex(v1);
		auto tmp_neighbour = (*x).getNeighbour();
		if (tmp_neighbour.find(v2) == tmp_neighbour.end())
			return false;
		else
			return true;
	}	
	else if (Graph::isVertex(v2)) {
		x = Graph::getVertex(v2);
		auto tmp_neighbour = (*x).getNeighbour();
		if (tmp_neighbour.find(v1) == tmp_neighbour.end())
			return false;
		else
			return true;
	}
	else
		return false;

}

Vertex* Graph::getVertex(int index) {
	return Graph::vertex.find(index)->second;
}
void Graph::deleteVertex(int index) {
	Graph::vertex.erase(index);
}

void Graph::addVertex(Vertex* v) {
	Graph::vertex[(*v).getValue()] = v;
}

void Graph::edgeCoarsening(Edge* e){
	//更新邻居
	//起点
 	Vertex* u = (*e).getV1();
	//终点
	Vertex* v = (*e).getV2();
	map <int, int>::iterator neighbourIT;
	map <int, int> neighbour;
	int tmp_value = (*u).getValue();
	auto tmp_neighbour = (*u).getNeighbour();
	//更新起点点的每个邻居中与终点相连的边
	neighbour = (*v).getNeighbour();
	//for (neighbourIT = neighbour.begin(); neighbourIT != neighbour.end(); neighbourIT++) {
	//	Vertex* tmp = Graph::getVertex(neighbourIT->first);
	//	(*tmp).deleteNeighbour(v);
	//	if (tmp_neighbour.find((*tmp).getValue()) == tmp_neighbour.end() && (*u).getValue() != (*tmp).getValue()) {
	//		(*tmp).addNeighbour(u);
	//		(*u).addNeighbour(tmp);
	//	}
	//		
	//}
	//更新邻居
	(*u).setW((*u).getW() + (*v).getW());
	//更新合并set
	(*u).addCoarsed((*v).getCoarsed());
	//更改所有含有被合并节点的边
	vector <Edge*> ::iterator edgeit;
	int uValue = (*u).getValue();
	map <int, Edge*> savedEdgeForV = (*v).getsavedEdge();
	for (auto it = savedEdgeForV.begin(); it != savedEdgeForV.end();) {
		Edge* tmpEdge = (*it).second;
		if ((*(*tmpEdge).getV1()).getValue() == (*v).getValue()) {
			Vertex* otherNode = (*tmpEdge).getV2();
			auto tmp_neighbour = (*otherNode).getNeighbour();
			//38
			(*otherNode).deleteNeighbour(v);
			//
			if ((*otherNode).getValue() == uValue || tmp_neighbour.find(uValue) != tmp_neighbour.end()) {
				//38
				if ((*otherNode).getValue() == uValue)
					(*v).deleteNeighbour(otherNode);
				(*otherNode).deletesavedEdge((*it).first);
				//
				(*v).deletesavedEdge((*it).first);
				Graph::deleteEdge((*it).first);
				it++;
			}
			else {
				(*tmpEdge).setV1(u);
				//38
				(*otherNode).addNeighbour(u);
				(*u).addNeighbour(otherNode);
				(*u).addsavedEdge((*it).first, (*it).second);
				//
				it++;
			}
		}
		else if ((*(*tmpEdge).getV2()).getValue() == (*v).getValue()) {
			Vertex* otherNode = (*tmpEdge).getV1();
			auto tmp_neighbour = (*otherNode).getNeighbour();
			//38
			(*otherNode).deleteNeighbour(v);
			//

			if ((*otherNode).getValue() == uValue || tmp_neighbour.find(uValue) != tmp_neighbour.end()) {
				//38
				if ((*otherNode).getValue() == uValue)
					(*v).deleteNeighbour(otherNode);
				(*otherNode).deletesavedEdge((*it).first);
				//
				(*v).deletesavedEdge((*it).first);
				Graph::deleteEdge((*it).first);
				it++;
			}
			else {
				(*tmpEdge).setV2(u);
				//38
				(*otherNode).addNeighbour(u);
				(*u).addNeighbour(otherNode);
				(*u).addsavedEdge((*it).first, (*it).second);
				//
				it++;
			}
		}
	}
	//删除被合并节点
	Graph::deleteVertex((*v).getValue());
	//重新计算MANCN
	//Graph::calculateWANCN(u);

}

void Graph::calculateWANCN() {
	Vertex u;
	Vertex v;

	for (auto edgeIT = edge.begin(); edgeIT != edge.end(); edgeIT++) {
		u = *(*(*edgeIT)).getV1();
		v = *(*(*edgeIT)).getV2();
		map <int, int> neighbour_u = u.getNeighbour();
		map <int, int> neighbour_v = v.getNeighbour();
		set <int> nu;
		set <int> nv;
		vector <int> CN;
		map <int, int>::iterator nit;
		for (nit = neighbour_u.begin(); nit != neighbour_u.end(); nit++) {
			nu.insert((*nit).first);
		}
		for (nit = neighbour_v.begin(); nit != neighbour_v.end(); nit++) {
			nv.insert((*nit).first);
		}
		//求两个点的CommonNeighbour
		set_intersection(nu.begin(), nu.end(), nv.begin(), nv.end(), back_inserter(CN));
		
		double wancn = CN.size() * 1.0 / sqrt((u.getW()*neighbour_u.size()*v.getW()*neighbour_v.size()*1.0));
		(*(*edgeIT)).setWANCN(wancn);
	}

}

void Graph::calculateWANCN(Vertex* uu) {
	Vertex u;
	Vertex v;
	//N(x) U x
	map <int, Edge*> NX = (*uu).getsavedEdge();
	map <int, int> tmp_neighbour = (*uu).getNeighbour();
	for (auto it = tmp_neighbour.begin(); it != tmp_neighbour.end(); it++) {
		Vertex* neighbour = Graph::getVertex((*it).first);
		map <int, Edge*> tmp_savedNeighbour = (*neighbour).getsavedEdge();
		for (auto it2 = tmp_savedNeighbour.begin(); it2 != tmp_savedNeighbour.end(); it2++) {
			NX[(*it2).first] = (*it2).second;
		}
	}
	for (auto it = NX.begin(); it != NX.end(); it++) {
		Edge* tmpEdge = (*it).second;
		u = *(*tmpEdge).getV1();
		v = *(*tmpEdge).getV2();
		map <int, int> neighbour_u = u.getNeighbour();
		map <int, int> neighbour_v = v.getNeighbour();
		set <int> nu;
		set <int> nv;
		if (neighbour_u.size() >= Graph::bound || neighbour_v.size() >= Graph::bound)
			continue;
		vector <int> CN;
		map <int, int>::iterator nit;
		for (nit = neighbour_u.begin(); nit != neighbour_u.end(); nit++) {
			nu.insert((*nit).first);
		}
		for (nit = neighbour_v.begin(); nit != neighbour_v.end(); nit++) {
			nv.insert((*nit).first);
		}
		//求两个点的CommonNeighbour
		set_intersection(nu.begin(), nu.end(), nv.begin(), nv.end(), back_inserter(CN));
		double wancn = CN.size() * 1.0 / sqrt((u.getW()*neighbour_u.size()*v.getW()*neighbour_v.size()*1.0));
		(*tmpEdge).setWANCN(wancn);
	}
}

bool mycompare(Edge* arg1,Edge* arg2) {
	return (*arg1).getWANCN() > (*arg2).getWANCN();
}

void Graph::sortEdge() {
	sort(Graph::getAllEdge().begin(), Graph::getAllEdge().end(), mycompare);
}

Vertex* Graph::mergeNodes() {
	//for (unsigned int i = 0; i < Graph::edge.size(); i++) {

	for (auto it = this->edge.begin(); it != this->edge.end(); it++) {
		Edge* tmpedge = (*it);
		int coarsed1 = (*(*tmpedge).getV1()).getCoarsed().size();
		int coarsed2 = (*(*tmpedge).getV2()).getCoarsed().size();
		if ((coarsed1 > Graph::bound && coarsed2 > Graph::bound) || coarsed2 + coarsed1 >= Graph::bound*2)
			continue;
		Graph::edgeCoarsening(tmpedge);
		//Graph::deleteEdge(i);
		return (*tmpedge).getV1();
	}
	return false;

}
