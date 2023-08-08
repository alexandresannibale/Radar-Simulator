#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include "signalFuctions.cpp"
#include "DAConverter.cpp"
#include "VPConverter.cpp"
#include "radarPropagation.cpp"
#include "PVConverter.cpp"
#include "ADConverter.cpp"

int main(){
    //noise vector    vector<double> Tx;

    vector<double> noise;
    //pulse signal reversed
    vector<double> reversed;    
    //return signal
    vector<double> Rx;
    //return signal after convolution
    vector<double> convRx;
    //zeros vector
    vector<double> zeroV;
    //return signal with no noise
    vector<double> RxKaleen;

    DAConverter DAC(10.0, -10.0, 8);

    ADConverter ADC(10.0,-10.0, 8);

    radar_Propagation propagator;

    double dt = 0.001 _us;

    vector<double> TxChirp = chirpGenerator(1, 20 _MHz, 500 _MHz, 5 _us, 0, dt);

    vector <double> Vchirp = DAC.convertVector(TxChirp);

    vector <double> Pchirp = gainVPConverter(Vchirp, 50, 100);

    vector<double> PRx = propagator.caculatePowerReceived(Pchirp);
    
    vector<double> VRx = gainPVConverter(PRx,50,100);

    vector<int> VADCout = ADC.convertVector(VRx);

    noise = randomNoiseGenerator(60 _us, dt, 0, 1);
    
    //sineGenerator(&Tx , 1 , 200 _MHz, 2 _us ,0 , dt);
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