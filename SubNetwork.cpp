//
//  SubNetwork.cpp
//  CNImplementation
//
//  Created by 知里 長谷川 on 11/10/22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "SubNetwork.h"

void SubNetwork::makeSubNetwork(Network network, bool v[]){
    int* nodeIndex = getSubNetworkNodeIndex(network,v);
}

int* SubNetwork::getSubNetworkNodeIndex(Network network, bool v[]){
    int i;
    subNNode = 0;
    for( i=0; i<network.getNNode(); i++ ){
        subNNode = v[i] ? subNNode+1 : subNNode;
    }
}