/*
 *  Namelist.cpp
 *  CNImplementation
 *
 *  Created by 長谷川 知里 on 11/11/22.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Namelist.h"

int getIdFromName( string name ){
	for( int i=0; NAMELIST[i]!="\0"; i++ ){
		if( name.compare(0,name.size(),NAMELIST[i])==0 )
			return i;
	}
	return -1;
}