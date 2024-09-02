#include <stdio.h>
#include <string.h>
#include "headers/algo.h"
#include "headers/graph.h"
#include "headers/queue.h"
#include "headers/stack.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    if (argc == 2) {
      printf("> tip: you can run multiple algos on CLI: %s bfs dfs kosajaru\n",
             argv[0]);
    }
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "bfs") == 0) {
        bfs_example(argc, argv);
      } else if (strcmp(argv[i], "dfs") == 0) {
        dfs_example(argc, argv);
      } else if (strcmp(argv[i], "kosajaru") == 0) {
        kosajaru_example(argc, argv);
      }
    }
  } else {
    char choice;

    printf("> tip: you can run what u want on CLI: %s bfs\n", argv[0]);
    printf("what algo do you want to run\n");
    printf("  > 1. bfs\n");
    printf("  > 2. dfs\n");
    printf("  > 3. kosajaru\n");
    scanf("%c", &choice);
    printf("\n");

    switch (choice) {
      case '1':
        bfs_example(argc, argv);
        break;
      case '2':
        dfs_example(argc, argv);
        break;
      case '3':
        kosajaru_example(argc, argv);
        break;
      default:
        printf("invalid choice\n");
        break;
    }
  }
}