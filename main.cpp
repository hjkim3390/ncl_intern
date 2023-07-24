#include <iostream>
#include <vector>
#include "cell.h"

using namespace std;

int main(){
    vector<double> vmvec;
    Cell cell = Cell();
    cell.initialize(-60);
    for(int i=0;i<100;i++){
        cout << cell.vm << endl;
        cell.step();
        vmvec.push_back(cell.vm);
    }
    return 0;
}


