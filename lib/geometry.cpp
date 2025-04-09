#include <iostream>

#include "../include/parameters.hpp"

void Geometry::print_all() {
  std::cout << "Geometry related parameters: " << "\n";
  std::cout << "dimension DIM = " << DIM << "\n";
  std::cout << "extent L = " << L << "\n";
  std::cout << "volume V = " << d_vol << "\n";
  std::cout << "inverse volume 1/V = " << d_inv_vol << "\n";
}

void Geometry::lex_to_cart(long cart_coord[], long lex) {
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
  for (int i = (DIM - 1); i >= 0; i--)
  {
    cart_coord[i] = (int)(lex / aux[i]);
    lex -= aux[i] * cart_coord[i];
  }
}

int Geometry::cart_to_lex(long cart_coord[]) {
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

void Geometry::init_geometry() {
  int i, value, valuep, valuem;
  long r, rm, rp;
  long cart_coord[DIM];

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
    d_nnp[r] = &d_nnp_mem[i * DIM];
    d_nnm[r] = &d_nnm_mem[i * DIM];
}

  // initializing
  for (r = 0; r < d_vol; r++) {
    lex_to_cart(cart_coord, r);

    for (i = 0; i < DIM; i++) {
      value = cart_coord[i];

      valuep = value + 1;

      // implementing PBC in positive direction
      if (valuep >= d_size[i]) {
        valuep -= d_size[i];
      }

      cart_coord[i] = valuep;
      rp = cart_to_lex(cart_coord);

      d_nnp[r][i] = rp;

      valuem = value - 1;
      // implementing PBC in negative direction
      if (valuem < 0) {
        valuem += d_size[i];
      }

      cart_coord[i] = valuem;
      rm = cart_to_lex(cart_coord);
      d_nnm[r][i] = rm; // segfault

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