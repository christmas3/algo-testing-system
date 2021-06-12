# sorting

Read from test.N.in file input array and length. Sorting array and 
compare with result from test.N.out and print execution time of every test

# Dependencies

* c++17
* cmake
* stdc++fs
* gtest

# Compiling

``` shell
mkdir ../build
cd ../build
cmake ..
cmake --build .
```

## Running

```shell 
./testing                                            # for execute all tests (some test cases execute forever)
./testing --gtest_filter=RandomSortSuit/*            # for execute sorting algorithms with random numbers
./testing --gtest_filter=DigitsSortSuit/*            # for execute sorting algorithms with random digits
./testing --gtest_filter=SortedSortSuit/*            # for execute sorting algorithms with 99% sorted data
./testing --gtest_filter=ReversSortSuit/*            # for execute sorting algorithms with revers sorted data
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
