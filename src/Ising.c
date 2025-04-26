#include "macro.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/params.h"
#include "../include/random.h"
#include "../include/spin_conf.h"

int main(int argc, char **argv) {
  int i, aux;
  long n;
  double acc, m, e;

  Geometry geo;
  Spin_Conf SC;
  Params params;

  if (argc != (7 + DIM)) {
    fprintf(stdout, "How to use this program:\n");
    fprintf(
        stdout,
        "  %s beta start sample measevery seed datafile L0 L1 ... LDIM-1 \n\n",
        argv[0]);
    fprintf(stdout, "  beta = inverse temperature\n");
    fprintf(stdout, "  start = 0 ordered 1 disordered\n");
    fprintf(stdout, "  sample = number of draws to be extracted\n");
    fprintf(stdout, "  measevery = measure every measevery updates\n");
    fprintf(stdout, "  seed = seed for reproducibility\n");
    fprintf(stdout,
            "  datafile = name of the file on which to write the data\n\n");
    fprintf(stdout, "  Li = linear size of the lattice in direction i "
                    "(dimension defined by macro)\n");
    fprintf(stdout, "Compiled for:\n");
    fprintf(stdout, "  dimensionality = %d\n\n", DIM);
    fprintf(stdout, "Output:\n");
    fprintf(stdout,
            "configuration_number magnetization energy acceptance_rate\n");

    return EXIT_SUCCESS;
  }

  params.d_beta = atof(argv[1]);
  params.d_start = atoi(argv[2]);

  params.d_sample = atol(argv[3]);
  params.d_measevery = atoi(argv[4]);

  params.d_randseed = (unsigned long int)atol(argv[5]);

  if (strlen(argv[6]) >= STD_STRING_LENGTH) {
    fprintf(stderr,
            "File name too long. Increse STRING_LENGTH or shorten the name "
            "(%d)\n",
            __LINE__);
    return EXIT_FAILURE;
  } else {
    strcpy(params.d_data_file, argv[6]);
  }

  for (i = 0; i < DIM; i++) {
    aux = atoi(argv[7 + i]);
    if (aux <= 0) {
      fprintf(stderr, "L in direction %d must be strictly positive!\n", i);
      return EXIT_FAILURE;
    } else
      params.d_insize[i] = aux;
  }

  myrand_init(params.d_randseed, params.d_randseed + 127);

  init_geometry(&geo, params.d_insize);
  init_spin_conf(&SC, &geo, &params);

  FILE *fp;

  fp = fopen(params.d_data_file, "w");
  if (fp == NULL) {
    fprintf(stderr, "Error in opening the file %s (%d)", params.d_data_file,
            __LINE__);
    return EXIT_FAILURE;
  }

  for (i = 0; i <= 2 * DIM; i++) {
    SC.weights[i] = exp(-2.0 * params.d_beta * ((double)(2 * (i - DIM))));
  }

  for (n = 0; n <= params.d_sample; n++) {
    acc = update(&SC, &geo);

    if (n % params.d_measevery == 0) {
      m = magn(&SC, &geo);
      e = energy(&SC, &geo);

      fprintf(fp, "%f %.12f %.12f\n", acc, fabs(m), e);
    }
  }

  fclose(fp);

  free_spin_conf(&SC);
  free_geometry(&geo);

  return EXIT_SUCCESS;
}