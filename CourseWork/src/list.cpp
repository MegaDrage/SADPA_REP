#include "list.h"

list* init(record data) {
    list* p = new (list);
    p->data = data;
    p->next = nullptr;
    return p;
}

void queueInit(list*& head, list*& tail) { tail = (list*)&head; }
void push(list*& head, record data) {
    if (!head) {
        head = init(data);
        return;
    }
    head = head->next;
    head = init(data);
}

void pushBack(list*& tail, record data) {
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
void destroyList(list*& head) {
    while (head) {
        list* p = head;
        head = head->next;
        delete p;
    }
}