#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    clock_t begin = clock(), end = clock();

    int n1 = 0, m1 = 0;
    int n2 = 0, m2 = 0;

    printf("\nEnter rows and colons for first matrix: ");
    scanf("%d %d", &n1, &m1);

    printf("\nEnter rows and colons for second matrix: ");
    scanf("%d %d", &n2, &m2);

    if (m1 == n2)
    {
        int k = m1;
        int t = 0;

        int **arr1 = (int **)malloc(sizeof(int *) * n1);
        int **arr2 = (int **)malloc(sizeof(int *) * n2);

        for (int i = 0; i < n1; i++)
        {
            arr1[i] = (int *)malloc(sizeof(int) * m1);
        }

        for (int i = 0; i < n2; i++)
        {
            arr2[i] = (int *)malloc(sizeof(int) * m2);
        }

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m1; j++)
            {
                arr1[i][j] = rand() % (2 + 7) + 8 - 7;
                // printf("%d ", arr1[i][j]);
            }
            // printf("\n");
        }

        // printf("\n");

        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                arr2[i][j] = rand() % (2 + 7) + 8 - 7;
                // printf("%d ", arr2[i][j]);
            }
            // printf("\n");
        }

        // printf("\n\n");

        begin = clock();
        int *str_arr1 = (int *)malloc(sizeof(int) * n1 * k); // row - colons
        int *str_arr2 = (int *)malloc(sizeof(int) * m2 * k); // colon - rows

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < k; j++)
            {
                str_arr1[t] = arr1[i][j];
                // printf("%d ", str_arr1[t++]);
            }
        }

        t = 0;
        // printf("\n");

        for (int j = 0; j < m2; j++)
        {
            for (int i = 0; i < k; i++)
            {
                str_arr2[t] = arr2[i][j];
                // printf("%d ", str_arr2[t++]);
            }
        }

        // printf("\n\n");

        int *answer = (int *)malloc(sizeof(int) * n1 * m2);

        for (int i = 0; i < n1 * m2; i++)
        {
            answer[i] = 0;
        }

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                for (int q = 0; q < k; q++)
                {
                    answer[i * n1 + j] += str_arr1[q + i * k] * str_arr2[q + j * k];
                }
            }
            // printf("\n");
        }

        end = clock();
        printf("\nONLY ROWS TIME = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

        /* for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                printf("%d ", answer[i * n1 + j]);
            }
            printf("\n");
        } */

        // printf("\n\n");

        begin = clock();

        int **answ = (int **)malloc(sizeof(int *) * n1);
        for (int i = 0; i < n1; i++)
        {
            answ[i] = (int *)malloc(sizeof(int) * m2);
            for (int j = 0; j < m2; j++)
            {
                answ[i][j] = 0;
            }
        }

        // cache-friendly algorithm of multiply matrix
        for (int i = 0; i < n1; i++)
        {
            for (int q = 0; q < k; q++)
            {
                for (int j = 0; j < m2; j++)
                {
                    answ[i][j] += arr1[i][q] * arr2[q][j];
                }
                // printf("%d ", sum);
            }
            // printf("\n");
        }

        end = clock();
        printf("\nCACHE-FRIENDLY TIME = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

        begin = clock();
        int sum = 0;
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                sum = 0;
                for (int q = 0; q < k; q++)
                {
                    sum += arr1[i][q] * arr2[q][j];
                }
                // printf("%d ", sum);
            }
            // printf("\n");
        }

        end = clock();
        printf("\nSTANDART ALGORITHM TIME = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

        // free arrays
        for (int i = 0; i < n1; i++)
        {
            free(arr1[i]);
            free(answ[i]);
        }
        for (int i = 0; i < n2; i++)
        {
            free(arr2[i]);
        }
        free(answer);
        free(str_arr1);
        free(str_arr2);
        free(answ);
        free(arr1);
        free(arr2);
    }
    else
        return -1;

    return 0;
}