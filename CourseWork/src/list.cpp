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
    int i = 0;
    while (head) {
        showRecord(head->data, i++, 0);
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
        showRecord(index[i]->data, i, 1);
    }
}

void showIndexArr(list** index, int start, int end) {
    for (int i = start; i < end; i++) {
        showRecord(index[i]->data, i, 0);
    }
}

int binarySearch(list** index, const char* x) {
    if (!x) {
        return -1;
    }
    int left = 0;
    int right = MAX_DATA - 1;
    int result = -1;
    char data[KEY_SIZE + 1];
    while (left <= right) {
        int mid = left + (right - left) / 2;
        stringCopy(data, index[mid]->data.streetName, KEY_SIZE);
        if (stringCompare(data, x) == 0) {
            result = mid;
            left = mid + 1;
        } else if (stringCompare(data, x) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// int binarySearch(point* pair, const char* x) {
//     if (!x) {
//         return -1;
//     }
//     int left = 0;
//     int right = 9;
//     char data[KEY_SIZE + 1];
//     while (left < right) {
//         int mid = (left + right) / 2;
//         stringCopy(data, pair[mid].key, KEY_SIZE);
//         if (stringCompare(data, x) < 0) {
//             left = mid + 1;
//         } else {
//             right = mid;
//         }
//     }
//     stringCopy(data, pair[right].key, KEY_SIZE);
//     if (stringCompare(data, x) == 0) {
//         return right;
//     }
//     else {
//         return -1;
//     }
// }

point* replaceMove(point* src, int count, int start, int end, char* key) {
    point* newSrc = new point[count + 1];
    for (int i = 0; i < count; i++) {
        newSrc[i] = src[i];
    }
    delete[] src;
    newSrc[count - 1].start = (start > 0) ? start + 1 : start;
    newSrc[count - 1].end = end + 1;
    stringCopy(newSrc[count - 1].key, key, KEY_SIZE);
    return newSrc;
}

int findAllKeys(list** indexArr, point*& index) {
    int i = 0;
    int count = 0;
    char* key = findKey(indexArr, i);
    index = new point[count + 1];
    index->start = 0;
    index->end = 0;
    stringCopy(index->key, key, KEY_SIZE);
    while (i <= MAX_DATA - 1) {
        int start = i;
        int end = binarySearch(indexArr, key);
        i = end;
        count++;
        index = replaceMove(index, count, start, end, key);
        delete[] key;
        key = findKey(indexArr, i + 1);
        if (!key) {
            break;
        }
    }
    // return index;
    return count;
}

char* findKey(list** indexArr, int index) {
    char* key = NULL;
    if (index == -1) {
        return NULL;
    }
    if (index < MAX_DATA) {
        key = new char[MAX_DATA + 1];
        stringCopy(key, indexArr[index]->data.streetName, KEY_SIZE);
    }
    return key;
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
