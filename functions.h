#pragma once
#define _USE_MATH_DEFINES 

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <random>
#include "Vector3f.h"

using namespace std;

vector<Vector3f> generate_torus_positions(int num_neurons, double total_radius, double torus_radius) {
    vector<Vector3f> positions;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0, 2 * M_PI);

    for (int i = 0; i < num_neurons; ++i) {
        double theta = uniform_dist(gen);
        double phi = uniform_dist(gen);
        double x = (total_radius + torus_radius * cos(theta)) * cos(phi);
        double y = (total_radius + torus_radius * cos(theta)) * sin(phi);
        double z = torus_radius * sin(theta);
        positions.push_back(Vector3f(x, y, z));
    }
    return positions;
}

vector<int> generate_sender_gid(vector<Vector3f> positions) {
    vector<int> ans;
    int num_cell = positions.size();
    int cell_num = num_cell * 926 / 20000;

    return ans;
}

vector<int> generate_receiver_exc_gid(vector<Vector3f> positions) {
    vector<int> ans;

    int num_cell = positions.size();
    int cell_num = num_cell * 463 / 20000;
    return ans;

}

vector<int> generate_receiver_inh_gid(vector<Vector3f> positions) {
    vector<int> ans;

    int num_cell = positions.size();
    int cell_num = num_cell * 73 / 20000;
    return ans;

}

// generate poisson inputs
random_device rd;  // Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
uniform_real_distribution<> dis(0.0, 1.0);

vector<double> generate_poisson_input(double dt = 0.1, double tmax = 650.0, double max_rate = 140.0/1000, double f_osc = 10.0/1000){
    vector<double> spike_time;

    for(int i=0;i<tmax/dt;i++){
        double time = i * dt;
        double rate = max_rate * (sin(2*M_PI*f_osc*i*dt)+1)/2;
        // cout << rate << endl;
        if (dis(gen) < rate * dt){
            spike_time.push_back(time);
        }
    }
    return spike_time;
}

// export function

void export2csv_singlecell(string filename, Cell cell, string option="spike_timing"){
    vector<double> recording_vec; 

    if(option == "spike_timing"){
        recording_vec = cell.spike_timing;
    }else if(option == "voltage_trace"){
        recording_vec = cell.voltage_trace;
    }else {
        cout << "wrong option! option is 'spike_timing' or 'voltage_trace'" << endl;
        return;
    }

    ofstream myfile;
    myfile.open(filename);
    myfile << option << endl;
    for(int i=0;i<recording_vec.size();i++){
        myfile << recording_vec.at(i) << endl;
    }
}