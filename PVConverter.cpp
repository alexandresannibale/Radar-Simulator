#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;

vector<double> gainPVConverter(vector<double> &RxChirp,  double resistance, double Gt)
{
    vector<double> PVSignalVector;
    int n = RxChirp.size();
    PVSignalVector.reserve(n);
    for (int i=0; i < n; i++)
    {
        PVSignalVector.push_back(sqrt((RxChirp.at(i))*Gt*resistance));
    }
    return PVSignalVector;
}


double gainPVConverter(double PRx,  double resistance, double Gt)
{
    return sqrt(PRx*Gt*resistance);
}