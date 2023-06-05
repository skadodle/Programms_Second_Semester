#include "../include/include.h"

int sum(int to_file)
{
    int how_to_scan = 0;
    int n1 = 0, m1 = 0, n2 = 0, m2 = 0, rand_upper = 2;

    printf("1 - console, 2 - file, 3 - random:\n");
    scanf("%d", &how_to_scan);

    if (how_to_scan == 3)
    {
        printf("Write upper limit:\n");
        scanf("%d", &rand_upper);
    }

    if (how_to_scan == 1 || how_to_scan == 3)
    {
        printf("First matrix nxm:\n");
        scanf("%d %d", &n1, &m1);

        if (n1 <= 0 || m1 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n1, m1);
            return -5;
        }

        double **arr1 = (double **)malloc(sizeof(double *) * n1);
        for (int i = 0; i < n1; i++)
        {
            arr1[i] = (double *)malloc(sizeof(double) * m1);
        }

        for (int i = 0; i < n1; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m1; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr1[i][j]);
                else
                {
                    arr1[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr1[i][j]);
                }
            }
        }

        printf("\nSecond matrix nxm:\n");
        scanf("%d %d", &n2, &m2);

        if (n2 <= 0 || m2 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n2, m2);
            return -5;
        }

        double **arr2 = (double **)malloc(sizeof(double *) * n2);
        for (int i = 0; i < n2; i++)
        {
            arr2[i] = (double *)malloc(sizeof(double) * m2);
        }

        for (int i = 0; i < n2; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m2; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr2[i][j]);
                else
                {
                    arr2[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr2[i][j]);
                }
            }
        }

        printf("\n");

        if (n1 != n2 || m1 != m2)
        {
            printf("ERROR! Can't sum %dx%d and %dx%d!", n1, m1, n2, m2);

            free_array(&arr1, n1);
            free_array(&arr2, n2);

            return -5;
        }
        else
        {
            FILE *output;
            if ((output = fopen("output.txt", "w")) == NULL)
            {
                printf("ERROR! Can't open the output.txt!\n");

                free_array(&arr1, n1);
                free_array(&arr2, n2);

                return -5;
            }

            for (int i = 0; i < n1; i++)
            {
                if (to_file)
                    fprintf(output, "\n");
                else
                    printf("\n");
                for (int j = 0; j < m1; j++)
                {
                    if (to_file)
                        fprintf(output, "%.2lf\t", arr1[i][j] + arr2[i][j]);
                    else
                        printf("%.2lf\t", arr1[i][j] + arr2[i][j]);
                }
            }
            fclose(output);
        }

        free_array(&arr1, n1);
        free_array(&arr2, n2);
    }
    else if (how_to_scan == 2)
    {

        int count_of_elements = 0;

        char *filename1;
        printf("Name of first file:\n");
        scanf("%s", filename1);
        FILE *fp1;
        if ((fp1 = fopen(filename1, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename1);
            return -5;
        }
        fscanf(fp1, "%d %d", &n1, &m1);

        if (n1 <= 0 || m1 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n1, m1);

            fclose(fp1);

            return -5;
        }

        char *filename2;
        printf("Name of second file:\n");
        scanf("%s", filename2);
        FILE *fp2;
        if ((fp2 = fopen(filename2, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename2);

            fclose(fp1);

            return -5;
        }
        fscanf(fp2, "%d %d", &n2, &m2);

        if (n2 <= 0 || m2 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n2, m2);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }

        double **arr1 = (double **)malloc(sizeof(double *) * n1);
        for (int i = 0; i < n1; i++)
        {
            arr1[i] = (double *)malloc(sizeof(double) * m1);
            for (int j = 0; j < m1; j++)
            {
                if (fscanf(fp1, "%lf", &arr1[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n1 * m1)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr1, n1);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }

        count_of_elements = 0;

        double **arr2 = (double **)malloc(sizeof(double *) * n2);
        for (int i = 0; i < n2; i++)
        {
            arr2[i] = (double *)malloc(sizeof(double) * m2);
            for (int j = 0; j < m2; j++)
            {
                if (fscanf(fp2, "%lf", &arr2[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n2 * m2)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr1, n1);
            free_array(&arr2, n2);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }

        if (n1 != n2 || m1 != m2)
        {
            printf("ERROR! Can't sum %dx%d and %dx%d!", n1, m1, n2, m2);

            free_array(&arr1, n1);
            free_array(&arr2, n2);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }
        else
        {
            FILE *output;
            if ((output = fopen("output.txt", "w")) == NULL)
            {
                printf("ERROR! Can't open the output.txt!\n");

                free_array(&arr1, n1);
                free_array(&arr2, n2);

                fclose(fp1);
                fclose(fp2);

                return -5;
            }

            for (int i = 0; i < n1; i++)
            {
                if (to_file)
                    fprintf(output, "\n");
                else
                    printf("\n");
                for (int j = 0; j < m1; j++)
                {
                    if (to_file)
                        fprintf(output, "%.2lf\t", arr1[i][j] + arr2[i][j]);
                    else
                        printf("%.2lf\t", arr1[i][j] + arr2[i][j]);
                }
            }
            fclose(output);
        }

        free_array(&arr1, n1);
        free_array(&arr2, n2);

        fclose(fp1);
        fclose(fp2);
    }

    else
    {
        printf("ERROR! Value beyond the limit!\n");
        return -5;
    }

    return 0;
}

int multiply_matrix_constant(int to_file)
{
    int how_to_scan = 0;
    int constant = 0;
    int n = 0, m = 0, rand_upper = 2;

    printf("Write constant:\n");
    scanf("%d", &constant);

    printf("1 - console, 2 - file, 3 - random:\n");
    scanf("%d", &how_to_scan);

    if (how_to_scan == 3)
    {
        printf("Write upper limit:\n");
        scanf("%d", &rand_upper);
    }

    if (how_to_scan == 1 || how_to_scan == 3)
    {
        printf("Matrix nxm:\n");
        scanf("%d %d", &n, &m);

        if (n <= 0 || m <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n, m);
            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * m);
        }

        for (int i = 0; i < n; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr[i][j]);
                if (how_to_scan == 3)
                {
                    arr[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr[i][j]);
                }
            }
        }

        printf("\n");

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            return -5;
        }

        for (int j = 0; j < m; j++)
        {
            if (to_file)
                fprintf(output, "\n");
            else
                printf("\n");
            for (int i = 0; i < n; i++)
            {
                if (to_file)
                    fprintf(output, "%.2lf\t", arr[i][j]);
                else
                    printf("%.2lf\t", arr[i][j]);
            }
        }

        free_array(&arr, n);

        fclose(output);
    }
    else if (how_to_scan == 2)
    {
        int count_of_elements = 0;

        char *filename;
        printf("Name of file:\n");
        scanf("%s", filename);
        FILE *fp;
        if ((fp = fopen(filename, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename);
            return -5;
        }
        fscanf(fp, "%d %d", &n, &m);

        if (n <= 0 || m <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n, m);

            fclose(fp);

            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * m);
            for (int j = 0; j < m; j++)
            {
                if (fscanf(fp, "%lf", &arr[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n * m)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);
            fclose(fp);

            return -5;
        }

        for (int i = 0; i < n; i++)
        {
            if (to_file)
                fprintf(output, "\n");
            else
                printf("\n");
            for (int j = 0; j < m; j++)
            {
                if (to_file)
                    fprintf(output, "%.2lf\t", arr[i][j] * constant);
                else
                    printf("%.2lf\t", arr[i][j] * constant);
            }
        }

        free_array(&arr, n);

        fclose(output);
        fclose(fp);
    }

    else
    {
        printf("ERROR! Value beyond the limit!\n");
        return -5;
    }

    return 0;
}

