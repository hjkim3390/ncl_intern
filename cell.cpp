#include "cell.h"

Cell::Cell(int num_cell, int gid, Vector3f pos) {
    this->gid = gid;
    if (gid < num_cell * 3 / 4) {
        type = "exc";
    }
    else if (gid < (num_cell / 4) * 0.65) {
        type = "gl_inh";
    }
    else {
        type = "loc_inh";
    }

    this->vrest = -60;
    this->vth = -50;

    this->cm = 0.2;
    this->gl = 0.01;
    this->tau = this->cm / this->gl;
    this->Eex = 0;
    this->Einh = -80;
    this->tauex = 5;
    this->tauinh = 10;
    this->gex = 0;
    this->ginh = 0;

    this->refractory_period = 5;
    this->ib = 0.25;

    this->t = 0;
    this->dt = 0.1;

    this->spike_cnt = 0;
    this->vm = this->vrest;
    this->ongoing = true;
    this->spiked = false;
    this->spiking_ongoing = false;

    this->pos = pos;
}

bool Cell::operator<(const Cell& cell) const
{
    return gid < cell.gid;
}

void Cell::set_pos(Vector3f newpos)
{
    pos = newpos;
}

void Cell::step()
{
    if (ongoing) {
        t += dt;
        control_gs();
        //cout << "t " << t << endl;;
        //cout << "vm " << vm << endl;
        //cout << "spiked " << spiked << endl;
        //cout << "spiking " << spiking_ongoing << endl;
        //cout << "gex " << gex << endl;
        if (!spiking_ongoing) {
            vm += (1 / cm) * (gl * (vrest - vm) + gex * (Eex - vm) + ginh * (Einh - vm) + ib) * dt;
            spike();
        }

        if (spiking_ongoing) {
            // cell is spiking ...
            if (spike_timing[spike_cnt-1] != t) {
                spiked= false;
            }

            if (t - spike_timing[spike_cnt-1] >= refractory_period) {
                spiking_ongoing = false;
            }
        }
        voltage_trace.push_back(vm);
    }

}

void Cell::spike()
{
    if ((this->vm > vth) && (spiking_ongoing == false)) {
        this->vm = vrest;
        spiking_ongoing = true;
        spiked = true;
        spike_cnt += 1;
        spike_timing.push_back(t);
    }
}

void Cell::control_gs()
{
    bool no_pre_ex_input = true;
    bool no_pre_inh_input = true;

    for (auto iter = exc_conns.begin(); iter != exc_conns.end(); iter++) {
        Cell* presynaptic_cell = iter->first;
        double gsyn = iter->second;
   /*     cout << "in control_gs(), presynaptic.spiked: " << presynaptic_cell->spiked << endl;
        cout << "in control_gs(), gsyn: " << gsyn << endl;*/

        if (presynaptic_cell->spiked) {
            gex += gsyn;
            no_pre_ex_input = false;
        }
    }

    for (auto iter = inh_conns.begin(); iter != inh_conns.end(); iter++) {
        Cell* presynaptic_cell = iter->first;
        double gsyn = iter->second;
        if (presynaptic_cell->spiked) {
            ginh += gsyn;
            no_pre_inh_input = false;
        }
    }

    if (no_pre_ex_input) {
        gex -= (1 / tauex) * gex * dt;
    }

    if (no_pre_inh_input) {
        ginh -= (1 / tauinh) * ginh * dt;
    }
}