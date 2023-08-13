#include <iostream>
#include <cmath>
#include <vector>
#define _us *1e-6
#define _MHz *1e6

using namespace std;

class radar_Propagation {
private:
   
    double P= 1000;  //Peak transmit power in watts
    
    double Gt = 1; //Transmitter gain
    
    double Gr = 1; //Receiver gain
    
    double phi = 0.3; //Radar operating frequency wavelength in meters
    
    double L = 1; //General loss factor to account for both system and propagation loss
    
    double Rt= 1000; //Range from transmiter to the target
    
    double Rr=1000; //Range from the target to receiver
    
    double k=1.380658e-23; //Boltzman Constant
    
    double sigma = 1; //target area cross section

    double c = 2.998e+8; //speed of light in meters per second

    double Rmax = 20000; //radar maxiumum range for testing


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

    void setRmax(double Rmax_){
        Rmax = Rmax_;
    }
    double getRmax(){
        return Rmax;
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

    radar_Propagation(){}

    
//fuctions 
    double caculatePowerReceived(double Pin)
    {
    // Returns power in Watt units       
        double PRx = (Pin*Gt*Gr*phi*phi*sigma)/((4*M_PI)*(4*M_PI)*(4*M_PI)*Rt*Rt*Rr*Rr*L);
    //    cout << Prx << "W" << endl;
    //    cout << endl;
        return PRx;
    }

    vector<double> caculatePowerReceived(vector<double> &signal)
    {
        vector<double> newSignal;
        int n = signal.size();
        for (int i=0; i < n; i++)
        {        
        newSignal.push_back(caculatePowerReceived(signal.at(i)));
        }
        return newSignal;
    }
};