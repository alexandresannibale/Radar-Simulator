#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "LNA.cpp"
#include "signalFunctions.cpp"
#include <gtest/gtest.h>

using namespace std;

void vectorPrint(vector<double> &vp)
{

    for (int i=0; i < vp.size(); i++)
    {
    cout << i << " " << vp.at(i) << endl;  
    }
}

int main()
{
    vector<double> v{1,2,300,0.7};
    LNA Signal1(10.0, -10.0, 8,2);
    //cout << Signal1.converter(5.3); 
    vector <double> b = Signal1.amplifyVector(v);
    vectorPrint(b);
    cout << endl << Signal1.gain;
    return 0;
}