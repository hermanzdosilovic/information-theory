#ifndef TRIE_H
#define TRIE_H

#include "graph.h"

struct Trie {
    struct Vertex * root;
};

struct Trie * const newTrie();

void updateTrie(struct Trie * const trie, char const * const string, void * const content);

void const * const queryTrie(struct Trie const * const trie, char const * const string, size_t const N);

#endif // TRIE_H
