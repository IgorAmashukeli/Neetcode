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

**/

using namespace std;

class Solution {
public:
  int minOperations(vector<int> &nums, int x) {
    bool found = false;
    int min_op = nums.size();
    unordered_map<long long, int> prefix_positions;
    unordered_map<long long, int> suffix_positions;
    long long prefix_sum = 0;
    long long suffix_sum = 0;
    prefix_positions[0] = 0;
    suffix_positions[0] = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
      prefix_sum = prefix_sum + nums[i];
      prefix_positions[prefix_sum] = i + 1;
    }
    for (size_t i = 0; i < nums.size(); ++i) {
      size_t j = nums.size() - i - 1;
      suffix_sum = suffix_sum + nums[j];
      suffix_positions[suffix_sum] = i + 1;
    }

    for (const auto &[value, pref_pos] : prefix_positions) {
      if (suffix_positions.contains(x - value)) {
        int suf_pos = suffix_positions[x - value];
        if (pref_pos + suf_pos <= min_op) {
          found = true;
          min_op = pref_pos + suf_pos;
        }
      }
    }

    if (!found) {
      return -1;
    } else {
      return min_op;
    }
  }
};

int main() {
  vector<int> nums = {1, 1};
  int x = 3;
  cout << Solution().minOperations(nums, x) << "\n";
}