cmake_minimum_required(VERSION 3.20)

project(memory_order)

set(CMAKE_CXX_STANDARD 20)


add_executable(dead_lock dead_lock/main.cpp)
add_executable(method_of_thread method_of_thread/main.cpp)
add_executable(Thread_Creation Thread_Creation/main.cpp)
add_executable(Singleton_meyers Singleton_meyers/main.cpp)
add_executable(Singleton_call_one Singleton_call_one/main.cpp)
