#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <random>
#include "signalFunctions.h"
#include "DAConverter.h"
using namespace std;

DAConverter::DAConverter(double max, double min, int numBits, double sigma)
{
    maxV = max;
    minV = min;
    sigmaV = sigma;
    scaler = (pow(2,numBits)-1)/max; //most significant bit used for the sign
}
    
double DAConverter::converter(int digital)
{
    default_random_engine generator;

    normal_distribution<double> distribution(0,sigmaV);
    double conversion = digital/scaler + distribution(generator);
    return conversion;       
}

vector<double> DAConverter::convertVector(vector<int> &TxChirp)
{
    vector<double> convertedAnalogVector;
    int n = TxChirp.size();
    convertedAnalogVector.reserve(n);
    vector<double> noise = randomNoiseGenerator(n, 0, sigmaV);

    for (int i = 0; i < n; i++)     
    {   
        double digital = TxChirp.at(i)/scaler + noise.at(i);
            
        if (digital > maxV)
            digital = maxV;

        else if (digital < minV)
            digital = minV;

        convertedAnalogVector.push_back(digital);
    //    convertedAnalogVector.push_back(digital);

    }       
    return convertedAnalogVector;
}

