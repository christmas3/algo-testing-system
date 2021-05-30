cmake_minimum_required(VERSION 3.14)
project(testing)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(testing main.cpp StringLength.cpp BaseTask.h Tickets.cpp Power.cpp Fibo.cpp Primes.cpp MultilineResultBaseTask.h BitChess.cpp Arrays.h ArraysTest.cpp ArraysInt.h ForwardedList.h PriorityQueueTest.cpp PriorityQueue.h)

target_link_libraries(testing gtest_main gtest pthread stdc++fs -lgmpxx -lgmp)

include(GoogleTest)
gtest_discover_tests(testing)
