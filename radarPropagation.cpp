#include <iostream>
#include <cmath>
#include <vector>
#define _us *1e-6
#define _MHz *1e6

using namespace std;
class radar_Propagation {
private:
   
    double P= 1000;  //Peak transmit power in watts
    
    double Gt = 20; //Transmitter gain
    
    double Gr = 20; //Receiver gain
    
    double phi = 0.3; //Radar operating frequency wavelength in meters
    
    double L = 1; //General loss factor to account for both system and propagation loss
    
    double Rt= 10320; //Range from transmiter to the target
    
    double Rr=10320; //Range from the receiver to the target
    
    double k=1.380658e-23; //Botz Constant
    
    double sigma = 1; //target area cross section

public:

//getters and setters
    void setP(double P_){
        P = P_;
    }
    double getP(){
        return P;
    }

    void setGt(double Gt_){
        Gt = Gt_;
    }
    double getGt(){
        return Gt;
    }
    
    void setGr(double Gr_){
        Gr = Gr_;
    }
    double getGr(){
        return Gr;
    }
    
    void setphi(double phi_){
        phi = phi_;
    }
    double getphi(){
        return phi;
    }
    
    void setL(double L_){
        L = L_;
    }
    double getL(){
        return L;
    }
    
    void setRt(double Rt_){
        Rt = Rt_;
    }
    double getRt(){
        return Rt;
    }
    
    void setRr(double Rr_){
        Rr = Rr_;
    }
    double getRr(){
        return P;
    }    
    
    void setsigma(double sigma_){
        sigma = sigma_;
    }
    double getsigma(){
        return sigma;
    }
    
    void setk(double k_){
        k = k_;
    }
    double getk(){
        return k;
    }

// class constructor
    radar_Propagation(double P_, double Gt_, double Gr_, double phi_,double sigma_, double L_, double Rt_,double Rr_)
    {
        P = P_;
        Gt = Gt_;
        Gr = Gr_;
        phi = phi_;
        sigma = sigma_;
        L = L_;
        Rt = Rt_;
        Rr = Rr_;
    }

//fuction 
    double caculatePowerReceived()
    {
    // Returns power in Watt units       
        double Prx = (P*Gt*Gr*phi*phi*sigma)/((4*M_PI)*(4*M_PI)*(4*M_PI)*Rt*Rt*Rr*Rr*L);
    //    cout << Prx << "W" << endl;
    //    cout << endl;
        return Prx;
    }
};
void sineGenerator(vector<double> *v, double A ,double f,double t, double phi, double dt)
{
    int n= int(t/dt);
 //   v->reserve(n);
    for (int i=0; i < n; i++)
    {
        v->push_back(A*sin(2*M_PI*f*dt*i+phi));
      //  cout << i * 0.01 _us << " " << v[i] << endl;
    }
}

void signalReverse(vector<double> *r, vector<double> *s)
{
    int n= s->size();
    for (int i=n-1; i >= 0; i--)
    {
        r->push_back(s->at(i));
    }
}

void noiseGenerator(vector<double> *v, double t, double dt)
{
    int n= int(t/dt);
    //v->reserve(n);
    for (int i=0; i < n; i++)
    {
        v->push_back(0);
    }

}

void signalAdd(vector<double> *vC, vector<double> *v1, vector<double> *v2, double t0, double dt)
{
    
    int n = v1->size();
   // vC->reserve(n);
    int b = int(t0/dt);
    int e = v2->size() + b;
     // cout << e << " "<< b << " " << n << endl;
    for (int i=0; i < n; i++)
    {
        
        if ((i >= b) && (i < e))
        {

         //   cout << i-b<< " " << i << endl;
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

void vectorPrinter(vector<double> *vp)
{
    for (int i=0; i < vp->size(); i++)
    {
    cout << i * 0.01 _us << " " << vp->at(i) << endl;  
    }
}



int main(){
    //noise generator vector
    vector<double> noise;
    //pulse signal reversed
    vector<double> reversed;
    //pulse signal
    vector<double> Tx;
    //return signal
    vector<double> Rx;
    //return signal after convolution
    vector<double> conv;

    noiseGenerator(&noise, 6 _us, 0.01 _us);
    sineGenerator(&Tx , 1 , 1 _MHz, 2 _us ,0 , 0.01 _us);
    signalAdd(&Rx, &noise, &Tx, 1  _us, 0.01 _us); 
    signalReverse(&reversed, &Tx);
    convolution(&Rx,&reversed,&conv);
    vectorPrinter(&conv);

}