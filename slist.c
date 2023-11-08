#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

SList* createSList() {
    SList* list = (SList*)malloc(sizeof(SList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation error in createSList.\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertMove(SList* list, int move) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error in insertMove.\n");
        exit(1);
    }
    newNode->move = move;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void freeSList(SList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
