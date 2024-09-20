#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->elements = (void**)malloc(sizeof(void*) * capacity);  // generic void* elements
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack* stack, void* element) {
    if (stack->top < stack->capacity - 1) {
        stack->elements[++stack->top] = element;
    }
}

void* pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->elements[stack->top--];
    }
    return NULL;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void freeStack(Stack* stack) {
    free(stack->elements);
    free(stack);
}

// generic print function that takes a print function pointer to handle different types
void printStack(Stack* stack, void (*printElement)(void*)) {
    printf("Stack: ");
    for (int i = stack->top; i >= 0; i--) {
        printElement(stack->elements[i]);  // use the provided print function to print each element
    }
    printf("\n");
}

void printNodeElement(void* element) {
    Node* node = (Node*)element;  // cast back to Node*
    printf("%c ", node->name);
}

void printEdgeElement(void* element) {
    Edge* edge = (Edge*)element;
    printf("(%c <-> %c) ", edge->u->name, edge->v->name);
}