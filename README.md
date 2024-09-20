### an algo collection
*might* add notes and references later

- **BFS (Breadth-First Search)**

  Breadth-First Search explores nodes level by level. It first visits all nodes at distance 0, then all nodes at distance 1, and so on.

- **DFS (Depth-First Search)**

  Depth-First Search explores as far as possible along each branch before backtracking. It chooses a path from the root and goes to the end of it recursively before returning. It proceeds by exploring all possible paths and marking already visited nodes.

- **Kosaraju's Algorithm**

  Kosaraju's Algorithm finds strongly connected components in a graph.

- **BCC (Biconnected Components)**

  Finds articulation points in non-directed graphs, this can then be used to calculate biconnected components.

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


#### LINUX/MAC

to compile just run:
```shell
make
```

algos are centralized through a `./out/main` entrypoint 
```shell
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
./out/main bfs

# bfs runs
```

test files are compiled with their own main functions, if interested run them separetely


#### WINDOWS

> tbh you should install wsl..... but here it comes

to compile *just* run, add all functions manually if I forgot one:
```shell
gcc -Wall -Wextra -Iheaders -o out/main.exe headers/colors.c headers/graph.c headers/queue.c headers/stack.c bcc.c bfs.c dfs.c kosajaru.c main.c
```

algos are centralized through a `./out/main.exe` entrypoint 
```shell
./out/main.exe

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
./out/main.exe bfs

# bfs runs
```

if you want to compile tests, just do the same thing

### commit msg conventions:

- **feat:** for new implementations, code updates, anything meaningfull

example -> feat: implement btp

- **chore:** update comments, settings, .gitignore, dir structure

example -> chore: delete trash code

