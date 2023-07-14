#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <string>

#define _us *1e-6
#define _MHz *1e6

using namespace std;

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

void chirpGenerator(vector<double> *v, double A ,double f1, double f2, double t, double phi, double dt)
{
    int n = int(t/dt);
    v->clear();
    v->reserve(n);

    double df_dt = (f2-f1)/t;
    cout << f1 << " " << f2 << " " << df_dt << " " << t << " " << dt * 1e6 << endl;
    for (int i=0; i < n; i++)
    {
        double f = df_dt*i*dt+ f1;
        v->push_back(A*sin(2*M_PI*f*dt*i+phi));
       //cout << dt*i << " " << v->at(i) << endl;
    }
}

void signalReverse(vector<double> *r, vector<double> *s)
{
    int n= s->size();
    r->clear();
    r->reserve(n);

    for (int i=n-1; i >= 0; i--)
    {
        r->push_back(-s->at(i));
    }
}

void zerosGenerator(vector<double> *v, double t, double dt)
{
    int n= int(t/dt);
    v->assign(n, 0);
}


void randomNoiseGenerator(vector<double> *v, double t, double dt, double mu, double sigma)
{
    default_random_engine generator;
    normal_distribution<double> distribution(mu,sigma);
    
    int n = int(t/dt);
    v->clear();
    v->reserve(n);

    for (int i=0; i < n; i++)
    {
        v->push_back(distribution(generator));
    }

}

void signalAdd(vector<double> *vC, vector<double> *v1, vector<double> *v2, double t0, double dt)
{
    
    int n = v1->size();
    vC->clear();
    vC->reserve(n);

    int b = int(t0/dt);
    int e = v2->size() + b;
     // cout << e << " "<< b << " " << n << endl;
    for (int i=0; i < n; i++)
    {
        
        if ((i >= b) && (i < e))
        {
         // cout << i-b<< " " << i << endl;
            vC->push_back(v1->at(i)+v2->at(i-b));
        }
        else
        {
            vC->push_back(v1->at(i));
        }
    }
}

void convolution(vector<double> *v, vector<double> *r, vector<double> *c)
{
    int I = v->size();
    int K = r->size();

    for (int i=0; i < I-K; i++)
    {
        double x = 0;

        for(int k = 0; k < K; k++)
        {
            x = x + r->at(k) * v->at(i + k);
        }
        c->push_back(x);
    }
    
}

void vectorPrinter(vector<double> *vp, double dt)
{
    for (int i=0; i < vp->size(); i++)
    {
    cout << i * dt << " " << vp->at(i) << endl;  
    }
}

void saveVector(vector<double> *vp, double dt, string data_path)
{
    ofstream fw(data_path, ofstream::out);
    for (int i=0; i < vp->size(); i++)
    {
        fw << i * dt << " " << vp->at(i) << endl;  
    }
    fw.close();
}


int main(){
    //noise vector
    vector<double> noise;
    //pulse signal reversed
    vector<double> reversed;    
    //pulse signal
    vector<double> Tx;
    //return signal
    vector<double> Rx;
    //return signal after convolution
    vector<double> conv;
    //Tx chirp signal
    vector<double> TxChirp;

    //return signal with no noise
    vector<double> RxKaleen;


    double dt = 0.001 _us;

    randomNoiseGenerator(&noise, 60 _us, dt, 0, 1);
    
    //sineGenerator(&Tx , 1 , 200 _MHz, 2 _us ,0 , dt);
    chirpGenerator(&Tx,1, 20 _MHz, 500 _MHz, 5 _us, 0, dt);
    signalReverse(&reversed, &Tx);
    
    signalAdd(&Rx, &noise, &reversed, 20  _us, dt); 
    
    convolution(&Rx, &reversed,&conv);
    
    //vectorPrinter(&noise);
    
    zerosGenerator(&noise, 60 _us, dt);
    signalAdd(&RxKaleen, &noise, &reversed, 20  _us, dt); 
    

    saveVector(&reversed, dt, "reversed.txt");
    saveVector(&Rx, dt, "Rx.txt");
    saveVector(&RxKaleen, dt, "RxKaleen.txt");
    saveVector(&Tx, dt, "Tx.txt");

    saveVector(&conv, dt, "convolutionSignal.txt");
    saveVector(&noise, dt, "randomNoise.txt");
}