#ifndef QUEUE_H
#define QUEUE_H

#include "graph.h"

typedef struct Queue {
  Node** elements;
  int front;
  int rear;
  int capacity;
  int size;
} Queue;

Queue* createQueue(int capacity);
void enqueue(Queue* queue, Node* element);
Node* dequeue(Queue* queue);
int isQueueEmpty(Queue* queue);
void freeQueue(Queue* queue);

#endif  // QUEUE_H
