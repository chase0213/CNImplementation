//
//  DirectedEdge.h
//  CNImplementation
//
//  Created by 長谷川 知里 on 12/05/07.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef CNImplementation_DirectedEdge_h
#define CNImplementation_DirectedEdge_h

class DirectedEdge {
    int snID; // source vertex ID
    int dnID; // destination vertex ID
    int weight;
    DirectedEdge *prev;
    DirectedEdge *next;
    
public:
    // Constructor
    DirectedEdge(int sID, int dID, int w, DirectedEdge* p, DirectedEdge* n){
        snID = sID;
        dnID = dID;
        weight = w;
        prev = p;
        next = n;
    };
    
    // Setter
    void setDirectedEdge(int sID, int dID){snID = sID; dnID = dID;};
    void setPreviousLink(DirectedEdge* pe){prev = pe;};
    void setNextLink(DirectedEdge* ne){next = ne;};
    void setLink(DirectedEdge* pe,DirectedEdge* ne){prev = pe; next = ne;};
    void setWeight(int w){weight = w;};
    
    // Getter
    int getSourceNodeID(){return snID;};
    int getDestinationNodeID(){return dnID;};
    int getWeight(){return weight;};
    DirectedEdge* getPreviousLink(){return prev;};
    DirectedEdge* getNextLink(){return next;};
};

#endif
