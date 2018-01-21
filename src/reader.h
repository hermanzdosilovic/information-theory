#ifndef READER_H
#define READER_H

#include <stdlib.h>

struct Buffer {
    char * content;
    size_t capacity;
    size_t size;
};

struct Buffer * newBuffer();

void appendToBuffer(struct Buffer * const buffer, char const character);

void removeLastFromBuffer(struct Buffer * const buffer);

void clearBuffer(struct Buffer * const buffer);

char * readFile(char *const fileName);

char * read();

#endif // READER_H
