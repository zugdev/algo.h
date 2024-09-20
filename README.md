### an algo collection

*might* add notes and references later

- bfs 

breath first search, goes by levels first all distance = 0 nodes, then all distance = 1 nodes...

- dfs

depth first search, chooses a path from root and goes to the end of it recursively before returning. it proceeds by doing all possible paths and marking already visited ones.

- kosajaru 

finds strongly connected components, this can also be used to find elbows and articulations

### understanding

you should know at least the principal structs, for a list of useful util functions dive into `/headers` specially `graph.h`

```c
typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct Node {
  char name;
  int id;
  int distance;
  int t_entering;
  int t_leaving;
  Color color;
  struct Node** neighbors;
  int out_degree;
  struct Node* parent;
} Node;

typedef struct Graph {
  Node** nodes;
  int size;
} Graph;
```

im aggregating all algo properties in a single type struct for commodity I know this is not max efficiency. I think general code is pretty easy to understand, prioritizing clear code x efficiency driven. btw some of those are my thoughts so stuff might not *always* be optimal complexity

### executing

you must have a compiler installed. `Makefile` is set to run `gcc`:

1. if you have a different compiler go into `Makefile` and change the alias
2. if you don't have a compiler installed please refer to [this manual.](https://gcc.gnu.org/install/)

to compile just run:
```shell
make
```

algos are centralized through a `main.c` entrypoint 
```shell
# linux
./out/main 

# > tip: you can run what u want on CLI: ./out/main bfs
# what algo do you want to run
#   > 1. bfs
#   > 2. dfs
#   > 3. kosajaru

bfs

# bfs runs
```

you can run them directly through CLI
```shell
# linux
./out/main bfs

# bfs runs
```

test files are compiled with their own main functions, if interested run them separetely

### commit msg conventions:

- **feat:** for new implementations, code updates, anything meaningfull

example -> feat: implement btp

- **chore:** update comments, settings, .gitignore, dir structure

example -> chore: delete trash code

