/**Given a 1-indexed array of integers numbers that is already sorted in
non-decreasing order, find two numbers such that they add up to a specific
target number. Let these two numbers be numbers[index1] and numbers[index2]
where 1 <= index1 < index2 < numbers.length.

Return the indices of the two numbers, index1 and index2, added by one as an
integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use
the same element twice.

Your solution must use only constant extra space.



Example 1:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We
return [1, 2]. Example 2:

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We
return [1, 3]. Example 3:

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We
return [1, 2].


Constraints:

2 <= numbers.length <= 3 * 10^4
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.

idea: two pointer technique
first pointer at first element
second pointer at the last element
pointers meet in the middle of the array
first pointer "s" shifts right <=> a[s] + a[t] < k
second pointer "t" shifts left <=> a[s] + a[t] > k

Such pair (i, j) exists
If it is not found, this means that 2 situation can happen

1) s was shifted to i + 1, when t was > j
2) t was shifted to j - 1, when s was < i

1) s was shifted to i + 1 => it happened because before that:
a[s] + a[t] = a[i] + a[t] < k
=> a[i] + a[t] < a[i] + a[j]
=> a[t] < a[j] => t < j, but t was > j (by 1 point)

2) t was shifted to j - 1 => => it happened because before that:
a[s] + a[t] = a[s] + a[j] > k
=> a[s] + a[j] > a[i] + a[j]
=> a[s] > a[i] => s > i, but s was < i (by 2 point)

=> this pair will be found


**/

#include <vector>

using namespace std;

vector<int> twoSum(vector<int> &numbers, int target) {
  size_t i = 0;

  // size is at least 1
  size_t j = numbers.size() - 1;

  // there exists such two i and j and there is only one such pair
  while (i != j) {
    if (numbers[i] + numbers[j] < target) {
      ++i;
    } else if (numbers[i] + numbers[j] > target) {
      --j;

      // such value exists
    } else if (numbers[i] + numbers[j] == target) {

      // return 1-indexed answer
      return {(int)i + 1, (int)j + 1};
    }
  }

  // only for compiler
  return {0, 0};
}