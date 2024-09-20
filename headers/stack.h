#ifndef STACK_H
#define STACK_H

#include "graph.h"

typedef struct Stack {
    void** elements;  // stack of generic void* elements
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity);
void push(Stack* stack, void* element);
void* pop(Stack* stack);
int isStackEmpty(Stack* stack);
void freeStack(Stack* stack);
void printStack(Stack* stack, void (*printElement)(void*));  // print function accepts a function pointer to handle different types
void printNodeElement(void* element);
void printEdgeElement(void* element);

#endif // STACK_H
