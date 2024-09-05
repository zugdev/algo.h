#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/queue.h"

/*
 * Breadth-First Search (BFS) Algorithm:
 *
 * 1. It searchs by level, starting from a node it will visit all of it's sons
 *    before visiting every grandson.
 *
 * 2. All nodes start as WHITE (unvisited). BFS begins from the start node,
 *    which is marked GRAY (discovered) and enqueued for exploration. The
 *    distance from the start node to itself is set to 0.
 *
 * 3. The algorithm proceeds by dequeuing a node, marking it BLACK (fully
 *    processed) after all its neighbors are explored. For each unvisited
 *    (WHITE) neighbor, the neighbor is marked GRAY, its distance from the start
 *    node is set, and it is enqueued.
 *
 * 4. This process continues until the queue is empty, indicating that all
 *    reachable nodes have been explored. The nodes are visited level by level,
 *    making BFS particularly useful for finding the shortest path in unweighted
 *    graphs.
 */

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

int bfs_example() {
  printf_cyan("bfs example\n");
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
  printFound(graph);

  freeGraph(graph);
  return 0;
}
