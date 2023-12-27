#include "generator.hpp"

char random_char(int index) {
    char charset[] = " ΅Ά¤£¥ρ¦§¨©ª«¬­®―ΰαβγδεζηθικλμνξο€‚ƒ„…π†‡‰‹‘’“”•–—™›";  // 66 // 128-175 ; 224 - 241
    return charset[index];
}

void generate_random_ru_file(const char* filename) {
    FILE* fp = fopen(filename, "w");
    unsigned int len = FILE_SIZE;
    for (unsigned int i = 0; i < len; i++) {
        for (int j = 0; j < 500; j++) {
            char symbol = (rand() % 2) ? 241 - rand() % 18 : 175 - rand() % 48;
            fputc(symbol, fp);
        }
    }
    printf("FILE GENERATED\n");
    fclose(fp);
}