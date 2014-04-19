/*
 *  Community.h
 *  CNImplementation
 *
 *  Created by 長谷川 知里 on 11/10/22.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "stdafx.h"

using namespace std;

class Community {
	
private:
	double modularity;
	vector<bool> community;
    int size;
    
public:
    Community(){};
	Community(vector<bool> com){community = com; size = com.size();};
	~Community(){};
    void reserve(int n){community.reserve(n);};
    void setCommunity(vector<bool> com){community = com; size = com.size();};
	void setModularity(double mlt){modularity = mlt;};
    double getModularity(){return modularity;};
    vector<bool> getCommunity(){return community;};
    int getSize(){return size;};

};