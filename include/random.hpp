#pragma once

#include <random>

class Random {
private:
  std::mt19937 rng;

public:
  explicit Random(int seed = 0);

  int uniform_int(int a, int b);
  double uniform_double();
};