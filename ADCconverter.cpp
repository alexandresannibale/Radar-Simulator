#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;


class ADC_Converter
{
public:
//float voltage;
float maxV;
float minV;
float scaler;
public:
    ADC_Converter(float max, float min, int numBits)
    {
        maxV = max;
        minV = min;
        scaler = (pow(2,numBits+1)-1)/max;
    }
    
    int converter(float voltage)
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

    vector<int> converterVector(vector<float> &voltageVector)
    {
       vector<int> convertedVoltage;
       int n = voltageVector.size();
       convertedVoltage.reserve(n);
       
       for (int i = 0; i < n; i++)     
        {   
            float voltage = voltageVector.at(i);
            if (voltage > maxV)
                voltage = maxV;

            else if (voltage < minV)
                voltage = minV;

           convertedVoltage.push_back(voltage * scaler);
          
        }       
        return convertedVoltage;
    }
};

void vectorPrint(vector<int> &vp)
{

    for (int i=0; i < vp.size(); i++)
    {
    cout << i << " " << vp.at(i) << endl;  
    }
}

int main()
{
    vector<float> v{1,2,300};
    ADC_Converter Signal1(10.0, -10.0, 8);
    //cout << Signal1.converter(5.3); 
    vector <int> b = Signal1.converterVector(v);
    vectorPrint(b);
    cout << endl << Signal1.scaler;
}