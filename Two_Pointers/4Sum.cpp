#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <vector>

/**Given an array nums of n integers, return an array of all the unique
quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.



Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]


Constraints:

1 <= nums.length <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9



idea: two pointers 2sum 2 + two outer loop

how to avoid duplicates

1) k is pointer of outer first
2) s is pointer of outer second
2) i and j are two inner pointers

we save {nums[k], nums[s], nums[i], nums[j]}

Then,
k < s by loops (s starts at k + 1)
i < s by definition of i (i starts at s + 1)
i < j by definition of two pointer technique
That means, that nums[k] < nums[s] < nums[i] < nums[j]
That means, that
{nums[k], nums[s], nums[i], nums[j]} are always in the same order

That means, the only duplicates are if
nums[k] are duplicated (we skip this)
nums[s] are duplicated (we skip this)
nums[i] or nums[j] are duplicated

For this we check only one: we check nums[i]
(actually we can skip nums[i] or nums[j], cause they can never be there in the
output, cause this is repetition, but we don't need to: when nums[i] will
increase the result is not nums[k] + nums[i] + nums[j] => we will move j
definetely to the left => therefore everything is already checked for nums[j]
and will be skipped)


**/

using namespace std;

vector<vector<int>> fourSum(vector<int> &nums, int target) {
  vector<vector<int>> result;
  // sorting values
  sort(nums.begin(), nums.end());

  // iterate over all nums[k]
  for (int k = 0; k + 2 < nums.size(); ++k) {
    if (k > 0 && nums[k] == nums[k - 1]) {
      continue;
    }

    for (int s = k + 1; s + 1 < nums.size(); ++s) {
      if (s > k + 1 && nums[s] == nums[s - 1]) {
        continue;
      }

      int i = s + 1;

      // size is at least 1
      int j = nums.size() - 1;
      ssize_t a = static_cast<ssize_t>(nums[i]);
      ssize_t b = static_cast<ssize_t>(nums[j]);
      ssize_t c = static_cast<ssize_t>(nums[k]);
      ssize_t d = static_cast<ssize_t>(nums[s]);
      while (i != j) {
        if (a + b + c + d < target) {
          ++i;
        } else if (a + b + c + d > target) {
          --j;
          // such value exists
        } else if (a + b + c + d == target) {
          vector<int> answer = {nums[k], nums[s], nums[i], nums[j]};
          result.push_back(answer);
          ++i;
          while (nums[i] == nums[i - 1] && i < j) {
            ++i;
          }
        }
      }
    }
  }

  return result;
}

int main() {
  vector<int> nums = {1, 0, -1, 0, -2, 2};
  int target = 0;
  vector<vector<int>> result = fourSum(nums, target);
  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << " ";
    }
    cout << "\n";
  }
}