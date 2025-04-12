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
  } else if (rng.uniform_double() <= weights_Metropolis[k / 2 - 1]) {
    lattice[r].value *= -1;
    acc = 1;
  }
  return acc;
}

// perform one site update with heat-bath
// return 1 if accepted, 0 otherwise
void Configuration::heatbath(long r) {
  int i, S_r;
  S_r = 0;

  for (i = 0; i < DIM; i++) {
    S_r += lattice[geo.nnm(r, i)].value + lattice[geo.nnp(r, i)].value;
  }

  double p_s_r = std::exp(sim.beta * S_r) /
                 (std::exp(-sim.beta * S_r) + std::exp(sim.beta * S_r));

  if (rng.uniform_double() < p_s_r)
    lattice[r].value = +1;

  else
    lattice[r].value = -1;
}

// perform a complete update using the
// Metropolis algorithm
double Configuration::update_Metropolis() {
  long r, count, acc_rate;

  acc_rate = 0;
  count = 0;

  for (count = 0; count < geo.d_vol; count++) {
    r = rng.uniform_long(0, geo.d_vol - 1);
    acc_rate += Metropolis(r);
  }

  return (double)acc_rate / (double)geo.d_vol;
}

// perform a complete update using the
// heatbath algorithm
void Configuration::update_heatbath() {
  long r, count;

  count = 0;

  for (count = 0; count < geo.d_vol; count++) {
    r = rng.uniform_long(0, geo.d_vol - 1);
    heatbath(r);
  }
}
