#pragma once

typedef struct Node_s {
    const char *value;
    struct Node_s* prev;
} Node;

Node* make_node(const char* value);
void init_node(Node* node, const char* value);

typedef struct Stack_s {
    Node *top;
} Stack;

void init_stack(Stack* stack);
int is_empty(Stack* stack);
void push(Stack* stack, const char* value);
void pop(Stack* stack, const char** value);
