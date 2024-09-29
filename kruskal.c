#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/mst.h"
#include "headers/stack.h"

/*
 * Kruskal's Algorithm:
 *
 * 1. Sort all edges by their weight.
 * 2. Initialize each node as its own component.
 * 3. Process each edge in sorted order, adding the edge to the Minimum Spanning
 * Tree (MST) if it connects two nodes that are in different components.
 * 4. The MST is complete when it contains exactly (V - 1) edges, where V is the
 * number of vertices.
 */

Stack* kruskal(Graph* graph, Edge** edges, int num_edges) {
  Stack* mstStack = createStack(graph->size - 1);  // so store the MST edges

  // sort the edges by weight
  sortWeightedEdges(edges, num_edges);

  // create subsets for union-find
  Subset* subsets = malloc(graph->size * sizeof(Subset));
  for (int i = 0; i < graph->size; i++) {
    subsets[i].parent = graph->nodes[i];
    subsets[i].rank = 0;
  }

  // process sorted edges and build the MST
  for (int i = 0, e = 0; e < graph->size - 1 && i < num_edges; i++) {
    Edge* edge = edges[i];

    Node* uSet = find(subsets, edge->u);
    Node* vSet = find(subsets, edge->v);

    if (uSet != vSet) {
      // this edge can be added to the MST
      push(mstStack, edge);
      unionSet(subsets, uSet, vSet);
      e++;  // increment the count of edges in MST
    }
  }

  free(subsets);

  return mstStack;
}

int kruskal_example() {
  printf_cyan("kruskal example\n\n");
  Node* a = createNode('a');
  Node* b = createNode('b');
  Node* c = createNode('c');
  Node* d = createNode('d');
  Node* e = createNode('e');
  Node* f = createNode('f');

  Node* nodes[] = {a, b, c, d, e, f};

  Edge* e1 = createWeightedEdge(a, b, 4);
  Edge* e2 = createWeightedEdge(a, c, 4);
  Edge* e3 = createWeightedEdge(b, d, 2);
  Edge* e4 = createWeightedEdge(c, d, 3);
  Edge* e5 = createWeightedEdge(d, e, 6);
  Edge* e6 = createWeightedEdge(e, f, 5);

  Edge* edges[] = {e1, e2, e3, e4, e5, e6};
  int num_edges = sizeof(edges) / sizeof(edges[0]);

  Graph* graph = createGraph(nodes, 6);

  Stack* mstStack = kruskal(graph, edges, num_edges);

  printf_magenta("edges in the MST:\n");
  printStack(mstStack, printEdgeElement);

  freeGraph(graph);
  freeStack(mstStack);

  return 0;
}
