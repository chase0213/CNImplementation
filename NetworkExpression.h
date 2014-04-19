/*
 *  NetworkExpression.h
 *  CNImplementation
 *
 *  Created by 長谷川 知里 on 11/09/29.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "stdafx.h"
#include "resource.h"
#include "Community.h"

using namespace std;

typedef vector<Community> Communities;
typedef vector<double> array;

class Network {
    
private:
	int nNode; // # of nodes of whole network
	int nEdge; // # of edges of whole network
    int nDetectedCommunity;
	int **adjMatrix;
	int *degreeVector;
    MatrixXd subgraph;
    vector<int> comKind; // vector for kinds of communities
    vector<double> modVector; // vector for modularities in the process
    vector<int> sdv; // degree vector of subgraph
    int snd; // sum of degrees of subgraph
    int snn; // # of nodes of subgraph
    int noc; // # of communities
    const void makeSelfAdjoint(bool); // make any graphs self adjoint

public:
	// コンストラクタ
	Network(string);
	// デコンストラクタ
	~Network();
    
    // Network coefficient
	const double getEdgeBetweeness(int,int); // NOT implemented
    const int getNNode(){return nNode;};
    const int getNEdge(){return nEdge;};
	const int getDegree(int i){return degreeVector[i];};
    const int getAMElement(int i,int j){return adjMatrix[i][j];};
    const int getNDetectedCommunity(){return nDetectedCommunity;};
    const double getModularity(); // if no variables are derived, calculate for the graph
    const double getModularity(const vector<bool>);
    const double getModularity(const vector<int>);
    
    // Graph Arithmetics
	const vector<bool> getAdjacent(int);
    const vector<bool> getIntersectionVertexSet(vector<bool>,vector<bool>);
    const vector<bool> getUnionVertexSet(vector<bool>,vector<bool>);
	const vector<bool> getTwoIntersectionWithAdjacentVertex(int,int);
    const vector<bool> getTwoUnionWithAdjacentVertex(int,int);
    
    // Community Detection for One Node
    const vector<bool> getCandidateOfCommunity(int,int,int);
    const Community* detectCommonCommunity(int,int);
	const Community optimizeCommunity(Community,int,int);
	const Community greedyOptimizeCommunity(Community,int,int);
	const Community optimizeByGeneticAlgorithm(Community,int,int);

    // Community Detection for the Whole Network
    const vector<int> getComKind();
    const vector<bool> createCommunity(int,bool*);
    const void spectralCommunityStructure();
    const void createSubgraph(vector<bool>);
    const void deleteSubgraph();
    const void setCommunities(double,VectorXd,int);
    const void showKoC();
    const bool eigenProcess(int);
    
    // More casual community detection
    const void casualMethodSingleLayer();
    const int maxDegreeVertex(vector<bool>);
    const vector<int> makeRandomPermutation();
    const bool fullMarked(vector<bool>);
    const void removeOverlap(vector< vector<bool> >);
};