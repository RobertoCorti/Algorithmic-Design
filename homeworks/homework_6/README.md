## Homework 06: Dijkstra Algorithm

#### How to compile

A `Makefile` can be produced by using `cmake` as follows:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt 
```

Afterwards you can compile the code by executing `make`. This produces an executable named `strassen_test` which can be executed in POSIX systems by using the command:

```bash
./dijkstra_test 
```

The result will show a test between the Dijkstra algorithm implemented with an array priority queue and a binary heap version:

```bash
size    Array           Heap
34      0.000000        0.000000 
68      0.000000        0.000000 
136     0.000000        0.000000 
273     0.000000        0.000000 
546     0.000000        0.000000 
1093    0.000000        0.000000 
2187    0.000000        0.000000 
4375    0.000000        0.000000 
8750    0.000000        0.000000 
17500   0.000000        0.000000 
```

