#include <iostream>

#include "../include/spin_conf.hpp"

double Configuration::magnetization(bool normalize) {
  double magnetization = 0.0;
  long r;

  for (r = 0; r < geo.d_vol; r++) {
    magnetization += lattice[r].value;
  }

  if (normalize) {
    magnetization *= geo.d_inv_vol;
  }

  return magnetization;
}

double Configuration::energy(bool normalize) {
  double energy = 0.0;
  long r, i;

  for (r = 0; r < geo.d_vol; r++) {
    for (i = 0; i < DIM; i++) { // vibe coded, check again
      energy += -sim.J * lattice[r].value * lattice[geo.nnp(r, i)].value;
    }
  }

  if (normalize) {
    energy *= geo.d_inv_vol;
  }
  return energy;
}