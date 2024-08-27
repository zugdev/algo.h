#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static int id = 0;

Node* createNode(char name) {
  Node* node = (Node*)malloc(sizeof(Node));
  if (!node) {
    fprintf(stderr, "Memory allocation failed for Node\n");
    exit(1);
  }
  node->name = name;
  node->id = id++;
  node->distance = -1;
  node->t_entering = -1;
  node->t_leaving = -1;
  node->color = WHITE;
  node->neighbors = NULL;
  node->out_degree = 0;
  node->parent = NULL;
  return node;
}

void addArc(Node* from, Node* to) {
  from->out_degree++;
  if (from->neighbors == NULL) {
    from->neighbors = (Node**)malloc(sizeof(Node*));
  } else {
    from->neighbors =
        (Node**)realloc(from->neighbors, from->out_degree * sizeof(Node*));
  }

  if (!from->neighbors) {
    fprintf(stderr, "Memory allocation failed in addArc\n");
    exit(1);
  }

  from->neighbors[from->out_degree - 1] = to;
}

void addEdge(Node* a, Node* b) {
  a->out_degree++;
  b->out_degree++;

  if (a->neighbors == NULL) {
    a->neighbors = (Node**)malloc(sizeof(Node*));
  } else {
    a->neighbors = (Node**)realloc(a->neighbors, a->out_degree * sizeof(Node*));
  }

  if (!a->neighbors) {
    fprintf(stderr, "Memory allocation failed in addEdge\n");
    exit(1);
  }

  a->neighbors[a->out_degree - 1] = b;

  if (b->neighbors == NULL) {
    b->neighbors = (Node**)malloc(sizeof(Node*));
  } else {
    b->neighbors = (Node**)realloc(b->neighbors, b->out_degree * sizeof(Node*));
  }

  if (!b->neighbors) {
    fprintf(stderr, "Memory allocation failed in addEdge\n");
    exit(1);
  }

  b->neighbors[b->out_degree - 1] = a;
}

Graph* createGraph(Node** nodes, int size) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (!graph) {
    fprintf(stderr, "Memory allocation failed for Graph\n");
    exit(1);
  }
  graph->nodes = nodes;
  graph->size = size;

  return graph;
}

Graph* invertArcs(Graph* graph) {
  Graph* invertedGraph = (Graph*)malloc(sizeof(Graph));
  if (!invertedGraph) {
    fprintf(stderr, "Memory allocation failed for Inverted Graph\n");
    exit(1);
  }

  invertedGraph->nodes = (Node**)malloc(graph->size * sizeof(Node*));
  invertedGraph->size = graph->size;

  // Clone nodes to the new graph
  for (int i = 0; i < graph->size; i++) {
    Node* original = graph->nodes[i];
    Node* copy = createNode(original->name);
    copy->id = original->id;
    invertedGraph->nodes[i] = copy;
  }

  // Invert the arcs
  for (int i = 0; i < graph->size; i++) {
    Node* originalNode = graph->nodes[i];
    for (int j = 0; j < originalNode->out_degree; j++) {
      Node* neighbor = originalNode->neighbors[j];
      addArc(invertedGraph->nodes[neighbor->id], invertedGraph->nodes[i]);
    }
  }

  return invertedGraph;
}

void freeNode(Node* node) {
  if (node->neighbors != NULL) {
    free(node->neighbors);
  }
  free(node);
}

void freeGraph(Graph* graph) {
  for (int i = 0; i < graph->size; i++) {
    freeNode(graph->nodes[i]);
  }
  free(graph);
}

void printNode(Node* node) {
  printf("\n-- Node %c (id: %d)\n", node->name, node->id);

  if (node->distance == -1) {
    printf("\tdistance    -\n");
  } else {
    printf("\tdistance    %d\n", node->distance);
  }

  if (node->t_entering == -1) {
    printf("\tt_entering  -\n");
  } else {
    printf("\tt_entering  %d\n", node->t_entering);
  }

  if (node->t_leaving == -1) {
    printf("\tt_leaving   -\n");
  } else {
    printf("\tt_leaving   %d\n", node->t_leaving);
  }

  printf("\tcolor       ");
  switch (node->color) {
    case WHITE:
      printf("WHITE\n");
      break;
    case GRAY:
      printf("GRAY\n");
      break;
    case BLACK:
      printf("BLACK\n");
      break;
    default:
      printf("-\n");
      break;
  }

  printf("\tout_degree  %d\n", node->out_degree);

  if (node->out_degree == 0) {
    printf("\tneighbors   -\n");
  } else {
    printf("\tneighbors   [");
  }
  Node* neighbor;
  for (int i = 0; i < node->out_degree; i++) {
    neighbor = node->neighbors[i];
    if (i == node->out_degree - 1) {
      printf("%c]\n", neighbor->name);
      break;
    }
    printf("%c,", neighbor->name);
  }
}

void printGraph(Graph* graph) {
  printf("<Graph>\n");
  for (int i = 0; i < graph->size; i++) {
    printNode(graph->nodes[i]);
  }
  printf("\n<\\Graph>\n");
}