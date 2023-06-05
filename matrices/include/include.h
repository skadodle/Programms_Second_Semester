#ifndef ONE
#define ONE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int writedown_to_file();
void Multiply(double **MatrixA, double **MatrixB, double **MatrixC, int MatrixSize);
void Plus(double **hA, double **hB, double **hC, int MatrixSize);
void Minus(double **hA, double **hB, double **hC, int MatrixSize);
int step_of_2(int n);
void free_array(double ***array, int length);
void menu(int *command);

int sum(int to_file);
int multiply_matrix_constant(int to_file);
void Strass(double **A, double **B, double **C, int MatrixSize);
int multiply_matrix_matrix(int to_file);
int trans(int to_file);
int det(int to_file);
void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double **newMatrix);
double matrixDet(double **matrix, int size);
int obrat(int to_file);

#endif