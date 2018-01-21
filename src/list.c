#include "list.h"

#include <stdio.h>

struct List * newList(size_t const numOfElements) {
    if (numOfElements == 0) {
        fprintf(stderr, "Number of nodes must be greater than 0\n");
        exit(-1);
    }

    struct List * const list = (struct List *) calloc(1, sizeof(struct List));
    list->numOfElements = numOfElements;

    list->head = newNode(NULL);

    struct Node * current = list->head;
    for (int i = 1; i < numOfElements; ++i) {
        struct Node *node = newNode(NULL);
        current->next = node;
        node->previous = current;
        current = node;
    }

    list->tail = current;

    return list;
}

struct Node * newNode(void * const content) {
    struct Node * const node = (struct Node *) calloc(1, sizeof(struct Node));
    node->content = content;
    return node;
}

void addNode(struct List * const list, struct Node * const node) {
    if (list->numOfElements == 0) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }

    list->numOfElements++;
}

void removeNode(struct List * const list, struct Node * const node) {
    if (node->next != NULL) {
        node->next->previous = node->previous;
    }

    if (node->previous != NULL) {
        node->previous->next = node->next;
    }

    if (list->head == node) {
        list->head = list->head->next;
    }

    if (list->tail == node) {
        list->tail = list->tail->previous;
    }

    list->numOfElements--;

    free(node);
}