void Strass(double **A, double **B, double **C, int MatrixSize)
{
    if (MatrixSize <= 2)
        Multiply(A, B, C, MatrixSize);

    else
    {
        int hS = MatrixSize / 2; // Делим всю матрицу

        double **a11 = (double **)malloc(sizeof(double *) * hS);
        double **a12 = (double **)malloc(sizeof(double *) * hS);
        double **a21 = (double **)malloc(sizeof(double *) * hS);
        double **a22 = (double **)malloc(sizeof(double *) * hS);

        double **b11 = (double **)malloc(sizeof(double *) * hS);
        double **b12 = (double **)malloc(sizeof(double *) * hS);
        double **b21 = (double **)malloc(sizeof(double *) * hS);
        double **b22 = (double **)malloc(sizeof(double *) * hS);

        double **p1 = (double **)malloc(sizeof(double *) * hS);
        double **p2 = (double **)malloc(sizeof(double *) * hS);
        double **p3 = (double **)malloc(sizeof(double *) * hS);
        double **p4 = (double **)malloc(sizeof(double *) * hS);
        double **p5 = (double **)malloc(sizeof(double *) * hS);
        double **p6 = (double **)malloc(sizeof(double *) * hS);
        double **p7 = (double **)malloc(sizeof(double *) * hS);

        double **c11 = (double **)malloc(sizeof(double *) * hS);
        double **c12 = (double **)malloc(sizeof(double *) * hS);
        double **c21 = (double **)malloc(sizeof(double *) * hS);
        double **c22 = (double **)malloc(sizeof(double *) * hS);

        double **hA = (double **)malloc(sizeof(double *) * hS);
        double **hB = (double **)malloc(sizeof(double *) * hS);

        for (int i = 0; i < hS; i++)
        {
            a11[i] = (double *)malloc(sizeof(double) * hS);
            a12[i] = (double *)malloc(sizeof(double) * hS);
            a21[i] = (double *)malloc(sizeof(double) * hS);
            a22[i] = (double *)malloc(sizeof(double) * hS);
            b11[i] = (double *)malloc(sizeof(double) * hS);
            b12[i] = (double *)malloc(sizeof(double) * hS);
            b21[i] = (double *)malloc(sizeof(double) * hS);
            b22[i] = (double *)malloc(sizeof(double) * hS);
            c11[i] = (double *)malloc(sizeof(double) * hS);
            c12[i] = (double *)malloc(sizeof(double) * hS);
            c21[i] = (double *)malloc(sizeof(double) * hS);
            c22[i] = (double *)malloc(sizeof(double) * hS);
            p1[i] = (double *)malloc(sizeof(double) * hS);
            p2[i] = (double *)malloc(sizeof(double) * hS);
            p3[i] = (double *)malloc(sizeof(double) * hS);
            p4[i] = (double *)malloc(sizeof(double) * hS);
            p5[i] = (double *)malloc(sizeof(double) * hS);
            p6[i] = (double *)malloc(sizeof(double) * hS);
            p7[i] = (double *)malloc(sizeof(double) * hS);
            hA[i] = (double *)malloc(sizeof(double) * hS);
            hB[i] = (double *)malloc(sizeof(double) * hS);
        }

        for (int i = 0; i < hS; i++)
            for (int j = 0; j < hS; j++)
            {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + hS];
                a21[i][j] = A[i + hS][j];
                a22[i][j] = A[i + hS][j + hS];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + hS];
                b21[i][j] = B[i + hS][j];
                b22[i][j] = B[i + hS][j + hS];
            }

        Plus(a11, a22, hA, hS);
        Plus(b11, b22, hB, hS);
        Strass(hA, hB, p1, hS);

        Plus(a21, a22, hA, hS);
        Strass(hA, b11, p2, hS);

        Minus(b12, b22, hB, hS);
        Strass(a11, hB, p3, hS);

        Minus(b21, b11, hB, hS);
        Strass(a22, hB, p4, hS);

        Plus(a11, a12, hA, hS);
        Strass(hA, b22, p5, hS);

        Minus(a21, a11, hA, hS);
        Plus(b11, b12, hB, hS);
        Strass(hA, hB, p6, hS);

        Minus(a12, a22, hA, hS);
        Plus(b21, b22, hB, hS);
        Strass(hA, hB, p7, hS);

        // Заполнение С //

        Plus(p1, p4, hA, hS);
        Minus(hA, p5, hB, hS);
        Plus(hB, p7, c11, hS);
        Plus(p3, p5, c12, hS);
        Plus(p2, p4, c21, hS);
        Minus(p1, p2, hA, hS);
        Plus(hA, p3, hB, hS);
        Plus(hB, p6, c22, hS);

        for (int i = 0; i < hS; i++)
            for (int j = 0; j < hS; j++)
            {
                C[i][j] = c11[i][j];
                C[i][j + hS] = c12[i][j];
                C[i + hS][j] = c21[i][j];
                C[i + hS][j + hS] = c22[i][j];
            }

        for (int i = 0; i < hS; i++)
        {
            free(a11[i]);
            free(a12[i]);
            free(a22[i]);
            free(a21[i]);
            free(b11[i]);
            free(b12[i]);
            free(b21[i]);
            free(b22[i]);
            free(p1[i]);
            free(p2[i]);
            free(p3[i]);
            free(p4[i]);
            free(p5[i]);
            free(p6[i]);
            free(p7[i]);
            free(c11[i]);
            free(c12[i]);
            free(c21[i]);
            free(c22[i]);
        }
        free(a11);
        free(a12);
        free(a22);
        free(a21);
        free(b11);
        free(b12);
        free(b21);
        free(b22);
        free(p1);
        free(p2);
        free(p3);
        free(p4);
        free(p5);
        free(p6);
        free(p7);
        free(c11);
        free(c12);
        free(c21);
        free(c22);
    }
}

