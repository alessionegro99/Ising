#include "../include/macro.h"

#include "../include/random.h"
#include "../include/spin_conf.h"

// perform one site update with Metropolis
// return 1 if accepted, 0 otherwise
int Metropolis(Spin_Conf *SC, Geometry const *const geo, long r) {
  int i, acc, s_r, S_r, k;

  S_r = 0;
  for (i = 0; i < DIM; i++) {
    S_r += SC->lattice[nnp(geo, r, i)];
    S_r += SC->lattice[nnm(geo, r, i)];
  }

  s_r = SC->lattice[r];
  k = s_r * S_r;
  if (k <= 0) {
    SC->lattice[r] *= -1;
    acc = +1;
  } else if (myrand() <= SC->weights[k / 2 + DIM]) {
    SC->lattice[r] *= -1;
    acc = +1;
  } else {
    acc = 0;
  }
  return acc;
}

// perform a complete update with Metropolis
double update_Metropolis(Spin_Conf *SC, Geometry const *const geo) {
  long r, raux, acc_rate;

  acc_rate = 0;
  for (r = 0; r < geo->d_volume; r++) {
    raux = (long)((double)geo->d_volume * myrand());
    acc_rate += Metropolis(SC, geo, raux);
  }

  return (double)acc_rate * (double)geo->d_inv_vol;
}

// perform one site update with the heatbath algorithm
void heatbath(Spin_Conf *SC, Geometry const *const geo, long r) {
  int i, s_r;

  s_r = 0;

  for (i = 0; i < DIM; i++) {
    s_r += SC->lattice[nnp(geo, r, i)];
    s_r += SC->lattice[nnm(geo, r, i)];
  }

  if (myrand() < SC->weights[s_r / 2 + DIM]) {
    SC->lattice[r] = +1;
  } else {
    SC->lattice[r] = -1;
  }
}

// perform a complete update with heatbath
void update_heatbath(Spin_Conf *SC, Geometry const *const geo) {
  long r, raux;

  for (r = 0; r < geo->d_volume; r++) {
    raux = (long)((double)geo->d_volume * myrand());
    heatbath(SC, geo, raux);
  }
}

// build a cluster of neighbouring spins with the same orientation
void update_single_cluster(Spin_Conf *SC, Geometry const *const geo,
                           Params const *const param, long *cluster,  long r) {
  long x;
  int n_old, n_new, l_c, s_x, s_r;

  s_r = SC->lattice[r];
  cluster[0] = r;
  n_old = 0;
  n_new = 1;
  l_c = 1;

  while (n_new > n_old) {
    int p;

    for (p = n_old; p < n_new; p++) {
      int i;

      for (i = 0; i < DIM; i++) {
        int j;
        int flag;

        x = nnp(geo, r, i);
        flag = 0;

        for (j = 0; j < l_c; j++) {
          if (cluster[j] == x) {
            flag = 1;
            break;
          }
        }
        s_x = SC->lattice[x];
        if (s_x == s_r) {
          if (my_rand() < param->P_add) {
            cluster[l_c] = x;
          }
        }
      }
    }
  }
  n_old = n_new;
  n_new = l_c;

  int i;
  for (i = 0; i < l_c; i++) {
    x = cluster[i];
    SC->lattice[x] *= -1;
  }
}
