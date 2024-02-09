#include <assert.h>
#include <iostream>
#include <unordered_map>
#include <vector>

/**
1658. Minimum Operations to Reduce X to Zero
You are given an integer array nums and an integer x. In one operation, you can
either remove the leftmost or the rightmost element from the array nums and
subtract its value from x. Note that this modifies the array for future
operations.

Return the minimum number of operations to reduce x to exactly 0 if it is
possible, otherwise, return -1.



Example 1:

Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x
to zero. Example 2:

Input: nums = [5,6,7,8,9], x = 4
Output: -1
Example 3:

Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements and the
first two elements (5 operations in total) to reduce x to zero.


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
1 <= x <= 10^9


one of the ideas of O(n) in average (or guaranteed O(n long n) in worst case
using map instead of unordered map )

create prefix sums, create suffix sums, remember positions of prefix sums and
sufix sums for each prefix sums find the value - prefix sum in the map and it
position if the sum of the positions is valid (<= n, not intersecting prefix and
suffix sums) and less than global minimum, update global minimum



another idea: find prefix sums and value - sufix sums on the fly, while moving
left and right pointer prefix sums are sorted in ascending order.

sufix sums are sorted in ascending order.
value - sufix sums are sorted in descending order.
but the min value in value - sufix sums is value - sum of all the array and each
next value can be found by adding nums[i].
Therefore, we can iterate over "value - sufix sums" in ascending order.

Therefore, there are two arrays: prefix sums and "value - sufix sums" in
ascending order and the task is to find equal elements with lowest sum of index
of the first array + n - sum of the second array (because, we are iterating over
the second array in reverse order). This can be done, using two pointer
techinique: if a[left] < b[right] -> left++ if a[right] < b[left] -> right++
else check and update the sum of indices.

**/

using namespace std;

class Solution {
public:
  int minOperations(vector<int> &nums, int x) {
    bool found = false;
    int min_ops = nums.size() + 1;
    if (nums.size() == 0) {
      return -1;
    }
    long long sufix = x;
    long long prefix = 0;
    for (size_t k = 0; k < nums.size(); ++k) {
      sufix -= nums[k];
    }

    int left = 0;
    int right = 0;
    while (left < nums.size() || right < nums.size()) {
      if (prefix == sufix) {
        size_t right_index = nums.size() - right;
        if (right_index + left <= nums.size() && left + right_index < min_ops) {
          found = true;
          min_ops = left + right_index;
        }
        if (left < right) {
          prefix += nums[left];
          left++;
        } else {
          sufix += nums[right];
          right++;
        }
      } else if ((prefix < sufix && left < nums.size()) ||
                 right >= nums.size()) {
        prefix += nums[left];
        left++;
      } else if ((prefix > sufix && right < nums.size()) ||
                 left >= nums.size()) {
        sufix += nums[right];
        right++;
      }
    }

    if (!found) {
      return -1;
    } else {
      return min_ops;
    }
  }
};

int main() {
  vector<int> nums = {1, 1};
  int x = 3;
  cout << Solution().minOperations(nums, x) << "\n";
}