#include "list.h"

#include "record.h"
list* init(Record data) {
    list* p = new (list);
    p->data = data;
    p->next = nullptr;
    return p;
}

void queueInit(list*& head, list*& tail) { tail = (list*)&head; }
void push(list*& head, Record data) {
    list* p = new (list);
    p->data = data;
    p->next = head;
    head = p;
}

void pushBack(list*& tail, Record data) {
    list* p = init(data);
    tail->next = p;
    tail = p;
}
void showList(list* head) {
    while (head) {
        showRecord(head->data);
        head = head->next;
    }
}
void showStackLikeQueue(list* head) {
    if (head) {
        showStackLikeQueue(head->next);
        showRecord(head->data);
    }
}
void destroyList(list*& head) {
    while (head) {
        list* p = head;
        head = head->next;
        delete p;
    }
}
void digitalSortByStreetName(list*& S) {
    queue Q[256];
    list* p;
    int d;
    int L = 4;
    for (int j = L; j >= 0; j--) {
        for (int i = 0; i < 256; i++) {
            queueInit(Q[i].head, Q[i].tail);
        }
        p = S;
        while (p) {
            d = (p->data.streetName[j]) & 0xFF;
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
        }
        p = (list*)&S;
        for (int i = 0; i < 256; i++) {
            if (Q[i].tail != (list*)&Q[i].head) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
            p->next = nullptr;
        }
    }
}
void digitalSortByHouseNumber(list*& S) {
    queue Q[256];
    list* p;
    int d;
    int L = sizeof(short int);
    for (int j = L; j >= 0; j--) {
        for (int i = 0; i < 256; i++) {
            queueInit(Q[i].head, Q[i].tail);
        }
        p = S;
        while (p) {
            d = (p->data.houseNumber >> (j * 8)) & 0xFF;
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
        }
        p = (list*)&S;
        for (int i = 0; i < 256; i++) {
            if (Q[i].tail != (list*)&Q[i].head) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
            p->next = nullptr;
        }
    }
}
void digitalSortAll(list*& S) {
    digitalSortByStreetName(S);
    digitalSortByHouseNumber(S);
}
