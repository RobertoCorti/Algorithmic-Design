## Homework 01: Matrix Multiplication

#### How to compile

A `Makefile` can be produced by using `cmake` as follows:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt 
```

Afterwards you can compile the code by executing `make`. This produces an executable named `strassen_test` which can be executed in POSIX systems by using the command:

```bash
./strassen_test 
```

The result will show at first the following table:
```bash
n      Naive Alg.   Strassen Alg.      Same result
1	    0.000000	0.000000	       1
2	    0.000000	0.000000	       1
4	    0.000000	0.000000	       1
8	    0.000000	0.000000	       1
16	    0.000000	0.000000	       1
32	    0.000000	0.000000	       1
64	    0.000000	0.000000	       1
128	    0.000000	0.000000	       1
256	    0.000000	0.000000	       1
512	    0.000000	0.000000	       1
1024        0.000000    0.000000               1
2048        0.000000    0.000000               1
4096        0.000000    0.000000               1
```

The first column reports the number of the rows and columns in the tested matrices. The second and third columns in the output report the execution-time in seconds of the implementations of the naive algorithm and of the Strassen's algorithm, respectively.  Finally, the last column, which is exclusively meant to validate the implementations, contains the value 1 if and only if the result of the naive algorithm and that of the Strassen's algorithm are the same.

After this table `strassen_test` will report a similar table that compares normal implementation of Strassen's Algorithm with an optimized version:

```bash
n       Strassen Alg.   Opt.Strassen        Same result
1	    0.000000	    0.000000	            1
2	    0.000000	    0.000000	            1
4	    0.000000	    0.000000	            1
8	    0.000000	    0.000000	            1
16	    0.000000	    0.000000	            1
32	    0.000000	    0.000000	            1
64	    0.000000	    0.000000	            1
128	    0.000000	    0.000000	            1
256	    0.000000	    0.000000	            1
512	    0.000000	    0.000000	            1
1024        0.000000        0.000000                1
2048        0.000000        0.000000                1
4096        0.000000        0.000000                1
```

#### Report

The final report of this homework can be read [here](https://github.com/RobertoCorti/Algorithmic-Design/blob/master/homeworks/homework_1/report/report.pdf)