#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Buffer * newBuffer() {
    struct Buffer * const buffer = (struct Buffer *) calloc(1, sizeof(struct Buffer));
    buffer->capacity = 16;
    buffer->size = 0;
    buffer->content = (char *) calloc(buffer->capacity, sizeof(char));
    return buffer;
}

void appendToBuffer(struct Buffer * const buffer, char const character) {
    if (buffer->size >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->content = (char *) realloc(buffer->content, buffer->capacity * sizeof(char));
    }
    buffer->content[buffer->size++] = character;
}

void removeLastFromBuffer(struct Buffer * const buffer) {
    if (buffer->size > 0) {
        buffer->content[buffer->size - 1] = '\0';
        buffer->size--;
    }
}

void clearBuffer(struct Buffer * const buffer) {
    memset(buffer->content, 0, sizeof(buffer->content));
    buffer->size = 0;
}

char * readFile(char * const fileName) {
    FILE * file = fopen(fileName, "rb");
    if (file == NULL) {
        perror(fileName);
        exit(-1);
    }

    struct Buffer * const buffer = newBuffer();

    while (1) {
        char c;
        fread(&c, sizeof(c), 1, file);
        if (feof(file)) {
            break;
        }
        appendToBuffer(buffer, c);
    }

    fclose(file);

    return buffer->content;
}

char * read() {
    struct Buffer * const buffer = newBuffer();

    int c;
    while ((c = fgetc(stdin)) != EOF) {
        appendToBuffer(buffer, c);
    }

    return buffer->content;
}

