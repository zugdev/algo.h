#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

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

Edge* createEdge(Node* u, Node* v) {
  Edge* edge = (Edge*)malloc(sizeof(Edge));
  edge->u = u;
  edge->v = v;
  if (!edge) {
    fprintf(stderr, "Memory allocation failed for Edge\n");
    exit(1);
  }
  return edge;
}

Edge* createWeightedEdge(Node* u, Node* v, int weight) {
  Edge* edge = (Edge*)malloc(sizeof(Edge));
  edge->u = u;
  edge->v = v;
  edge->weight = weight;
  if (!edge) {
    fprintf(stderr, "Memory allocation failed for Edge\n");
    exit(1);
  }
  return edge;
}

int compareEdges(const void* a, const void* b) {
  Edge* edgeA = *(Edge**)a;
  Edge* edgeB = *(Edge**)b;
  return edgeA->weight - edgeB->weight;
}

void sortWeightedEdges(Edge** edges, int size) {
  qsort(edges, size, sizeof(Edge*), compareEdges);
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

// this is the same as transposing the graph matrix
// most of the code is to clone objects and not copy object address
Graph* invertArcs(Graph* graph) {
  Graph* invertedGraph = (Graph*)malloc(sizeof(Graph));
  if (!invertedGraph) {
    fprintf(stderr, "Memory allocation failed for Inverted Graph\n");
    exit(1);
  }

  invertedGraph->nodes = (Node**)malloc(graph->size * sizeof(Node*));
  invertedGraph->size = graph->size;

  // clone nodes to the new graph
  for (int i = 0; i < graph->size; i++) {
    Node* original = graph->nodes[i];
    Node* copy = createNode(original->name);
    copy->id = original->id;
    invertedGraph->nodes[i] = copy;
  }

  // invert the arcs / transpose
  for (int i = 0; i < graph->size; i++) {
    Node* originalNode = graph->nodes[i];
    for (int j = 0; j < originalNode->out_degree; j++) {
      Node* neighbor = originalNode->neighbors[j];
      addArc(invertedGraph->nodes[neighbor->id], invertedGraph->nodes[i]);
    }
  }

  return invertedGraph;
}

void relax(Node* u, Node* v, int weight) {
    if (v->distance == -1 || v->distance > u->distance + weight) {
        v->distance = u->distance + weight;
        v->parent = u;
    }
}

void topologicalSortUtil(Node* node, int* visited, Stack* stack) {
    visited[node->id] = 1; 
    
    for (int i = 0; i < node->out_degree; i++) {
        Node* neighbor = node->neighbors[i];
        if (!visited[neighbor->id]) {
            topologicalSortUtil(neighbor, visited, stack); 
        }
    }
    push(stack, node);  
}

Stack* topologicalSort(Graph* graph) {
    Stack* stack = createStack(graph->size);  

    int* visited = (int*)calloc(graph->size, sizeof(int)); 

    for (int i = 0; i < graph->size; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph->nodes[i], visited, stack);
        }
    }

    free(visited);
    return stack;
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
  magenta();
  printf("\n-- Node %c (id: %d)\n", node->name, node->id);
  reset_color();

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

void printNodeElement(void* element) {
    Node* node = (Node*)element;  // cast back to Node*
    printf("%c ", node->name);
}

void printEdgeElement(void* element) {
    Edge* edge = (Edge*)element;  // cast back to Edge*
    printf("(%c <-> %c) ", edge->u->name, edge->v->name);
}

void printGraph(Graph* graph) {
  printf_blue("<Graph>");
  for (int i = 0; i < graph->size; i++) {
    printNode(graph->nodes[i]);
  }
  printf_blue("<\\Graph>\n");
}

void printFound(Graph* graph) {
  printf("Found (BLACK): [");
  int firstNode = 1;
  for (int i = 0; i < graph->size; i++) {
    if (graph->nodes[i]->color == BLACK) {
      if (!firstNode) {
        printf(",");
      }
      printf("%c", graph->nodes[i]->name);
      firstNode = 0;
    }
  }
  printf("]\n");
}