#include "sgf.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

/*
This function creates an inverse matriic of the matrix given
in case of error returns matrix of size 1
*/

bm::matrix<double> inverseMat(bm::matrix<double> Mat){
    bm::matrix<double>zeromat(1,1);
    bm::matrix<double> Minv = bm::identity_matrix<double>(Mat.size1()); //create matrix Ainv
    typedef bm::permutation_matrix<std::size_t> pmatrix;
    pmatrix pm(Mat.size1());
    try{ lu_factorize(Mat,pm);
        lu_substitute(Mat,pm,Minv);
    }
    catch(...){
        Minv = zeromat;
        return zeromat;
    } //fill matrix Minv
    return Minv;
}

