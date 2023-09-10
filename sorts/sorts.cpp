#include <math.h>
#include <time.h>

#include "stuff.h"
void QuickSort(int *A, long long L, long long R) {
    while (L < R) {
        int x = A[(L + R) / 2];
        long i = L;
        long j = R;
        while (i <= j) {
            while (A[i] < x) {
                i++;
            }
            while (A[j] > x) {
                j--;
            }
            if (i <= j) {
                swapArrElem(&A[i], &A[j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSort(A, L, j);
            L = i;
        } else {
            QuickSort(A, i, R);
            R = j;
        }
    }
}

void SelectSort(int *A, long long size) {
    int k = 0;
    long i = 0;
    long j = 0;
    for (i = 0; i < size; i++) {
        k = i;
        for (j = i + 1; j < size; j++) {
            if (A[k] > A[j]) {
                k = j;
            }
        }
        if (i != k) {
            swapArrElem(&A[i], &A[k]);
        }
    }
}

long long BubbleSort(int *A, long long size) {
    for (long i = 0; i < size; i++) {
        for (long j = size - 1; j > 0; j--) {
            if (A[j] < A[j - 1]) {
                swapArrElem(&A[j], &A[j - 1]);
            }
        }
    }
}
long long ShakerSort(int *A, long long size) {
    long L = 0;
    long R = size - 1;
    long k = size - 1;
    do {
        for (int j = R; j > L; j--) {
            if (A[j] < A[j - 1]) {
                swapArrElem(&A[j], &A[j - 1]);
                k = j;
            }
        }
        L = k;
        for (int j = L; j < R; j++) {
            if (A[j] > A[j + 1]) {
                swapArrElem(&A[j], &A[j + 1]);
                k = j;
            }
        }
        R = k;
    } while (L < R);
}

void InsertSort(int *A, long long size) {
    for (long i = 0; i < size; i++) {
        int t = A[i];
        long j = i - 1;
        while (j > 0 && t < A[j]) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = t;
    }
}

void ShellSort(int *A, long long size) {
    long long t, j;
    long k = 1;
    for (int i = 1; i < log(size) - 1; i++) {
        k = 2 * k + 1;
    }
    for (k; k > 0; k = (k - 1) / 2) {
        for (int i = k; i < size; i++) {
            t = A[i];
            for (j = i; j >= k && A[j - k] > t; j -= k) {
                A[j] = A[j - k];
            }
            A[j] = t;
        }
    }
}

void HeapMake(int *A, long long n, long long left) {
    int x = A[left];
    long i = left;
    while (1) {
        int j = 2 * i;
        if (j > n) {
            break;
        }
        if ((j < n - 1) && (A[j + 1] >= A[j])) {
            j++;
        }
        if (x >= A[j]) {
            break;
        }
        A[i] = A[j];
        i = j;
    }
    A[i] = x;
    return;
}
long long HeapSort(int *A, long long n) {
    long long start_time = clock();
    long long L = floor(n / 2);
    while (L >= 0) {
        HeapMake(A, n, L);
        L--;
    }
    int R = n - 1;
    while (R > 1) {
        swapArrElem(&A[0], &A[R]);
        R--;
        HeapMake(A, R, 0);
    }
    long long end_time = clock();
    return end_time - start_time;
}