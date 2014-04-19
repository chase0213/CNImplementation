//
//  CasualMethod.cpp
//  CNImplementation
//
//  Created by 知里 長谷川 on 12/02/15.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "NetworkExpression.h"

const void Network::casualMethodSingleLayer(){
    
    vector< vector<bool> > ovlp;
    
    vector<bool> marks(nNode);
    for( int i=0; i<nNode; i++ )
        marks[i] = false;

    int c=1;
    
    // for debugging
    cout << nNode << " nodes we have" << endl;
    
    vector<int> rp = makeRandomPermutation();
    for( int j=0; j<nNode; j++ ){

        // break if all the verticies are marked
        if( fullMarked(marks) ) break;

        // choose one vertex at random if it is not marked
        int v = rp[j];
        if( marks[v] ) continue;
        
        // get adjacent verticies of v, chosen at random
        vector<bool> adj = getAdjacent(v);
        adj[v] = true;
        // get the maximum degree vertex of the subset
        int u = maxDegreeVertex(adj);
    
        // treat those as community
        adj = getAdjacent(u);
        adj[u] = true;
        for( int i=0; i<nNode; i++ ){
            if( adj[i] ){
                marks[i] = true;
            }
        }
        
        ovlp.push_back(adj);
        
        for( int i=0; i<nNode; i++ )
            cout << (adj[i] ? c : 0) << " ";
        cout << endl;
        c++;
    }
    
    // overlapping process
    removeOverlap(ovlp);
}

const int Network::maxDegreeVertex(vector<bool> adj){
    int idx = 0;
    for( int i=0; i<nNode; i++ ){
        if( adj[i] > adj[idx] ){
            idx = i;
        }
    }
    return idx;
}

const vector<int> Network::makeRandomPermutation(){
    vector<int> rp(nNode);
    for( int i=0; i<nNode; i++ )
        rp[i] = i;
    
    for( int i=nNode-1; i>=1; i-- ){
        int ri = rand()%i;
        swap(rp[i],rp[ri]);
    }
    return rp;
}

const bool Network::fullMarked(vector<bool> marks){
    for( int i=0; i<nNode; i++ )
        if( !marks[i] )
            return false;
    return true;
}

const void Network::removeOverlap(vector< vector<bool> > ovlp){
    int nOverlapped;
    for( int i=0; i<nNode; i++ ){
        nOverlapped = 0;
        for( int j=0; j<ovlp.size(); j++ ){
            if( ovlp[j][i] )
                nOverlapped++;
        }
        if( nOverlapped<=1 )
            continue;
        
        
    }
}