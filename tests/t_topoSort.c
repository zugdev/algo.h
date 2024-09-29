#include <stdio.h>
#include <stdlib.h>
#include "../headers/colors.h"
#include "../headers/graph.h"
#include "../headers/stack.h"

int main() {
    // create nodes
    Node* a = createNode('a');
    Node* b = createNode('b');
    Node* c = createNode('c');
    Node* d = createNode('d');
    Node* e = createNode('e');

    // add directed edges (arcs)
    addArc(a, b);
    addArc(a, c);
    addArc(b, d);
    addArc(c, d);
    addArc(d, e);

    // create graph
    Node* nodes[] = {a, b, c, d, e};
    Graph* graph = createGraph(nodes, 5);

    // run topological sort
    Stack* topoSortStack = topologicalSort(graph);

    printStack(topoSortStack, printNodeElement);

    // check if topological sort is correct (a valid sort would be [a, b, c, d, e])
    Node* topNode = (Node*)pop(topoSortStack);
    
    if (topNode->name != 'a') {
        printf_error("Error: Test case 1 failed\n");
        return 1;
    }

    topNode = (Node*)pop(topoSortStack);
    if (topNode->name != 'c') {
        printf_error("Error: Test case 2 failed\n");
        return 2;
    }

    topNode = (Node*)pop(topoSortStack);
    if (topNode->name != 'b') {
        printf_error("Error: Test case 3 failed\n");
        return 3;
    }

    topNode = (Node*)pop(topoSortStack);
    if (topNode->name != 'd') {
        printf_error("Error: Test case 4 failed\n");
        return 4;
    }

    topNode = (Node*)pop(topoSortStack);
    if (topNode->name != 'e') {
        printf_error("Error: Test case 5 failed\n");
        return 5;
    }

    printf_green("All topologicalSort tests passed :)\n");

    freeStack(topoSortStack);
    freeGraph(graph);

    return 0;
}
