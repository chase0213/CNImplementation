//
//  DirectRelation.cpp
//  CNImplementation
//
//  Created by 長谷川 知里 on 12/04/26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "DirectRelation.h"

const void DirectRelation::setDirectRelation( const int relID ){
    relIDs.push_back(relID);
    nRel++;
}

const void DirectRelation::replaceDirectRelation( const int oldRelID, const int newRelID ){
    replace(relIDs.begin(), relIDs.end(), oldRelID, newRelID);
}

const bool DirectRelation::removeDirectRelation(const int removingRelID){
    vector<int>::iterator itr = find(relIDs.begin(), relIDs.end(), removingRelID);
    if( itr == relIDs.end() ){
        return false;
    }
    itr = relIDs.erase(itr);
    return true;
}