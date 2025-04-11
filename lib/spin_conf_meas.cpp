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