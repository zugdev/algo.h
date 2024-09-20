#ifndef GRAPH_H
#define GRAPH_H

typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct Node {
  char name;                  // this is for printing only
  int id;                     // node's backend identifier
  int distance;               // distance from an arbitrary root
  int t_entering;             // time entering the node for dfs
  int t_leaving;              // time leaving the node for dfs
  Color color;                // color for algos like bfs, dfs
  struct Node** neighbors;    // list of adjacency
  int out_degree;             // number of edges leaving the graph (directed or not
  struct Node* parent;        // direct parent
  int low;                    // lowest point reachable from this node
  int is_articulation_point;  // flag for articulation points
} Node;

typedef struct Edge {
    Node* u;
    Node* v;
} Edge;

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
void printFound(Graph* graph);

#endif  // GRAPH_H