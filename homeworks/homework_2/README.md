## Homework 02: Binary Heaps

#### How to compile

A `Makefile` can be produced by using `cmake` as follows:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt 
```

This will produce a `Makefile`; you can compile by executing `make`. This will generate an executable called `heap_test` that will evaluate
the execution time for an increasing number of istances. The result will be written in a output file `result/insertion_time.txt`, that will contain the following table:

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