#define _USE_MATH_DEFINES 

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include "Vector3f.h"

using namespace std;
// Make torus
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