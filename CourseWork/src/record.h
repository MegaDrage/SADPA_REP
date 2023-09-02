#ifndef RECORD_H
#define RECORD_H
#include <stdio.h>
/*ФИО гражданина: текстовое поле 32 символа
                    фоpмат <Фамилия>_<Имя>_<Отчество>
    Название улицы: текстовое поле 18 символов
    Номер дома:     целое число
    Номер квартиры: целое число
    Дата поселения: текстовое поле 10 символов
                    фоpмат дд-мм-гг
*/
struct Record {
    char name[32];
    char streetName[18];
    short int houseNumber;
    short int appNumber;
    char settlementDate[10];
};
void showRecord(Record record);
#endif