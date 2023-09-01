#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <string.h>
typedef struct record {
    char name[32];
    char streetName[18];
    short int houseNumber;
    short int appNumber;
    char settlementDate[10];
} record;
void showRecord(record Record);
#endif