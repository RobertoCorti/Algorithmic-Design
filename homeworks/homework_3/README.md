## Homework 03

1. By modifying the code written during the last lessons, provide an array-
   based implementation of binary heaps which avoids to swap the elements in the array A.
   (Hint: use two arrays, key pos and rev pos, of natural numbers reporting the position of the key of a node and the node corresponding to a given position, respectively)

2. Consider the next algorithm: 
  ``` pseudocode
  def Ex2 ( A )
    D ← build ( A )
    while ¬ is_empty ( D )
     extract_min ( D )
   endwhile
 enddef ```
  ```

where A is an array. Compute the time-complexity of the algorithm when:

* `` build, is_empty``  are Theta(1) , ```extract_min ``` is  Theta(|D|);
* ``build`` is Theta(|A|), ``is_empty`` is Theta(1), ``extract_min`` is O(log |D|);