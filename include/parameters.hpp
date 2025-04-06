#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class parameters {
private:
  std::unordered_map<std::string, std::string> p;

public:
  explicit parameters(const std::string &filename) { load_from_file(filename); }

  void load_from_file(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
      throw std::runtime_error("Error: Cannot open file " + filename);
    }

    std::string key, value;
    while (file >> key >> value) {
      p[key] = value;
    }

    file.close();
  }

  std::string get_string(const std::string &key) const {
    auto it = p.find(key);

    if (it == p.end()) {
      throw std::runtime_error("Error: Parameter '" + key + "' not found.");
    }
    return it->second;
  }

  int get_int(const std::string &key) const {
    return std::stoi(get_string(key));
  }

  double get_double(const std::string &key) const {
    return std::stod(get_string(key));
  }

  void display() const {
    for (const auto &pair : p) {
      std::cout << pair.first << ": " << pair.second << std::endl;
    }
  }
};

// simulation parameters
class simulation {
public:
  const long n_confs, n_meas, n_save, seed;
  const std::string start, updater;
  const double beta;
  const double J;

  simulation(const parameters &p)
      : n_confs(p.get_int("n_confs")), n_meas(p.get_int("n_meas")),
        n_save(p.get_int("n_save")), seed(p.get_int("seed")),
        start(p.get_string("start")), updater(p.get_string("updater")),
        beta(p.get_double("beta")), J(p.get_double("J"))

  {}

  void print_all();
};

// in geometry.cpp
class geometry {
public:
  const size_t L; // extent of the lattice

  size_t d_size[DIM]; // size of the lattice

  long d_vol;       // total volume
  double d_inv_vol; // 1/(total volume)

  long *d_nnp_mem;
  long *d_nnm_mem;

  long **d_nnp; // d_nnp[r][i] = next neighbour (on the local lattice) in dir
                // +i of site r
  long **d_nnm; // d_nnm[r][i] = next neighbour (on the local lattice) in dir
                // -i of site r

  explicit geometry(const parameters &p) : L(p.get_int("L")) {
    init_geometry();
  }

  inline long nnp(long r, int i) const { return d_nnp[r][i]; }
  inline long nnm(long r, int i) const { return d_nnm[r][i]; }

  void lex_to_cart(long cart_coord[], long lex);
  int cart_to_lex(long cart_coord[]);

  void print_all();
  void init_geometry();
  void free_geometry();
};
