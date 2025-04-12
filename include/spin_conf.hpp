#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Z2.hpp"
#include "parameters.hpp"
#include "random.hpp"

class Configuration {
private:
  const Geometry &geo;
  const Simulation &sim;

  Random &rng;

  double weights_Metropolis[DIM];

  void init_weights_Metropolis() {
    for (int i = 0; i < DIM; ++i) {
      weights_Metropolis[i] = std::exp(-4 * sim.beta * (i+1));
    }
  }

public:
  Z2 *lattice; // [volume] lattice of Z2 spins

  Configuration(const Geometry &geom_ref, const Simulation &simul_ref,
                Random &rng_ref)
      : geo(geom_ref), sim(simul_ref), rng(rng_ref) {
    init_spin_conf();
    init_weights_Metropolis();
  }

  // in spin_conf_def.cpp
  void init_spin_conf(); // initializes gauge configuration
  void free_spin_conf(); // frees gauge configuration memory

  // in spin_conf_meas.cpp
  double magnetization(bool normalize); // measures magnetization

  // in spin_conf_upd.cpp
  int Metropolis(long r);
  void heatbath(long r);
  double update_Metropolis();
  void update_heatbath();
};
