#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue* createQueue(int capacity) {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  if (!queue) {
    fprintf(stderr, "Memory allocation failed for Queue\n");
    exit(1);
  }
  queue->elements = (Node**)malloc(capacity * sizeof(Node*));
  if (!queue->elements) {
    fprintf(stderr, "Memory allocation failed for Queue elements\n");
    exit(1);
  }
  queue->front = 0;
  queue->rear = 0;
  queue->capacity = capacity;
  queue->size = 0;
  return queue;
}

void enqueue(Queue* queue, Node* element) {
  if (queue->size == queue->capacity) {
    fprintf(stderr, "Queue is full\n");
    exit(1);
  }
  queue->elements[queue->rear] = element;
  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->size++;
}

Node* dequeue(Queue* queue) {
  if (queue->size == 0) {
    fprintf(stderr, "Queue is empty\n");
    exit(1);
  }
  Node* element = queue->elements[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;
  return element;
}

int isQueueEmpty(Queue* queue) {
  return queue->size == 0;
}

void freeQueue(Queue* queue) {
  free(queue->elements);
  free(queue);
}

void printQueue(Queue* queue) {
  printf("Queue: ");
  for (int i = 0; i < queue->size; i++) {
    printf("%c ", queue->elements[i]->name);
  }
  printf("\n");
}