//
//  Eigen.cpp
//  CNImplementation
//
//  Created by 知里 長谷川 on 12/01/31.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "Eigen.h"

double Eigen::inner_product(array x, array y){
    double ans=0.0;
    for( int i=0; i<x.size(); i++ )
        ans += x[i]*y[i];
    return ans;
}

// O(n^3)
void Eigen::hessenberg(matrix &A){
    const int n = A.size();
    for( int k=1; k<=n-2; k++ ){
        array u(n);
        for( int i=k; i<n; i++)
            u[i] = A[i][k-1];
        
        double ss = 0;
        for( int i=k+1; i<n; i++ )
            ss += u[i] * u[i];
        if( fabs(ss) <= 0.0 )
            continue;
        double s = sqrt( ss+u[k]*u[k] );
        if( u[k] > 0.0 )
            s = -s;
        
        u[k] -= s;
        double uu = sqrt( ss+u[k]*u[k] );
        for( int i=k; i<n; i++ )
            u[i] /= uu;
        
        array f(n), g(n);
        for( int i=0; i<n; i++ ){
            for( int j=k; j<n; j++ ){
                f[i] += A[i][j] * u[j];
                g[i] += A[j][i] * u[j];
            }
        }
        double gamma = inner_product(u,g);
        for( int i=0; i<n; i++ ){
            f[i] -= gamma * u[i];
            g[i] -= gamma * u[i];
        }
        
        for( int i=0; i<n; i++ )
            for( int j=0; j<n; j++ ){
                A[i][j] = A[i][j] - 2*u[i]*g[j] - 2*f[i]*u[j];
            }
    }
}

// find all eigenvalues using Hessenberg-QR Method
// O( n^3 + M n^2 ) where M is the number of iterations.
vector<double> Eigen::eigenvalues(matrix A) {
    const int n = A.size();
    hessenberg(A);
    counter = 0;
    vector<double> s(n), c(n);
    for (int m = n; m >= 2; ) {
        if (fabs(A[m-1][m-2]) < eps) { --m; continue; }
        if( counter++ > count_limit ){
            array false_vector(n);
            return false_vector;
        }
        double shift = A[m-1][m-1];
        for (int i = 0; i < m; ++i) A[i][i] -= shift;
        for (int k = 0; k < m-1; ++k) {
            double a = A[k][k], b = A[k+1][k], r = sqrt(a*a + b*b);
            s[k] = r == 0.0 ? 0.0 : b/r,
            c[k] = r == 0.0 ? 0.0 : a/r;
            for (int j = k; j < m; ++j) {
                double x = A[k][j], y = A[k+1][j];
                double a = A[k][j];
                A[ k ][j] =  c[k] * x + s[k] * y;
                a = A[k][j];
                A[k+1][j] = -s[k] * x + c[k] * y;
            }
        }
        for (int k = 0; k < m-1; ++k) {
            for (int i = 0; i <= k+1; ++i) {
                double x = A[i][k], y = A[i][k+1];
                A[i][ k ] =  c[k] * x + s[k] * y;
                A[i][k+1] = -s[k] * x + c[k] * y;
            }
        }
        for (int i = 0; i < m; ++i) A[i][i] += shift;
    }
//    cout << "count : " << counter << endl;
    vector<double> lambda;
    for (int i = 0; i < n; ++i)
        lambda.push_back( A[i][i] );
    return lambda;
}

// find the corresponding eigenvector from the eigenvalue.
// O ( n^3 + M n^2 ) where M is the number of iterations.
array Eigen::eigenvector(matrix A, double lambda) {
    const int n = A.size();
    array y(n);
    y[0] = 1.0;
    for( int i=1; i<n; i++ ) y[i] = 0.0;
    for (int i = 0; i < n; i++) A[i][i] -= lambda;
    LUinfo data = LU_decomposition(A);
    double mu, v2, v2s;
    do {
        array v = LU_backsubstitution(data, y); // A v = y
        mu = inner_product(v, y);
        v2 = inner_product(v, v);
        v2s = sqrt(v2);
        for( int j=0; j<n; j++ ) y[j] = v[j] / v2s;
    } while (fabs(1.0-mu*mu/v2) > eps);
    return y;
}

// O( n^3 ), Gaussian forward elimination
LUinfo Eigen::LU_decomposition(matrix A) {
    const int n = A.size();
    LUinfo data;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i+1; j < n; ++j)
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[i]);
        data.index.push_back(pivot);
        // if A[i][i] == 0, LU decomposition failed.
        for(int j = i+1; j < n; ++j) {
            A[j][i] /= A[i][i];
            for(int k = i+1; k < n; ++k)
                A[j][k] -= A[i][k] * A[j][i];
            data.value.push_back(A[j][i]);
        }
    }
    for(int i = n-1; i >= 0; --i) {
        for(int j = i+1; j < n; ++j)
            data.value.push_back(A[i][j]);
        data.value.push_back(A[i][i]);
    }
    return data;
}

// O( n^2 ) Gaussian backward substitution
array Eigen::LU_backsubstitution(const LUinfo data, array b) {
    const int n = b.size();
    int k = 0;
    for (int i = 0; i < n; ++i){
        swap(b[data.index[i]], b[i]);
        for(int j = i+1; j < n; ++j)
            b[j] -= b[i] * data.value[k++];
    }
    for (int i = n-1; i >= 0; --i) {
        for (int j = i+1; j < n; ++j)
            b[i] -= b[j] * data.value[k++];
        b[i] /= data.value[k++];
    }
    return b;
}