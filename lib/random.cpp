#include <iostream>

#include "../include/random.hpp"

std::mt19937 initialize_rng(int seed)
{
    if (seed != 0)
    {
        return std::mt19937(seed); // Seeded RNG for reproducibility
    }
    else
    {
        std::random_device rd;
        return std::mt19937(rd()); // Random seed
    }
}
