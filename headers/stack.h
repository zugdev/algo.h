#ifndef STACK_H
#define STACK_H

#include "graph.h"

typedef struct Stack {
  Node** elements;
  int top;
  int capacity;
} Stack;

Stack* createStack(int capacity);
void push(Stack* stack, Node* element);
Node* pop(Stack* stack);
int isStackEmpty(Stack* stack);
void freeStack(Stack* stack);
void printStack(Stack* stack);

#endif  // STACK_H