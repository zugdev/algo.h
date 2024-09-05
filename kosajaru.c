#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/stack.h"

void kosaraju(Graph* graph) {
  int time = 0;
  Stack* stack = dfs(graph, time);            // first DFS to fill the stack
  Graph* inverted_graph = invertArcs(graph);  // invert the graph edges

  // reset node colors for the second DFS
  for (int i = 0; i < inverted_graph->size; i++) {
    inverted_graph->nodes[i]->color = WHITE;
  }

  printf("Strongly connected components:\n");

  int component_number = 1;
  // second DFS based on the finishing times from the first DFS
  while (!isStackEmpty(stack)) {
    Node* node = pop(stack);
    Node* inverted_node =
        inverted_graph->nodes[node->id];  // access the corresponding node in
                                          // the inverted graph by index
    if (inverted_node->color == WHITE) {
      printf("Component %d: ", component_number++);
      dfs_visit(inverted_node, NULL, &time);  // DFS on the inverted graph
      printf("\n");
    }
  }

  freeStack(stack);
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
  addArc(b, d);
  addArc(d, b);
  addArc(e, f);

  Graph* graph = createGraph(nodes, 6);

  kosaraju(graph);

  freeGraph(graph);
  return 0;
}
