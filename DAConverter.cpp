#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;


class DAC_Converter
{
public:
double maxV;
double minV;
double scaler;
public:
    DAC_Converter(double max, double min, int numBits)
    {
        maxV = max;
        minV = min;
        scaler = (pow(2,numBits+1)-1)/max;
    }
    
    double converter(double digital)
    {
        double conversion = digital/scaler;
        return conversion;       
    }

    vector<double> converterVector(vector<double> &TxChirp)
    {
       vector<double> convertedAnalogVector;
       int n = TxChirp.size();
       convertedAnalogVector.reserve(n);
       
       for (int i = 0; i < n; i++)     
        {   
            double digital = TxChirp.at(i);
            if (digital > maxV)
                digital = maxV;

            else if (digital < minV)
                digital = minV;

           convertedAnalogVector.push_back(digital/scaler);
          
        }       
        return convertedAnalogVector;
    }
};

void vectorPrint(vector<double> &vp)
{

    for (int i=0; i < vp.size(); i++)
    {
    cout << i << " " << vp.at(i) << endl;  
    }
}

int bill()
{
    vector<double> v{1,2,300};
    DAC_Converter Signal1(10.0, -10.0, 8);
    //cout << Signal1.converter(5.3); 
    vector <double> b = Signal1.converterVector(v);
    vectorPrint(b);
    cout << endl << Signal1.scaler;
    return 0;
}