#ifndef _LIBS_HPP
#define _LIBS_HPP
#include <stdio.h>
#include <string.h>

#include <cmath>

#include "../generator.hpp"

typedef struct c_var {
    long double var_arr[ALPHABET_LEN];
    char charset[66];
} c_var;

void find_variance(long double* var_arr, const char* str);
void QuickSort(long double* A, long long L, long long R);
void swapArrElem(long double* A, long double* B);
void print_variance_arr(long double* var_arr);
void print_codes(const char codes[ALPHABET_LEN][ALPHABET_LEN], const long* code_letter_lens,
                 int alphabet_size);
void shannon_alg(long double* var_arr, const int alphabet_size, long double* Q, long* code_letter_lens,
                 char codes[ALPHABET_LEN][ALPHABET_LEN]);
void gilbert_moore_alg(long double* var_arr, const int alphabet_size, long double* Q, long* code_letter_lens,
                       char codes[ALPHABET_LEN][ALPHABET_LEN]);
void huffman_opt_alg(long double* var_arr, const int alphabet_size, char codes[ALPHABET_LEN][ALPHABET_LEN],
                     long* code_letter_lens);
void fano_alg(int L, int R, int k, long double* var_arr, long* code_letter_lens,
              char codes[ALPHABET_LEN][ALPHABET_LEN]);
int Med(int L, int R, long double* var_arr);
#endif  // _LIBS_HPP