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
  } else if (myrand() <= SC->weights[k/2 + DIM]) {
    SC->lattice[r] *= -1;
    acc = +1;
  } else {
    acc = 0;
  }
  return acc;
}

// perform a complete update
double update(Spin_Conf *SC, Geometry const *const geo) {
  long r, raux, acc_rate;

  acc_rate = 0;
  for (r = 0; r < geo->d_volume; r++) {
    raux = (long)((double)geo->d_volume * myrand());
#if UPDATER == 0
    acc_rate += Metropolis(SC, geo, raux);
#endif
  }

  return (double)acc_rate * (double)geo->d_inv_vol;
}
