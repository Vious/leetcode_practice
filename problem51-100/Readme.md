# Notes
My solution code for problems 51 (N-Queens) to 100 (Same Tree). File naming from "part11.cpp" to "part20.cpp". (Every 5 problems in one part)

## Part 11
Code from problems 51 (N-Queens) to 55 (Jump Game).

For Problem 51 (N-Queens), typical backtracing. But remember use one for loop by increasing row number.

For Problem 52 (N-Queens II), counting version of P51.
- A faster code trick is to use 3 one-dimenstional vectors instead of two dim bool arrays, reduces time costs from 200ms+ to about 4ms. (New solution code are uploaded)

For Problem 53. (Maximum Subarray), greedy. (Needs some time to review)

For Problem 54. (Spiral Matrix), code beats 100%, feeling a bit nice.
- Set a turn flag, and dx, dy as directions, when should dx be 1 or -1.
- Update four boundary values left-right, up-bottom (decrease, increase, in need).

For Problem 55. (Jump Game), two pointers, near, far and a value for farthest. 

## Part 12
Code from problems 56 (Merge Intervals) to 60 (Permutation Sequence).

For Problem 56. (Merge Intervals), there are intervals like: [[2,3],[4,5],[6,7],[8,9],[1,10]], needs to be sorted, a bit tricky, I was kind of fooled by the given examples.

Problem 57. (Insert Interval), similar to P56. We could try using two pointers for binary search and then merge.

Problem 58. (Length of Last Word), back counting (faster), or string split.

Problem 59. (Spiral Matrix II), counting version of Problem 54. (Spiral Matrix).

Problem 60. (Permutation Sequence), acutally, we can think about that if k < (n - 1)!, then the first one must be 1, and if k < (n - 2), then the second digit would be 2... So we can,
- Use an initial initStr with "123456...n", then find idx = k / fact[n - 1], set result += initStr[idx]
- Remove initStr[idx] from initStr, k mod fact[n - 1], n--.

## Part 13
My solution code from problems 61 (Rotate List) to 65 ().

Problem 61. Rotate List, first find the last pointer and make a circle, then move it and the head according to k.

Problem 62. Unique Paths, dp[i][j] = dp[i - 1][j] + dp[i][j - 1].

Problem 63. Unique Paths II, condtioned version of P62. But, watch out for the test cases like [[1]], [[1, 0]]

Problem 64. Minimum Path Sum, similar to P62 and P63.


## Part 14
My solution code from Problem 66. (Plus One) to 70 ().

Problem 66. (Plus One) to Problem 67. (Add Binary), similar, check carry value, char to int, int to char.

Problem 69. Sqrt(x), I just add check code for 2147395599 and the numbers above it (seems a little stupid). 

Problem 70. Climbing Stairs, simple dynamic programming.
