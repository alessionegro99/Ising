#include <array>
#include <cassert>
#include <cmath>

#include "../include/random.hpp"
#include "../include/spin_conf.hpp"

struct Boltzmann {
  static constexpr int max = 4 * DIM;
  static constexpr int num = 2 * DIM + 1;

  std::array<double, num> weights;

  Boltzmann(double beta) {
    for (int i = 0; i < num; i++) {
      int S = 4 * (i - DIM); // 0 .. (2*DIM) -> -4*DIM .. 4*DIM
      weights[i] = exp(-beta * S);
    }
  }

  double operator()(int S) const {
    assert(S % 4 == 0);
    int index = S / 4 + DIM;
    assert(index >= 0 && index < num);
    return weights[index];
  }
};

// perform one site update with Metropolis
// return 1 if accepted, 0 otherwise
int Configuration::Metropolis(long r) {
  int i, acc, s_r, S_r;
  Boltzmann boltz(sim.beta); // might be compuitng them every time???

  acc = 0;
  S_r = 0;

  for (i = 0; i < DIM; i++) {
    S_r += lattice[geo.nnm(r, i)].value + lattice[geo.nnp(r, i)].value;
  }

  s_r = lattice[r].value;
  if (s_r * S_r <= 0) {
    lattice[r].value *= -1;
    acc = 1;
  } else if (rng.uniform_double() <= std::exp(-2 * s_r * S_r)) {
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
