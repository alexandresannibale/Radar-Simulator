#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "DAConverter.cpp"

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
    vector<int> v{127,128,255,-255,0,256,-256};
    DAConverter Signal1(10.0, -10.0, 8);
    //cout << Signal1.converter(5.3); 
    vector <double> b = Signal1.convertVector(v);
    vectorPrint(b);
    cout << endl << Signal1.scaler;
    return 0;
}