#include <array>
#include <cassert>
#include <cmath>

#include "../include/random.hpp"
#include "../include/spin_conf.hpp"

// perform one site update with Metropolis
// return 1 if accepted, 0 otherwise
int Configuration::Metropolis(long r) {
  int i, acc, s_r, S_r, k;
  acc = 0;
  S_r = 0;

  for (i = 0; i < DIM; i++) {
    S_r += lattice[geo.nnm(r, i)].value + lattice[geo.nnp(r, i)].value;
  }

  s_r = lattice[r].value;
  k = s_r * S_r;
  if (k <= 0) {
    lattice[r].value *= -1;
    acc = 1;
  } else if (rng.uniform_double() <= weights[k/2 - 1]) {
    lattice[r].value *= -1;
    acc = 1;
  }
  return acc;
}

// perform a complete update
double Configuration::update() {
  long r, count, acc_rate;

  acc_rate = 0;
  count = 0;

  for (count = 0; count < geo.d_vol; count++) {
    r = rng.uniform_int(0, geo.d_vol - 1);
    acc_rate += Metropolis(r);
  }

  return (double)acc_rate / (double)geo.d_vol;
}
