# HW 3: Strongly Connected Components

## How to compile
Run `make` command to compile source code.
```
make
```

## How to run
`SCC` gets an input graph from standard input and finds all strongly connected components in it, by using 3 different data structures: adjacency matrix, adjacency list, and adjacency array. It prints the results and runtime of each algorithm. To see how to give a graph information to the program, read [report.pdf](report.pdf).

Run `SCC` by this command:
```
./SCC
```

If you have the text file of an input graph, run:
```
cat <input file> | ./SCC
```

If you want to check only the elapsed time of each algorithm, run:
```
cat <input file> | ./SCC | grep -E "Result|time"
```

