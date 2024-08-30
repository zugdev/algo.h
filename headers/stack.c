#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack(int capacity) {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->elements = (Node**)malloc(sizeof(Node*) * capacity);
  stack->top = -1;
  stack->capacity = capacity;
  return stack;
}

void push(Stack* stack, Node* element) {
  if (stack->top < stack->capacity - 1) {
    stack->elements[++stack->top] = element;
  }
}

Node* pop(Stack* stack) {
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

void printStack(Stack* stack) {
  printf("Stack: ");
  for (int i = stack->top; i >= 0; i--) {
    printf("%c ", stack->elements[i]->name);
  }
  printf("\n");
}