#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <random>

using namespace std;

vector<double> randomNoiseGenerator(int , double , double );


class LNA
{
public:
double maxV;
double minV;
double gain;
double sigmaV= 100e-6;

public:
    LNA(double max, double min, double G, double sigma)
    {
        maxV = max;
        minV = min;
        gain = G;
        sigmaV= sigma;
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
       vector<double> noise = randomNoiseGenerator(n, 0, sigmaV);


       
       for (int i = 0; i < n; i++)     
        {   
            double Vout = voltageVector.at(i) * gain +noise.at(i);

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

