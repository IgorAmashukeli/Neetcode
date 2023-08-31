/**Given an integer array nums and an integer k, return true if nums has a good
subarray or false otherwise.

A good subarray is a subarray where:

its length is at least two, and
the sum of the elements of the subarray is a multiple of k.
Note that:

A subarray is a contiguous part of the array.
An integer x is a multiple of k if there exists an integer n such that x = n *
k. 0 is always a multiple of k.


Example 1:

Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up
to 6. Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements
sum up to 42. 42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false


Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= sum(nums[i]) <= 2^31 - 1
1 <= k <= 2^31 - 1

**/

#include <unordered_map>
#include <vector>

using namespace std;

bool checkSubarraySum(vector<int> &nums, int k) {
  // vector of positions of prefixes:
  // 0...k-1 -> remainders of k -> last positions, where such prefix was,
  // ending on i - 2, cause we need length 2
  // -1 - empty
  // -2 - not found

  unordered_map<int, int> positions;
  int cur_prefix = 0;
  for (int i = 0; i < nums.size(); ++i) {

    // update prefix
    cur_prefix += nums[i];

    // check if such sum exists, return true, else try to find
    if (positions.find(cur_prefix % k) != positions.end() &&
        positions[cur_prefix % k] <= i - 2) {
      return true;
    }

    // position of i - 1 will be needed on i + 1
    positions[(cur_prefix - nums[i]) % k] = i - 1;
  }

  return false;
}