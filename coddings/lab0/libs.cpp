#include "libs.hpp"

#include "../generator.hpp"

void find_variance(long double* var_arr, const char* str) {
    for (int i = 0; i < ALPHABET_LEN; i++) {
        for (int j = 0; j < FILE_SIZE * FILE_LEN; j++) {
            if (str[j] == random_char(i)) {
                var_arr[i]++;
            }
        }
    }
    for (int i = 0; i < ALPHABET_LEN; i++) {
        var_arr[i] /= (FILE_SIZE * FILE_LEN);
    }
}

void print_variance_arr(long double* var_arr) {
    for (int i = 0; i < ALPHABET_LEN; i++) {
        printf("%Lf\n", var_arr[i]);
    }
}

void shannon_alg(long double* var_arr, const int alphabet_size, long double* Q, long* code_letter_lens,
                 char codes[ALPHABET_LEN][ALPHABET_LEN]) {
    Q[0] = 0.0;
    code_letter_lens[0] = -ceil(log2(var_arr[0]));
    for (int i = 1; i < alphabet_size; i++) {
        Q[i] = Q[i - 1] + var_arr[i - 1];
        code_letter_lens[i] = -ceil(log2(var_arr[i]));
    }
    for (int i = 0; i < alphabet_size; i++) {
        for (int j = 0; j < code_letter_lens[i]; j++) {
            Q[i] = Q[i] * 2.;
            codes[i][j] = floor(Q[i]);
            if (Q[i] > 1) Q[i]--;
        }
    }
}

void gilbert_moore_alg(long double* var_arr, const int alphabet_size, long double* Q, long* code_letter_lens,
                       char codes[ALPHABET_LEN][ALPHABET_LEN]) {
    long double pr = 0.0;
    for (int i = 0; i < alphabet_size; i++) {
        Q[i] = pr + var_arr[i] / 2.;
        pr += var_arr[i];
        code_letter_lens[i] = -ceil(log2(var_arr[i])) + 1;
    }
    for (int i = 0; i < alphabet_size; i++) {
        for (int j = 0; j < code_letter_lens[i]; j++) {
            Q[i] = Q[i] * 2.;
            codes[i][j] = floor(Q[i]);
            if (Q[i] > 1) Q[i]--;
        }
    }
}

int Up(const int alphabet_size, long double* var_arr, long double q) {
    int j = 0;
    for (int i = alphabet_size - 2; i > 0; i--) {
        if (var_arr[i - 1] < q) {
            var_arr[i] = var_arr[i - 1];
        } else {
            j = i;
            break;
        }
    }
    var_arr[j] = q;
    return j;
}

void Down(const int alphabet_size, long* code_letter_lens, char codes[ALPHABET_LEN][ALPHABET_LEN], int j) {
    char S[code_letter_lens[j]];
    for (int i = 0; i < code_letter_lens[j]; i++) {
        S[i] = codes[j][i];
    }
    long letter_len = code_letter_lens[j];
    for (int i = j; i <= alphabet_size - 2; i++) {
        for (int k = 0; k < code_letter_lens[i + 1]; k++) {
            codes[i][k] = codes[i + 1][k];
        }
        code_letter_lens[i] = code_letter_lens[i + 1];
    }
    code_letter_lens[alphabet_size - 1] = letter_len + 1;
    code_letter_lens[alphabet_size] = letter_len + 1;
    for (int i = 0; i < letter_len; i++) {
        codes[alphabet_size - 1][i] = S[i] = codes[alphabet_size][i] = S[i];
    }
    codes[alphabet_size - 1][letter_len] = 0;
    codes[alphabet_size][letter_len] = 1;
}
void huffman_opt_alg(long double* var_arr, const int alphabet_size, char codes[ALPHABET_LEN][ALPHABET_LEN],
                     long* code_letter_lens) {
    if (alphabet_size == 2) {
        codes[1][1] = 0;
        code_letter_lens[1] = 1;
        codes[2][1] = 1;
        code_letter_lens[2] = 1;
    } else {
        long double q = var_arr[alphabet_size - 2] + var_arr[alphabet_size - 1];
        int j = Up(alphabet_size, var_arr, q);
        huffman_opt_alg(var_arr, alphabet_size - 1, codes, code_letter_lens);
        Down(alphabet_size - 1, code_letter_lens, codes, j);
    }
}

int Med(int L, int R, long double* var_arr) {
    long double SL = 0;
    for (int i = L; i < R; i++) {
        SL += var_arr[i];
    }
    long double SR = var_arr[R];
    int m = R;
    while (SL >= SR) {
        m--;
        SL -= var_arr[m];
        SR += var_arr[m];
    }
    return m;
}

void fano_alg(int L, int R, int k, long double* var_arr, long* code_letter_lens,
              char codes[ALPHABET_LEN][ALPHABET_LEN]) {
    if (L < R) {
        k++;
        int m = Med(L, R, var_arr);
        for (int i = L; i <= R; i++) {
            if (i <= m) {
                codes[i][k - 1] = 0;
                code_letter_lens[i] += 1;
            } else {
                codes[i][k - 1] = 1;
                code_letter_lens[i] += 1;
            }
        }
        fano_alg(L, m, k, var_arr, code_letter_lens, codes);
        fano_alg(m + 1, R, k, var_arr, code_letter_lens, codes);
    }
}

void print_codes(const char codes[ALPHABET_LEN][ALPHABET_LEN], const long* code_letter_lens,
                 int alphabet_size) {
    for (int i = 0; i < alphabet_size; i++) {
        for (int j = 0; j < code_letter_lens[i]; j++) {
            printf("%d", codes[i][j]);
        }
        printf("\t%ld", code_letter_lens[i]);
        puts("");
    }
}

void swapArrElem(long double* A, long double* B) {
    long double temp = *A;
    *A = *B;
    *B = temp;
}

void QuickSort(long double* A, long long L, long long R) {
    while (L < R) {
        long double x = A[(L + R) / 2];
        long i = L;
        long j = R;
        while (i <= j) {
            while (A[i] > x) {
                i++;
            }
            while (A[j] < x) {
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

void swap_arr(long double* arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        swapArrElem(&arr[i], &arr[size - 1 - i]);
    }
}
