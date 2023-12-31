/**

https://leetcode.com/problems/contains-duplicate/

Given an integer array nums, return true if any value appears at least twice in
the array, and return false if every element is distinct.



Example 1:

Input: nums = [1,2,3,1]
Output: true
Example 2:

Input: nums = [1,2,3,4]
Output: false
Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true


Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

idea: use unordered_set
time: O(n) in average
**/

#include <unordered_set>
#include <vector>

using namespace std;

bool containsDuplicate(const vector<int> &nums) {
  unordered_set<int> num_set;
  for (const auto &num : nums) {
    if (num_set.contains(num)) {
      return true;
    } else {
      num_set.insert(num);
    }
  }
  return false;
}
