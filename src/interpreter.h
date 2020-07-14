#pragma once
#include <stdlib.h>

typedef struct Interpreter {
    char* data;
    char* ptr;
    size_t size;


} Interpreter_t;

typedef enum InterpretationResult {
    INTERPRETATION_OK,
    INTERPRETATION_UNMATCHED_BRACKET
} InterpretationResult_t;

int init_interpreter(Interpreter_t* interpreter, size_t size);
void deinit_interpreter(Interpreter_t* t);

InterpretationResult_t interpret(Interpreter_t* interpreter, const char* buf, size_t size);

