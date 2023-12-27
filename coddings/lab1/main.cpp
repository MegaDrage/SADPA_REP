#include <stdio.h>
#include <stdlib.h>
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
    return 0;
}
