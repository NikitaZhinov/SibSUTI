# How to run

Required packages:
- cmake
- ninja
- clang/gcc 
- clang-format
- sfml
- gtest

## Run:

```sh
mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./GameOfLife
```

## Test
```sh
ctest -R GameOfLifeTest
```

## Clang-format:
```sh
clang-format -i *.cpp
```

## Docs

Required packages:
- doxygen

Gen docs:
```sh
cd docs
cmake .
ninja
doxygen
```