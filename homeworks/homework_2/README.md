## Homework 02: Binary Heaps

#### How to compile

A `Makefile` can be produced by using `cmake` as follows:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt 
```

This will produce a `Makefile` that is able to generate two executables: `heap_test` and `test_insert`. The first one will show the correctness of all the requested functions implemented in `src/binheap.c`. On the other hand,  `test_insert`  will evaluate the execution time of the `insert_key` function for an increasing number of istances. The result will be written in a output file `result/insertion_time.txt`, that will contain the following table:

```bash
N        time
5       0.000000
15      0.000000
25      0.000000
35      0.000000
45      0.000000
55      0.000000
65      0.000000
75      0.000000
85      0.000000
95       0.000000
105      0.000000
115      0.000000
...      ....
 ```