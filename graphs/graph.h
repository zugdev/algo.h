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
Graph* createGraph(Node** nodes, int size);
Graph* invertArcs(Graph* graph);
void freeNode(Node* node);
void freeGraph(Graph* graph);
void printNode(Node* node);
void printGraph(Graph* graph);

#endif  // GRAPH_H