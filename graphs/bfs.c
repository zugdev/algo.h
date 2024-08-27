#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"

void bfs(Graph* graph, Node* startNode) {
  Queue* queue = createQueue(graph->size);
  startNode->color = GRAY;
  startNode->distance = 0;
  enqueue(queue, startNode);

  while (!isQueueEmpty(queue)) {
    Node* currentNode = dequeue(queue);

    for (int i = 0; i < currentNode->out_degree; i++) {
      Node* neighbor = currentNode->neighbors[i];
      if (neighbor->color == WHITE) {
        neighbor->color = GRAY;
        neighbor->parent = currentNode;
        neighbor->distance = currentNode->distance + 1;
        enqueue(queue, neighbor);
      }
    }

    currentNode->color = BLACK;
  }

  freeQueue(queue);
}

int main(int argc, char* argv[]) {
  Node* a = createNode('a');
  Node* b = createNode('b');
  Node* c = createNode('c');
  Node* d = createNode('d');
  Node* e = createNode('e');
  Node* f = createNode('f');

  Node* nodes[] = {a, b, c, d, e, f};

  addArc(a, b);
  addArc(a, c);
  addArc(d, e);
  addArc(e, f);
  addArc(f, d);
  addArc(e, b);

  Graph* graph = createGraph(nodes, 6);

  bfs(graph, a);
  printGraph(graph);
  freeGraph(graph);
}
