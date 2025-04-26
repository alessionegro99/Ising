#include "../include/macro.h"

#include <stdlib.h>

#include "../include/random.h"
#include "../include/params.h"
#include "../include/spin_conf.h"

void init_spin_conf(Spin_Conf *SC, Geometry const *const geo,
                    Params const *const param) {
  long r;
  int err;

  // allocate the local lattice
  err = posix_memalign((void **)&(SC->lattice), (size_t)INT_ALIGN,
                       (size_t)geo->d_volume * sizeof(long));
  if (err != 0) {
    fprintf(stderr, "Problems in allocating the lattice! (%d)\n", __LINE__);
    exit(EXIT_FAILURE);
  }

  // initialize lattice
  if (param->d_start == 0) // ordered start
  {
    for (r = 0; r < (geo->d_volume); r++) {
      SC->lattice[r] = 1;
    }
  }
  if (param->d_start == 1) // random start (todo: add rand {-1, 1})
  {
    for (r = 0; r < (geo->d_volume); r++) {
      if (myrand() >= 0.5)
        SC->lattice[r] = 1;
      else
        SC->lattice[r] = -1;
    }
  }
}

void free_spin_conf(Spin_Conf *SC) { free(SC->lattice); }
