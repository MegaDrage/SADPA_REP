#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <cctype>
#include "list.h"
int main() {
    setlocale(LC_ALL, ".866");
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
    FILE* fp = fopen("testBase4.dat", "rb");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }
    record Record;
    list* head = nullptr;
    while (fread(&Record, sizeof(record), 1, fp) == 1) {
        push(head, Record);
    }
    showList(head);
    destroyList(head);
    fclose(fp);
    return 0;
}