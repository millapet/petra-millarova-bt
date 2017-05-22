#ifndef SGF_H
#define SGF_H

#include <string>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

namespace bm = boost::numeric::ublas;

struct points{
    double x, yin, yout;
    points(double x_, double yin_, double yout_ = 0) : x(x_),yin(yin_),yout(yout_){}
};

bool load(const std::string &inputPath, std::vector<points *> &data);
bool save(const std::string &outputFileName, const std::string &outputFolder, std::vector<points *> &data);
std::string getfilename(const std::string &inputPath, const std::string params);

bm::matrix<double> inverseMat(bm::matrix<double> Mat);

class Basefilter{
public:
    Basefilter();
    virtual ~Basefilter();
    virtual bool filter(std::vector<points *> &data) = 0;
    virtual bool loadConfig(std::string &config) = 0;
    virtual bool derivative(std::vector<points *> &data) = 0;
};

class SGFilter : public Basefilter{
public:
    SGFilter(unsigned int M, unsigned int N, unsigned int S);
    SGFilter();
    virtual ~SGFilter();
    virtual bool filter(std::vector<points *> &data);
    virtual bool loadConfig(std::string &config);
    virtual bool derivative(std::vector<points *> &data);
private:
    bm::matrix<double> matrixH();
    unsigned int M;
    unsigned int N;
    unsigned int S;
};

class MAFilter : public Basefilter{
public:
    MAFilter(unsigned int M);
    MAFilter();
    virtual ~MAFilter();
    virtual bool filter(std::vector<points *> &data);
    virtual bool loadConfig(std::string &config);
    virtual bool derivative(std::vector<points *> &data);
private:
    unsigned int M;
};

#endif // SGF_H
//base filter

