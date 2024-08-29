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

Problem 58. (Length of Last Word), 