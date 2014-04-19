//
//  DirectRelation.h
//  CNImplementation
//
//  Created by 長谷川 知里 on 12/04/26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef CNImplementation_DirectRelation_h
#define CNImplementation_DirectRelation_h

#include "stdafx.h"

class DirectRelation {
private:
    int nRel;
    vector<int> relIDs;
public:
    DirectRelation(){ nRel = 0; };
    const int getNRel(){ return nRel; };
    const void setDirectRelation( const int relID );
    const void replaceDirectRelation( const int oldRelID, const int newRelID );
    const bool removeDirectRelation( const int removingRelID );
};

#endif
