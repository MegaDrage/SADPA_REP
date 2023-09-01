#include "database.h"

void showRecord(record Record) {
    printf("%s\n", Record.name);
    printf("%s\n", Record.streetName);
    printf("%d\n", Record.houseNumber);
    printf("%d\n", Record.appNumber);
    printf("%s\n", Record.settlementDate);
}