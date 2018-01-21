#include "graph.h"

struct Vertex * newVertex(void * const content) {
    struct Vertex * const vertex = (struct Vertex *) calloc(1, sizeof(struct Vertex));

    vertex->content = content;
    vertex->neighboursCapacity = 16;
    vertex->numOfNeighbours = 0;

    vertex->neighbours = (struct Vertex **) calloc(vertex->neighboursCapacity, sizeof(struct Vertex *));
}

void deleteVertex(struct Vertex * const vertex) {
    free(vertex->neighbours);
    free(vertex);
}

void addNeighbour(struct Vertex * const vertex, struct Vertex * const neighbour) {
    if (vertex->numOfNeighbours >= vertex->neighboursCapacity) {
        vertex->neighboursCapacity *= 2;
        vertex->neighbours = (struct Vertex **) realloc(vertex->neighbours, vertex->neighboursCapacity * sizeof(struct Vertex *));
    }

    vertex->neighbours[vertex->numOfNeighbours++] = neighbour;
}

void removeNeighbour(struct Vertex * const vertex, struct Vertex * const neighbour) {
    int neighbourIndex = 0;
    for (; neighbourIndex < vertex->numOfNeighbours; ++neighbourIndex) {
        if (vertex->neighbours[neighbourIndex] == neighbour) {
            break;
        }
    }

    for (; neighbourIndex < vertex->numOfNeighbours - 1; ++neighbourIndex) {
        vertex->neighbours[neighbourIndex] = vertex->neighbours[neighbourIndex + 1];
    }
    vertex->neighbours[vertex->numOfNeighbours - 1] = NULL;

    vertex->numOfNeighbours--;
}
