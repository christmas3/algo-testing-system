# testing-system
Read input data and answers from files; 
execute all given tests - string length, lucky tickets task, N power of number, Fibonacci numbers and primes numbers;
compare results with answers; 
print execution time of every test

# Dependencies
* c++17
* cmake
* stdc++fs
* gtest
* gmp

# Compiling
``` shell
mkdir build
cd build
cmake ..
cmake --build .
```

## Running
```shell 
./testing                                   # for execute all tests
./testing --gtest_filter=TicketsSuit/*      # for execute lucky tickets test
./testing --gtest_filter=StringLengthSuit/* # for execute string length test
```

# Docker
```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
