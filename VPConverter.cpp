#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;

vector<double> gainVPConverter(vector<double> &TxChirp,  double resistance, double Gt)
{
    vector<double> VPSignalVector;
    int n = TxChirp.size();
    VPSignalVector.reserve(n);
    for (int i=0; i < n; i++)
    {
        VPSignalVector.push_back((pow(TxChirp.at(i),2)/resistance));
    }
    return VPSignalVector;
}