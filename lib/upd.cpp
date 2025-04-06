#include <array>
#include <cmath>

#include "../include/upd.hpp"

struct boltzmann_lookup {
  static constexpr int max_dE = 4 * DIM;
  static constexpr int num_dE = 2 * DIM + 1;

  std::array<double, num_dE> weights;

  boltzmann_lookup(double beta) {
    for (int i = 0; i < num_dE; i++) {
      int dE = 4 * (i - DIM); // 0 .. (2*DIM) -> -4*DIM .. 4*DIM
      weights[i] = exp(-beta * dE);
    }
  }

  double operator()(int dE) const {
    asser(dE % 4 == 0);
    int index = dE / 4 + DIM;
    assert(index >= 0 && index < num_entries);
    return weights[index];
  }
};