#include <array>
#include <cassert>
#include <cmath>
#include <omp.h>

#include "../include/random.hpp"
#include "../include/spin_conf.hpp"

// perform one site update with Metropolis
// return 1 if accepted, 0 otherwise
int Configuration::Metropolis(long r) {
  int i, acc, s_r, S_r, k;

  S_r = 0;

  for (i = 0; i < DIM; i++) {
    S_r += lattice[geo.nnm(r, i)].value + lattice[geo.nnp(r, i)].value;
  }

  s_r = lattice[r].value;
  k = s_r * S_r;
  if (k <= 0) {
    lattice[r].value *= -1;
    acc = +1;
  } else if (rng.uniform_double() <= weights_Metropolis[k / 2 - 1]) {
    lattice[r].value *= -1;
    acc = +1;
  } else {
    acc = 0;
  }
  return acc;
}

// perform one site update with heat-bath
// return 1 if accepted, 0 otherwise
int Configuration::heatbath(long r) {
  int i, S_r, acc;

  S_r = 0;

  for (i = 0; i < DIM; i++) {
    S_r += lattice[geo.nnm(r, i)].value + lattice[geo.nnp(r, i)].value;
  }

  double p_s_r = std::exp(sim.beta * S_r) /
                 (std::exp(-sim.beta * S_r) + std::exp(sim.beta * S_r));

  if (rng.uniform_double() < p_s_r) {
    lattice[r].value = +1;
    acc = +1;
  } else {
    lattice[r].value = -1;
    acc = 0;
  }
  return acc;
}

// perform a complete update
double Configuration::update() {
  long r, acc_rate;

  acc_rate = 0;

#pragma omp parallel for private(r) reduction(+ : acc_rate)
  for (r = 0; r < geo.d_vol / 2; r++) {
    acc_rate += heatbath(r);
  }
#pragma omp parallel for private(r) reduction(+ : acc_rate)
  for (r = geo.d_vol / 2; r < geo.d_vol; r++) {
    acc_rate += heatbath(r);
  }

  return (double)acc_rate * (double)geo.d_inv_vol;
}