//
//  Eigen.h
//  CNImplementation
//
//  Created by 知里 長谷川 on 12/01/31.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "stdafx.h"
#include "math.h"

using namespace std;

const double eps = 1e-8;
const int count_limit = 100000;

typedef vector<double> array;
typedef vector<array> matrix;


struct LUinfo {
    vector<double> value;
    vector<int> index;
};

class Eigen {
private:
    int counter;
    double inner_product(array,array);
    LUinfo LU_decomposition(matrix);
    array LU_backsubstitution(const LUinfo,array);
public:
    void hessenberg(matrix &A);
    vector<double> eigenvalues(matrix A);
    array eigenvector(matrix A, double lambda);
};