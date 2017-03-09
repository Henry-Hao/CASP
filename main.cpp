#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>

using namespace std;
LARGE_INTEGER start, End, freq;
double timer;

int main(int argc, char* argv[]) {
	//输入文件 p值 bound值 输出文件  
	string inputfile = argv[1];
	int p = atoi(argv[2]);
	int bound = atoi(argv[3]);
	string outputfile = argv[4];
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	printf("processing\n");
	 
	Graph graph(inputfile,bound);
	int n = graph.getAllVertex().size();
	graph.calculateWANCN();
	graph.sortEdge();
	for (int l = 0; l < n - p; l++) {
		printf("%d\n",l);
		Vertex* mergedNode = graph.mergeNodes();
		if (mergedNode == false)
			break;
		graph.calculateWANCN(mergedNode);
		graph.sortEdge();
		if (l % 1000 == 0)
			printf("percent:%f", l*100.0 / (n - p));
	}
	FILE *out;
	fopen_s(&out, outputfile.c_str(), "w");
	map <int, Vertex*>& v = graph.getAllVertex();
	map <int, Vertex*>::iterator vit;
	map <int, int>::iterator cit;
	fprintf(out, "nodeNumber:%d\np:%d\nbound:%d\n", n, p, bound);
	for (vit = v.begin(); vit != v.end(); vit++) {
		fprintf(out, "vertex: %ld\n coarsed node:", (*vit).first);
			for (cit = (*(*vit).second).getCoarsed().begin(); cit != (*(*vit).second).getCoarsed().end(); cit++)
				fprintf(out, "%d ", (*cit).first);
		fprintf(out, "\n ");
	}
	QueryPerformanceCounter(&End);
	timer = (double)(End.QuadPart - start.QuadPart) / freq.QuadPart;
	fprintf(out, "%lg s", timer);
	printf("success\n");
	int a = 1;


}