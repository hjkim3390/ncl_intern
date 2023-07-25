#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Vector3f.h"

using namespace std;

class Cell {
private:
    int gid;
    string type;

    double vrest; // mV
    double vth; // mV
    double vaction;

    double cm; // nF
    double gl; // uS
    double tau; // ms
    double Eex; // mV
    double gex; // uS
    double tauex; // ms
    double Einh; // mV
    double ginh; // uS
    double tauinh; //ms

    double refractory_period; // ms

    double ib; // nA

    Vector3f pos;

public:
    bool ongoing;
    bool spiking_ongoing;
    bool spiked;
    double dt;
    double t; // ms
    double vm; // mV
    map<Cell*, double> exc_conns;
    map<Cell*, double> inh_conns;

    vector<double> spike_timing;
    int spike_cnt;
    vector<double> voltage_trace;

    Cell(int num_cell, int gid, Vector3f pos);

    bool operator<(const Cell& cell) const;

    void set_pos(Vector3f newpos);

    void step(); // steps derivative function for membrane potential
    void spike(); // spikes when vm > -50, add info into spike_timing
    void control_gs(); // step synaptic conductances. this function is inside void step().

    void make_conns();

    double get_gex() { return gex; }

    // spike force : external poisson input 
    void spike_force();
};