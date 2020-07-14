#include "io.h"
#include <stdlib.h>
#include <assert.h>

char* read_all(size_t* size, FILE* file) {
    size_t elements_read;
    size_t capacity = 1024;
    size_t total_read = 0;
    assert(capacity != 0);
    char* buf = (char*) calloc(capacity, sizeof(char));
    if (buf == NULL) {
        goto read_all_failed;
    }
    for (elements_read = fread(buf, sizeof(char), capacity, file);
         elements_read == capacity - total_read;
         elements_read = fread(buf + total_read, sizeof(char), capacity - total_read, file)) {
        total_read += elements_read;
        capacity *= 2;
        buf = reallocarray(buf, capacity, sizeof(char));
        if (buf == NULL) {
            goto read_all_buf;
        }
    }
    total_read += elements_read;
    if (ferror(file)) {
        goto read_all_buf;
    }
    *size = total_read;
    return buf;
read_all_buf:
    free(buf);
read_all_failed:
    return NULL;
}
