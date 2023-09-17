#include "database.h"

#include "list.h"

FILE* openDB() {
    FILE* fp = fopen("/home/megadrage/programming/SADPA_REP/CourseWork/src/testBase4.dat", "rb");
    return fp;
}

void menuShow() { printf("Output Database Like Stack: 1\nSort Database: 2\n"); }
void showFullMenu(int& key) {
    printf("if you want to output database enter 1:\n");
    printf("If you want to take binary search enter: 2\n");
    printf("If you want to get out of menu enter: 0\n");
    if (scanf("%d", &key) != 1) {
        key = -1;
    }
    if (key == 0) {
        printf("\n\t!EXIT!\n");
    }
}
void menu(int& key, FILE*& fp, list*& head) {
    int boolean = 0;
    struct list* pointer[4000];
    fp = openDB();
    if (!fp) {
        printf("Error opening file\n");
        return;
    }
    readData(fp, head);
    indexArr(head, pointer);
    while (key != 0) {
        switch (key) {
            case 1:
                menuShow();
                if ((scanf("%d", &key) == 1) && (key >= 0 && key <= 4)) {
                    int count = 0;
                    int saveKey = key;
                    while (count != 3980) {
                        switch (key) {
                            case 1:
                                showList(head);
                                boolean = 0;
                                break;
                            case 2:
                                if (!boolean) {
                                    digitalSortAll(head);
                                    indexArr(head, pointer);
                                }
                                showIndexArr(pointer, count);
                                boolean = 1;
                                break;
                            case 0:
                                if (saveKey != 2) {
                                    boolean = 0;
                                }
                                printf("\n\t!EXIT MENU!\n");
                                count = 3980;
                                break;
                            default:
                                break;
                        }
                        if (count != 3980 && key) {
                            count += 20;
                            printf("To continue enter same number, to exit enter 0: ");
                            scanf("%d", &key);
                        }
                        if (saveKey != key && key != 0) {
                            printf("\n\t!WRONG\tINPUT!\n");
                            break;
                        }
                    }
                } else {
                    printf("\n\t!WRONG\tINPUT!\n");
                    return;
                }
                showFullMenu(key);
                break;
            case 2:
                if (boolean) {
                    point* find;
                    int count = findAllKeys(pointer, find);
                    char keyToFind[KEY_SIZE + 1];
                    for (int i = 0; i < count; i++) {
                        printf("Key %d: %s\n", i + 1, find[i].key);
                    }
                    printf("Enter key to find: ");
                    scanf("%s", keyToFind);
                    int i = 0;
                    for (i = 0; i < count; i++) {
                        if (stringCompare(find[i].key, keyToFind) == 0) {
                            showIndexArr(pointer, find[i].start, find[i].end);
                            break;
                        }
                    }
                    
                    delete[] find;
                    showFullMenu(key);
                } else {
                    printf("\n\t!DB wasn't opened or sorted!\t\n");
                    showFullMenu(key);
                }
                break;
            case 0:
                printf("\n\t!EXIT!\n");
                break;
            default:
                printf("\n\t!WRONG\tINPUT!\n");
                return;
                break;
        }
    }
}

int readData(FILE* fp, list*& head) {
    Record record;
    while (fread(&record, sizeof(Record), 1, fp)) {
        push(head, record);
    }
    fclose(fp);
    return 1;
}
