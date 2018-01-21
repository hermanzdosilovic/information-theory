#include "trie.h"

#include <string.h>

const int kDegree = 128;

struct Vertex * newTrieVertex() {
    struct Vertex *const vertex = newVertex(NULL);

    free(vertex->neighbours);

    vertex->neighboursCapacity = kDegree;
    vertex->neighbours = (struct Vertex **) calloc(vertex->neighboursCapacity, sizeof(struct Vertex *));

    return vertex;
}

struct Trie * const newTrie() {
    struct Trie * const trie = (struct Trie *) calloc(1, sizeof(struct Trie));
    trie->root = newTrieVertex();
}

void updateTrie(struct Trie * const trie, char const * const string, void * const content) {
    struct Vertex * root = trie->root;
    size_t const N = strlen(string);
    for (size_t i = 0; i < N; ++i) {
        if (root->neighbours[string[i]] == NULL) {
            root->neighbours[string[i]] = newTrieVertex();
        }
        root = root->neighbours[string[i]];
    }
    root->content = content;
}

void const * const queryTrie(struct Trie const * const trie, char const * const string, size_t const N) {
    struct Vertex * root = trie->root;
    for (size_t i = 0; i < N; ++i) {
        if (root->neighbours[string[i]] == NULL) {
            return NULL;
        }
        root = root->neighbours[string[i]];
    }
    return root->content;
}
