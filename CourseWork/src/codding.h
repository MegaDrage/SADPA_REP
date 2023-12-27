#ifndef _CODDING_H
#define _CODDING_H
#define MAX_CHAR_LEN 256
#include <math.h>
#include <stdio.h>

typedef struct gbc {
    long double Q;
    long double P;
    unsigned char c;
    short int L;
} gbc;

void CodePrint(gbc* A, long double entropy, char** codes);
void BaseCoding(gbc* A, int* sum, long double* entropy, int* sym_count, char** codes);
void compRatio();
void codeDB(gbc* A, char** codes);
#endif  // _CODDING_H