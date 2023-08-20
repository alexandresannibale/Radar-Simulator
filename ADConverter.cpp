#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;
vector<double> randomNoiseGenerator(int , double , double );


class ADConverter
{
public:
//double voltage;
double maxV;
double minV;
double sigmaV = 100e-6;
double scaler;

public:
    ADConverter(double max, double min, int numBits, double sigma)
    {
        maxV = max;
        minV = min;
        sigmaV = sigma;

        scaler = (pow(2,numBits+1)-1)/max;
    }
    int converter(double voltage)
    {
        if (voltage > maxV)
            {
                voltage = maxV;
            }
        else if (voltage < minV)
        {
            voltage = minV;
        }

        int conversion = int(voltage * scaler);
        return conversion;       
    }

    vector<int> convertVector(vector<double> &voltageVector)
    {
       vector<int> convertedVoltage;
       int n = voltageVector.size();
       convertedVoltage.reserve(n);
       vector<double> noise = randomNoiseGenerator(n, 0, sigmaV);

       
       for (int i = 0; i < n; i++)     
        {   
            double voltage = voltageVector.at(i)+ noise.at(i);
            if (voltage > maxV)
                voltage = maxV;

            else if (voltage < minV)
                voltage = minV;

           convertedVoltage.push_back(voltage * scaler);
          
        }       
        return convertedVoltage;
    }
};