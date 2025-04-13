cmake_minimum_required(VERSION 3.19)
project(Ising CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(Ising src/Ising.cpp)

add_library(IsingLib STATIC 
    lib/geometry.cpp
    lib/io.cpp
    lib/random.cpp
    lib/simulation.cpp
    lib/spin_conf_def.cpp
    lib/spin_conf_meas.cpp
    lib/spin_conf_upd.cpp  
)

target_link_libraries(Ising PRIVATE IsingLib)
target_include_directories(Ising PRIVATE include)
target_include_directories(IsingLib PRIVATE include)

target_compile_definitions(Ising PRIVATE DIM=${DIM})
target_compile_definitions(IsingLib PRIVATE DIM=${DIM})

target_link_libraries(Ising PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(IsingLib PRIVATE OpenMP::OpenMP_CXX)
