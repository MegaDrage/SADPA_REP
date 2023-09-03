#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "record.h"
/*ФИО гражданина: текстовое поле 32 символа
                    фоpмат <Фамилия>_<Имя>_<Отчество>
    Название улицы: текстовое поле 18 символов
    Номер дома:     целое число
    Номер квартиры: целое число
    Дата поселения: текстовое поле 10 символов
                    фоpмат дд-мм-гг
*/
FILE* openDB();
void menu(int& key, FILE*& fp, list*& head);
int readData(FILE* fp, list*& head);
void menuShow();
void showfullMenu(int& key);
#endif