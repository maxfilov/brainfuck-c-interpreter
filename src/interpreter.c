#include "interpreter.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int init_interpreter(Interpreter_t* interpreter, size_t size) {
    char* data = calloc(size, sizeof(char));
    if (data == NULL) {
        return EXIT_FAILURE;
    }
    interpreter->data = data;
    interpreter->ptr = data;
    interpreter->size = size;
    return EXIT_SUCCESS;
}

void deinit_interpreter(Interpreter_t* t) {
    free(t->data);
}

const char* find_closing(const char* begin, const char* end);

InterpretationResult_t interpret(Interpreter_t* interpreter, const char* buf, size_t size) {
    const char* end = buf + size;
    Stack bracket_stack;
    init_stack(&bracket_stack);
    for (const char* cur = buf; cur != end; ) {
        char c = *cur;
        switch (c) {
            case '+':
                ++*(interpreter->ptr);
                ++cur;
                break;
            case '-':
                --*(interpreter->ptr);
                ++cur;
                break;
            case '>':
                ++interpreter->ptr;
                ++cur;
                break;
            case '<':
                --interpreter->ptr;
                ++cur;
                break;
            case '.':
                putchar(*interpreter->ptr);
                ++cur;
                break;
            case '[': {
                const char* closing = find_closing(cur + 1, end);
                if (closing == NULL) {
                    return INTERPRETATION_UNMATCHED_BRACKET;
                }
                if (*interpreter->ptr == 0) {
                    cur = closing + 1;
                    break;
                }
                push(&bracket_stack, cur++);
                break;
            }
            case ']':
                if (is_empty(&bracket_stack)) {
                    return INTERPRETATION_UNMATCHED_BRACKET;
                }
                pop(&bracket_stack, &cur);
                break;
            default:
                ++cur;
                break;
        }
    }
    return INTERPRETATION_OK;
}

const char* find_closing(const char* begin, const char* end) {
    int accum = 1;
    for (const char* cur = begin; cur != end; ++cur) {
        switch (*cur) {
            case '[':
                ++accum;
                break;
            case ']':
                --accum;
                break;
            default:
                break;
        }
        if (accum == 0) {
            return cur;
        }
    }
    return NULL;
}
