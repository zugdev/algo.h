#ifndef GRAPH_H
#define GRAPH_H

typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct Node {
  char name;
  int id;
  int distance;
  int t_entering;
  int t_leaving;
  Color color;
  struct Node** neighbors;
  int out_degree;
  struct Node* parent;
} Node;

typedef struct Graph {
  Node** nodes;
  int size;
} Graph;

Node* createNode(char name);
void addArc(Node* from, Node* to);
void addEdge(Node* a, Node* b);
void freeNode(Node* node);
Graph* createGraph(Node** nodes, int size);
Graph* invertArcs(Graph* graph);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);

#endif  // GRAPH_H