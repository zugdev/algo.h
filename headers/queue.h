#ifndef QUEUE_H
#define QUEUE_H

#include "graph.h"

typedef struct Queue {
  void** elements;
  int front;
  int rear;
  int capacity;
  int size;
} Queue;

Queue* createQueue(int capacity);
void enqueue(Queue* queue, void* element);
void* dequeue(Queue* queue);
int isQueueEmpty(Queue* queue);
void freeQueue(Queue* queue);
void printNodeQueue(Queue* queue);
void printEdgeQueue(Queue* queue);

#endif  // QUEUE_H
