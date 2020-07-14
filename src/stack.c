#include "stack.h"


#include <stdlib.h>
#include <assert.h>

Node* make_node(const char* value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    init_node(node, value);
    return node;
}

void init_node(Node* node, const char* value) {
    node->value = value;
}

void init_stack(Stack* stack) {
    stack->top = NULL;
}

int is_empty(Stack* stack) {
    if (stack == NULL) {
        return 1;
    }
    return stack->top == NULL;
}

void push(Stack* stack, const char* value) {
    if (stack == NULL) {
        return;
    }
    Node* new_node = make_node(value);
    if (new_node == NULL) {
        return;
    }
    new_node->prev = stack->top;
    stack->top = new_node;
}

void pop(Stack* stack, const char** value) {
    assert(!is_empty(stack));
    Node* top = stack->top;
    *value = top->value;
    stack->top = top->prev;
    free(top);
}
