/*
 *  Dijkstra.h
 *  CNImplementation
 *
 *  Created by 長谷川 知里 on 11/09/29.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

class Dijkstra {
private:
	int* treeV;
	int** treeE;
	int* arrival;
	int nNode;
	int nEdge;
	int *degree;
	int** graph;
	int** take;
	
	void dijkstraProcess(int,int);
	void deleteParentEdge(int);
	bool treeIncludes(int);
	int* showPath(int,int);
	void reverseOrder(int,int[]);
public:
	Dijkstra();
	~Dijkstra();
	int* executeDijkstra(int,int);
};