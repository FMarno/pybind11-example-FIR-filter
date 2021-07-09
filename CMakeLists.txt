cmake_minimum_required(VERSION 3.10)
project(cpp_fir)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Python COMPONENTS Interpreter Development)
add_subdirectory(pybind11)
pybind11_add_module(cpp_fir fir.cpp)