#ifndef ALGO_H
#define ALGO_H

#include "graph.h"
#include "queue.h"
#include "stack.h"

void dfs_visit(Node* node, Stack* stack, int time);
Stack* dfs(Graph* graph);
void bfs(Graph* graph, Node* start);

#endif  // ALGO_H