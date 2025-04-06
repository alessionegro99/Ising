#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Z2.hpp"
#include "parameters.hpp"

class configuration {
private:
  const geometry &geo;
  const simulation &sim;

public:
  Z2 *lattice; // [volume] lattice of Z2 spins

  configuration(const geometry &geom, const simulation &simul)
      : geo(geom), sim(simul) {
    init_spin_conf();
  }

  // in spin_conf_def.cpp
  void init_spin_conf(); // initializes gauge configuration
  void free_spin_conf(); // frees gauge configuration memory

  // in spin_conf_meas.cpp
  double magnetization(bool normalize = true); // measures magnetization
  double energy(bool normalize);               // measures energy
};
