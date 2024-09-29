#ifndef ALGO_H
#define ALGO_H

#include "graph.h"
#include "mst.h"
#include "queue.h"
#include "stack.h"

void dfs_visit(Node* node, Stack* stack, int* time);
Stack* dfs(Graph* graph, int time);
void bfs(Graph* graph, Node* start);
void kosajaru(Graph* graph);
Stack* kruskal(Graph* graph, Edge** edges, int num_edges);
int dfs_example();
int bfs_example();
int kosajaru_example();
int bcc_example();
int kruskal_example();
#endif  // ALGO_H