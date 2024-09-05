
#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/stack.h"

/*
 * Depth-First Search (DFS) Algorithm:
 *
 * 1. All nodes start WHITE (unvisited). DFS will be called from every WHITE
 *    node to ensure all nodes, even disconnected ones, are discovered.
 *
 * 2. The algorithm proceeds by visiting each node in the graph. When we first
 *    encounter a node, we mark it as GRAY to indicate that it is being
 *    explored.
 *
 * 3. From the current node, we recursively explore all possible paths by
 *    visiting each of its unvisited (WHITE) neighbors.
 *
 * 4. After all the descendants of a node have been fully explored, we mark the
 *    node as fully processed, which we denote as BLACK. At this point, the
 *    node's finishing time is recorded, and it is pushed onto the stack,
 *    indicating that it is finished.
 *
 * 5. The stack will eventually contain all nodes in the order of their
 *    finishing times, with the most recently finished node on top.
 */

void dfs_visit(Node* node, Stack* stack, int* time);  // c interface

Stack* dfs(Graph* graph, int time) {
  time = 0;
  Stack* stack = createStack(graph->size);
  for (int i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->color == WHITE) {
      dfs_visit(graph->nodes[i], stack, &time);
    }
  }
  return stack;
}

void dfs_visit(Node* node, Stack* stack, int* time) {
  (*time)++;
  node->t_entering = *time;
  node->color = GRAY;
  for (int i = 0; i < node->out_degree; i++) {
    Node* son = node->neighbors[i];
    if (son->color == WHITE) {
      son->parent = node;
      dfs_visit(son, stack, time);
    }
  }
  node->color = BLACK;
  (*time)++;
  node->t_leaving = *time;
  if (stack == NULL) {
    printf("%c ", node->name);
  }
  if (stack != NULL) {
    push(stack, node);
  }
}

int dfs_example() {
  printf_cyan("dfs example\n");
  Node* a = createNode('a');
  Node* b = createNode('b');
  Node* c = createNode('c');
  Node* d = createNode('d');
  Node* e = createNode('e');
  Node* f = createNode('f');

  Node* nodes[] = {a, b, c, d, e, f};

  addArc(a, b);
  addArc(a, c);
  addArc(b, d);
  addArc(d, b);
  addArc(e, f);

  Graph* graph = createGraph(nodes, 6);

  Stack* stack = dfs(graph, 0);

  printGraph(graph);
  printStack(stack);

  freeGraph(graph);
  freeStack(stack);
  return 0;
}