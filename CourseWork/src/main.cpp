#include <stdio.h>
#include <windows.h>

#include <iostream>

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
    Record record;
    list* head = nullptr;
    while (fread(&record, sizeof(Record), 1, fp) == 1) {
        push(head, record);
    }
    digitalSortStreetName(head);
    showStack(head);
    destroyList(head);
    fclose(fp);
    return 0;
}