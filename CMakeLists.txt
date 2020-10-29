cmake_minimum_required(VERSION 3.17)
project(labo3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(labo3 labo3.cpp montantEnVaudois.cpp)