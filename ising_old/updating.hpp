
// Computes the variation in the energy due to nearest neighbour interaction.
int deltaH(std::vector<int> spin_config, int x, const size_t N, const size_t S_DIM)
{
    int dH{0};

    for (int i = 0; i < 2; i++)
    {
        dH += spin_config[(x + i * (N - 1) + 1) % (N * N)] + spin_config[(x - i * (N - 1) - 1) % (N * N)];
    }

    return dH/2 + S_DIM;
}

// Performs one updating sweep of the entire lattice. Every point subsequentially undergoes an accept/reject
// step, a lá Metropolis-Hastings.
double updateMetropolis(std::vector<int> &spin_config, std::vector<double> weights_Boltzmann, const size_t N, size_t S_DIM)
{
    int accepted_per_sweep{0};

    for (int x = 0; x < N * N; x++)
    {
        
        if (randUnif(0., 1.) < weights_Boltzmann[deltaH(spin_config, x, N, S_DIM)])
        {
            spin_config[x] = -spin_config[x];
            accepted_per_sweep += 1;
        }
    }
    return accepted_per_sweep / double(N * N);
}

// Performs one updating sweep of the entire lattice. Every point on the lattice is touched with a heat-bath 
// with coolness equal to beta.
void updateHeatbath(std::vector<int> &spin_config, const double J, const double beta, const size_t N)
{
    std::vector<int> spin_config_tmp{spin_config};
    for (int x = 0; x < N * N; x++)
    {   

        spin_config_tmp[x] = 1;
        if (randUnif(0., 1.) < 1/(1 + exp(beta * deltaH(spin_config_tmp, J, x, N))))
            spin_config[x] = 1;
        else
            spin_config[x] = -1;
    }
}