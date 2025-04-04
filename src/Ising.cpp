#include <iostream>
#include <iomanip>

#ifndef DIM
#define DIM 2
#endif

#include "../include/io.hpp"
#include "../include/parameters.hpp"
#include "../include/spin_conf.hpp"

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
    parameters p(filename);
    geometry geo(p);
    simulation sim(p);

    std::cout << "/*****************************/" << "\n";

    // print all geometric parameters
    geo.printAll();

    std::cout << "/*****************************/" << "\n";

    // print all simulation parameters
    sim.printAll();
    std::cout << "/*****************************/" << "\n";

    configuration test_conf(geo, sim);

    test_conf.initSpinConf();

    

    test_conf.freeSpinConf();

    return 0;
}