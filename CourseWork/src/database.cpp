#include "database.h"

#include "list.h"

FILE* openDB() {
    FILE* fp = fopen("testBase4.dat", "rb");
    return fp;
}

void menuShow() {
    printf(
        "Output Database Like Stack: 1\nSort Database by street name: 2\nSort Database by house number: 3\n");
}
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
    boolean = readData(fp, head);
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
                                indexArr(head, pointer);
                                showStackLikeQueue(head);
                                boolean = 0;
                                break;
                            case 2:
                                if (count < 20) {
                                    digitalSortByStreetName(head);
                                    indexArr(head, pointer);
                                }
                                showIndexArr(pointer, count);
                                boolean = 1;
                                break;
                            case 3:
                                if (count < 20) {
                                    digitalSortByHouseNumber(head);
                                    indexArr(head, pointer);
                                }
                                showIndexArr(pointer, count);
                                boolean = 0;
                                break;
                            case 4:
                                digitalSortAll(head);
                                showStackLikeQueue(head);
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
                    char x[KEY_SIZE + 1];
                    printf("Enter key: ");
                    scanf("%s", x);
                    int index = binSearch(pointer, x);
                    if (index == -1) {
                        printf("NOT FOUND");
                    } else {
                        queue* Q = findAllKeys(pointer, 0, x);
                        showList(Q[asciiSum(x)].head);
                    }
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
