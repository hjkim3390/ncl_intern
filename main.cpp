#include <iostream>
#include <vector>
#include <chrono>
#include "cell.h"
#include "Vector3f.h"
#include "functions.h"

using namespace std;
using namespace std::chrono;

// configurations

int num_cell = 2000;

int num_exc = num_cell * 3 / 4;
int num_gl_inh = (num_cell / 4) * 0.65;
int num_loc_inh = (num_cell / 4) * 0.35;

int total_radius = 100;
int torus_radius = 33;
int runtime = 650; // ms

vector<Vector3f> positions = generate_torus_positions(num_cell, total_radius, torus_radius);
vector<vector<double> > distance_map = make_distance_map(positions);
vector<pair<int, int> > exc_connlist = generate_exc_connlist(num_cell);
vector<pair<int, int> > gl_inh_connlist = generate_gl_inh_connlist(num_cell);
vector<pair<int, int> > loc_inh_connlist = generate_loc_inh_connlist(num_cell, distance_map);
vector<int> sender_gid_list = generate_sender_gid(positions, distance_map);
vector<vector<double> > sender_poisson_input;


vector<Cell*> cell_list;
map<string, vector<int> > pop;

int main() {
    // make cells

    auto start = high_resolution_clock::now();

    for (int i = 0; i < num_cell; i++) {
        cell_list.push_back(new Cell(num_cell, i, positions[i]));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    
    start = high_resolution_clock::now();

    // make conns
    for (int i = 0; i < exc_connlist.size(); i++) {
        cell_list[exc_connlist[i].second]->exc_conns[cell_list[exc_connlist[i].first]] = 0.00008;
    }

    for (int i = 0; i < gl_inh_connlist.size(); i++) {
        cell_list[gl_inh_connlist[i].second]->inh_conns[cell_list[gl_inh_connlist[i].first]] = 0.00015;
    }

    for (int i = 0; i < loc_inh_connlist.size(); i++) {
        cell_list[loc_inh_connlist[i].second]->inh_conns[cell_list[loc_inh_connlist[i].first]] = 0.00075;
    }
    // make poisson stims 
    for (auto gid : sender_gid_list){
        sender_poisson_input.push_back(generate_poisson_input());
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    
    start = high_resolution_clock::now();

    // run
    for (int i = 0;i < runtime;i++) {

        for (int i=0; i<sender_gid_list.size();i++){
            cout << i << endl;
            int gid = sender_gid_list.at(i);
            cout << 1;
            // Cell* cell = cell_list[gid];
            if (sender_poisson_input[gid].front() <= cell_list[gid]->t) {
                cout << 2;
                sender_poisson_input[gid].erase(sender_poisson_input[gid].begin());
                cout << 3;
                cell_list[gid]->spike_force();
                cout << 4;
            }
        }
        for (int j = 0; j < num_cell; j++) {
            cell_list[j]->step();
        }
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    export2csv_singlecell("cell_0_s.csv", *cell_list[0]);
    export2csv_singlecell("cell_0_v.csv", *cell_list[0], "voltage_trace");
    export2csv_multiple_voltage("cell_voltage.csv", cell_list);

    // for(int gid : sender_gid_list){
    //     cout << gid << " "; 
    // }
    
    cout << sender_gid_list.size() << endl;

    return 0;
}