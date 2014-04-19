#include "stdafx.h"
#include "Dijkstra.h"
#include "NetworkExpression.h"
#include "namelist.h"


int main (int argc, char * const argv[]) {
    // insert code here...
	//int i;
    
//    Matrix2d A, c;
//    Vector2d b;
//    map<double,Vector2d> ev;
//    A << 10,0,-1,4;
//    cout << "Here is the matrix A:\n" << A << endl;
//    SelfAdjointEigenSolver<Matrix2d> eigensolver(A);
//    if (eigensolver.info() != Success) abort();
//    b = eigensolver.eigenvalues();
//    c = eigensolver.eigenvectors();
//    for( int i=0; i<2; i++ ){
//        ev.insert( make_pair( b(i,0), c.row(i) ));
//    }
//    map<double,Vector2d>::iterator it = ev.begin();
//    while( it!=ev.end() ){
//        cout << (*it).first << endl << (*it).second << endl;
//        it++;
//    }
    
//    cout << "The eigenvalues of A are:\n" << b << endl;
//    cout << "Here's a matrix whose columns are eigenvectors of A \n"
//    << "corresponding to these eigenvalues:\n"
//    << c << endl;
    
	
//	int x, y;
//	x = getIdFromName("chase0213");
//	y = getIdFromName("yusuketaka");
//	if( x==-1 || y==-1 ){
//		cout << "user not found!" << endl;
//		exit(1);
//	}

	Network network(INPUT_GRAPH);
    network.casualMethodSingleLayer();
//    network.spectralCommunityStructure();
//    vector<int> ck = network.getComKind();
//    ofstream ofs("result.txt");
//    if( ofs==NULL ){
//        cerr << "file cannot be opened" << endl;
//        exit(1);
//    }
//    ofs << "Kind of Communities" << endl;
//    for( int i=0; i<ck.size(); i++ ){
//        if( i%10 == 0 && i!=0 ) ofs << endl;
//        ofs << ck[i] << " ";
//    }
//    ofs << endl;
//    ofs.close();
//    
//    vector<int> koc;
//    for( int i=0; i<ck.size(); i++ ){
//        vector<int>::iterator index = find(koc.begin(),koc.end(),ck[i]);
//        if( index==koc.end() ){
//            koc.push_back(ck[i]);
//        }
//    }
    
//    for( int k=0; k<koc.size(); k++ ){
//        for( int i=0; i<ck.size(); i++ ){
//            if( ck[i] == koc[k] ){
//                cout << NAMELIST[i] << " ";
//            }
//        }
//        cout << endl << endl;
//    }
    
//    Eigen eigen;
//    matrix A(2,array(2));
//    A[0][0] = 8;
//    A[0][1] = 1;
//    A[1][0] = 4;
//    A[1][1] = 5;
//    array eigenvalues = eigen.eigenvalues(A);
//    array eigenvector = eigen.eigenvector(A,eigenvalues[0]);
//    
//    cout << "eigenvalues: " << eigenvalues[0] << " " << eigenvalues[1] << endl;
//    cout << "eigenvector for eigenvalue " << eigenvalues[0] << " : " << eigenvector[0] << " " << eigenvector[1] << endl;
//    eigenvector = eigen.eigenvector(A, eigenvalues[1]);
//    cout << "eigenvector for eigenvalue " << eigenvalues[0] << " : " << eigenvector[0] << " " << eigenvector[1] << endl;
    
//	cout << endl << "----- raw community -----" << endl;
//    for( i=0; i<network.getNDetectedCommunity(); i++ ){
//        vector<bool> com = coms[i].getCommunity();
//		cout << endl << coms[i].getModularity() << " : ";
//        for( int j=0; j<network.getNNode(); j++ ){
//			if( com[j] )
//				cout << NAMELIST[j] << " ";
//        }
//    }
//	
//	cout << endl << "----- optimized community -----" << endl;
//	for( i=0; i<network.getNDetectedCommunity(); i++ ){
//        vector<bool> com = coms[i].getCommunity();
//		Community community = network.optimizeCommunity(coms[i],x,y);
//		com = community.getCommunity();
//		cout << endl << community.getModularity() << " : ";
//        for( int j=0; j<network.getNNode(); j++ ){
//			if( com[j] )
//				cout << NAMELIST[j] << " ";
//        }
//	}
//	
//	cout << endl << "----- greedy optimized community -----" << endl;
//	for( i=0; i<network.getNDetectedCommunity(); i++ ){
//        vector<bool> com = coms[i].getCommunity();
//		Community community = network.greedyOptimizeCommunity(coms[i],x,y);
//		com = community.getCommunity();
//		cout << endl << community.getModularity() << " : ";
//        for( int j=0; j<network.getNNode(); j++ ){
//            if( com[j] )
//				cout << NAMELIST[j] << " ";
//		}
//	}
//	
//    delete[] coms;
    
	return 0;
}
