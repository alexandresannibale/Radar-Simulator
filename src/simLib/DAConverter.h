#ifndef _SIMLIB_DACONVERTER
#define _SIMLIB_DACONVERTER 1

#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <random>
using namespace std;

class DAConverter
{
public:
double maxV =10;
double minV =-10;
double sigmaV = 0;
double scaler = (pow(2,8)-1)/maxV;

public:
    DAConverter(double max, double min, int numBits, double sigma);
    
    double converter(int digital);

    vector<double> convertVector(vector<int> &TxChirp);
};

#endif