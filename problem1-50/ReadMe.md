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
Part2 marks the code for Problem 6. (Zigzag Conversion) to Problem 10. ().

For P6. (Zigzag Conversion), write the index of each zigzag converted string, assume the numrows = 1, we can find that the index goes from 0123210123... Therefore, I use map to map each character into specitic rows, and use iterator to combine them together. Another solution would be directly assigning the char into specific index of zigzag converted results' string.

For P7. (Reverse Integer), note that the system does not allow us to use 64-bits long integer.
- One thing to note is that we may get runtime error, a trick to avoid is by checking the value > INT32_MAX / 10 or value < INT32_MIN / 10.

For P8. (String to Integer (atoi)), there are several tiny bugs we would make.
- Check overflow, the simple way is to declare long long int. But if we must use only int, we need to check whether the result is larger then INT32_MAX/10, when it equals INT32_MAX, the next integer must not be greater than 7. (INT32_MIN=-2147483648, and INT32_MAX=2147483647)

For P9. (Palindrome Number), the brute-force solution, we can use vector to store each digit. Smarter way is to reverse the integer and check overflow (we can use long long int to avoid this).

For P10. (Regular Expression Matching)