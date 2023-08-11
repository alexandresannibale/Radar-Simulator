#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;

vector<double> gainVPConverter(vector<double> &v,  double resistance, double Gt)
{
    vector<double> VPSignalVector;
    int n = v.size();
    VPSignalVector.reserve(n);
    
    for (int i=0; i < n; i++)
        VPSignalVector.push_back(v.at(i)*v.at(i)/resistance*Gt);

    return VPSignalVector;
}