#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/graph.h"
#include "headers/stack.h"
#include "headers/colors.h"

void dfs_visit_bcc(Node* node, Stack* stack, int* time, int* component_count);

void dfs_bcc(Graph* graph) {
  int time = 0;
  int component_count = 0;
  Stack* stack = createStack(graph->size * graph->size);  // stack for edges
  for (int i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->color == WHITE) {
      dfs_visit_bcc(graph->nodes[i], stack, &time, &component_count);
    }
  }
  freeStack(stack);
}

// DFS with BCC detection
void dfs_visit_bcc(Node* node, Stack* stack, int* time, int* component_count) {
  (*time)++;
  node->t_entering = node->low = *time;
  node->color = GRAY;
  int children = 0;

  for (int i = 0; i < node->out_degree; i++) {
    Node* neighbor = node->neighbors[i];

    if (neighbor->color == WHITE) {
      neighbor->parent = node;
      push(stack, node);  // store edge (node, neighbor)
      dfs_visit_bcc(neighbor, stack, time, component_count);
      node->low = (node->low < neighbor->low) ? node->low : neighbor->low;

      // articulation point condition
      if (neighbor->low >= node->t_entering && node->parent != NULL) {
        printf("articulation point: %c\n", node->name);
        (*component_count)++;
        // bcc component: pop the stack until you get to this edge
        while (stack->top != -1) {
          Node* edge_node = pop(stack);
          if (edge_node == node) break;
        }
        printf("\n");
      }

      children++;
    } else if (neighbor != node->parent && neighbor->t_entering < node->low) {
      // back edge
      node->low = (node->low < neighbor->t_entering) ? node->low : neighbor->t_entering;
      push(stack, node);  // store edge (node, neighbor)
    }
  }

  node->color = BLACK;

  // special case: root node
  if (node->parent == NULL && children > 1) {
    printf("root articulation point: %c\n", node->name);
    (*component_count)++;
    while (stack->top != -1) {
      Node* edge_node = pop(stack);
      printf("%c ", edge_node->name);
      if (edge_node == node) break;
    }
    printf("\n");
  }
}

int bcc_example() {
  printf_cyan("find biconnected components example\n");
  Node* a = createNode('a');
  Node* b = createNode('b');
  Node* c = createNode('c');
  Node* d = createNode('d');
  Node* e = createNode('e');
  Node* f = createNode('f');

  Node* nodes[] = {a, b, c, d, e, f};

  addEdge(a, b);
  addEdge(a, c);
  addEdge(b, d);
  addEdge(c, d);
  addEdge(c, e);
  addEdge(e, f);

  Graph* graph = createGraph(nodes, 6);

  dfs_bcc(graph);

  freeGraph(graph);

  return 0;
}
