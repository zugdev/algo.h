#include "mst.h"

Node* find(Subset* subsets, Node* u) {
  if (subsets[u->id].parent != u) {
    // path compression
    subsets[u->id].parent = find(subsets, subsets[u->id].parent);
  }
  return subsets[u->id].parent;
}

void unionSet(Subset* subsets, Node* u, Node* v) {
  Node* rootU = find(subsets, u);
  Node* rootV = find(subsets, v);

  if (rootU == rootV)
    return;

  // union by rank
  if (subsets[rootU->id].rank < subsets[rootV->id].rank) {
    subsets[rootU->id].parent = rootV;
  } else if (subsets[rootU->id].rank > subsets[rootV->id].rank) {
    subsets[rootV->id].parent = rootU;
  } else {
    subsets[rootV->id].parent = rootU;
    subsets[rootU->id].rank++;
  }
}
