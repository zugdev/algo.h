#ifndef MST_H
#define MST_H

#include "graph.h"

typedef struct Subset {
    Node* parent;
    int rank;
} Subset;

Node* find(Subset* subsets, Node* node);
void unionSet(Subset* subsets, Node* u, Node* v);

#endif // MST_H