#include <iostream>
#include <iomanip>

#ifndef DIM
#define DIM 2
#endif

#include "../include/io.hpp"
#include "../include/parameters.hpp"
#include "../include/spin_conf.hpp"
#include "../include/timer.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " -f <filename>" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    if (flag != "-f")
    {
        std::cerr << "Error: Unknown flag " << flag << ". Expected -f." << std::endl;
        return 1;
    }

    std::string filename = argv[2];

    // initialize
    Parameters p(filename);
    Geometry geo(p);
    Simulation sim(p);

    std::cout << "/*****************************/" << "\n";

    // print all geometric parameters
    geo.print_all();

    std::cout << "/*****************************/" << "\n";

    // print all Simulation parameters
    sim.print_all();
    std::cout << "/*****************************/" << "\n";

    Configuration test_conf(geo, sim);

    test_conf.init_spin_conf();

    test_conf.free_spin_conf();

    return 0;
}