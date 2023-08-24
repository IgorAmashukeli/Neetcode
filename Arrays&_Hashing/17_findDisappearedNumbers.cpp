/**
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

Given an array nums of n integers where nums[i] is in the range [1, n],
return an array of all the integers in the range [1, n] that do not appear in
nums.



Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
Example 2:

Input: nums = [1,1]
Output: [2]


Constraints:

n == nums.length
1 <= n <= 10^5
1 <= nums[i] <= n


Follow up: Could you do it without extra space and in O(n) runtime? You may
assume the returned list does not count as extra space.

idea: value are in range [1, n] -> we can use indicies [0, n - 1]
to map values

we will add 10^9 to nums[i - 1], if we found i in array

time: O(n)
space: O(1s)
**/

#include <algorithm>
#include <vector>

using namespace std;

vector<int> findDisappearedNumbers(vector<int> &nums) {

  // this number doesn't exist: this is 10^9
  int n = 1000000000;

  for (size_t i = 0; i < nums.size(); ++i) {

    // take original nums[i]
    int original_val = nums[i];
    if (original_val > n) {
      original_val = nums[i] - n;
    }

    // if wasn't added: add 10^9 to the value by that index to know, this index
    // was found
    int value_to_change = nums[original_val - 1];
    if (value_to_change < n) {
      nums[original_val - 1] += n;
    }
  }

  vector<int> answer;
  for (size_t i = 0; i < nums.size(); ++i) {
    if (nums[i] < n) {
      answer.push_back(i + 1);
    }
  }

  return answer;
}