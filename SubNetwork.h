//
//  SubNetwork.h
//  CNImplementation
//
//  Created by 知里 長谷川 on 11/10/22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "NetworkExpression.h"

class SubNetwork : public Network {
    
private:
    int subNNode;
    
public:
    SubNetwork();
    ~SubNetwork();
    void makeSubNetwork(Network,bool[]);
    int* getSubNetworkNodeIndex(Network,bool[]);
};