#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
using namespace std;
vector<double> randomNoiseGenerator(int , double , double );

vector<double> gainPVConverter(vector<double> &RxChirp,  double resistance, double Gt, double sigmaV)
{
    vector<double> PVSignalVector;
    int n = RxChirp.size();
    PVSignalVector.reserve(n);
    vector<double> noise = randomNoiseGenerator(n, 0, sigmaV);

    
    for (int i=0; i < n; i++)
    {
        PVSignalVector.push_back(sqrt((RxChirp.at(i))*Gt*resistance)+noise.at(i));
    }
    return PVSignalVector;
}


double gainPVConverter(double PRx,  double resistance, double Gt)
{
    return sqrt(PRx*Gt*resistance);
}