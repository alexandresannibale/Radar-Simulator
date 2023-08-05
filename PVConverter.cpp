#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;

vector<double> gainVPConverter(vector<double> &RxChirp,  double resistance, double Gt)
{
    vector<double> PVSignalVector;
    int n = RxChirp.size();
    PVSignalVector.reserve(n);
    for (int i=0; i < n; i++)
    {
        PVSignalVector.push_back(sqrt(RxChirp.at(i)*resistance));
    }
    return PVSignalVector;
}