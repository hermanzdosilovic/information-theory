#include "graph.h"
#include "list.h"
#include "reader.h"
#include "types.h"

#include <stdio.h>
#include <string.h>

const ushort kNumberOfNodes = 128;

struct Symbol {
    char character;
    uint frequency;
    char code;
};

struct Symbol * newSymbol(uint frequency) {
    struct Symbol * const symbol = (struct Symbol *) calloc(1, sizeof(struct Symbol));
    symbol->frequency = frequency;
    return symbol;
}

void validateText(char * text) {
    size_t N = strlen(text);
    for (size_t i = 0; i < N; ++i) {
        if (text[i] < 0 || text[i] > kNumberOfNodes) {
            fprintf(stderr, "Illegal character with ASCII code %d\n", text[i]);
            exit(-1);
        }
    }
}

void calculateFrequency(char * text, uint * frequency) {
    size_t N = strlen(text);
    for (size_t i = 0; i < N; ++i) {
        frequency[text[i]]++;
    }
}

struct Node * const findSmallestFrequency(struct List * const list) {
    struct Node * node = NULL;
    uint smallestFrequency;

    struct Node * head = list->head;
    while (head != NULL) {
        struct Vertex * const vertex = (struct Vertex *) head->content;
        struct Symbol * const symbol = (struct Symbol *) vertex->content;
        if (node == NULL || symbol->frequency < smallestFrequency) {
            node = head;
            smallestFrequency = symbol->frequency;
        }
        head = head->next;
    }

    return node;
}

void constructCodes(struct Vertex * const node, char * const parentCode, char ** codes) {
    struct Symbol * const symbol = (struct Symbol *) node->content;

    char * const nodeCode = (char *) calloc(strlen(parentCode) + 2, sizeof(char));
    strcpy(nodeCode, parentCode);
    nodeCode[strlen(nodeCode)] = symbol->code;

    if (node->numOfNeighbours == 0) {
        codes[symbol->character] = nodeCode;
        return;
    }

    for (size_t i = 0; i < node->numOfNeighbours; ++i) {
        constructCodes(node->neighbours[i], nodeCode, codes);
    }
}

int main(int args, char ** argv) {
    char * const text = read();
    validateText(text);

    uint frequency[kNumberOfNodes];
    memset(frequency, 0, sizeof(frequency));

    char * codes[kNumberOfNodes];

    calculateFrequency(text, frequency);

    struct List * const list = newList(kNumberOfNodes);
    struct Node * head = list->head;
    for (size_t i = 0; i < kNumberOfNodes; ++i) {
        struct Symbol * const symbol = newSymbol(frequency[i]);
        symbol->character = (char) i;
        symbol->code = '0';

        struct Vertex * const vertex = newVertex((void *) symbol);

        head->content = (void *) vertex;
        head = head->next;
    }

    while (list->numOfElements > 1) {
        struct Node * const nodeX = findSmallestFrequency(list);
        struct Vertex * const vertexX = (struct Vertex *) nodeX->content;
        struct Symbol * const symbolX = (struct Symbol *) vertexX->content;
        symbolX->code = '0';
        removeNode(list, nodeX);

        struct Node * const nodeY = findSmallestFrequency(list);
        struct Vertex * const vertexY = (struct Vertex *) nodeY->content;
        struct Symbol * const symbolY = (struct Symbol *) vertexY->content;
        symbolY->code = '1';
        removeNode(list, nodeY);

        struct Symbol * const mergeSymbol = newSymbol(symbolX->frequency + symbolY->frequency);
        struct Vertex * const mergeVertex = newVertex((void *) mergeSymbol);
        addNeighbour(mergeVertex, vertexX);
        addNeighbour(mergeVertex, vertexY);

        addNode(list, newNode((void *) mergeVertex));
    }

    struct Vertex * root = (struct Vertex *) list->head->content;
    constructCodes(root, "", codes);

    FILE * mapFile = fopen(argv[1], "w");
    if (mapFile == NULL) {
        perror(argv[1]);
        exit(-1);
    }

    for (size_t i = 0; i < kNumberOfNodes; ++i) {
        fprintf(mapFile, "%d %s\n", frequency[i], codes[i]);
    }

    fclose(mapFile);

    size_t N = strlen(text);
    for (size_t i = 0; i < N; ++i) {
        printf("%s", codes[text[i]]);
    }

    return 0;
}