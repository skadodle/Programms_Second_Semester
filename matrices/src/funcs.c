#include "../include/include.h"

int writedown_to_file()
{
    int to_file = 0;
    printf("Write the answer to file output.txt? (0 - not to file):\n");
    scanf("%d", &to_file);
    return to_file;
}

void Multiply(double **MatrixA, double **MatrixB, double **MatrixC, int MatrixSize)
{
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int k = 0; k < MatrixSize; k++)
        {
            for (int j = 0; j < MatrixSize; j++)
                MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
        }
    }
}

void Plus(double **hA, double **hB, double **hC, int MatrixSize)
{
    for (int i = 0; i < MatrixSize; i++)
        for (int j = 0; j < MatrixSize; j++)
            hC[i][j] = hA[i][j] + hB[i][j];
}

void Minus(double **hA, double **hB, double **hC, int MatrixSize)
{
    for (int i = 0; i < MatrixSize; i++)
        for (int j = 0; j < MatrixSize; j++)
            hC[i][j] = hA[i][j] - hB[i][j];
}

int step_of_2(int n)
{
    while (n % 2 == 0)
    {
        n /= 2;
    }
    return n == 1;
}

void free_array(double ***array, int length)
{
    for (int i = 0; i < length; i++)
    {
        free((*array)[i]);
    }
    free(*array);
}

void menu(int *command)
{
    int to_file = 0;
    switch (*command)
    {
    case 1:
        to_file = writedown_to_file();
        sum(to_file);
        break;
    case 2:
        to_file = writedown_to_file();
        multiply_matrix_constant(to_file);
        break;
    case 3:
        to_file = writedown_to_file();
        multiply_matrix_matrix(to_file);
        break;
    case 4:
        to_file = writedown_to_file();
        trans(to_file);
        break;
    case 5:
        to_file = writedown_to_file();
        det(to_file);
        break;
    case 6:
        to_file = writedown_to_file();
        obrat(to_file);
        break;

    default:
        printf("\nERROR! Unknown command! Try again!\n");
        break;
    }
    return;
}