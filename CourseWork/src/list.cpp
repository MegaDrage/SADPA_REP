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
void indexArr(list* head, list** index) {
    int i = 0;
    list* p = head;
    while (p) {
        index[i++] = p;
        p = p->next;
    }
}
void showIndexArr(list** index, int count) {
    for (int i = 0; i < count + 20; i++) {
        showRecord(index[i]->data);
    }
}

int binSearch(list** index, char x[KEY_SIZE + 1]) {
    int L = 0;
    int R = MAX_DATA - 1;
    char data[KEY_SIZE + 1];
    while (L < R) {
        int mid = (L + R) / 2;
        stringCopy(data, index[mid]->data.streetName, KEY_SIZE);
        if (stringCompare(data, x) < 0) {
            L = mid + 1;
        } else {
            R = mid;
        }
    }
    stringCopy(data, index[R]->data.streetName, KEY_SIZE);
    if (stringCompare(data, x) == 0) {
        return R;
    } else {
        return -1;
    }
}

queue* findAllKeys(list** index, int i, char x[4]) {
    char data[KEY_SIZE + 1];
    int keyMaxSize = findMaxKeySum(index);
    queue* keys = new queue[keyMaxSize];
    int keyIndex = asciiSum(data);
    queueInit(keys[keyIndex].head, keys[keyIndex].tail);
    while (1) {
        stringCopy(data, index[i]->data.streetName, KEY_SIZE);
        if (stringCompare(data, x) != 0) {
            break;
        }
        pushBack(keys[keyIndex].tail, index[i]->data);
        i++;
    }
    return keys;
}
int findMaxKeySum(list** index) {
    char data[KEY_SIZE + 1];
    int i = 0;
    stringCopy(data, index[i]->data.streetName, KEY_SIZE);
    int maxSum = asciiSum(data);
    for (i = 1; i < MAX_DATA; i++) {
        stringCopy(data, index[i]->data.streetName, KEY_SIZE);
        if (maxSum < asciiSum(data)) {
            maxSum = asciiSum(data);
        }
    }
    return maxSum;
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
