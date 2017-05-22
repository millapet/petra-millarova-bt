#include "sgf.h"
#include <iostream>
#include <typeinfo>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

/*
These functions deal with the .xml input and output
 */

namespace pt = boost::property_tree;

//load data from xml
bool load(const std::string &inputPath, std::vector<points*> &data){
    pt::ptree tree;
    try { //catching an exception in the event of a non-existing file
        pt::read_xml(inputPath, tree);
    }
    catch (...){
        std::cerr<<"Failed to read file."<<"\n";
        return false;
    }

    try{
        for (auto point : tree.get_child("endmember.spectraldata")) {
            points *ptr = new points(point.second.get<double>("x"),point.second.get<double>("y"));
            data.push_back(ptr);
         }
    }
    catch (...){
        std::cerr<<"Failed to load data."<<"\n";
        return false;
    }

    std::cout<<"Data loaded."<<"\n";
    return true;
}

// write data to xml
bool save(const std::string &outputFileName, const std::string &outputFolder, std::vector<points *> &data){
    pt::ptree tree;
    pt::ptree itreeator;
    pt::xml_writer_settings<std::string> settings(' ', 4);

    tree.put("endmember.header.name",outputFileName.substr(0,outputFileName.size()-4));
    for(unsigned int i=0; i< data.size();i++){
        std::stringstream strx;
        std::stringstream stry;
       strx <<std::fixed << std::setprecision(4)<<data[i]->x;
       stry <<std::fixed << std::setprecision(4)<<data[i]->yout;

       itreeator.put("x",strx.str());
       itreeator.put("y",stry.str());
       try{
           tree.add_child("endmember.spectraldata.point",itreeator);
       }
       catch (...){
           std::cerr<<"Failed to create file."<<"\n";
           return false;
       }

    };

    try{
        pt::write_xml(outputFolder+"/"+outputFileName, tree, std::locale(), settings);
    }
    catch(pt::xml_parser_error){
        std::cerr<<"Failed to write data into file."<<"\n";
        return false;
    }

    std::cout<<"File created succesfully. Yay!"<<"\n";
    return true;
    }

std::string getfilename(const std::string &inputPath, const std::string params){
    size_t pos = inputPath.find_last_of('\\');
    size_t dot = inputPath.find_last_of('.');
    std::string outputFileName = params+inputPath.substr(pos + 1, inputPath.size()-pos-5)+inputPath.substr(dot,inputPath.size()-dot);
    return outputFileName;
}
