#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;
vector<double> randomNoiseGenerator(int , double , double );


vector<double> gainVPConverter(vector<double> &v,  double resistance, double Gt, double sigmaV)
{
    vector<double> VPSignalVector;
    int n = v.size();
    VPSignalVector.reserve(n);
    vector<double> noise = randomNoiseGenerator(n, 0, sigmaV);

    
    for (int i=0; i < n; i++)
        VPSignalVector.push_back(v.at(i)*v.at(i)/resistance*Gt+noise.at(i));

    return VPSignalVector;
}