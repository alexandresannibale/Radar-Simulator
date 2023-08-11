#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;


class DAConverter
{
public:
double maxV;
double minV;
double scaler;
public:
    DAConverter(double max, double min, int numBits)
    {
        maxV = max;
        minV = min;
        scaler = (pow(2,numBits)-1)/max; //most significant bit used for the sign
    }
    
    double converter(int digital)
    {
        double conversion = digital/scaler;
        return conversion;       
    }

    vector<double> convertVector(vector<int> &TxChirp)
    {
       vector<double> convertedAnalogVector;
       int n = TxChirp.size();
       convertedAnalogVector.reserve(n);
       
       for (int i = 0; i < n; i++)     
        {   
            int digital = TxChirp.at(i)/scaler;
            if (digital > maxV)
                digital = maxV;

            else if (digital < minV)
                digital = minV;

           convertedAnalogVector.push_back(digital);
          
        }       
        return convertedAnalogVector;
    }
};