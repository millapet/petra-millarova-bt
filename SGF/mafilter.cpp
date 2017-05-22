#include "sgf.h"
#include <iostream>
#include <cmath>

/*
This child class smoothes the data with a moving average filter of given length
 */

MAFilter::MAFilter(){}
MAFilter::MAFilter(unsigned int M_) : M(M_){}
MAFilter::~MAFilter(){}

bool MAFilter::loadConfig(std::string &config){
    if (std::count(config.begin(), config.end(), '-')!=0){
        std::cerr<<"Invalid number of parametres for this filter."<<"\n";
        return false;
    }

    try{
        M = std::stoi(config);
    }
    catch(...){
        std::cerr<<"Config load failed."<<"\n";
        return false;
    }

    if(M<=0){
            std::cerr<<"Invalid input, please enter numbers larger than 0."<<"\n";
            return false;
        }
    return true;
}

bool MAFilter::filter(std::vector<points *> &data){

    for(unsigned int n=M;n<data.size();n++){ //iterate over data and smooth it
        for(unsigned int m=n-M;m<=n+M;m++){
            if(n < data.size()-M){
                data[n]->yout += (1/(2.0*M + 1))*data[m]->yin;
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

bool MAFilter::derivative(std::vector<points *> &data){
    std::cerr<<"Invalid function."<<"\n";
    return false;
}
