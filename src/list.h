#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

struct Node {
    struct Node * previous;
    struct Node * next;
    void * content;
};

struct List {
    struct Node * head;
    struct Node * tail;

    size_t numOfElements;
};

struct List * newList(size_t const numOfElements);

struct Node * newNode(void * const content);

void addNode(struct List * const list, struct Node * const node);

void removeNode(struct List * const list, struct Node * const node);

#endif // LIST_H
