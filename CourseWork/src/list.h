#ifndef LIST_H
#define LIST_H
#include "record.h"
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
void showList(list* head);
void showStackLikeQueue(list* head);
void pushBack(list*& tail, Record data);
void destroyList(list*& head);
void digitalSortAll(list*& head);
void digitalSortByStreetName(list*& S);
void digitalSortByHouseNumber(list*& S);
#endif