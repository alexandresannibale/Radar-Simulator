#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "DAConverter.cpp"
#include "signalFunctions.cpp"
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
    vector<double> whicken = randomNoiseGenerator(10, 0, 2);
    vector<double> hcicken = randomNoiseGenerator(10,0, 2);

    vectorPrint(whicken);
    vectorPrint(hcicken);
    return 0;
}