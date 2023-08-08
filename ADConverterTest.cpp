#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "ADConverter.cpp"

using namespace std;


void vectorPrint(vector<int> &vp)
{

    for (int i=0; i < vp.size(); i++)
    {
    cout << i << " " << vp.at(i) << endl;  
    }
}

int main()
{
    vector<double> v{1,2,300};
    ADConverter Signal1(10.0, -10.0, 8);
    //cout << Signal1.converter(5.3); 
    vector <int> b = Signal1.convertVector(v);
    vectorPrint(b);
    cout << endl << Signal1.scaler;
}