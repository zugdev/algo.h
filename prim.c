#include <limits.h>  // for INT_MAX
#include <stdio.h>
#include <stdlib.h>
#include "headers/algo.h"
#include "headers/colors.h"
#include "headers/graph.h"
#include "headers/queue.h"
#include "headers/stack.h"

/*
 * Prim's Algorithm:
 *
 * 1. Initialize the key of each vertex to infinity and its parent to
 * NULL.
 * 2. Start from an arbitrary vertex and set its key to 0.
 * 3. Use a priority queue to extract the vertex with the smallest key.
 * 4. For each adjacent vertex, if the weight of the edge is smaller than the
 * current key, update the key and parent of that vertex.
 */

#define INF INT_MAX

Stack* prim(Graph* graph, Edge** edges, int num_edges, Node* start) {
  Stack* mstStack = createStack(graph->size - 1);  // to store MST edges
  int* key =
      malloc(graph->size * sizeof(int));  // to store key values for nodes
  Node** parent = malloc(graph->size * sizeof(Node*));  // to store parent nodes
  int* inMST =
      calloc(graph->size, sizeof(int));  // to track if a node is in MST

  // initialize keys to infinity and parents to NULL
  for (int i = 0; i < graph->size; i++) {
    key[i] = INF;
    parent[i] = NULL;
  }

  // start with the given start node
  key[start->id] = 0;

  while (1) {
    // extract the node with the minimum key that is not in the MST
    Node* u = extractMin(graph->nodes, key, inMST, graph->size);
    if (!u)
      break;  // if no node is left, stop

    inMST[u->id] = 1;  // mark this node as part of the MST

    // for each edge connected to this node, update the key and parent if needed
    for (int i = 0; i < num_edges; i++) {
      Node* v = NULL;
      Edge* uvEdge = edges[i];

      // check if this edge connects the current node to another node
      if (uvEdge->u == u && !inMST[uvEdge->v->id]) {
        v = uvEdge->v;
      } else if (uvEdge->v == u && !inMST[uvEdge->u->id]) {
        v = uvEdge->u;
      }

      if (v != NULL && uvEdge->weight < key[v->id]) {
        key[v->id] = uvEdge->weight;
        parent[v->id] = u;
      }
    }
  }

  // build the MST by storing the edges in the stack
  for (int i = 1; i < graph->size; i++) {
    if (parent[i]) {
      for (int j = 0; j < num_edges; j++) {
        Edge* edge = edges[j];
        if ((edge->u == graph->nodes[i] && edge->v == parent[i]) ||
            (edge->v == graph->nodes[i] && edge->u == parent[i])) {
          push(mstStack, edge);
          break;
        }
      }
    }
  }

  free(key);
  free(parent);
  free(inMST);

  return mstStack;
}

int prim_example() {
  printf_cyan("Prim example\n\n");

  Node* a = createNode('a');
  Node* b = createNode('b');
  Node* c = createNode('c');
  Node* d = createNode('d');
  Node* e = createNode('e');
  Node* f = createNode('f');

  Node* nodes[] = {a, b, c, d, e, f};

  Edge* e1 = createWeightedEdge(a, b, 4);
  Edge* e2 = createWeightedEdge(a, c, 4);
  Edge* e3 = createWeightedEdge(b, d, 2);
  Edge* e4 = createWeightedEdge(c, d, 3);
  Edge* e5 = createWeightedEdge(d, e, 6);
  Edge* e6 = createWeightedEdge(e, f, 5);

  Edge* edges[] = {e1, e2, e3, e4, e5, e6};
  int num_edges = sizeof(edges) / sizeof(edges[0]);

  Graph* graph = createGraph(nodes, 6);

  Stack* mstStack = prim(graph, edges, num_edges, a);

  printf_magenta("Edges in the MST:\n");
  printStack(mstStack, printEdgeElement);

  freeGraph(graph);
  freeStack(mstStack);

  return 0;
}
