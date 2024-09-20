#ifndef MST_H
#define MST_H

#include "graph.h"

typedef struct WeightedEdge {
    Node* u;
    Node* v;
    int weight;
} WeightedEdge;

typedef struct Subset {
    Node* parent;
    int rank;
} Subset;

int find(Subset* subsets, Node* node);
void unionSets(Subset* subsets, Node* u, Node* v);

#endif // MST_H