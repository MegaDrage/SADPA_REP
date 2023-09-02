#include <stdio.h>
#include <windows.h>

#include <iostream>

#include "database.h"
#include "list.h"
#include "record.h"
int main() {
    setlocale(LC_ALL, ".866");
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
    int key = welcome();
    FILE* fp;
    list* head = nullptr;
    menu(key, fp, head);
    destroyList(head);
    fclose(fp);
    return 0;
}