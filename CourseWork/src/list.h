#ifndef LIST_H
#define LIST_H
#include "database.h"
typedef struct list {
    struct list* next;
    record data;
} list;
list* init(record data);
void push(list*& head, record data);
void showList(list* head);
void destroyList(list*& head);
#endif