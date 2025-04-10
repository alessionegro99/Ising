#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Z2.hpp"
#include "parameters.hpp"

class Configuration {
private:
  const Geometry &geo;
  const Simulation &sim;

public:
  Z2 *lattice; // [volume] lattice of Z2 spins

  Configuration(const Geometry &geom, const Simulation &simul)
      : geo(geom), sim(simul) {
    init_spin_conf();
  }

  // in spin_conf_def.cpp
  void init_spin_conf(); // initializes gauge configuration
  void free_spin_conf(); // frees gauge configuration memory

  // in spin_conf_meas.cpp
  double magnetization(bool normalize); // measures magnetization
  double energy(bool normalize);        // measures energy

  // in spin_conf_upd.cpp
  int Metropolis(long r);
  double update();
};
