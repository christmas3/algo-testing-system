# testing-system

Read input data and answers from files; execute all given tests: 
* string length;
* lucky tickets ;
* N power of number;
* Fibonacci numbers; 
* primes numbers;
* bitmap chess;
  
compare results with answers and print execution time of every test

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
./testing                                            # for execute all tests (some test cases execute forever)
./testing --gtest_filter=StringLengthSuit/*          # for execute string length test suites (1 test error)
./testing --gtest_filter=TicketsSuit/*               # for execute lucky tickets test suites

./testing --gtest_filter=PowerIterationSuit/*        # for execute power iteration test suites
./testing --gtest_filter=PowerPostMultipleSuit/*     # for execute power post multiple test suites
./testing --gtest_filter=PowerBinaryDecomposeSuit/*  # for execute power binary decompose test suites

./testing --gtest_filter=FiboRecursionSuit/*         # for execute calculation fibonacci number through recursion (dead lock on 7 case)
./testing --gtest_filter=FiboIterationSuit/*         # for execute calculation fibonacci number through iteration
./testing --gtest_filter=FiboGoldenRatioSuit/*       # for execute calculation fibonacci number through golden ration formulas
./testing --gtest_filter=FiboMatrixSuit/*            # for execute calculation fibonacci number through power matrix

./testing --gtest_filter=PrimesSimpleASuit/*         # for execute calculation primes numbers in (1, N] interval through devider iteration; method A (dead lock on 10 case)
./testing --gtest_filter=PrimesSimpleBSuit/*         # for execute calculation primes numbers in (1, N] interval through devider iteration; method B (dead lock on 11 case)
./testing --gtest_filter=PrimesSimpleCSuit/*         # for execute calculation primes numbers in (1, N] interval through devider iteration; method C (dead lock on 11 case)
./testing --gtest_filter=PrimesSimpleDSuit/*         # for execute calculation primes numbers in (1, N] interval through devider iteration; method D (dead lock on 13 case)
./testing --gtest_filter=PrimesSimpleESuit/*         # for execute calculation primes numbers in (1, N] interval through devider iteration; method E (dead lock on 13 case)
./testing --gtest_filter=PrimesSimpleArraySuit/*     # for execute calculation primes numbers in (1, N] interval through devider iteration; method Array (dead lock on 13 case)
./testing --gtest_filter=PrimesEratosfenSuit/*       # for execute calculation primes numbers in (1, N] interval through devider iteration; method Eratosfen with O(nloglog n)

./testing --gtest_filter=KingSuit/*                  # for execute calculation possible king moves count and direction bit mask
./testing --gtest_filter=HorseSuit/*                 # for execute calculation possible horse moves count and direction bit mask
./testing --gtest_filter=RookSuit/*                  # for execute calculation possible rook moves count and direction bit mask
./testing --gtest_filter=BishopSuit/*                # for execute calculation possible bishop moves count and direction bit mask
./testing --gtest_filter=QueenSuit/*                 # for execute calculation possible queen moves count and direction bit mask
./testing --gtest_filter=Arrays*                     # for execute all array implementations tests and printed performance on 100000 operations
./testing --gtest_filter=PriorityQueue*              # for execute priority queue implementation tests
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
