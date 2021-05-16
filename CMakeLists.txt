cmake_minimum_required(VERSION 3.14)
project(testing)

set(CMAKE_CXX_STANDARD 17)

add_executable(testing main.cpp StringLength.cpp BaseTask.h Tickets.cpp Power.cpp Fibo.cpp Primes.cpp MultilineResultBaseTask.h BitChess.cpp)

target_link_libraries(testing gtest_main gtest pthread stdc++fs -lgmpxx -lgmp)

include(GoogleTest)
gtest_discover_tests(testing)
