#include <iostream>
#include <vector>
#include "cell.h"
#include "Vector3f.h"
#include "functions.h"

using namespace std;

// configurations
int num_cell = 100; // 4의 배수로

int num_exc = num_cell * 3 / 4;
int num_gl_inh = (num_cell / 4) * 0.65;
int num_loc_inh = (num_cell / 4) * 0.35;

int total_radius = 100;
int torus_radius = 33;
int runtime = 1.5 * 1000; // ms

vector<Vector3f> positions = generate_torus_positions(num_cell, total_radius, torus_radius);
vector<vector<double>> distance_map = make_distance_map(positions);
vector<pair<int, int>> exc_connlist = generate_exc_connlist(num_cell);
vector<pair<int, int>> gl_inh_connlist = generate_gl_inh_connlist(num_cell);
vector<pair<int, int>> loc_inh_connlist = generate_loc_inh_connlist(num_cell, distance_map);

vector<Cell*> cell_list;
map<string, vector<int>> pop;

int main() {
   for (int i = 0; i < num_cell; i++) {
        cell_list.push_back(new Cell(num_cell, i, positions[i]));
    }


    // make conns
    for (int i = 0; i < size(exc_connlist); i++) {
        cell_list[exc_connlist[i].second]->exc_conns[cell_list[exc_connlist[i].first]] = 0.00008;
    }

    for (int i = 0; i < size(gl_inh_connlist); i++) {
        cell_list[gl_inh_connlist[i].second]->inh_conns[cell_list[gl_inh_connlist[i].first]] = 0.00015;
    }

    for (int i = 0; i < size(loc_inh_connlist); i++) {
        cell_list[loc_inh_connlist[i].second]->inh_conns[cell_list[loc_inh_connlist[i].first]] = 0.00075;
    }


    // run
    for (int i = 0;i < runtime;i++) {
        for (int j = 0; j < num_cell; j++) {
            cell_list[j]->step();
        }
    }

    return 0;
}