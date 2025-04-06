#include <iostream>

#include <../include/parameters.hpp>

void simulation::print_all()
{
    std::cout << "Simulation related parameters: " << "\n";
    std::cout << "number of configurations generated = " << n_confs << "\n";
    std::cout << "number of configurations used for measurements = " << n_meas << "\n";
    std::cout << "number of configurations saved = " << n_save << "\n";
    std::cout << "seed = " << seed << "\n";
    std::cout << "starting condition = " << start << "\n";
    std::cout << "beta = " << beta << "\n";
    std::cout << "J = " << J << "\n";
    std::cout << "updater = " << updater << "\n";
}