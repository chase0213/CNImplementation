/*
 *  NetworkExpression.cpp
 *  CNImplementation
 *
 *  Created by 長谷川 知里 on 11/09/29.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "NetworkExpression.h"
#include "Namelist.h"

using namespace std;

// コンストラクタ
Network::Network(string file){
	ifstream ifs;
    ifs.open(file.c_str());
    if( ifs==NULL ){
        cerr << "file " + file + " not found" << endl;
		exit(1);
	}
	nEdge = 0;
	ifs >> nNode;
	adjMatrix = new int*[nNode];
	degreeVector = new int[nNode];
	for( int i=0; i<nNode; i++ ){
		int deg = 0;
		adjMatrix[i] = new int[nNode];
		for( int j=0; j<nNode; j++ ){
			ifs >> adjMatrix[i][j];
			deg = (adjMatrix[i][j]>0) ? deg+1 : deg;
		}
		degreeVector[i] = deg;
		nEdge += deg;
	}
	nEdge /= 2;
	ifs.close();
    nDetectedCommunity = 0;
    
    // 有向グラフを無向グラフに変換
    makeSelfAdjoint(true);
    
    ofstream ofs(MIDLOG,ios::app);
    if( ofs==NULL ){
        cerr << "file cannot be opened";
        exit(1);
    }
    ofs << "------- Trial begins from here -------" << endl
    << "This is a result for " << INPUT_GRAPH << endl << endl;
    ofs.close();
}

// deconstructor
Network::~Network(){
	for(int i=0; i<nNode; i++){
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
	delete[] degreeVector;
}

// make any graphs self adjoint
const void Network::makeSelfAdjoint(bool strict){
    int tMatrix[nNode][nNode];
    for( int i=0; i<nNode; i++ )
        for( int j=0; j<nNode; j++ )
            tMatrix[i][j] = adjMatrix[j][i];
    for( int i=0; i<nNode; i++ ){
        for( int j=0; j<nNode; j++ ){
            if( strict )
                adjMatrix[i][j] = (adjMatrix[i][j]==1 && tMatrix[i][j]==1) ? 1 : 0;
            else
                adjMatrix[i][j] = (adjMatrix[i][j]==1 || tMatrix[i][j]==1) ? 1 : 0;
        }
    }
}

// NOT implemented yet
const double Network::getEdgeBetweeness(int nodeId1, int nodeId2){
	return 0.0;
}

// calculate the modularity of a given graph
const double Network::getModularity(){
	double modularity = 0.0;
    vector<int> tcom;
    
    for( int i=0; i<nNode; i++ ){
        vector<int>::iterator itr = find(tcom.begin(),tcom.end(),comKind[i]);
        if( itr==tcom.end() )
            tcom.push_back(comKind[i]);
    }
    
    // for all community
    for( int c=0; c<tcom.size(); c++ ){
        
        // add modularity derived from each community
        for( int i=0; i<nNode; i++ ){
            for( int j=0; j<nNode; j++ ){
                
                // continue if vi and vj are not in the same community, or if treating the same vertex
                if( comKind[i]!=tcom[c] || comKind[j]!=tcom[c] || i==j )
                    continue;
                
                // vi and vj are in the same community
                modularity += adjMatrix[i][j] - (degreeVector[i]*degreeVector[j])/(double)(2*nEdge);
            }
        }
        
    }
	modularity /= (2*nEdge);
	return modularity;
}

// calculate the modularity of given community
const double Network::getModularity(const vector<bool> v){
	double modularity = 0.0;
	for( int i=0; i<nNode; i++ ){
		// 入ってない頂点を見てもしょうがない
		if( !v[i] )
			continue;
		
		for( int j=0; j<nNode; j++ ){
			// 入ってない頂点、または自分自身を見てもしょうがない
			if( !v[j] || i==j )
				continue;
            
			modularity += adjMatrix[i][j] - (degreeVector[i]*degreeVector[j])/(double)(2*nEdge);
		}
	}
	modularity /= (2*nEdge);
	return modularity;
}

// calculate the modularity of a given graph
const double Network::getModularity(const vector<int> koc){
	double modularity = 0.0;
    vector<int> tcom;
    
    for( int i=0; i<nNode; i++ ){
        vector<int>::iterator itr = find(tcom.begin(),tcom.end(),koc[i]);
        if( itr==tcom.end() )
            tcom.push_back(koc[i]);
    }
    
    // for all community
    for( int c=0; c<tcom.size(); c++ ){
        
        // add modularity derived from each community
        for( int i=0; i<nNode; i++ ){
            for( int j=0; j<nNode; j++ ){
                
                // continue if vi and vj are not in the same community, or if treating the same vertex
                if( koc[i]!=tcom[c] || koc[j]!=tcom[c] || i==j )
                    continue;
                
                // vi and vj are in the same community
                modularity += adjMatrix[i][j] - (degreeVector[i]*degreeVector[j])/(double)(2*nEdge);
            }
        }
        
    }
	modularity /= (2*nEdge);
	return modularity;
}

const vector<bool> Network::getUnionVertexSet(vector<bool> u, vector<bool> v){
    vector<bool> r;
    for( int i=0; i<nNode; i++ ){
        r.push_back((u[i] || v[i]) ? true : false);
    }
    return r;
}

const vector<bool> Network::getIntersectionVertexSet(vector<bool> u, vector<bool> v){
    vector<bool> r;
    for( int i=0; i<nNode; i++ ){
        r.push_back((u[i] && v[i]) ? true : false);
    }
    return r;
}

// reutrn adjacent verticies to v
const vector<bool> Network::getAdjacent(int v){
	vector<bool> adj;
	for( int i=0; i<nNode; i++ ){
		adj.push_back(adjMatrix[v][i]);
	}
	return adj;
}

const vector<bool> Network::getTwoIntersectionWithAdjacentVertex(int u, int v){
	vector<bool> x = getAdjacent(u);
	vector<bool> y = getAdjacent(v);
	vector<bool> z = getIntersectionVertexSet(x,y);
	return z;
}

const vector<bool> Network::getTwoUnionWithAdjacentVertex(int u, int v){
    vector<bool> x = getAdjacent(u);
    vector<bool> y = getAdjacent(v);
    vector<bool> z = getUnionVertexSet(x,y);
    return z;
}

// uまたはvと隣接するtの隣接ノードを列挙する
const vector<bool> Network::getCandidateOfCommunity(int u, int v, int t){
    vector<bool> r = getTwoUnionWithAdjacentVertex(u,v);
    vector<bool> s = getAdjacent(t);
    r = getIntersectionVertexSet(r,s);
    r[u] = r[v] = r[t] = true;
    return r;
}

// detect common community between u and v
const Community* Network::detectCommonCommunity(int u, int v){
	int i, n;
    vector<bool> r = getTwoIntersectionWithAdjacentVertex(u,v);
    nDetectedCommunity = 0;
    for( i=0; i<nNode; i++ ){
        if( r[i] )
            nDetectedCommunity++;
    }
    Community *coms = new Community[nDetectedCommunity];
    vector<bool> s;
    for( i=0, n=0; i<nNode; i++ ){
        if( !r[i] )
            continue;
        s = getCandidateOfCommunity(u,v,i);
        coms[n].setCommunity(s);
        coms[n].setModularity(getModularity(s));
        n++;
    }
    return coms;
}

// u,v : 判定する2頂点
const Community Network::optimizeCommunity(Community com, int u, int v){
	// community with max modularity
	vector<bool> cwmm = com.getCommunity();
	double maxMod = com.getModularity();
	int maxIndex = -1;
	for( int i=0; i<com.getSize(); i++ ){
		for( int j=0; j<com.getSize(); j++ ){
			if( !cwmm[j] || j==u || j==v )
				continue;
			cwmm[j] = false;
			double mod = getModularity(cwmm);
			if( maxMod < mod ){
				maxMod = mod;
				maxIndex = j;
			}
			cwmm[j] = true;
		}
		if( maxIndex==-1 )
			return com;
		cwmm[maxIndex] = false;
	}
	Community optCom(cwmm);
	optCom.setModularity(maxMod);
	return optCom;
}

const Community Network::greedyOptimizeCommunity(Community com, int u, int v){
	// community
	vector<bool> cwmm = com.getCommunity();
	double maxMod = com.getModularity();
	for( int i=0; i<com.getSize(); i++ ){
		for( int j=0; j<com.getSize(); j++ ){
			if( !cwmm[j] || j==u || j==v )
				continue;
			cwmm[j] = false;
			double mod = getModularity(cwmm);
			if( maxMod < mod ){
				maxMod = mod;
			} else {
				cwmm[j] = true;
			}
		}
	}
	Community optCom(cwmm);
	optCom.setModularity(maxMod);
	return optCom;
}


// Spectral Method
const void Network::spectralCommunityStructure(){
    comKind.reserve(nNode); // i-th node is in the comKind[i]-th community
    modVector.reserve(2*nNode);
    for( int i=0; i<2*nNode-1; i++ ){
        bool found = false;
        vector<bool> com = createCommunity(i,&found);
        if( !found ) continue;
        createSubgraph(com);
        if( eigenProcess(2*i+1) ) continue;
    }
}

// change comKind to bool vector "com"
const vector<bool> Network::createCommunity(int j, bool* found){
    vector<bool> com(nNode);
    for( int i=0; i<nNode; i++ ){
        if( comKind[i]==(j+1)/2 || j==0 ){
            com[i] = true;
            *found = true;
        } else {
            com[i] = false;
        }
    }
    return com;
}

// calculate eigenvalues and eigenvectors
const bool Network::eigenProcess(int j2){
    
    // create and initialize subgraph
    MatrixXd B(snn,snn);
    for( int i=0; i<snn; i++ )
        for( int j=0; j<snn; j++ )
            B(i,j) = subgraph(i,j);
    
    // declare eigen solver
    SelfAdjointEigenSolver<MatrixXd> eigensolver(B);
    if( eigensolver.info()!=Success ) return false;
    VectorXd eigenvalues = eigensolver.eigenvalues();
    MatrixXd eigenvectors = eigensolver.eigenvectors();
    map<double,VectorXd> eigen_pair;
    for( int i=0; i<snn; i++ ){
        eigen_pair.insert( make_pair(eigenvalues(i,0),eigenvectors.col(i)) );
    }
    
    // set maximum eigenvalue and corresponding eivenvector
    map<double,VectorXd>::iterator it = eigen_pair.end();
    it--;
    
    // keep deviding into two communities until devided enough
    int idx = (j2-1)/2;
    modVector[idx] = (*(it)).first;
    if( (*it).first < eps ){
        return false;
    } else if( (*it).first < modVector[(idx-1)/2] ){
        modVector[idx] = modVector[(idx-1)/2];
        return false;
    }
    
    // output midlog
    ofstream ofs(MIDLOG,ios::app);
    if( ofs==NULL ){
        cerr << "file cannot be opened";
        exit(1);
    }
    ofs << (*it).first << " : " <<  modVector[(idx-1)/2] << endl;
    ofs.close();
    
    // set eigenvector
    VectorXd eigenvector(snn);
    if( (j2-1)/2 == 0 ){
//        it--;
        eigenvector = (*it).second;
//        it++;
    } else {
        eigenvector = (*it).second;
    }
    
    // set communities according to eigenvector
    setCommunities(eigenvalues[0],eigenvector,j2);
    
    // show kinds of communities
    showKoC();
    
    return true;
}

const void Network::setCommunities(double ev, VectorXd eigenvector, int j2){
    noc += 2;
    for( int i=0; i<eigenvector.size(); i++ ){
        if( eigenvector(i,0)>eps )
            comKind[i] = j2;
        else
            comKind[i] = j2+1;
    }
}

const void Network::createSubgraph(vector<bool> com){
    int n=0, x=0, y=0;
    snn = 0;
    
    // allocation of memory for subgraph
    for( int i=0; i<com.size(); i++ )
        if( com[i] )
            n++;
    sdv.reserve(n);
    subgraph.resize(n,n);
    for( int i=0; i<n; i++ ){
        sdv[i] = 0;
    }
    snd = 0;
    
    // actually creating a subgraph
    for( int i=0; i<nNode; i++ ){
        if( com[i] ){
            int degree = 0;
            snn++;
            y = 0;
            for( int j=0; j<nNode; j++ ){
                if( com[j] ){
                    subgraph(x,y) = (double)adjMatrix[i][j];
                    y++;
                    if( adjMatrix[i][j] )
                        degree++;
                }
            }
            sdv[i] = degree;
            snd += sdv[i];
            x++;
        }
    }
    
    // Bij = Aij - ki*kj / 2m
    for( int i=0; i<snn; i++ ){
        for( int j=0; j<snn; j++ ){
            subgraph(i,j) = subgraph(i,j) - sdv[i]*sdv[j] / (double)snd;
        }
    }
}

const void Network::deleteSubgraph(){
    sdv.clear();
}

// return comKind as a vector<int>
const vector<int> Network::getComKind(){
    vector<int> ck(nNode);
    for( int i=0; i<nNode; i++ )
        ck[i] = comKind[i];
    return ck;
}

// method for showing Kind of Community
const void Network::showKoC(){
    ofstream ofs(MIDLOG,ios::app);
    if( ofs==NULL ){
        cerr << "file cannot be opened" << endl;
        return;
    }
    ofs << "Modularity : " << getModularity() << endl;
    for( int i=0; i<nNode; i++ ){
        ofs << comKind[i] << " ";
    }
    ofs << endl << "-------------------------------" << endl;
    ofs.close();
}


