#include <iostream>
#include <vector>
#include "cell.h"
#include "Vector3f.h"
#include "functions.h"

using namespace std;

// configurations
int num_cell = 2000; // 4의 배수로

int num_exc = num_cell * 3 / 4;
int num_gl_inh = (num_cell / 4) * 0.65;
int num_loc_inh = (num_cell / 4) * 0.35;

int total_radius = 100;
int torus_radius = 33;
int runtime = 1.5 * 1000; // ms

vector<Vector3f> positions = generate_torus_positions(num_cell, total_radius, torus_radius);

vector<Cell*> cell_list;
map<string, vector<int>> pop;

int main() {
   /* for (int i = 0; i < num_cell; i++) {
        cell_list.push_back(new Cell(num_cell, i, positions[i]));
    }*/

    Cell *precell = new Cell(num_cell, 0, Vector3f(0, 0, 0));
    Cell *postcell = new Cell(num_cell, 1, Vector3f(0, 0, 0));
    postcell->exc_conns[precell] = 0.00008;


    for (int i = 0;i < runtime;i++) {
        cout << "t " << postcell->t << endl;
        cout << "vm " << precell->vm << endl;
        cout << "spiking_ongoing " << precell->spiking_ongoing << endl;
        cout << "spiked " << precell->spiked << endl;
        cout << "vm " << postcell->vm << endl;
        cout << "spiking_ongoing " << postcell->spiking_ongoing << endl;
        cout << "spiked " << postcell->spiked << endl;
        cout << "gex " << postcell->get_gex() << endl;

        cout << endl;

        precell->step();
        postcell->step();


    }
    return 0;
}


