
#include <stdio.h>
#include <stdlib.h>
#include "headers/graph.h"
#include "headers/stack.h"

int time;

void dfs_visit(Node* node, Stack* stack);  // c interface

Stack* dfs(Graph* graph) {
  time = 0;
  Stack* stack = createStack(graph->size);
  for (int i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->color == WHITE) {
      dfs_visit(graph->nodes[i], stack);
    }
  }
  return stack;
}

void dfs_visit(Node* node, Stack* stack) {
  time++;
  node->t_entering = time;
  node->color = GRAY;
  for (int i = 0; i < node->out_degree; i++) {
    Node* son = node->neighbors[i];
    if (son->color == WHITE) {
      son->parent = node;
      dfs_visit(son, stack);
    }
  }
  node->color = BLACK;
  time++;
  node->t_leaving = time;
  push(stack, node);
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

  Stack* stack = dfs(graph);

  printGraph(graph);
  printStack(stack);

  freeGraph(graph);
}