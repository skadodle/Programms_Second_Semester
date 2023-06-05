#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int n1 = 0, m1 = 0;
    int n2 = 0, m2 = 0;

    printf("\nEnter rows and colons for first matrix: ");
    scanf("%d %d", &n1, &m1);

    printf("\nEnter rows and colons for second matrix: ");
    scanf("%d %d", &n2, &m2);

    clock_t begin = clock();

    if (m1 == n2)
    {
        int **arr1 = (int **)malloc(sizeof(int *) * n1);
        int **arr2 = (int **)malloc(sizeof(int *) * n2);
        int **answ = (int **)malloc(sizeof(int *) * n1);

        for (int i = 0; i < n1; i++)
        {
            arr1[i] = (int *)malloc(sizeof(int) * m1);
            answ[i] = (int *)malloc(sizeof(int) * m2);
            for (int j = 0; j < m2; j++)
            {
                answ[i][j] = 0;
            }
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

        for (int i = 0; i < n1; i++)
        {
            for (int k = 0; k < n2; k++)
            {
                for (int j = 0; j < m2; j++)
                {
                    answ[i][j] += arr1[i][k] * arr2[k][j];
                }
            }
        }

        FILE *file;
        file = fopen("output_c.txt", "w");
        if (file == NULL)
        {
            printf("Error open the file!\n");
            return -1;
        }
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                fprintf(file, "%d ", answ[i][j]);
            }
            fprintf(file, "\n");
        }

        /* for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                printf("%d ", answ[i][j]);
            }
            printf("\n");
        } */

        for (int i = 0; i < n1; i++)
        {
            free(arr1[i]);
            free(answ[i]);
        }
        for (int i = 0; i < n2; i++)
        {
            free(arr2[i]);
        }
    }

    printf("\n%lf\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

    return 0;
}