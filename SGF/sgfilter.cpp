#include "sgf.h"
#include <iostream>
#include <cmath>

/*
This child class deals with smoothing data using the Savitzky-Golay filter
and it also calculates derivatives using this method
 */

Basefilter::Basefilter(){}
Basefilter::~Basefilter(){}

SGFilter::SGFilter(){}
SGFilter::SGFilter(unsigned int M_, unsigned int N_, unsigned S_) : M(M_), N(N_), S(S_) {}
SGFilter::~SGFilter(){}

bool SGFilter::loadConfig(std::string &config){
    if(std::count(config.begin(), config.end(), '-')==1){
        size_t pos = config.find_first_of('-');
        std::string mstr = config.substr(0,pos);
        std::string nstr = config.substr(pos + 1, config.size() - pos);
        M = std::stoi(mstr);
        N = std::stoi(nstr);
        S = 0;
        if(M<=0|| N<=0 ){
            std::cerr<<"Invalid input, please enter numbers larger than 0."<<"\n";
            return false;
            }
        else if (M<N){
            std::cerr<<"Invalid input, polynomial order must be a smaller number than the filter length."<<"\n";
               return false;
            }
        return true;
    }
    else if(std::count(config.begin(), config.end(), '-')==2){
        size_t pos1 = config.find_first_of('-');
        size_t pos2 = config.find_last_of('-');
        std::string mstr = config.substr(0,pos1);
        std::string nstr = config.substr(pos1 + 1, config.size() - pos1);
        std::string sstr = config.substr(pos2+1, config.size()-pos2);
        M = std::stoi(mstr);
        N = std::stoi(nstr);
        S = std::stoi(sstr);
        if (S<0){
            std::cerr<<"Invalid input, please enter numbers larger than 0."<<"\n";
            return false;
        }
        if(M<=0|| N<=0 ){
                std::cerr<<"Invalid input, please enter numbers larger than 0."<<"\n";
                return false;
            }
        else if (M<N){
                std::cerr<<"Invalid input, polynomial order must be a smaller number than the filter length."<<"\n";
                   return false;
            }
        return true;
    }
    else{
        std::cerr<<"Invalid number of parametres for this filter."<<"\n";
        return false;
    }
}

bm::matrix<double> SGFilter::matrixH(){
    std::vector<int> n;
    for(int k =M*(-1);k<=(int)M;k++){ //inserting variables into n from -M to M
       n.push_back(k);
       }

   bm::matrix<double> A(2*M+1, N+1); //create design matrix A
    for(unsigned int i = 0;i<=N;i++){
        for(unsigned int k = 0;k<n.size();k++){
            A(k,i) = std::pow(n[k],i);
       }
    }
    bm::matrix<double>H(N+1,2*M+1); //create matrix H for further use
    bm::matrix<double> AtA = bm::prod(bm::trans(A),A);
    bm::matrix<double> AtAinv = inverseMat(AtA);   //compute H
    if(AtAinv.size1()==1){
        return AtAinv;
    }

    H = bm::prod(AtAinv,bm::trans(A));

   return H;
}

bool SGFilter::filter(std::vector<points *> &data){
        if (M>=1+(data.size()*2)){
            std::cerr<<"Invalid input, filter length exceeds the ammount of data."<<"\n";
            return false;
        }

    bm::matrix<double> H = matrixH();
    if (H.size1()==1){
        std::cerr<<"Failed to filter data."<<"\n";
        return false;
    }

    for(unsigned int n=M;n<data.size();n++){ //iterate over data and smooth it
        for(unsigned int m=n-M;m<=n+M;m++){
            if(n < data.size()-M){
                data[n]->yout += H(0,(M-(n-m)))*data[m]->yin;
            }
            else{
                data[n]->yout = data[data.size()-M-1]->yout; //adding the end data manually
            }
        }
    }

    for(unsigned int n=0;n<M;n++){
        data[n]->yout = data[M]->yout; //adding the data to the beginning manually
            }
    std::cout<<"Data filtered successfully."<<"\n";
    return true;
}

bool SGFilter::derivative(std::vector<points *> &data){
        if (M>=1+(data.size()*2)){
            std::cerr<<"Invalid input, filter length exceeds the ammount of data."<<"\n";
            return false;
        }

    bm::matrix<double> H = matrixH();
    if (H.size1()==1){
        std::cerr<<"Failed to filter data."<<"\n";
        return false;
    }

    for(unsigned int n=M;n<data.size();n++){ //iterate over data and smooth it
        for(unsigned int m=n-M;m<=n+M;m++){
            if(n < data.size()-M){
                data[n]->yout += H(S,M-(n-m))*data[m]->yin;
            }
            else{
                data[n]->yout = data[data.size()-M-1]->yout; //adding the end data manually
            }
        }
    }

    for(unsigned int n=0;n<M;n++){
        data[n]->yout = data[M]->yout; //adding the data to the beginning manually
            }
    std::cout<<"Data filtered successfully."<<"\n";
    return true;
}





