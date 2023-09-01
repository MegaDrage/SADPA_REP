#include "list.h"

list* init(record data) {
    list* p = new (list);
    p->data = data;
    p->next = nullptr;
    return p;
}
void push(list*& head, record data) {
    if (!head) {
        head = init(data);
        return;
    }
    push(head->next, data);
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