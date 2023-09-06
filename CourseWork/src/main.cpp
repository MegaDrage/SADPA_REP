#include <stdio.h>

#include <iostream>

#include "database.h"
#include "list.h"
#include "record.h"
int main() {
    int key;
    showFullMenu(key);
    FILE* fp;
    list* head = nullptr;
    menu(key, fp, head);
    destroyList(head);
    return 0;
}
