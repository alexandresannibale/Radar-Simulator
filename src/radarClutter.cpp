#include <iostream>
#include <cmath>
#include "radarPropagation.cpp"
using namespace std;
//Distance from radar to the target
class point{
public:
    double p[3];


    double radarTargetDistance(){

        return sqrt(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]);
    }
    point (double x, double y, double z){

        p[0] = x;
        p[1] = y;
        p[2] = z;
        
    }


};

bool detection(double Prx, double P){
    if (Prx < (0.01*P)){
        return false;
    }
    else{
        return true;
    }
}


int main(){

    point P = point(5,4,3);
    double R = P.radarTargetDistance();

    radar_Propagation target = radar_Propagation(1000,20 ,20, 0.3,1,R,R,1);
    double Prx = target.caculatePowerReceived();
    cout << Prx << endl;
    double Ptx = target.getP();
    cout << Ptx << endl;
    cout << "detected " << detection(Prx,Ptx) << endl;


   
}

/*
    position_Radar

    propagate_Beam

    finds_Return_Power

    determines_Detection

    updates_Radar_Screen

    propagate_Beam

    finds_Return_Power

    determine_Target_Velocity

    update_Radar_Screen

    plot_Target_Trajectory

*/

