#include "trie.h"
#include "reader.h"

#include <stdio.h>
#include <string.h>

const size_t kInitialDictSize = 128;
const size_t kMaxDictSize = 65536;

int main(int args, char ** argv) {
    struct Trie * const trie = newTrie();
    char *codes[kMaxDictSize];
    memset(codes, 0, sizeof(codes));

    for (size_t i = 0; i < kInitialDictSize; ++i) {
        char * const c = (char *) malloc(sizeof(char));
        int * const v = (int *) malloc(sizeof(int));
        *c = (char) i;
        *v = (int) i;
        updateTrie(trie, c, (void *) v);
        codes[i] = c;
    }

    int codeCounter = kInitialDictSize;

    struct Buffer * buffer = newBuffer();

    int index;
    while (scanf("%d", &index) == 1) {
        char * code = codes[index];
        if (code == NULL) {
            int bufferIndex = 0;
            while (codes[index] == NULL) {
                if (bufferIndex >= buffer->size) {
                    fprintf(stderr, "Cannot decode %d", index);
                    exit(-1);
                }
                appendToBuffer(buffer, buffer->content[bufferIndex++]);

                int * const v = (int *) malloc(sizeof(int));
                *v = codeCounter;
                updateTrie(trie, buffer->content, (void *) v);
                codes[codeCounter] = (char *) calloc(buffer->size + 1, sizeof(char));
                strcpy(codes[codeCounter], buffer->content);
                codeCounter++;
            }

            printf("%s", codes[index]);
            clearBuffer(buffer);
        } else {
            printf("%s", code);
            size_t N = strlen(code);
            for (int i = 0; i < N; ++i) {
                appendToBuffer(buffer, code[i]);
                if (queryTrie(trie, buffer->content, buffer->size) == NULL) {
                    int * const v = (int *) malloc(sizeof(int));
                    *v = codeCounter;
                    updateTrie(trie, buffer->content, (void *) v);
                    codes[codeCounter] = (char *) calloc(buffer->size + 1, sizeof(char));
                    strcpy(codes[codeCounter], buffer->content);
                    codeCounter++;

                    clearBuffer(buffer);
                    appendToBuffer(buffer, code[i]);
                }
            }
        }
    }

    return 0;
}
