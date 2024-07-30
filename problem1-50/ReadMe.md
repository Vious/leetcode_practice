# Notes
My solution code for problems from 1 (two sum) to 50 (Pow (x,n)).

## Part1
This part includes solution code from problem 1 (two sum) to 5 (Longest Palindromic Substring).

For problem 1, 

- In this case, we could use c++ unordered map find(), which is faster than map.
- I noted down here that using {num1, num2} to return as vector would still improve the speed.

For problem 2, I choose not to change the original l1 and l2 pointer by initializing two temporary ptrs (just to be more safe) in the callee function. To save memory, just use the original l1 and l2. Another useful trick would be,

```c++
int val1 = (l1 == nullptr) ? 0 : l1->val;
int val2 = (l2 == nullptr) ? 0 : l2->val;
int sum = val1 + val2 + carryF;
```

For problem 3, use STL set by inserting right char and check the set if it is contained, then increasing left index.

For problem 4 (Median of Two Sorted Arrays), the request is an algorithm with time complexity of O(log(m+n)), so binary search algorithms are needed here. One trick to make the code quicker is to determine the size first and by recalling the function to simply swap the position of nums1 and nums2.

For problem 5 (Longest Palindromic Substring), a classical solution would be dynamic programming. I use two inner loop to check the two types of Palindromic string, one for pattern like \"aba\" those with central characters, and another one pattern "baab".


## Part2
