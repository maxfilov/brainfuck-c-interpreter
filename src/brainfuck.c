#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#include <error.h>

#include "interpreter.h"
#include "io.h"

int main() {
    size_t size;
    int result;
    char* source = read_all(&size, stdin);
    if (source == NULL) {
        fprintf(stderr, "Failed to initialize interpreter\n");
        result = EXIT_FAILURE;
        goto main_failed;
    }
    
    Interpreter_t interpreter;
    if (init_interpreter(&interpreter, 30000) != EXIT_SUCCESS) {
        fprintf(stderr, "Failed to initialize interpreter\n");
        result = EXIT_FAILURE;
        goto main_source;
    }
    result = interpret(&interpreter, source, size);
    deinit_interpreter(&interpreter);
main_source:
    free(source);
main_failed:
    return result;
}

