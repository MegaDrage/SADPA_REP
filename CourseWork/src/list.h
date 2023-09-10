#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

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
int binSearch(list** index, char x[KEY_SIZE + 1]);
int binSearch2(list** index, char x[KEY_SIZE + 1]);
void findAllKeys(list** indexArr);
void indexArr(list* head, list** index);
char* findKey(list** indexArr, int index);
void showIndexArr(list** index, int count);
void digitalSortByStreetName(list*& S);
void digitalSortByHouseNumber(list*& S);
#endif