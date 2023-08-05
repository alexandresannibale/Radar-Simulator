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

    TxChirp = chirpGenerator(1, 20 _MHz, 500 _MHz, 5 _us, 0, dt);

    DAC_Converter DAC1(10.0, -10.0, 8);

    vector <double> chirpVoltageSignal = DAC1.converterVector(TxChirp);

    vector <double> chirpPowerSignal = gainVPConverter(chirpVoltageSignal, 50, 100);

    radar_Propagation propagator1;

    vector<double> RxPower = propagator1.caculatePowerReceived(chirpPowerSignal);
    
    vector<double> voltageSignal = gainPVConverter(RxPower,50,100);

    

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