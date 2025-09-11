#ifndef GPARAM_H
#define GPARAM_H

#include "macro.h"

typedef struct Params {
  // lattice dimensions
  int d_insize[DIM];

  // simulation parameters
  double d_beta;

  // simulation details
  long d_sample;
  long d_measevery;
  double P_add;

  // initialization & saving
  int d_start;
  int d_saveconf_back_every;
  int d_saveconf_analysis_every;

  // output file names
  char d_conf_file[STD_STRING_LENGTH];
  char d_data_file[STD_STRING_LENGTH];
  char d_log_file[STD_STRING_LENGTH];

  // random seed
  unsigned long int d_randseed;

} Params;

#endif