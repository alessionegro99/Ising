#include <iostream>

#include "../include/geometry.hpp"

// cartesian coordinates -> single index
long (Geometry::*cart_to_si)(int const *const cart_coord) const =
    &Geometry::cart_to_lexeo;
// single index -> cartesian coordinates
void (Geometry::*si_to_cart)(int *cart_coord,
                             long si) const = &Geometry::lexeo_to_cart;
// lexicographic -> single index
long (Geometry::*lex_to_si)(long lex) const = &Geometry::lex_to_lexeo;
// single_index -> lexicographic index
long (Geometry::*si_to_lex)(long si) const = &Geometry::lexeo_to_lex;

void Geometry::print_all() {
  std::cout << "Geometry related parameters: " << "\n";
  std::cout << "dimension DIM = " << DIM << "\n";
  std::cout << "extent L = " << L << "\n";
  std::cout << "volume V = " << d_vol << "\n";
  std::cout << "inverse volume 1/V = " << d_inv_vol << "\n";
}

void Geometry::init_geometry() {
  int i, value, valuep, valuem;
  long r, rm, rp;
  int cart_coord[DIM];

  for (i = 0; i < DIM; ++i) {
    d_size[i] = L;
  }

  d_vol = 1;

  for (i = 0; i < DIM; ++i) {
    d_vol *= d_size[i];
  }

  d_inv_vol = 1.0 / ((double)d_vol);

  // allocate memory
  d_nnp_mem = new long[d_vol * DIM];

  if (!d_nnp_mem) {
    std::cerr << "Failed to allocate memory for d_nnp_mem.\n";
  }

  d_nnp = new long *[d_vol];

  if (!d_nnp) {
    std::cerr << "Failed to allocate memory for d_nnp.\n";
  }

  d_nnm_mem = new long[d_vol * DIM];

  if (!d_nnm_mem) {
    std::cerr << "Failed to allocate memory for d_nnm_mem.\n";
  }

  d_nnm = new long *[d_vol];

  if (!d_nnm) {
    std::cerr << "Failed to allocate memory for d_nnm.\n";
  }

  // setting row pointers
  for (r = 0; r < d_vol; ++r) {
    d_nnp[r] = &d_nnp_mem[r * DIM];
    d_nnm[r] = &d_nnm_mem[r * DIM];
  }

  // initializing
  for (r = 0; r < d_vol; r++) {

    (this->*si_to_cart)(cart_coord, r);

    for (i = 0; i < DIM; i++) {

      value = cart_coord[i];

      valuep = value + 1;

      // implementing PBC in positive direction
      if (valuep >= d_size[i]) {
        valuep -= d_size[i];
      }

      cart_coord[i] = valuep;

      rp = (this->*cart_to_si)(cart_coord);

      d_nnp[r][i] = rp;

      valuem = value - 1;
      // implementing PBC in negative direction
      if (valuem < 0) {
        valuem += d_size[i];
      }

      cart_coord[i] = valuem;
      rm = (this->*cart_to_si)(cart_coord);
      d_nnm[r][i] = rm;

      cart_coord[i] = value;
    }
  } // end of loop on r
}

void Geometry::free_geometry() {
  delete[] d_nnp;
  delete[] d_nnp_mem;

  delete[] d_nnm;
  delete[] d_nnm_mem;
}

//----------- these are not to be used outside geometry.c-------------

// cartesian coordinates -> lexicographic index
long Geometry::cart_to_lex(int const *const cart_coord) const {
  long res, aux;

  res = 0;
  aux = 1;

  for (int i = 0; i < DIM; i++) {
    res += cart_coord[i] * aux;
    aux *= d_size[i];
  }

  // res = cart_coord[0]
  //      +cart_coord[1]*size[0]
  //      +cart_coord[2]*size[0]*size[1]
  //      +...
  //      +cart_coord[STDIM-1]*size[0]*size[1]*...*size[STDIM-2]

  return res;
}

// lexicographic index -> cartesian coordinates
void Geometry::lex_to_cart(int *cart_coord, long lex) const {
  long aux[DIM];

  aux[0] = 1;
  for (int i = 1; i < DIM; i++) {
    aux[i] = aux[i - 1] * d_size[i - 1];
  }
  // aux[0]=1
  // aux[1]=size[0]
  // aux[2]=size[0]*size[1]
  // ...
  // aux[STDIM-1]=size[0]*size[1]*...*size[STDIM-2]
  for (int i = (DIM - 1); i >= 0; i--) {
    cart_coord[i] = (int)(lex / aux[i]);
    lex -= aux[i] * cart_coord[i];
  }
}

// cartesian coordinates -> lexicographic even/odd index
long Geometry::cart_to_lexeo(int const *const cart_coord) const {
  long lex;
  int i, eo;

  lex = cart_to_lex(cart_coord);

  eo = 0;
  for (i = 0; i < DIM; i++) {
    eo += cart_coord[i];
  }

  if (eo % 2 == 0) {
    return lex / 2;
  } else {
    return (lex + d_vol) / 2;
  }

  // even sites are written first
}

// lexicographic eo index -> cartesian coordinates
void Geometry::lexeo_to_cart(int *cart_coord, long lexeo) const {
  long lex;
  int i, eo;

  if (d_vol % 2 == 0) {
    if (lexeo < d_vol / 2) {
      lex = 2 * lexeo;
    } else {
      lex = 2 * (lexeo - d_vol / 2);
    }

    lex_to_cart(cart_coord, lex);

    eo = 0;
    for (i = 0; i < DIM; i++) {
      eo += cart_coord[i];
    }
    eo = eo % 2;

    // this is to take care of the case where d_vol is even but not
    // all the lattice extents are even
    if ((eo == 0 && lexeo >= d_vol / 2) || (eo == 1 && lexeo < d_vol / 2)) {
      lex += 1;
      lex_to_cart(cart_coord, lex);
    }
  } else {
    if (lexeo <= d_vol / 2) {
      lex = 2 * lexeo;
    } else {
      lex = 2 * (lexeo - d_vol / 2) - 1;
    }
    lex_to_cart(cart_coord, lex);
  }
}

//  lexicographic index -> lexicographic eo index
long Geometry::lex_to_lexeo(long lex) const {
  int cart_coord[DIM];

  lex_to_cart(cart_coord, lex);

  return cart_to_lexeo(cart_coord);
}

//  lexicographic eo index -> lexicographic index
long Geometry::lexeo_to_lex(long lexeo) const {
  int cart_coord[DIM];

  lexeo_to_cart(cart_coord, lexeo);

  return cart_to_lex(cart_coord);
}
