cmake_minimum_required(VERSION 3.20)

project(task)

set(CMAKE_CXX_STANDARD 23)


add_executable(factorial factorial.cpp)
add_executable(SumVector SumVector.cpp)
add_executable(FuturePromise_vs_CV FuturePromise_vs_CV.cpp)


