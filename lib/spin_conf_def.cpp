#include <iostream>

#include "../include/spin_conf.hpp"
#include "../include/random.hpp"
#include "io.hpp"

void configuration::init_spin_conf()
{
    long r;

    lattice = new Z2[geo.d_vol];
    if (!lattice)
    {
        fatal_error("Failed to allocate memory for lattice.", __func__);
    }

    if (sim.start == "cold")
    {
        for(r = 0; r < geo.d_vol; r++)
        {
            lattice[r] = Z2(1);
        }
    }
}

void configuration::free_spin_conf()
{
    long r;

    delete[] lattice;
}