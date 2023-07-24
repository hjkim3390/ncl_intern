#include <iostream>

using namespace std;

class Cell{
    private:
    double vrest; //mV
    double vth; //mV

    double cm; //nF
    double gl; //uS

    double gex; //uS
    double eex; //mV
    double ginh; //uS
    double einh; //mV

    double ib; // nA

    public: 
    bool initialized;

    double dt;
    double t; // ms

    double vm; // mV
    bool activated;


    Cell(double vrest=-60, double vth=-50, double ib=0.3){
        cout << "cell initialized" << endl;
        this->vrest = vrest;
        this->vth = vth;

        this->cm = 0.2;
        this->gl = 0.01;

        // gex
        // eex
        // ginh
        // einh

        this->ib = ib;

        this->initialized = false;
        this->dt = 0.1;
        this->t = 0;
    }

    void initialize(double vm){
        this->vm = vm;
        this->initialized = true;
    }

    void step(){
        if(!initialized){
            cout << "not initialized Cell.initialize() needed" << endl;
        }

        double _il = gl * (vrest - vm); // 1) leak current
        double _ib = ib; // 2) bias current 

        double i = _il + _ib;

        vm += i / cm * dt;

        if(vm > vth){
            activated = true;
            cout << "activated" << endl;
            vm = vrest;
        }
    }
};