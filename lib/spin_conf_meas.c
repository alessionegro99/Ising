#include <iostream>

#include "../include/spin_conf.hpp"

double configuration::magnetization(bool normalize = true) {
  double magnetization = 0.0;
  long r;

  for (r = 0; r < geo.d_vol; r++) {
    magnetization += lattice[r];
  }

  if (Normalize) {
    magnetization *= geo.d_inv_vol;
  }

  return magnetization;
}

double configuration::energy(bool normalize = true) {
  double energy = 0.0;
  long r, i;

  for (r = 0; r < geo.d_vol; r++) {
    for (i = 0; i < DIM; i++) {
      energy += -sim.J * lattice[r] * lattice[geo.d_nnp[r][i]];
    }
  }

  if (normalize) {
    energy *= geo.d_inv_vol;
  }
  return energy;
}