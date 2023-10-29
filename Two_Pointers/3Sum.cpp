#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

/**Given an integer array nums, return all the triplets [nums[i], nums[j],
nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k]
== 0.

Notice that the solution set must not contain duplicate triplets.



Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not
matter. Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.


Constraints:

3 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5

idea: two pointers 2sum 2 + one outer loop

how to avoid duplicates

1) k is pointer of outer
2) i and j are two inner pointers

then save {nums[k], nums[i], nums[j]}
i starts at k + 1; j starts at n - 1
that means k < i and k < j
array is sorted for 2sum 2 task =>
nums[k] < nums[i]
and
nums[k] < nums[j]

=> {nums[i], ...} != {nums[k], nums[i], nums[j]}
 and {nums[j], ...} != {nums[k], nums[i], nums[j]}
(cause otherwise nums[i] = nums[k] or nums[j] = nums[k])

2sum 2 guarantees i < j => nums[i] < nums[j]
=> {nums[k], nums[i], nums[j]} != {nums[k], nums[j], nums[i]}

=> the only possible doubles are when nums[k], nums[i] or nums[j] repeats
themselves we skip the same nums[i] (only first one consider)
=> the only possible doubles now are when nums[i] or nums[j] repeats themselves
But if we found new {nums[k], nums[i], nums[j]}
we skip all equal nums[i]
(actually we can skip nums[i] or nums[j], cause they can never be there in the
output, cause this is repetition, but we don't need to: when nums[i] will
increase the result is not nums[k] + nums[i] + nums[j] => we will move j
definetely to the left => therefore everything is already checked for nums[j]
and will be skipped)
**/

using namespace std;

vector<vector<int>> threeSum(vector<int> &nums) {
  vector<vector<int>> result;
  // sorting values
  sort(nums.begin(), nums.end());

  // iterate over all nums[k]
  for (int k = 0; k + 1 < nums.size(); ++k) {
    bool found = false;
    int i = k + 1;

    // size is at least 1
    int j = nums.size() - 1;

    if (k > 0 && nums[k] == nums[k - 1]) {
      continue;
    }

    while (i != j) {
      if (nums[i - 1] == nums[i] && found) {
        ++i;
        continue;
      }
      // cout << i << " " << j << " " << k << "\n";
      if (nums[i] + nums[j] < -nums[k]) {
        ++i;
        found = false;
      } else if (nums[i] + nums[j] > -nums[k]) {
        --j;
        found = false;
        // such value exists
      } else if (nums[i] + nums[j] == -nums[k]) {
        vector<int> answer = {nums[i], nums[j], nums[k]};
        result.push_back(answer);
        ++i;
        found = true;
      }
    }
  }

  return result;
}

int main() {

  vector<int> nums = {-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6};
  vector<vector<int>> result = threeSum(nums);
  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << " ";
    }
    cout << "\n";
  }
}