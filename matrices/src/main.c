#include "../include/include.h"

int main()
{
    srand(time(NULL));
    clock_t begin = clock(), end = clock();

    int command = 0;

    printf("1 = A + B, 2 = A * constant, 3 = A * B, 4 = A^T, 5 = detA, 6 = A^(-1):\n");
    scanf("%d", &command);

    begin = clock();

    menu(&command);

    end = clock();

    printf("\n\nTIME = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("End of program!\n");

    getchar();

    return 0;
}