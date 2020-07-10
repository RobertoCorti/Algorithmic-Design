## Homework 05: Sorting Algorithms (second part)

#### How to compile

A `Makefile` can be produced by using `cmake` as follows:

```bash
cmake -G "Unix Makefiles" CMakeLists.txt 
```

Afterwards you can compile the code by executing `make`. This produces an executable named `test_sorting` which can be executed in POSIX systems by using the command:

```bash
./test_sorting
Size	Insertion Sort	          	        
    	(Random Case)	(Best Case)	(Worst Case)
2^2 	0.000000 (KO)	0.000000	0.000000 (KO)
2^3	0.000000 (KO)	0.000000	0.000000 (KO)
2^4	0.000000 (KO)	0.000000	0.000000 (KO)
2^5	0.000000 (KO)	0.000000	0.000000 (KO)
2^6	0.000000 (KO)	0.000000	0.000000 (KO)
2^7	0.000000 (KO)	0.000000	0.000000 (KO)
2^8	0.000000 (KO)	0.000000	0.000000 (KO)
2^9	0.000000 (KO)	0.000000	0.000000 (KO)
2^10	0.000000 (KO)	0.000000	0.000000 (KO)
2^11	0.000000 (KO)	0.000000	0.000000 (KO)
2^12	0.000000 (KO)	0.000000	0.000000 (KO)
2^13	0.000000 (KO)	0.000000	0.000000 (KO)


Size	Quick Sort	          	Quick Sort + Select
    	(Random Case)	(Worst Case)	(Random Case)	(Worst Case)
2^2 	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^3	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^4	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^5	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^6	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^7	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^8	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^9	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^10	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^11	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^12	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^13	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000


Size	Insertion Sort	Quick Sort	Bubble Sort	Selection Sort	Heap Sort
    	(Random Case)	(Random Case)			
2^2 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^3 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^4 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^5 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^6 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^7 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^8 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^9 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^10	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^11	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^12	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^13	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)


Size	Quick Sort  	Quick Sort +	Heap Sort
			  Select
    	(Random Case)	(Random Case)
2^14	0.000001 (KO)	0.000001 (KO)	0.000000 (KO)
2^15	0.000005 (KO)	0.000005 (KO)	0.000002 (KO)
2^16	0.000004 (KO)	0.000004 (KO)	0.000000 (KO)
2^17	0.000011 (KO)	0.000011 (KO)	0.000011 (KO)
2^18	0.000030 (KO)	0.000030 (KO)	0.000013 (KO)
2^19	0.000105 (KO)	0.000105 (KO)	0.000041 (KO)
2^20	0.000110 (KO)	0.000110 (KO)	0.000075 (KO)
```
The first column in the output report the size of the tested array. The remaining columns in the output report the execution-time in seconds of the implementations of sorting algorithms. Whenever the resulting arrays are not sorted (e.g., due to a bug) the word "KO" follows the execution-time.

#### Report

The final report of this homework can be read [here](https://github.com/RobertoCorti/Algorithmic-Design/blob/master/homeworks/homework_5/report/report.pdf)