#include "record.h"
void showRecord(Record record) {
    printf("%s\n", record.name);
    printf("%s\n", record.streetName);
    printf("%d\n", record.houseNumber);
    printf("%d\n", record.appNumber);
    printf("%s\n", record.settlementDate);
}