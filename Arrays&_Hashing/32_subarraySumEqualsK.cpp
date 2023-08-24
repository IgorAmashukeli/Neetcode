/**Given an array of integers nums and an integer k, return the total number of
subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2


Constraints:

1 <= nums.length <= 2 * 10^4
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7

idea:
find prefixes

remember in hasmap, to know, if cur prefix sum - K was found before
edge case: K == 0 -> it doesn't mean it is prev prefix sum, it can be current
Therefore, we subtract all found cur sums, cause they mean, the subarray is
empty

time: O(n)
space: O(n)

**/

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int subarraySum(const vector<int> &nums, int K) {
  // key: prefixsum, value: number of such prefix sums
  unordered_map<int, int> sum_counts;

  // number of subArrays with sum K
  int count = 0;

  // current prefix sum
  int prefix_sum = 0;

  for (size_t i = 0; i < nums.size(); ++i) {

    // update counts of this prefix sum

    sum_counts[prefix_sum]++;

    // check if sum_counts contains prefix_sum
    if (sum_counts.contains(prefix_sum - K)) {
      count += sum_counts[prefix_sum - K];
    }

    // update prefix sum
    prefix_sum += nums[i];
  }

  // check last prefix sum
  if (sum_counts.contains(prefix_sum - K)) {
    count += sum_counts[prefix_sum - K];
  }

  // however, if K == 0
  if (K == 0) {
    count -= (nums.size() + 1);
  }

  return count;
}

int main() {
  vector<int> nums = {-1, -1, 1};
  int K = 0;
  cout << subarraySum(nums, K) << "\n";
}