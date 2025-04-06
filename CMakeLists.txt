cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

set(DIM 2 CACHE STRING "Spatial dimension for the simulation")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(INCLUDE_DIR include)
set(LIB_DIR lib)
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp" "${LIB_DIR}/*.cpp")

add_executable(Ising ${SRC_FILES})

target_include_directories(Ising PRIVATE ${INCLUDE_DIR})

target_compile_definitions(Ising PRIVATE DIM=${DIM})

