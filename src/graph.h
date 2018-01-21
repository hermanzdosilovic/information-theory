#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

struct Vertex {
    struct Vertex ** neighbours;
    void * content;

    size_t neighboursCapacity;
    size_t numOfNeighbours;
};

struct Vertex * newVertex(void * const content);

void deleteVertex(struct Vertex * const vertex);

void addNeighbour(struct Vertex * const vertex, struct Vertex * const neighbour);

void removeNeighbour(struct Vertex * const vertex, struct Vertex * const neighbour);

#endif // GRAPH_H
