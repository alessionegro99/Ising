#include <iostream>

#include "../include/spin_conf.hpp"

double Configuration::magnetization(bool normalize = true) {
  double magnetization = 0.0;
  long r;

  for (r = 0; r < geo.d_vol; r++) {
    magnetization += lattice[r];
  }

  if (normalize) {
    magnetization *= geo.d_inv_vol;
  }

  return magnetization;
}

double Configuration::energy(bool normalize = true) {
  double energy = 0.0;
  long r, i;

  for (r = 0; r < geo.d_vol; r++) {
    for (i = 0; i < DIM; i++) { // vibe coded, check again
      energy += -sim.J * lattice[r] * lattice[geo.nnp(r, i)];
    }
  }

  if (normalize) {
    energy *= geo.d_inv_vol;
  }
  return energy;
}