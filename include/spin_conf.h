#ifndef SPIN_CONF_H
#define SPIN_CONF_H

#include "macro.h"

#include <stdio.h>

#include "geometry.h"
#include "params.h"

typedef struct Spin_Conf {
  double weights[2 * DIM + 1];
  int *lattice;
} Spin_Conf;

// in spin_conf_def.c
void init_spin_conf(Spin_Conf *SC, Geometry const *const geo,
                    Params const *const param);
void free_spin_conf(Spin_Conf *SC);

// in spin_conf_meas.c
double magn(Spin_Conf const *const SC, Geometry const *const geo);
double energy(Spin_Conf const *const SC, Geometry const *const geo);

// in spin_conf_upd.c
int Metropolis(Spin_Conf *SC, Geometry const *const geo, long r);
double update(Spin_Conf *SC, Geometry const *const geo);

#endif
