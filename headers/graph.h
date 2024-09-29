#ifndef GRAPH_H
#define GRAPH_H

#include "stack.h"

typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct Node {
    char name;                  // this is for printing only
    int id;                     // node's backend identifier
    int distance;               // distance from an arbitrary root
    int t_entering;             // time entering the node for dfs
    int t_leaving;              // time leaving the node for dfs
    Color color;                // color for algos like bfs, dfs
    struct Node** neighbors;    // list of adjacency
    int out_degree;             // number of edges leaving the graph (directed or not)
    struct Node* parent;        // direct parent
    int ret;                    // this is used to find blocks
    int component_number;       // used to find blocks/components
} Node;

typedef struct Edge {
    Node* u;
    Node* v;
    int weight;
} Edge;

typedef struct Graph {
    Node** nodes;
    int size;
} Graph;

// node functions
Node* createNode(char name);
Edge* createEdge(Node* a, Node* b);
Edge* createWeightedEdge(Node* a, Node* b, int weight);
void addArc(Node* from, Node* to);
void addEdge(Node* a, Node* b);
Graph* createGraph(Node** nodes, int size);
Graph* invertArcs(Graph* graph);
void freeNode(Node* node);
void freeGraph(Graph* graph);
void printNode(Node* node);
void printGraph(Graph* graph);
void printFound(Graph* graph);
void relax(Node* u, Node* v, int weight);   // edge relaxation
Stack* topologicalSort(Graph* graph);     

#endif  // GRAPH_H
