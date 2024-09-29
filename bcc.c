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
  node->t_entering = node->ret = *time;
  node->color = GRAY;

  for (int i = 0; i < node->out_degree; i++) {
    Node* neighbor = node->neighbors[i];
    Edge* edge = createEdge(node, neighbor);

    if (neighbor->color == WHITE) {
      neighbor->parent = node;
      push(stack, edge);  // queue edge (node, neighbor)
      dfs_visit_bcc(neighbor, stack, time, component_count);

      if (neighbor->ret >= node->t_entering) {
        (*component_count)++;
        magenta();
        printf("Component %d --\n", *component_count);
        reset_color();
        printf("articulation point: %c\n", node->name);
        printf("edges: ");
        // bcc component: pop the stack until you get to this edge
        while (stack->top != -1) {
          Edge* popped_edge = pop(stack);
          popped_edge->u->component_number = *component_count;
          popped_edge->v->component_number = *component_count;
          printf("(%c,%c) ", popped_edge->u->name, popped_edge->v->name);
          if (popped_edge->u == node && popped_edge->v == neighbor) {
            printf_magenta("\n---------------\n");
            break;
          }
        }
      } else {
        if (node->ret > neighbor->ret) {
          node->ret = neighbor->ret;
        }
      }
    } else {
      if (neighbor != node->parent) {
        if (neighbor->t_entering < node->t_entering) {  // prevent fake advance
          push(stack, edge);
        }
        if (node->ret > neighbor->t_entering) {
          node->ret = neighbor->t_entering;
        }
      }
    }
  }

  node->color = BLACK;
}

int bcc_example() {
  printf_cyan("find biconnected components example\n\n");
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