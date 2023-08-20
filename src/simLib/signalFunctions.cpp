#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include "signalFunctions.h"

#define _us *1e-6
#define _MHz *1e6


using namespace std;
// Generates Sine wave of radar propagation
void sineGenerator(vector<double> *v, double A ,double f,double t, double phi, double dt)
{
    int n= int(t/dt);
    v->clear();
    v->reserve(n); 

    for (int i=0; i < n; i++)
    {
        v->push_back(A*sin(2*M_PI*f*dt*i+phi));
      //  cout << dt*i << " " << v[i] << endl;
    }
}

vector<double> chirpGenerator(double A ,double f1, double f2, double t, double phi, double dt)
{
    vector<double> v;
    int n = int(t/dt);
    v.clear();
    v.reserve(n);

    double df_dt = (f2-f1)/t;
    cout << f1 << " " << f2 << " " << df_dt << " " << t << " " << dt * 1e6 << endl;
    for (int i=0; i < n; i++)
    {
        double f = df_dt*i*dt+ f1;
        v.push_back(A*sin(2*M_PI*f*dt*i+phi));
    }
    return v;
}

vector<double> signalReverse(vector<double> &s)
{
    vector<double> r;
    int n= s.size();
    r.clear();
    r.reserve(n);

    for (int i=n-1; i >= 0; i--)
        r.push_back(-s.at(i));
    
    return r;
}

vector<double> zerosGenerator(double t, double dt)
{
    vector<double> v;
    int n = int(t/dt);
    v.assign(n, 0);
    return v;
}

vector<double> randomNoiseGenerator(int n, double mu, double sigma)
{
    default_random_engine generator;
    normal_distribution<double> distribution(mu,sigma);
    vector<double> v;
    v.reserve(n);

    for (int i=0; i < n; i++)
        v.push_back(distribution(generator));
    
    return v;
}

vector<double> randomNoiseGeneratorOld(double t, double dt, double mu, double sigma)
{
    default_random_engine generator;
    normal_distribution<double> distribution(mu,sigma);
    vector<double> v;
    int n = int(t/dt);
    v.reserve(n);

    for (int i=0; i < n; i++)
        v.push_back(distribution(generator));
        
    return v;
}

vector<double> signalAdd(vector<double> &v1, vector<double> &v2, double t0, double dt)
{
    int n = v1.size();
    vector<double> vC;
    vC.clear();
    vC.reserve(n);
    
    int b = int(t0/dt);
    int e = v2.size() + b;
     // cout << e << " "<< b << " " << n << endl;
    for (int i=0; i < n; i++)
    {
        
        if ((i >= b) && (i < e))
        {
          if ( i <100) 
            cout << i-b<< " " << i << " " << v1.at(i)+v2.at(i-b) << endl;
            vC.push_back(v1.at(i)+v2.at(i-b));
        }
        else
        {
            vC.push_back(v1.at(i));
        }
    }
    return vC;
}
void vectorPrinterDouble(vector<double> &vp, double dt)
{
    for (int i=0; i < vp.size(); i++)
    {
    cout << i * dt << " " << vp.at(i) << endl;  
    }
}

vector <double> RxVector(vector <double> signal, double Rt, double Rr,double Rmax,double dt)
    {
        double c = 2.998e+8; //speed of light in meters per second
        //int b = int((((Rt + Rr)/c))/dt);
        double t0 = (Rt + Rr)/c;
        cout <<"t0: "<< t0 << endl;
        int m = int(2*Rmax/c/dt);
        cout <<"m: "<< m << endl;
        vector <double> delay(m,0);
        cout << "size: " << delay.size()<< endl;  

   //     vectorPrinterDouble(delay,dt);
        return signalAdd(delay, signal, t0, dt);
    }


vector<double> doubleConverter(vector<int> &v, double scalingFactor)
{
    vector<double> Dv;
    int n = v.size();
    Dv.reserve(n);
    for (int i=0; i < n; i++)
        Dv.push_back(double(v.at(i))*scalingFactor);
    return Dv;
}

vector<int> intConverter(vector<double> &v, double scalingFactor)
{
    vector<int> Iv;
    int n = v.size();
    Iv.reserve(n);
    for (int i=0; i < n; i++)
        Iv.push_back(int(round(v.at(i)* scalingFactor)));
    return Iv;
}
vector<double> convolution(vector<double> &original ,vector<double> &ret )
{
    vector<double> c;
    int I = original.size();
    int K = ret.size();
    cout << I<<"   cvbfcb    " << K << endl;
    for (int i=0; i <= I-K; i++)
    {
        double x = 0;
    //    cout << "for loop 1" << endl;
        for(int k = 0; k < K; k++)
        {
            x = x + ret.at(k) * original.at(i + k);
      //      cout << "for loop 2" << endl;
        }
        c.push_back(x);
    }
    return c;
    
}

double findMaxValue(vector<double> &v)
{
    
    double mV = v.at(0);   
    for (int i=1; i < v.size()  ; i++)
    {
        if (mV < v.at(i))
            mV = v.at(i);
    }
    return mV;
    
}



void vectorPrinterInt(vector<int> &vp, double dt)
{
    for (int i=0; i < vp.size(); i++)
    {
    cout << i * dt << " " << vp.at(i) << endl;  
    }
}

void saveVector(vector<double> &vp, double dt, string data_path)
{
    ofstream fw(data_path, ofstream::out);
    for (int i=0; i < vp.size(); i++)
    {
        fw << i * dt << " " << vp.at(i) << endl;  
    }
    fw.close();
}

void saveVectorInt(vector<int> &vp, double dt, string data_path)
{
    ofstream fw(data_path, ofstream::out);
    for (int i=0; i < vp.size(); i++)
    {
        fw << i * dt << " " << vp.at(i) << endl;  
    }
    fw.close();
}