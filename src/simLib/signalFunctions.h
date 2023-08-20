#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <string>

#define _us *1e-6
#define _MHz *1e6


using namespace std;
// Generates Sine wave of radar propagation
void sineGenerator(vector<double> *v, double A ,double f,double t, double phi, double dt);

vector<double> chirpGenerator(double A ,double f1, double f2, double t, double phi, double dt);

vector<double> signalReverse(vector<double> &s);

vector<double> zerosGenerator(double t, double dt);

vector<double> randomNoiseGenerator(int n, double mu, double sigma);

vector<double> randomNoiseGeneratorOld(double t, double dt, double mu, double sigma);

vector<double> signalAdd(vector<double> &v1, vector<double> &v2, double t0, double dt);

void vectorPrinterDouble(vector<double> &vp, double dt);

vector <double> RxVector(vector <double> signal, double Rt, double Rr,double Rmax,double dt);

vector<double> doubleConverter(vector<int> &v, double scalingFactor);

vector<int> intConverter(vector<double> &v, double scalingFactor);

vector<double> convolution(vector<double> &original ,vector<double> &ret );

double findMaxValue(vector<double> &v);

void vectorPrinterInt(vector<int> &vp, double dt);

void saveVector(vector<double> &vp, double dt, string data_path);

void saveVectorInt(vector<int> &vp, double dt, string data_path);
