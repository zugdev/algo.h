#include <stdio.h>
#include <stdlib.h>
#include "../headers/graph.h"

// #define PRINT_GRAPHS

int main(int argc, char* argv[]) {
  Node* a = createNode('a');
  Node* b = createNode('b');
  Node* c = createNode('c');
  Node* d = createNode('d');
  Node* e = createNode('e');

  Node* nodes[] = {a, b, c, d, e};

  addArc(a, b);
  addArc(a, c);
  addArc(c, d);
  addArc(d, e);

  Graph* graph = createGraph(nodes, 5);
  Graph* invertedGraph = invertArcs(graph);

#ifdef PRINT_GRAPHS
  printGraph(graph);
  printGraph(invertedGraph);
#endif

  if (invertedGraph->nodes[0]->neighbors != NULL) {
    fprintf(stderr, "Error: Test case 1 failed\n");
    return 1;
  }
  if (invertedGraph->nodes[1]->neighbors[0]->name != a->name) {
    fprintf(stderr, "Error: Test case 2 failed\n");
    return 2;
  }
  if (invertedGraph->nodes[2]->neighbors[0]->name != a->name) {
    fprintf(stderr, "Error: Test case 3 failed\n");
    return 3;
  }
  if (invertedGraph->nodes[3]->neighbors[0]->name != c->name) {
    fprintf(stderr, "Error: Test case 4 failed\n");
    return 4;
  }
  if (invertedGraph->nodes[4]->neighbors[0]->name != d->name) {
    fprintf(stderr, "Error: Test case 5 failed\n");
    return 5;
  }

  fprintf(stdout, "All invertArcs tests passed :)\n");

  freeGraph(graph);
  freeGraph(invertedGraph);
  return 0;
}