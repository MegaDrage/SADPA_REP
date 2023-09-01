#pragma once
#ifndef LIST_H
#define LIST_H
#include "database.h"
struct list {
    struct list* next;
    Record data;
};
struct queue {
    list* head;
    list* tail;
};
list* init(Record data);
void push(list*& head, Record data);
void queueInit(list*& head, list*& tail);
void showQueue(list* head);
void showStack(list* head);
void pushBack(list*& tail, Record data);
void destroyList(list*& head);
void digitalSortStreetName(list*& S);
#endif