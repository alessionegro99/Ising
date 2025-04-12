#include <iomanip>
#include <iostream>

#include "../include/io.hpp"
#include "../include/parameters.hpp"
#include "../include/random.hpp"
#include "../include/spin_conf.hpp"
#include "../include/timer.hpp"

int main(int argc, char *argv[]) {
  int n;
  double end_time;
  Stopwatch watch;

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " -f <filename>" << std::endl;
    return 1;
  }

  std::string flag = argv[1];
  if (flag != "-f") {
    std::cerr << "Error: Unknown flag " << flag << ". Expected -f."
              << std::endl;
    return 1;
  }

  std::string filename = argv[2];

  Parameters params(filename);
  Geometry geo(params);
  Simulation sim(params);
  Random rng(sim.seed);

  geo.print_all();
  sim.print_all();

  Configuration conf(geo, sim, rng);

  conf.init_spin_conf();

  std::cout << "Starting magnetization = " << conf.magnetization(true) << "\n";

  if (sim.updater == "Metropolis") {
    double acc_rate;

    std::cout << "configuration" << " " << "magnetization" << " "
              << "abs_magnetization" << " " << "acceptance"
              << " " << "time"
              << "\n";

    acc_rate = 0;
    for (n = 0; n <= sim.n_confs; n++) {

      watch.start();
      acc_rate = conf.update_Metropolis();
      end_time = watch.stop();

      if (!(n % sim.n_meas)) {
        std::cout << n << " " << conf.magnetization(true) << " "
                  << std::abs(conf.magnetization(true)) << " " << acc_rate
                  << " " << end_time << "\n";
      }
    }
  } else if (sim.updater == "heatbath") {
    std::cout << "configuration" << " " << "magnetization" << " "
              << "abs_magnetization" << " " << "time"
              << "\n";

    for (n = 0; n <= sim.n_confs; n++) {

      watch.start();
      conf.update_heatbath();
      end_time = watch.stop();

      if (!(n % sim.n_meas)) {
        std::cout << n << " " << conf.magnetization(true) << " "
                  << std::abs(conf.magnetization(true)) << " " << end_time
                  << "\n";
      }
    }
  }

  conf.free_spin_conf();

  return 0;
}