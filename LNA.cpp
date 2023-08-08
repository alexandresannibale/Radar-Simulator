#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;


class LNA
{
public:
double maxV;
double minV;
double gain;

public:
    LNA(double max, double min, double G)
    {
        maxV = max;
        minV = min;
        gain = G;
    }
    
    int amplify(double Vin)
    {
        double Vout = Vin * gain;
        if (Vout > maxV)
            Vout = maxV;

        else if (Vout < minV)
            Vout = minV;

        return Vout;       
    }

    vector<double> amplifyVector(vector<double> &voltageVector)
    {
       vector<double> VoutVector;
       int n = voltageVector.size();
       VoutVector.reserve(n);
       
       for (int i = 0; i < n; i++)     
        {   
            double Vout = voltageVector.at(i) * gain;

            if (Vout > maxV)
                Vout = maxV;

            else if (Vout < minV)
                Vout = minV;

           VoutVector.push_back(Vout);
          
        }       
        return VoutVector;
    }
};

// void vectorPrint(vector<int> &vp)
// {

//     for (int i=0; i < vp.size(); i++)
//     {
//     cout << i << " " << vp.at(i) << endl;  
//     }
// }