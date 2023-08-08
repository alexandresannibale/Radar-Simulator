#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;


class ADConverter
{
public:
//double voltage;
double maxV;
double minV;
double scaler;
public:
    ADConverter(double max, double min, int numBits)
    {
        maxV = max;
        minV = min;
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
       
       for (int i = 0; i < n; i++)     
        {   
            double voltage = voltageVector.at(i);
            if (voltage > maxV)
                voltage = maxV;

            else if (voltage < minV)
                voltage = minV;

           convertedVoltage.push_back(voltage * scaler);
          
        }       
        return convertedVoltage;
    }
};