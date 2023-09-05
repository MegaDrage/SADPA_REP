#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swapArrElem(int *A, int *B) {
    int temp = *A;
    *A = *B;
    *B = temp;
}

void fillrandint(int *A, long long n) {
    srand(time(NULL));
    for (long long i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}