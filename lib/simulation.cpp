#include <iostream>

#include <../include/parameters.hpp>

void Simulation::print_all()
{
    std::cout << "Simulation related parameters: " << "\n";
    std::cout << "number of updates = " << n_confs << "\n";
    std::cout << "measure every = " << n_meas << "\n";
    std::cout << "save every = " << n_save << "\n";
    std::cout << "seed = " << seed << "\n";
    std::cout << "starting condition = " << start << "\n";
    std::cout << "beta = " << beta << "\n";
    std::cout << "J = " << J << "\n";
    std::cout << "updater = " << updater << "\n";
}