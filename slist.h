#ifndef SLIST_H
#define SLIST_H

typedef struct Node {
    int move;
    struct Node* next;
} Node;

typedef struct SList {
    Node* head;
    int size;
} SList;

SList* createSList();
void insertMove(SList* list, int move);
void freeSList(SList* list);

#endif
