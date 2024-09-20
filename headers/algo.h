#ifndef ALGO_H
#define ALGO_H

#include "graph.h"
#include "queue.h"
#include "stack.h"

void dfs_visit(Node* node, Stack* stack, int* time);
Stack* dfs(Graph* graph, int time);
void bfs(Graph* graph, Node* start);
void kosajaru(Graph* graph);
int dfs_example();
int bfs_example();
int kosajaru_example();
int bcc_example();
#endif  // ALGO_H