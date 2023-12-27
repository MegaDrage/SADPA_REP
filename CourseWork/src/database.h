#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "record.h"
#include "treeFuncs.h"
#include "codding.h"
/*ФИО гражданина: текстовое поле 32 символа
                    <Фамилия>_<Имя>_<Отчество>
    Название улицы: текстовое поле 18 символов
    Номер дома:     целое число
    Номер квартиры: целое число
    Дата поселения: текстовое поле 10 символов
                    дд-мм-гг
*/
FILE* openDB();
void menu(int& key, FILE*& fp, list*& head);
int readData(FILE* fp, list*& head);
void menuShow();
void showFullMenu(int& key);
#endif