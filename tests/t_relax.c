#include <stdio.h>
#include <stdlib.h>
#include "../headers/colors.h"
#include "../headers/graph.h"
#include "../headers/stack.h"

// define weights for edges
#define WEIGHT_1 1
#define WEIGHT_4 4

int main() {
    // create nodes
    Node* a = createNode('a');
    Node* b = createNode('b');
    Node* c = createNode('c');

    // manually set distances
    a->distance = 0;
    b->distance = 4;
    c->distance = 10;

    // relax edges
    relax(a, b, WEIGHT_1);  // this should update b->distance to 1
    relax(a, c, WEIGHT_4);  // this should update c->distance to 4

    // check if the distances were correctly relaxed
    if (b->distance != 1) {
        printf_error("Error: Test case 1 failed\n");
        return 1;
    }

    if (c->distance != 4) {
        printf_error("Error: Test case 2 failed\n");
        return 2;
    }

    // attempt to relax again with worse weights, should not change
    relax(b, c, WEIGHT_4);  // c should remain with distance 4

    if (c->distance != 4) {
        printf_error("Error: Test case 3 failed\n");
        return 3;
    }

    printf_green("All relax tests passed :)\n");

    freeNode(a);
    freeNode(b);
    freeNode(c);

    return 0;
}
