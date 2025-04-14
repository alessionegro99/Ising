#pragma once

#include "parameters.hpp"

// in Geometry.cpp
class Geometry {
public:
  const size_t L; // extent of the lattice

  int d_size[DIM]; // size of the lattice

  long d_vol;       // total volume
  double d_inv_vol; // 1/(total volume)

  long *d_nnp_mem;
  long *d_nnm_mem;

  long **d_nnp; // d_nnp[r][i] = next neighbour (on the local lattice) in dir
                // +i of site r
  long **d_nnm; // d_nnm[r][i] = next neighbour (on the local lattice) in dir
  // -i of site r

  explicit Geometry(const Parameters &params) : L(params.get_int("L")) {
    cart_to_si = &Geometry::cart_to_lexeo;
    si_to_cart = &Geometry::lexeo_to_cart;
    lex_to_si = &Geometry::lex_to_lexeo;
    si_to_lex = &Geometry::lexeo_to_lex;

    init_geometry();
  }

  // next neighbour in + direction
  inline long nnp(long r, int i) const { return d_nnp[r][i]; }
  // next neighbour in - direction
  inline long nnm(long r, int i) const { return d_nnm[r][i]; }

  // these are the functions to be used in switching between differend indices
  // cartesian coordinates -> single index
  long (Geometry::*cart_to_si)(int const *const cart_coord) const;
  // single index -> cartesian coordinates
  void (Geometry::*si_to_cart)(int *cart_coord, long si) const;
  // lexicographic -> single index
  long (Geometry::*lex_to_si)(long lex) const;
  // single index -> lexicographic
  long (Geometry::*si_to_lex)(long si) const;

  // general functions
  void print_all();
  void init_geometry();
  void free_geometry();

  //----------- these are not to be used outside geometry.c-------------

  // cartesian coordinates -> lexicographic index
  long cart_to_lex(int const *const cart_coord) const;
  // lexicographic index -> cartesian coordinates
  void lex_to_cart(int *cart_coord, long lex) const;

  // cartesian coordinates -> lexicographic even/odd index
  long cart_to_lexeo(int const *const cart_coord) const;
  // lexicographic even/odd index -> cartesian coordinates
  void lexeo_to_cart(int *cart_coord, long lexeo) const;

  // lexicographic index -> lexicographic even/odd index
  long lex_to_lexeo(long lex) const;
  // lexicographic even/odd index -> lexicographic index
  long lexeo_to_lex(long lexeo) const;
};
