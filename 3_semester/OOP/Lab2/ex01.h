#pragma once

#include <print>
#include <iostream>
#include <random>

int** createMatrix(const std::size_t N);
void printMat(int** mat, const std::size_t N);
void printArr(int* arr, const std::size_t N);
void getRightDiagonal(int** mat, const std::size_t N);
void getLeftDiagonal(int** mat, const std::size_t N);
void spiralFromCenter(int** mat, const std::size_t N);
void spiralFromTopLeft(int** mat, const std::size_t N);
void freeMem(int** mat, const std::size_t N);
void main_ex01();
