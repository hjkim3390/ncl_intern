#include <iostream>

using namespace std;

class Cell{
    private:
    double vrest; //mV
    double vth; //mV
    double tau; // ms

    double ib; // nA

    public: 
    bool initialized;
    double dt;
    double t; // ms
    double vm; // mV


    Cell(double vrest=-60, double vth=-50, double tau=20, double ib=0){
        this->vrest = vrest;
        this->tau = tau;
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
        vm += 1/tau * (vrest - vm) * dt;
    }
};