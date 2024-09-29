#ifndef MST_H
#define MST_H

#include "graph.h"

typedef struct Subset {
    Node* parent;
    int rank;
} Subset;

Node* find(Subset* subsets, Node* node);
void unionSet(Subset* subsets, Node* u, Node* v);
Node* extractMin(Node** nodes, int* key, int* inMST, int size);

#endif // MST_H