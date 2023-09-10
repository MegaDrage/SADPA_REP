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
    int i = MAX_DATA;
    while (head) {
        showRecord(head->data, i);
        i--;
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
        showRecord(index[i]->data, i);
    }
}

void findAllKeys(list** indexArr) {
    int i = 0;
    int count = 0;
    char* key = findKey(indexArr, i);
    while (i <= MAX_DATA - 1) {
        int start = binSearch(indexArr, key);
        int end = binSearch2(indexArr, key);
        if (start != -1 && end != -1) {
            count++;
        } else {
            break;
        }
        i = end;
        key = findKey(indexArr, i + 1);
        printf("%s", key);
    }
    printf("%d\n", count);
}

char* findKey(list** indexArr, int index) {
    char* key = NULL;
    if (index < 4000) {
        key = new char[MAX_DATA + 1];
        stringCopy(key, indexArr[index]->data.streetName, MAX_DATA);
    }
    return key;
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
int binSearch2(list** index, char x[KEY_SIZE + 1]) {
    int L = 0;
    int R = MAX_DATA - 1;
    char data[KEY_SIZE + 1];
    while (L < R) {
        int mid = (L + R) / 2;
        stringCopy(data, index[mid]->data.streetName, KEY_SIZE);
        if (stringCompare(data, x) > 0) {
            L = mid - 1;
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
            d = (p->data.houseNumber >> j) & 0xFF;
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

void digitalSortByAppNumber(list*& S) {
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
            d = (p->data.appNumber >> j) & 0xFF;
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
    digitalSortByAppNumber(S);
    digitalSortByHouseNumber(S);
    digitalSortByStreetName(S);
}
