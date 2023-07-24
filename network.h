#pragma once
#include <iostream>
#include "cell.h"

using namespace std;

class Network {
	vector<Cell*> cells;
	map<string, vector<int>> pop;

	Network(int num_cell);
	void add_pops(string pop_name, vector<int> gid_list);
};