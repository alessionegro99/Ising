#include <chrono>

class Stopwatch {
public:
  void start(void)
  {
    m_start_time = std::chrono::high_resolution_clock::now();
  }

  double stop(void)
  {
    return 1.0e-9*std::chrono::duration_cast<std::chrono::nanoseconds>
      (std::chrono::high_resolution_clock::now()-m_start_time).count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
};
