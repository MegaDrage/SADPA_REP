#include "record.h"
void showRecord(Record record, int i, int l) {
    if (i % 20 == 0 && l != 0) {
        printf("\033c");
        printf("PAGE: %d\n", i / 20);
    }
    printf("%d. ", i + 1);
    printf("%s\t", record.name);
    printf("%s\t", record.streetName);
    printf("%d\t", record.houseNumber);
    printf("%d\t", record.appNumber);
    printf("%s\n", record.settlementDate);
}

void showRecord(Record record) {
    printf("%s ", record.name);
    printf("%s ", record.streetName);
    printf("%d ", record.houseNumber);
    printf("%d ", record.appNumber);
    printf("%s\n", record.settlementDate);
}
int stringCompare(const char* str, const char* str1) {
    while (*str && (*str == *str1)) {
        str++;
        str1++;
    }
    return *(const unsigned char*)str - *(const unsigned char*)str1;
}
void stringCopy(char* src, const char* dest, int count) {
    if (src == NULL || dest == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        src[i] = dest[i];
    }
    src[count] = '\0';
}