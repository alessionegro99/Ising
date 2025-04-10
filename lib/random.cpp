#include <iostream>

#include "../include/random.hpp"

Random::Random(int seed) {
  if (seed != 0) {
    rng.seed(seed);
  } else {
    std::random_device rd;
    rng.seed(rd());
  }
}

int Random::uniform_int(int a, int b) {
  std::uniform_int_distribution<int> dist(a, b);
  return dist(rng);
}

double Random::uniform_double() {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(rng);
}