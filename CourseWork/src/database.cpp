#include "database.h"

#include "list.h"

int welcome() {
    printf("Welcome to the database system testBase4.dat;\n");
    printf(
        "Before using the services, establish a connection with the database, to establish a connection "
        "enter 1; \nIf you want to exit the menu, enter 0;\n");
    int key = -1;
    scanf("%d", &key);
    return key;
}
FILE* openDB() {
    FILE* fp = fopen("testBase4.dat", "rb");
    return fp;
}

void menuShow() {
    printf(
        "Output Database Like Stack: 1\nSort Database by street name: 2\nSort Database by house number: 3\n");
}
void menu(int& key, FILE*& fp, list*& head) {
    switch (key) {
        case 1:
            fp = openDB();
            if (!fp) {
                printf("Error opening file\n");
                return;
            }

            menuShow();
            int count;
            if ((scanf("%d", &key) == 1) && (key >= 0 && key < 4)) {
                printf("Enter the number of output items (LIMITED BY 4000): ");
                if ((scanf("%d", &count) == 1) && readData(fp, head, count)) {
                    switch (key) {
                        case 1:
                            showStackLikeQueue(head);
                            break;
                        case 2:
                            digitalSortByStreetName(head);
                            showList(head);
                            break;
                        case 3:
                            digitalSortByHouseNumber(head);
                            showList(head);
                            break;
                        // case 4:
                        //     digitalSortAll(head);
                        //     showList(head);
                        case 0:
                        default:
                            break;
                    }
                }
            } else {
                printf("\n\t!WRONG\tINPUT!\n");
                return;
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

int readData(FILE* fp, list*& head, int count) {
    int boolean = 1;
    if (count > MAX_DATA) {
        printf("\n\tERROR:The number of elements cannot exceed%d\n", MAX_DATA);
        boolean = 0;
    }
    if (count <= 0) {
        printf("\n\tERROR:The number of elements can't be that number\n");
        boolean = 0;
    }
    if (boolean) {
        Record record;
        int i = 0;
        while (fread(&record, sizeof(Record), 1, fp) && i < count) {
            push(head, record);
            i++;
        }
    }
    return 1;
}