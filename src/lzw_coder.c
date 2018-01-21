#include "trie.h"
#include "reader.h"

#include <stdio.h>

const size_t kInitialDictSize = 128;

int main(int args, char ** argv) {
    struct Trie * const trie = newTrie();

    for (size_t i = 0; i < kInitialDictSize; ++i) {
        char * const c = (char *) malloc(sizeof(char));
        int * const v = (int *) malloc(sizeof(int));
        *c = (char) i;
        *v = (int) i;
        updateTrie(trie, c, (void *) v);
    }

    int codeCounter = kInitialDictSize;

    char character;
    scanf("%c", &character);

    struct Buffer * buffer = newBuffer();
    appendToBuffer(buffer, character);

    while (scanf("%c", &character) == 1) {
        appendToBuffer(buffer, character);
        if (queryTrie(trie, buffer->content, buffer->size) == NULL) {
            int * v = (int *) malloc(sizeof(int));
            *v = codeCounter++;
            updateTrie(trie, buffer->content, (void *) v);

            removeLastFromBuffer(buffer);
            printf("%d ", * (int *) queryTrie(trie, buffer->content, buffer->size));

            clearBuffer(buffer);
            appendToBuffer(buffer, character);
        }
    }

    return 0;
}