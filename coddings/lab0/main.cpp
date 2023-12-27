#include "libs.hpp"
int main() {
    FILE* fp = fopen("/home/megadrage/programming/SADPA_REP/coddings/random.txt", "r");
    if (fp == NULL) {
        printf("Error opening");
        exit(1);
    }
    char buffer[100000] = {'\0'};
    char c;
    int i = 0;
    while ((c = fgetc(fp)) != EOF) {
        buffer[i++] = c;
    }
    fclose(fp);
    long double var_array[ALPHABET_LEN] = {0.0};
    find_variance(var_array, buffer);
    long double sum = 0.0;
    for (int i = 0; i < ALPHABET_LEN; i++) {
        sum += var_array[i];
    }
    // printf("SUM of Variance:%Lf\n", sum);
    long double Q[ALPHABET_LEN] = {0.0};
    long code_letter_lens[ALPHABET_LEN] = {0};
    char codes_matrix[ALPHABET_LEN][ALPHABET_LEN] = {'\0'};
    // QuickSort(var_array, 0, ALPHABET_LEN - 1);
    shannon_alg(var_array, ALPHABET_LEN, Q, code_letter_lens, codes_matrix);
    // huffman_opt_alg(var_array, ALPHABET_LEN, codes_matrix, code_letter_lens);
    // fano_alg(0, ALPHABET_LEN - 1, 0, var_array, code_letter_lens, codes_matrix);
    // print_codes(codes_matrix, code_letter_lens, ALPHABET_LEN);
    /*TABLE PROTOTYPE*/
    printf("\n=====================SHANNON_CODE========================\n");
    printf("=========================================================\n");
    printf("|   CHAR  |    C_PROB     |    C_CHAR    |    C_LEN    |\n");
    printf("=========================================================\n");
    for (int i = 1; i < ALPHABET_LEN; i++) {
        printf("|%5c    |   %8.7Lf   |  ", random_char(i - 1), var_array[i]);
        for (int j = 0; j < code_letter_lens[i]; j++) {
            printf("%d", codes_matrix[i][j]);
        }
        printf("     |%9ld\t|\n", code_letter_lens[i]);
    }
    printf("=========================================================\n");
    for (int i = 0; i < ALPHABET_LEN; i++) {
        var_array[i] = 0.0;
        Q[i] = 0.0;
        for (int j = 0; j < code_letter_lens[i]; j++) {
            codes_matrix[i][j] = 0;
        }
        code_letter_lens[i] = 0;
    }
    find_variance(var_array, buffer);
    gilbert_moore_alg(var_array, ALPHABET_LEN, Q, code_letter_lens, codes_matrix);
    printf("\n=====================GILBERT_MOORE=======================\n");
    printf("=========================================================\n");
    printf("|   CHAR  |    C_PROB     |    C_CHAR    |    C_LEN    |\n");
    printf("=========================================================\n");
    for (int i = 1; i < ALPHABET_LEN; i++) {
        printf("|%5c    |   %8.7Lf   |  ", random_char(i - 1), var_array[i]);
        for (int j = 0; j < code_letter_lens[i]; j++) {
            printf("%d", codes_matrix[i][j]);
        }
        printf("     |%9ld\t|\n", code_letter_lens[i]);
    }
    printf("=========================================================\n");
    for (int i = 0; i < ALPHABET_LEN; i++) {
        var_array[i] = 0.0;
        code_letter_lens[i] = 0;
    }
    find_variance(var_array, buffer);
    fano_alg(0, ALPHABET_LEN - 1, 0, var_array, code_letter_lens, codes_matrix);
    printf("\n=====================GILBERT_MOORE=======================\n");
    printf("=========================================================\n");
    printf("|   CHAR  |    C_PROB     |    C_CHAR    |    C_LEN    |\n");
    printf("=========================================================\n");
    for (int i = 1; i < ALPHABET_LEN; i++) {
        printf("|%5c    |   %8.7Lf   |  ", random_char(i - 1), var_array[i]);
        for (int j = 0; j < code_letter_lens[i]; j++) {
            printf("%d", codes_matrix[i][j]);
        }
        printf("     |%9ld\t|\n", code_letter_lens[i]);
    }
    printf("=========================================================\n");

    return 0;
}
