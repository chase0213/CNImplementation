/*
 *  dijkstra.cpp
 *  GRAPH_ALGORITHM
 *
 *  Created by 長谷川 知里 on 11/03/27.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Dijkstra.h"
#include "resource.h"
#include "stdafx.h"
#include "NetworkExpression.h"

using namespace std;

// n:vertex g:graph
Dijkstra::Dijkstra(){
    
    Network g("graph.dat");
    nNode = g.getNNode();
    
	int i,j,sum=0;
	treeV = new int[nNode];
	treeE = new int*[nNode];
	degree = new int[nNode];
	arrival = new int[nNode];
	graph = new int*[nNode];
	take = new int*[nNode];
	for( i=0; i<nNode; i++ ){
		degree[i] = 0;
		treeE[i] = new int[2];
		graph[i] = new int[nNode];
		take[i] = new int[nNode];
		for( j=0; j<nNode; j++ ){
            graph[i][j] = g.getAMElement(i,j);
			take[i][j] = graph[i][j]>0 ? graph[i][j] : ML;
			degree[i] += graph[i][j]>0 ? 1 : 0;
		}
	}
	
	for( i=0; i<nNode; i++ ){
		arrival[i]=ML;
		sum+=degree[i];
		
		/* 要素が指定されていないところを-1で埋める */
		treeV[i] = -1;
		if( i!=nNode-1 ){
			treeE[i][0] = -1;
			treeE[i][1] = -1;
		}
	}
}

Dijkstra::~Dijkstra(){
	for(int i=0; i<nNode; i++ ){
		delete[] treeE[i];
		delete[] graph[i];
		delete[] take[i];
	}
	delete[] degree;
	delete[] treeV;
	delete[] treeE;
	delete[] arrival;
	delete[] graph;
	delete[] take;
}

int* Dijkstra::executeDijkstra(int start, int target)
{
	dijkstraProcess(start, target);
	return showPath(start, target);
}

void Dijkstra::dijkstraProcess(int start, int target)
{
	bool* definite = new bool[nNode];
	int i,j,k;
	int nv=1, ne=0;
	int s = start;
	
	arrival[s] = 0;
	definite[s]=true;
	int v = s;
	treeV[0] = s;
	
	/* Initializing */
	for( i=0, k=0; i<nNode; i++ ){
		definite[i] = false;
		if( graph[s][i]==0 ){
			continue;
		}
		v = i;
		treeV[k+1] = v;
		nv++;
		treeE[k][0] = s;
		treeE[k][1] = v;
		ne++;
		arrival[v] = graph[s][v];
		k++;
	}
	/* Main Process of the Algorithm */
	while( !definite[target] ){
		i = 1;
		v = treeV[i];
		int min = INT_MAX;
		int minV = INT_MAX;
		while( v>=0 && i<nNode ){
			if( !definite[v] ){
				if( min > arrival[v] ){
					min = arrival[v];
					minV = v;
				}
			}
			v = treeV[++i];
		}
		int x = minV;
		definite[x] = true;
		for( j=0; j<nNode; j++ ){
			if( graph[x][j]>=ML ){
				continue;
			}
			v = j;
			if( arrival[x]+take[x][v]<arrival[v] ){
				arrival[v] = arrival[x]+graph[x][v];
				if( treeIncludes(v) ){
					deleteParentEdge(v);
					ne--;
				} else {
					treeV[nv]=v;
					nv++;
				}
				treeE[ne][0]=x;
				treeE[ne][1]=v;
				ne++;
			}
		}
	}
}

bool Dijkstra::treeIncludes( int v ){
	int i=0;
	while( treeV[i]>=0 || i<nNode ){
		if( v==treeV[i] )
			return true;
		i++;
	}
	return false;
}

void Dijkstra::deleteParentEdge(int v)
{
	int i=0;
	while( treeE[i][1]!=v ){
		i++;
	}
	treeE[i][0]=-1;
	treeE[i][1]=-1;
}

int* Dijkstra::showPath(int start, int target)
{
	int* path = new int[nNode-1];
	for( int i=0; i<nNode-1; i++ ){
		path[i] = -1;
	}
	
	int p = target;
	int s = start;
	int k = 1;
	path[0]=p;
	
	while( p!=s ){
		for( int i=0; i<nNode-1; i++ ){
			if( treeE[i][1]==p ){
				p=treeE[i][0];
				path[k]=p;
				k++;
			}
			if( p==s ){
				break;
			}
		}
	}
	
	reverseOrder(k,path);
	return path;
}

void Dijkstra::reverseOrder(int k, int path[])
{
	int* w = new int[k];
	int i;
	
	for( i=0; i<k; i++ ){
		w[i] = path[k-i-1];
	}
	for( i=0; i<k; i++ ){
		path[i] = w[i];
	}
	delete [] w;
}
