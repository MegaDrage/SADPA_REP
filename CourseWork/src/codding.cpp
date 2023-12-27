#include "codding.h"

int code_index = 0;

void QuickSort(long long L, long long R, gbc* A) {
    while (L < R) {
        long double x = A[(L + R) / 2].P;
        long i = L;
        long j = R;
        while (i <= j) {
            while (A[i].P > x) {
                i++;
            }
            while (A[j].P < x) {
                j--;
            }
            if (i <= j) {
                gbc B = A[i];
                A[i] = A[j];
                A[j] = B;
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSort(L, j, A);
            L = i;
        } else {
            QuickSort(i, R, A);
            R = j;
        }
    }
}


void gilbert_moore_alg(const int alphabet_size, gbc* code, char** codes) {
    long double pr = 0.0;
    for (int i = code_index - 1; i < alphabet_size; i++) {
        code[i].Q = pr + code[i].P / 2;
        pr += code[i].P;
        code[i].L = -ceil(log2(code[i].P)) + 1;
    }
    for (int i = code_index - 1; i < alphabet_size; i++) {
        for (int j = 0; j < alphabet_size; j++) {
            code[i].Q = code[i].Q * 2;
            codes[i][j] = floor(code[i].Q);
            if (code[i].Q > 1) code[i].Q -= 1;
        }
    }
}

void BaseCoding(gbc* A, int* sum, long double* entropy, int* sym_count, char** codes) {
    FILE* f = fopen("/home/megadrage/programming/SADPA_REP/CourseWork/src/testBase4.dat", "rb");
    for (int i = 0; i < MAX_CHAR_LEN; i++) {
        A[i].P = 0.0;
        A[i].L = 0;
        A[i].Q = 0.0;
        A[i].c = (char)(i - 128);
    }
    while (!feof(f)) {
        char c;
        fscanf(f, "%c", &c);
        if (feof(f)) break;
        A[c + 128].P++;
        (*sum)++;
    }
    fclose(f);
    code_index = 0;
    QuickSort(0, MAX_CHAR_LEN - 1, A);
    while(A[code_index++].P == 0.0) {

    }
    for (int i = code_index - 1; i < MAX_CHAR_LEN && A[i].P != 0.0; i++) {
            A[i].P /= *sum;
            A[i].Q = A[i].P;
            *entropy += A[i].P * log2(A[i].P);
            (*sym_count)++;
    }
    *entropy = -*entropy;
    gilbert_moore_alg(MAX_CHAR_LEN, A, codes);
}

void CodePrint(gbc* A, long double entropy, char** codes) {
    long double lgm = 0;
    printf("\n\nOptimal code of Gilbert_Moore: \n");
    printf("-------------------------------------------------------------------------------\n");
    printf("|  Symbol num   | Symbol | Probability |       Code word      | Code word len |\n");
    printf("|-----------------------------------------------------------------------------|\n");
    for (int i = code_index - 1; i < MAX_CHAR_LEN && A[i].P != 0.0; i++) {
            printf("|  %12d |    %c   |  %2.6Lf   | ", i - code_index + 1, A[i].c, A[i].P);
            for (int j = 0; j < A[i].L + 1; j++) printf("%d", codes[i][j]);
            for (int j = A[i].L + 1; j < 18; j++) printf(" ");
            printf("   |  %7d      |\n", A[i].L + 1);
            printf("|-----------------------------------------------------------------------------|\n");
            lgm += A[i].P * A[i].L;
    }
    printf("_______________________________\n");
    printf("|  Entropy   |     Mid len     |\n");
    printf("|____________|_________________|\n");
    printf("| %10Lf |   %10.5Lf    |\n", entropy, lgm);
    printf("|____________|_________________|\n");
    printf("|---------------------------|\n");
    printf("| entropy  +  2   >   Lsr   |\n");
    printf("|___________________________|\n");
    printf("| %8Lf   > %8.5Lf     |\n", entropy + 2, lgm);
    printf("|___________________________|\n");
}

void codeDB(gbc* A, char** codes) {
    FILE* f = fopen("/home/megadrage/programming/SADPA_REP/CourseWork/src/testBase4.dat", "rb");
    FILE* cf = fopen("/home/megadrage/programming/SADPA_REP/CourseWork/src/testBase4c.dat", "wb");
    while (!feof(f)) {
        char c;
        fscanf(f, "%c", &c);
        if (feof(f)) break;
        for (int i = 0; i < MAX_CHAR_LEN; i++) {
            if (c == A[i].c) {
                fwrite(codes[i], 1, 1, cf);
            }
        }
    }
    fclose(f);
    fclose(cf);
}

void compRatio() {
    FILE* f = fopen("/home/megadrage/programming/SADPA_REP/CourseWork/src/testBase4.dat", "rb");
    FILE* cf = fopen("/home/megadrage/programming/SADPA_REP/CourseWork/src/testBase4c.dat", "rb");
    fseek(f, 0L, SEEK_END);
    long sf = ftell(f);
    fseek(cf, 0L, SEEK_END);
    long scf = ftell(cf);
    printf("Size of basic DB: %ld\n", sf);
    printf("Size of codded DB: %ld\n", scf);
    printf("Compression ratio: %Lf\n", (long double)scf / (long double)sf);
    fclose(f);
    fclose(cf);
}