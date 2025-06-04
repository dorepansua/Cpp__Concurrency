cmake_minimum_required(VERSION 3.20)

project(memory_order)

set(CMAKE_CXX_STANDARD 23)


add_executable(dead_lock dead_lock/main.cpp)
add_executable(method_of_thread method_of_thread/main.cpp)
add_executable(Thread_Creation Thread_Creation/main.cpp)
add_executable(Singleton_meyers Singleton_meyers/main.cpp)
add_executable(Singleton_call_one Singleton_call_one/main.cpp)
add_executable(Thread_Local_Data Thread_Local_Data/main.cpp)
add_executable(first_use_cv Condition_Variables/First_usage.cpp)
add_executable(ping_pong Condition_Variables/ping_pong.cpp)
add_executable(latch Latch/main.cpp)
add_executable(latch2 Latch/main2.cpp)
add_executable(barirer Barirer/main.cpp)


