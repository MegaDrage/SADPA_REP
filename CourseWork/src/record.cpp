#include "record.h"
void showRecord(Record record) {
    printf("%s\n", record.name);
    printf("%s\n", record.streetName);
    printf("%d\n", record.houseNumber);
    printf("%d\n", record.appNumber);
    printf("%s\n", record.settlementDate);
}

int stringCompare(const char* str, const char* str1) {
    while (*str && (*str == *str1)) {
        str++;
        str1++;
    }
    return *(const unsigned char*)str - *(const unsigned char*)str1;
}
void stringCopy(char* src, char* dest, int count) {
    for (int i = 0; i < count; i++) {
        src[i] = dest[i];
    }
    src[KEY_SIZE] = '\0';
}

int asciiSum(char* src) {
    int sum = 0;
    while (*src) {
        sum += *src++ & 0xFF;
    }
    return sum;
}