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

struct point {
    int start;
    int end;
    char key[KEY_SIZE + 1];
};
list* init(Record data);
void push(list*& head, Record data);
void queueInit(list*& head, list*& tail);
void showList(list* head);
void showStackLikeQueue(list* head);
void pushBack(list*& tail, Record data);
void destroyList(list*& head);
void digitalSortAll(list*& head);
int binarySearch(list** index, const char* x);
int binarySearch(point* pair, const char* x);
// point* findAllKeys(list** indexArr);
int findAllKeys(list** indexArr, point*& index);
void indexArr(list* head, list** index);
char* findKey(list** indexArr, int index);
void showIndexArr(list** index, int count);
void showIndexArr(list** index, int end, int start);
void digitalSortByStreetName(list*& S);
void digitalSortByHouseNumber(list*& S);
#endif