int multiply_matrix_matrix(int to_file)
{

    int how_to_scan = 0;
    int n1 = 0, m1 = 0, n2 = 0, m2 = 0, rand_upper = 2;

    printf("1 - console, 2 - file, 3 - random:\n");
    scanf("%d", &how_to_scan);

    if (how_to_scan == 3)
    {
        printf("Write upper limit:\n");
        scanf("%d", &rand_upper);
    }

    if (how_to_scan == 1 || how_to_scan == 3)
    {
        printf("First matrix nxm:\n");
        scanf("%d %d", &n1, &m1);

        if (n1 <= 0 || m1 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n1, m1);
            return -5;
        }

        double **arr1 = (double **)malloc(sizeof(double *) * n1);
        for (int i = 0; i < n1; i++)
        {
            arr1[i] = (double *)malloc(sizeof(double) * m1);
        }

        for (int i = 0; i < n1; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m1; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr1[i][j]);
                else
                {
                    arr1[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr1[i][j]);
                }
            }
        }

        printf("\nSecond matrix nxm:\n");
        scanf("%d %d", &n2, &m2);

        if (n2 <= 0 || m2 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n2, m2);

            free_array(&arr1, n1);

            return -5;
        }

        double **arr2 = (double **)malloc(sizeof(double *) * n2);
        for (int i = 0; i < n2; i++)
        {
            arr2[i] = (double *)malloc(sizeof(double) * m2);
        }

        for (int i = 0; i < n2; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m2; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr2[i][j]);
                else
                {
                    arr2[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr2[i][j]);
                }
            }
        }

        printf("\n");

        if (m1 != n2)
        {
            printf("ERROR! Can't multiply %dx%d and %dx%d!", n1, m1, n2, m2);

            free_array(&arr1, n1);
            free_array(&arr2, n2);

            return -5;
        }
        else
        {
            FILE *output;
            if ((output = fopen("output.txt", "w")) == NULL)
            {
                printf("ERROR! Can't open the output.txt!\n");

                free_array(&arr1, n1);
                free_array(&arr2, n2);

                return -5;
            }

            double **answ = (double **)malloc(sizeof(double *) * n1);
            for (int i = 0; i < n1; i++)
            {
                answ[i] = (double *)malloc(sizeof(double) * m2);
                for (int j = 0; j < m2; j++)
                {
                    answ[i][j] = 0;
                }
            }

            if (n1 == m1 && step_of_2(n1))
            {
                Strass(arr1, arr2, answ, n1);
                printf("\n\n----------------->Strass<-----------------\n\n");
            }
            else
                for (int i = 0; i < n1; i++)
                {
                    for (int k = 0; k < m1; k++)
                    {
                        for (int j = 0; j < m2; j++)
                        {
                            answ[i][j] += arr1[i][k] * arr2[k][j];
                        }
                    }
                }

            for (int i = 0; i < n1; i++)
            {
                if (to_file)
                    fprintf(output, "\n");
                else
                    printf("\n");
                for (int j = 0; j < m2; j++)
                {
                    if (to_file)
                        fprintf(output, "%.2lf\t", answ[i][j]);
                    else
                        printf("%.2lf\t", answ[i][j]);
                }
            }

            free_array(&answ, n1);
            fclose(output);
        }

        free_array(&arr1, n1);
        free_array(&arr2, n2);
    }
    else if (how_to_scan == 2)
    {
        int count_of_elements = 0;

        char *filename1;
        printf("Name of first file:\n");
        scanf("%s", filename1);
        FILE *fp1;
        if ((fp1 = fopen(filename1, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename1);
            return -5;
        }
        fscanf(fp1, "%d %d", &n1, &m1);

        if (n1 <= 0 || m1 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n1, m1);

            fclose(fp1);

            return -5;
        }

        char *filename2;
        printf("Name of second file:\n");
        scanf("%s", filename2);
        FILE *fp2;
        if ((fp2 = fopen(filename2, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename2);

            fclose(fp1);

            return -5;
        }
        fscanf(fp2, "%d %d", &n2, &m2);

        if (n2 <= 0 || m2 <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n2, m2);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }

        double **arr1 = (double **)malloc(sizeof(double *) * n1);
        for (int i = 0; i < n1; i++)
        {
            arr1[i] = (double *)malloc(sizeof(double) * m1);
            for (int j = 0; j < m1; j++)
            {
                if (fscanf(fp1, "%lf", &arr1[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n1 * m1)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr1, n1);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }

        count_of_elements = 0;

        double **arr2 = (double **)malloc(sizeof(double *) * n2);
        for (int i = 0; i < n2; i++)
        {
            arr2[i] = (double *)malloc(sizeof(double) * m2);
            for (int j = 0; j < m2; j++)
            {
                if (fscanf(fp2, "%lf", &arr2[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n1 * m1)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr1, n1);
            free_array(&arr2, n2);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }

        if (n2 != m1)
        {
            printf("ERROR! Can't multiply %dx%d and %dx%d!", n1, m1, n2, m2);

            free_array(&arr1, n1);
            free_array(&arr2, n2);

            fclose(fp1);
            fclose(fp2);

            return -5;
        }
        else
        {
            double **answ = (double **)malloc(sizeof(double *) * n1);
            for (int i = 0; i < n1; i++)
            {
                answ[i] = (double *)malloc(sizeof(double) * m2);
                for (int j = 0; j < m2; j++)
                {
                    answ[i][j] = 0;
                }
            }

            FILE *output;
            if ((output = fopen("output.txt", "w")) == NULL)
            {
                printf("ERROR! Can't open the output.txt!\n");

                free_array(&arr1, n1);
                free_array(&arr2, n2);
                free_array(&answ, n1);

                fclose(fp1);
                fclose(fp2);

                return -5;
            }

            if (n1 == m1 && step_of_2(n1))
            {
                Strass(arr1, arr2, answ, n1);
                printf("\n\n----------------->Strass<-----------------\n\n");
            }
            else
                for (int i = 0; i < n1; i++)
                {
                    for (int k = 0; k < m1; k++)
                    {
                        for (int j = 0; j < m2; j++)
                        {
                            answ[i][j] += arr1[i][k] * arr2[k][j];
                        }
                    }
                }

            for (int i = 0; i < n1; i++)
            {
                if (to_file)
                    fprintf(output, "\n");
                else
                    printf("\n");
                for (int j = 0; j < m2; j++)
                {
                    if (to_file)
                        fprintf(output, "%lf\t", answ[i][j]);
                    else
                        printf("%lf\t", answ[i][j]);
                }
            }

            free_array(&answ, n1);
            fclose(output);
        }

        free_array(&arr1, n1);
        free_array(&arr2, n2);

        fclose(fp1);
        fclose(fp2);
    }

    else
    {
        printf("ERROR! Value beyond the limit!\n");
        return -5;
    }

    return 0;
}

int trans(int to_file)
{
    int how_to_scan = 0;
    int n = 0, m = 0, rand_upper = 2;

    printf("1 - console, 2 - file, 3 - random:\n");
    scanf("%d", &how_to_scan);

    if (how_to_scan == 3)
    {
        printf("Write upper limit:\n");
        scanf("%d", &rand_upper);
    }

    if (how_to_scan == 1 || how_to_scan == 3)
    {
        printf("Matrix nxm:\n");
        scanf("%d %d", &n, &m);

        if (n <= 0 || m <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n, m);
            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * m);
        }

        for (int i = 0; i < n; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr[i][j]);
                if (how_to_scan == 3)
                {
                    arr[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr[i][j]);
                }
            }
        }

        printf("\n");

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            return -5;
        }

        for (int j = 0; j < m; j++)
        {
            if (to_file)
                fprintf(output, "\n");
            else
                printf("\n");
            for (int i = 0; i < n; i++)
            {
                if (to_file)
                    fprintf(output, "%.2lf\t", arr[i][j]);
                else
                    printf("%.2lf\t", arr[i][j]);
            }
        }

        free_array(&arr, n);

        fclose(output);
    }
    else if (how_to_scan == 2)
    {
        int count_of_elements = 0;

        char *filename;
        printf("Name of file:\n");
        scanf("%s", filename);
        FILE *fp;
        if ((fp = fopen(filename, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename);
            return -5;
        }
        fscanf(fp, "%d %d", &n, &m);

        if (n <= 0 || m <= 0)
        {
            printf("ERROR! Matrix can not be %dx%d!\n", n, m);

            fclose(fp);

            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * m);
            for (int j = 0; j < m; j++)
            {
                if (fscanf(fp, "%lf", &arr[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n * m)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        for (int j = 0; j < m; j++)
        {
            if (to_file)
                fprintf(output, "\n");
            else
                printf("\n");
            for (int i = 0; i < n; i++)
            {
                if (to_file)
                    fprintf(output, "%.2lf\t", arr[i][j]);
                else
                    printf("%.2lf\t", arr[i][j]);
            }
        }

        free_array(&arr, n);

        fclose(output);
        fclose(fp);
    }

    else
    {
        printf("ERROR! Value beyond the limit!\n");
        return -5;
    }

    return 0;
}

int det(int to_file)
{
    int how_to_scan = 0;
    int n = 0, m = 0, rand_upper = 2;
    double answer = 0;

    printf("1 - console, 2 - file, 3 - random:\n");
    scanf("%d", &how_to_scan);

    if (how_to_scan == 3)
    {
        printf("Write upper limit:\n");
        scanf("%d", &rand_upper);
    }

    if (how_to_scan == 1 || how_to_scan == 3)
    {
        printf("Matrix nxn:\n");
        scanf("%d %d", &n, &m);

        if (n != m || n <= 0)
        {
            printf("ERROR! Can't count det matrix %dx%d!\n", n, m);
            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * m);
        }

        for (int i = 0; i < n; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < m; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr[i][j]);
                if (how_to_scan == 3)
                {
                    arr[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr[i][j]);
                }
            }
        }

        printf("\n");

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            return -5;
        }

        answer = matrixDet(arr, n);

        if (to_file == 1)
            fprintf(output, "%.2lf\n", answer);
        else
            printf("%.2lf\n", answer);

        free_array(&arr, n);

        fclose(output);
    }
    else if (how_to_scan == 2)
    {
        int count_of_elements = 0;

        char *filename;
        printf("Name of file:\n");
        scanf("%s", filename);
        FILE *fp;
        if ((fp = fopen(filename, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename);
            return -5;
        }
        fscanf(fp, "%d %d", &n, &m);

        if (n != m || n <= 0)
        {
            printf("ERROR! Can't count det matrix %dx%d!\n", n, m);

            fclose(fp);

            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * m);
            for (int j = 0; j < m; j++)
            {
                if (fscanf(fp, "%lf", &arr[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n * m)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        answer = matrixDet(arr, n);

        if (to_file == 1)
            fprintf(output, "%.2lf\n", answer);
        else
            printf("%.2lf\n", answer);

        free_array(&arr, n);

        fclose(output);
        fclose(fp);
    }

    else
    {
        printf("ERROR! Value beyond the limit!\n");
        return -5;
    }

    return 0;
}

// Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double **newMatrix)
{
    int offsetRow = 0; // Смещение индекса строки в матрице
    int offsetCol = 0; // Смещение индекса столбца в матрице
    for (int i = 0; i < size - 1; i++)
    {
        // Пропустить row-ую строку
        if (i == row)
        {
            offsetRow = 1; // Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }

        offsetCol = 0; // Обнулить смещение столбца
        for (int j = 0; j < size - 1; j++)
        {
            // Пропустить col-ый столбец
            if (j == col)
            {
                offsetCol = 1; // Встретили нужный столбец, проускаем его смещением
            }

            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}

double matrixDet(double **matrix, int size)
{
    double det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя

    // Условие выхода из рекурсии
    if (size == 1)
    {
        return matrix[0][0];
    }
    // Условие выхода из рекурсии
    else if (size == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        // Матрица без строки и столбца
        double **newMatrix = (double **)malloc(sizeof(double *) * (size - 1));
        for (int i = 0; i < size - 1; i++)
        {
            newMatrix[i] = (double *)malloc(sizeof(double) * (size - 1));
        }

        // Раскладываем по 0-ой строке, цикл бежит по столбцам
        for (int j = 0; j < size; j++)
        {
            // Удалить из матрицы i-ю строку и j-ый столбец
            // Результат в newMatrix
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            // Рекурсивный вызов
            // По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
            // где minor_j - дополнительный минор элемента matrix[0][j]
            //  (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
            //"Накручиваем" степень множителя
            degree = -degree;
        }

        // Чистим память на каждом шаге рекурсии(важно!)
        for (int i = 0; i < size - 1; i++)
        {
            free(newMatrix[i]);
        }
        free(newMatrix);
    }

    return det;
}

int obrat(int to_file)
{
    int how_to_scan = 0;
    int n = 0, m = 0, rand_upper = 2;
    double r = 0;

    printf("1 - console, 2 - file, 3 - random:\n");
    scanf("%d", &how_to_scan);

    if (how_to_scan == 3)
    {
        printf("Write upper limit:\n");
        scanf("%d", &rand_upper);
    }

    if (how_to_scan == 1 || how_to_scan == 3)
    {
        printf("Matrix nxn:\n");
        scanf("%d %d", &n, &m);

        if (n != m || n <= 0)
        {
            printf("Error! Can't have A^(-1) when matrix %dx%d, matrix need to be a nxn!\n", n, m);
            return -3;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * n * 2);
        }

        for (int i = 0; i < n; i++)
        {
            if (how_to_scan == 3)
                printf("\n");
            for (int j = 0; j < n; j++)
            {
                if (how_to_scan == 1)
                    scanf("%lf", &arr[i][j]);
                if (how_to_scan == 3)
                {
                    arr[i][j] = rand() % (2 * rand_upper) + 10.4 - rand_upper;
                    printf("%.2lf\t", arr[i][j]);
                }
            }
        }

        if (!(matrixDet(arr, n)))
        {
            printf("ERROR! Can't count A^(-1) when det A = 0!\n");

            free_array(&arr, n);

            return -5;
        }

        printf("\n\n");

        for (int i = 0; i < n; i++)
        {
            for (int j = n; j < 2 * n; j++)
            {
                if (i == (j - n))
                    arr[i][j] = 1;
                else
                    arr[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    r = arr[j][i] / arr[i][i];
                    for (int k = 0; k < 2 * n; k++)
                    {
                        arr[j][k] -= r * arr[i][k];
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            r = arr[i][i];
            for (int j = 0; j < 2 * n; j++)
            {
                arr[i][j] /= r;
            }
        }

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            return -5;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = n; j < n * 2; j++)
            {
                if (to_file)
                    fprintf(output, "%.2lf\t", arr[i][j]);
                else
                    printf("%.2lf\t", arr[i][j]);
            }
            if (to_file)
                fprintf(output, "\n");
            else
                printf("\n");
        }

        free_array(&arr, n);
        fclose(output);
    }
    else if (how_to_scan == 2)
    {
        int count_of_elements = 0;

        char *filename;
        printf("Name of file:\n");
        scanf("%s", filename);
        FILE *fp;
        if ((fp = fopen(filename, "r")) == NULL)
        {
            printf("ERROR! Can't open the %s!\n", filename);
            return -5;
        }
        fscanf(fp, "%d %d", &n, &m);

        if (n != m || n <= 0)
        {
            printf("ERROR! Can't count A^(-1) when matrix %dx%d!\n", n, m);

            fclose(fp);

            return -5;
        }

        double **arr = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double *)malloc(sizeof(double) * n * 2);
            for (int j = 0; j < n; j++)
            {
                if (fscanf(fp, "%lf", &arr[i][j]) != EOF)
                    count_of_elements++;
                else
                    break;
            }
        }

        if (count_of_elements != n * m)
        {
            printf("ERROR! Don't have enought elements to fill the matrix!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        if (!(matrixDet(arr, n)))
        {
            printf("ERROR! Can't count A^(-1) when det A = 0!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = n; j < 2 * n; j++)
            {
                if (i == (j - n))
                    arr[i][j] = 1;
                else
                    arr[i][j] = 0;
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    r = arr[j][i] / arr[i][i];
                    for (int k = 0; k < 2 * n; k++)
                    {
                        arr[j][k] -= r * arr[i][k];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            r = arr[i][i];
            for (int j = 0; j < 2 * n; j++)
            {
                arr[i][j] /= r;
            }
        }

        FILE *output;
        if ((output = fopen("output.txt", "w")) == NULL)
        {
            printf("ERROR! Can't open the output.txt!\n");

            free_array(&arr, n);

            fclose(fp);

            return -5;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = n; j < n * 2; j++)
            {
                if (to_file)
                    fprintf(output, "%.2lf\t", arr[i][j]);
                else
                    printf("%.2lf\t", arr[i][j]);
            }
            if (to_file)
                fprintf(output, "\n");
            else
                printf("\n");
        }

        free_array(&arr, n);

        fclose(output);
        fclose(fp);
    }

    else
    {
        printf("ERROR! Value beyond the limit!\n");
        return -5;
    }

    return 0;
}