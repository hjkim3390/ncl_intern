#include "network.h"

Network::Network(int num_cell)
{
	for (int i = 0; i < num_cell; i++) {
		cells.push_back(new Cell(i));
	}
}

void Network::add_pops(string pop_name, vector<int> gid_list)
{
	pop[pop_name] = gid_list;
}
