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

// perform one site update with metropolis
// return 1 if accepted, 0 otherwise
int Configuration::metropolis(long r) {
  int i, acc, s_r, S_r;
  Boltzmann boltz(sim.beta);

  acc = 0;
  S_r = 0;

  for (i = 0; i < DIM; i++) {
    S_r += lattice[geo.nnm(r, i)].value * lattice[geo.nnp(r, i)].value;
  }

  std::mt19937 rng = initialize_rng(sim.seed);
  std::uniform_real_distribution<double> uniform(0.0, 1.0);

  s_r = lattice[r].value;
  if (s_r * S_r) {
    lattice[r].value *= -1;
    acc = 1;
  } else if (uniform(rng) < boltz(s_r * S_r)) {
    lattice[r].value *= -1;
    acc = 1;
  }
  return acc;
}

// perform a complete update
double Configuration::update() {

  long r, count, acc_rate;

  std::mt19937 rng = initialize_rng(sim.seed);
  std::uniform_int_distribution<long> uniform(0, geo.d_vol - 1);

  acc_rate = 0;
  count = 0;

  while (count < geo.d_vol) {
    r = uniform(rng);
    acc_rate += metropolis(r);
    count++;
  }

  return (double)acc_rate / (double)geo.d_vol;
}
