#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include "signalFunctions.cpp"



using namespace std;

vector<double> signalTestingAdd(vector<double> &v1, vector<double> &v2, double t0, double dt)
{
    int n = v1.size();
    vector<double> vC;
    vC.clear();
    vC.reserve(n);
    
    int b = int(t0/dt);
    int e = v2.size() + b;
     // cout << e << " "<< b << " " << n << endl;
    for (int i=0; i < n; i++)
    {
        
        if ((i >= b) && (i < e))
        {
          if ( i <100) 
            cout << i-b<< " " << i << " " << v1.at(i)+v2.at(i-b) << endl;
            vC.push_back(v1.at(i)+v2.at(i-b));
        }
        else
        {
            vC.push_back(v1.at(i));
        }
    }
    return vC;
}


int main()
{
    vector<double> v1 =  {1,2,3,4,5,6,7,8,9,10};
    vector<double> v2 =  {10,20,30,40};

    vector <double> v3 = signalTestingAdd(v1,v2,3,1);

    vectorPrinterDouble(v3, 1);
    
}