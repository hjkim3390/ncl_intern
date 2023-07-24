#pragma once
#define _USE_MATH_DEFINES 

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <utility>
#include <algorithm>
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

vector<pair<int, int>> generate_exc_connlist(int num_cell) {
    vector<pair<int, int>> ans;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int i = 0; i < num_cell; i++) {
        if (i < num_cell * 3 / 4) { // this is excitatory cell
            for (int j = 0; j < num_cell; j++) {
                if (j != i) { // don't connect with myself
                    double random_number = uniform_dist(gen); // lets make connection!
                    if (random_number < 0.02) {
                        ans.push_back(make_pair(i, j));
                    }
                }
                
            }
            
        }
    }
    return ans;
}

vector<pair<int, int>> generate_gl_inh_connlist(int num_cell) {
    vector<pair<int, int>> ans;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int i = 0; i < num_cell; i++) {
        if (num_cell * 3 / 4 <= i < num_cell * 3 / 4 + (num_cell / 4) * 0.65) { // this is global inhibitory cell
            for (int j = 0; j < num_cell; j++) {
                if (j != i) { // don't connect with myself
                    double random_number = uniform_dist(gen); // lets make connection!
                    if (random_number < 0.02) {
                        ans.push_back(make_pair(i, j));
                    }
                }
            }
        }
    }
    return ans;
}


vector<vector<double>> make_distance_map(vector<Vector3f>& positions) {
    const int num_cell = positions.size();
    vector<vector<double>> ans(num_cell, vector<double>(num_cell, 0.0));

    for (int i = 0; i < num_cell; i++) {
        for (int j = i + 1; j < num_cell; j++) {
            ans[i][j] = ans[j][i] = positions[i].dist(positions[j]);
        }
    }
    return ans;
}

struct VectorWithGid {
    double value;
    int gid;
};

bool compare_by_value(const VectorWithGid& a, const VectorWithGid& b) {
    return a.value < b.value;
}

vector<pair<int, int>> generate_loc_inh_connlist(int num_cell, const vector<vector<double>> distance_map) {
    vector<pair<int, int>> ans;
    int boundary = num_cell * 500 / 20000;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniform_dist(0.0, 1.0);

    for (int i = 0; i < num_cell; i++) {
        if ((num_cell * 3 / 4 + (num_cell / 4) * 0.65) <= i) { // this is local inhibitory cell
            std::vector<VectorWithGid> pos_with_gid(num_cell);
            
            for (int j = 0; j < num_cell; ++j) {
                pos_with_gid[j].value = distance_map[i][j];
                pos_with_gid[j].gid = j;
            }
            std::sort(pos_with_gid.begin(), pos_with_gid.end(), compare_by_value);

            for (int j = 0; j < boundary; ++j){
                double random_number = uniform_dist(gen); // lets make connection!
                if (random_number < 5) {
                    ans.push_back(make_pair(i, pos_with_gid[j].gid));
                }
           }

        }
    }
    return ans;
}

vector<int> generate_sender_gid(vector<Vector3f> positions) {
    vector<int> ans;
    int num_cell = size(positions);
    int cell_num = num_cell * 926 / 20000;

    return ans;
}

vector<int> generate_receiver_exc_gid(vector<Vector3f> positions) {
    vector<int> ans;

    int num_cell = size(positions);
    int cell_num = num_cell * 463 / 20000;
    return ans;

}

vector<int> generate_receiver_inh_gid(vector<Vector3f> positions) {
    vector<int> ans;

    int num_cell = size(positions);
    int cell_num = num_cell * 73 / 20000;
    return ans;

}