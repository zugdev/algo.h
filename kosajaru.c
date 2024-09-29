#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/stack.h"

/*
 * Kosaraju's Algorithm for finding Strongly Connected Components (SCCs) in a
 * directed graph:
 *
 * 1. Perform a DFS on the original graph to compute the finishing times of the
 * nodes. The nodes are pushed onto a stack in the order of their finishing
 * times.
 *
 * 2. Invert the graph (reverse all the edges).
 *
 * 3. Perform a second DFS on the inverted graph, processing the nodes in the
 * order defined by the stack (which represents the nodes in the order of
 * decreasing finishing times).
 *
 * 4. Each DFS run in the inverted graph will discover a strongly connected
 * component. The nodes discovered in each DFS run form one SCC, and all SCCs
 * are printed.
 *
 * The algorithm efficiently finds all SCCs in O(V + E) time, where V is the
 * number of vertices and E is the number of edges in the graph.
 */

void kosaraju(Graph* graph) {
  int time = 0;
  Stack* stack = dfs(graph, time);            // first DFS to fill the stack
  printStack(stack);
  Graph* inverted_graph = invertArcs(graph);  // invert the graph edges

  // reset node colors for the second DFS
  for (int i = 0; i < inverted_graph->size; i++) {
    inverted_graph->nodes[i]->color = WHITE;
  }

  printf_green("\nStrongly Connected Components:\n");

  int component_number = 1;
  // second DFS based on the finishing times from the first DFS
  while (!isStackEmpty(stack)) {
    Node* node = (Node*)pop(stack);
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
  printf_cyan("kosajaru example\n\n");
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
