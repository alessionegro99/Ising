#include <array>
#include <cmath>

#include "../include/upd.hpp"

struct Boltzmann {
  static constexpr int max_dE = 4 * DIM;
  static constexpr int num_dE = 2 * DIM + 1;

  std::array<double, num_dE> weights;

  Boltzmann(double beta) {
    for (int i = 0; i < num_dE; i++) {
      int dE = 4 * (i - DIM); // 0 .. (2*DIM) -> -4*DIM .. 4*DIM
      weights[i] = exp(-beta * dE);
    }
  }

  double operator()(int dE) const {
    assert(dE % 4 == 0);
    int index = dE / 4 + DIM;
    assert(index >= 0 && index < num_dE);
    return weights[index];
  }
};

// perform one site update with metropolis
// return 1 if accepted, 0 otherwise
int Configuration::metropolis(long r) {
  int i, acc, dE;
  Boltzmann weight(sim.beta);

  acc = 0;
  dE = 0;

  for (i = 0; i < DIM; i++) {
    dE += lattice[geo.nnm(r, i)] * lattice[geo.nnp(r, i)];
  }

  dE *= 2 * lattice[r];

  

}
