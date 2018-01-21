#include "trie.h"
#include "types.h"
#include "reader.h"

#include <stdio.h>
#include <string.h>

const ushort kNumberOfNodes = 128;

char ** split(char * line) {
    size_t linesCapacity = 16;
    size_t linesSize = 0;
    char ** lines = (char **) calloc(linesCapacity, sizeof(char *));
    while (1) {
        line = strchr(line, ' ');
        if (line == NULL) {
            break;
        }

        line++;

        char * nextLine = strchr(line, '\n');
        *nextLine = '\0';
        nextLine++;

        if (linesSize >= linesCapacity) {
            linesCapacity *= 2;
            lines = (char **) realloc(lines, linesCapacity * sizeof(char *));
        }

        lines[linesSize++] = line;

        line = nextLine;
    }

    return lines;
}

int main(int args, char ** argv) {
    char **codes = split(readFile(argv[1]));

    struct Trie * const trie = newTrie();
    for (ushort i = 0; i < kNumberOfNodes; ++i) {
        char *c = (char *) malloc(sizeof(char));
        *c = (char) i;
        updateTrie(trie, codes[i], c);
    }

    char * text = read();

    size_t N = strlen(text);
    for (size_t l = 0, len = 1; l < N;) {
        char const * c = (char *) queryTrie(trie, text + l, len);
        if (c == NULL) {
            len++;
        } else {
            printf("%c", *c);
            l += len;
            len = 1;
        }
    }

    return 0;
}