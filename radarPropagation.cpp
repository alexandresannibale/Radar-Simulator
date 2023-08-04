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


vector<double> randomNoiseGenerator(double t, double dt, double mu, double sigma)
{
    default_random_engine generator;
    normal_distribution<double> distribution(mu,sigma);
    vector<double> v;
    int n = int(t/dt);
    v.clear();
    v.reserve(n);

    for (int i=0; i < n; i++)
    {
        v.push_back(distribution(generator));
    }
    return v;
}

vector<double> signalAdd(vector<double> &v1, vector<double> &v2, double t0, double dt)
{
    vector<double> vC;
    int n = v1.size();
    vC.clear();
    vC.reserve(n);

    int b = int(t0/dt);
    int e = v2.size() + b;
     // cout << e << " "<< b << " " << n << endl;
    for (int i=0; i < n; i++)
    {
        
        if ((i >= b) && (i < e))
        {
         // cout << i-b<< " " << i << endl;
            vC.push_back(v1.at(i)+v2.at(i-b));
        }
        else
        {
            vC.push_back(v1.at(i));
        }
    }
    return vC;
}

vector<double> convolution(vector<double> &v, vector<double> &r)
{
    vector<double> c;
    int I = v.size();
    int K = r.size();

    for (int i=0; i < I-K; i++)
    {
        double x = 0;

        for(int k = 0; k < K; k++)
        {
            x = x + r.at(k) * v.at(i + k);
        }
        c.push_back(x);
    }
    return c;
    
}

void vectorPrinter(vector<double> &vp, double dt)
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


int main(){
    //noise vector    vector<double> Tx;

    vector<double> noise;
    //pulse signal reversed
    vector<double> reversed;    
    //return signal
    vector<double> Rx;
    //return signal after convolution
    vector<double> convRx;
    //Tx chirp signal
    vector<double> TxChirp;
    //zeros vector
    vector<double> zeroV;
    //return signal with no noise
    vector<double> RxKaleen;


    double dt = 0.001 _us;

    noise = randomNoiseGenerator(60 _us, dt, 0, 1);
    
    //sineGenerator(&Tx , 1 , 200 _MHz, 2 _us ,0 , dt);
    TxChirp = chirpGenerator(1, 20 _MHz, 500 _MHz, 5 _us, 0, dt);
    reversed = signalReverse(TxChirp);
    
    Rx = signalAdd(noise, reversed, 20  _us, dt); 
    
    convRx = convolution(Rx, reversed);
    
    //vectorPrinter(&noise);
    
    zeroV = zerosGenerator(60 _us, dt);
    RxKaleen = signalAdd(zeroV, reversed, 20  _us, dt);
    

    saveVector(reversed, dt, "reversed.txt");
    saveVector(Rx, dt, "Rx.txt");
    saveVector(RxKaleen, dt, "RxKaleen.txt");
    saveVector(TxChirp, dt, "TxChirp.txt");

    saveVector(convRx, dt, "convolutionSignal.txt");
    saveVector(noise, dt, "randomNoise.txt");
}