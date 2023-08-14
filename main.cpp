#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include "signalFunctions.cpp"
#include "DAConverter.cpp"
#include "VPConverter.cpp"
#include "radarPropagation.cpp"
#include "PVConverter.cpp"
#include "ADConverter.cpp"
#include "LNA.cpp"

int main(){
    //noise vector    vector<double> Tx;

    vector<double> noise;
    //pulse signal reversed
    vector<double> reverse;    
    //return signal after convolution
    vector<double> convRx;
    //zeros vector
    vector<double> zeroV;
    //return signal with no noise
    vector<double> RxKaleen;
    //number of bit for scaling
    int numBits=8;
    double Gt = 1000;
    DAConverter DAC(10.0, -10.0, numBits, 0);

    ADConverter ADC(10.0,-10.0, numBits);

    LNA PA1(1000.0, -1000.0, 100);

    LNA LNA1(10.0, -10.0, 100);

    LNA LNA2(10.0, -10.0, 1000);

    radar_Propagation propagator;

    double dt = 0.001 _us;

    //sineGenerator(&Tx , 1 , 200 _MHz, 2 _us ,0 , dt);

    vector<double> TxChirp = chirpGenerator(1, 20 _MHz, 500 _MHz, 5 _us, 0, dt);

    vector<int> intTxChirp = intConverter(TxChirp,pow(2,numBits)-1);

    vector <double> Vchirp = DAC.convertVector(intTxChirp);

    Vchirp = PA1.amplifyVector(Vchirp);


    vector <double> Pchirp = gainVPConverter(Vchirp, 50, 100);

    double PTx = findMaxValue(Pchirp);
  
    cout << "PTx: "<< PTx << endl;

    double PRx = propagator.caculatePowerReceived(PTx);

    cout << "PRx: " << PRx << endl;


    double V0Rx = gainPVConverter(PRx,50,Gt);

    vector<double> VRxChirp = chirpGenerator(V0Rx, 20 _MHz, 500 _MHz, 5 _us, 0, dt);

    VRxChirp = signalReverse(VRxChirp);
    
 //   vector<double> VRx = RxVector(VRxChirp,0,0, propagator.getRmax() ,dt); 


    vector<double> VRx =RxVector(VRxChirp,propagator.getRt(), propagator.getRr(), propagator.getRmax() ,dt); 

    vector<double> VRxA = LNA1.amplifyVector(VRx);

    VRxA = LNA2.amplifyVector(VRxA);

    vector<int> VRxC = ADC.convertVector(VRxA);

    vector<double> Rx = doubleConverter(VRxC, 1/(pow(2,numBits)-1));

    reverse = signalReverse(TxChirp);

    convRx = convolution(Rx, reverse);
   
    zeroV = zerosGenerator(60 _us, dt);
    RxKaleen = signalAdd(zeroV, reverse, 20  _us, dt);
    //vectorPrinterInt(intTxChirp,dt);
   // vectorPrinterDouble(Vchirp,dt);
    saveVectorInt(intTxChirp, dt, "intTxChirp.txt");
    saveVector(Vchirp, dt, "Vchirp.txt");
    saveVector(Pchirp, dt, "Pchirp.txt");
    saveVector(VRxChirp, dt, "VRxChirp.txt");


    saveVector(VRxA, dt, "VRxA.txt");

    saveVectorInt(VRxC, dt, "VRxC.txt");

    saveVector(Rx, dt, "Rx.txt");
    saveVector(VRx, dt, "VRx.txt");

    saveVector(reverse, dt, "reverse.txt");
    saveVector(Rx, dt, "Rx.txt");
    saveVector(RxKaleen, dt, "RxKaleen.txt");
    saveVector(TxChirp, dt, "TxChirp.txt");

    saveVector(convRx, dt, "convolutionSignal.txt");
    saveVector(noise, dt, "randomNoise.txt");
}