#include <stdio.h>
#include <string.h>

#include "list.h"
int main() {
    FILE* fp = fopen("testBase4.dat", "rb");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }
    record Record;
    list* head = nullptr;
    // while (fread(&Record, sizeof(record), 1, fp) == 1) {
    //     push(head, Record);
    // }
    fread(&Record, sizeof(record), 1, fp);
    push(head, Record);
    showList(head);
    destroyList(head);
    fclose(fp);
    return 0;
}