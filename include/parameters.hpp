#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class Parameters {
private:
  std::unordered_map<std::string, std::string> p;

public:
  explicit Parameters(const std::string &filename) { load_from_file(filename); }

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

// Simulation parameters
class Simulation {
public:
  const long n_confs, n_meas, n_save, seed;
  const std::string start, updater;
  const double beta;
  const double J;

  Simulation(const Parameters &p)
      : n_confs(p.get_int("n_confs")), n_meas(p.get_int("n_meas")),
        n_save(p.get_int("n_save")), seed(p.get_int("seed")),
        start(p.get_string("start")), updater(p.get_string("updater")),
        beta(p.get_double("beta")), J(p.get_double("J"))

  {}

  void print_all();
};