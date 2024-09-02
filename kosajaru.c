#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/stack.h"

void kosaraju(Graph* graph) {
  int time = 0;
  Stack* stack = dfs(graph, time);
  Graph* inverted_graph = invertArcs(graph);

  for (int i = 0; i < graph->size; i++) {
    graph->nodes[i]->color = WHITE;
  }

  printf("strongly connected components:\n");

  int i = 1;
  while (!isStackEmpty(stack)) {
    Node* node = pop(stack);
    if (node->color == WHITE) {
      printf("component %d: ", i++);
      dfs_visit(node, NULL, time);
      printf("\n");
    }
  }

  freeStack(stack);
  freeGraph(inverted_graph);
}

int kosajaru_example() {
  printf_cyan("kosajaru example\n");
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

  kosaraju(graph);

  freeGraph(graph);
  return 0;
}
