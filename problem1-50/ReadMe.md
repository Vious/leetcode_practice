# Notes
My solution code for problems from 1 (two sum) to 50 (Pow (x,n)).

## Part1
This part includes solution code from problem 1 to 3.

For problem 1, 

- We could use c++ unordered map find(), which is faster than map.
- I noted down here that using {num1, num2} to return as vector would still improve the speed.

For problem 2, I choose not to keep the original l1 and l2 pointer by initializing two temporary ptrs (just to be more safe) in the callee function. To save memory, just use the original l1 and l2. Another useful trick would be,

```c++
int val1 = (l1 == nullptr) ? 0 : l1->val;
int val2 = (l2 == nullptr) ? 0 : l2->val;
int sum = val1 + val2 + carryF;
```

## Part2
