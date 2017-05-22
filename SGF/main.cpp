#include "sgf.h"
#include <iostream>
#include <string>
#include <sstream>



int main(int argc, char **argv)
{
    std::string inpath = argv[1];
    std::string outpath = argv[2];
    std::string type;
    std::string config;
    if (argc > 3){
        type = argv[3];
        config = argv[4];
    }
    else{
        type = "SGF";
        config = "25-4";
    }

    std::string parametres = type+config;
    std::string outname = getfilename(inpath,parametres);
    Basefilter *fltr = NULL;
    //load data
    std::vector<points *>A;
    if (!load(inpath,A)){
    goto cleanup;
    }
   //check the data
    if(type == "SGF"){
           fltr = new SGFilter();
           if (!fltr) {
               std::cerr<<"Memory allocation failed."<<"\n";
               return -1;
           }

           if(!fltr->loadConfig(config)){
               return -1;
           }
           if(!fltr->filter(A)){
               goto cleanup;
           }
       }
    else if(type=="MA"){
        fltr = new MAFilter();
        if (!fltr) {
            std::cerr<<"Memory allocation failed."<<"\n";
            return -1;
        }

        if(!fltr->loadConfig(config)){
            return -1;
        }
        if(!fltr->filter(A)){
            goto cleanup;
        }
    }
    else if(type=="der"){
        fltr = new SGFilter();
        if (!fltr) {
            std::cerr<<"Memory allocation failed."<<"\n";
            return -1;
        }

        if(!fltr->loadConfig(config)){
            return -1;
        }
        if(!fltr->derivative(A)){
            goto cleanup;
        }

    }
    else{
        std::cerr<<"Invalid type of filter."<<"\n";
        return -1;
       }

     //save the data
     std::cout<<outname<<std::endl;
     if(!save(outname,outpath,A)){
         goto cleanup;
     }

cleanup:
        std::vector<points *>::iterator it;
        for (it = A.begin(); it != A.end(); ++it) {
            delete (*it);
        }

delete fltr;
return 0;
}

