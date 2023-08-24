/**
https://leetcode.com/problems/product-of-array-except-self/

Given an integer array nums, return an array answer such that answer[i] is
equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit
integer.

You must write an algorithm that runs in O(n) time and without using the
division operation.



Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]


Constraints:

2 <= nums.length <= 10^5
-30 <= nums[i] <= 30
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit
integer.


Follow up: Can you solve the problem in O(1) extra space complexity? (The output
array does not count as extra space for space complexity analysis.)

idea: calculate sufixes in array, calculate prefix on each iteration as a
variable
time: O(n)
space: O(1)
**/

#include <cstddef>
#include <vector>

using namespace std;

vector<int> productExceptSelf(vector<int> &nums) {
  vector<int> answer;

  // if nums vector is empty, return empty answer
  if (nums.size() == 0) {
    return answer;
  }

  // calculate sufixes
  answer.resize(nums.size());
  answer[nums.size() - 1] = 1;
  for (size_t i = 1; i < nums.size(); ++i) {
    size_t j = nums.size() - i - 1;
    answer[j] = answer[j + 1] * nums[j + 1];
  }

  // now answer[j] = sufix from j + 1 to n - 1

  // multiply by prefix
  // prefix on i iteration equals prefix from 0 to i - 1
  // (if i == 0 => prefix equals 1)
  int prefix = 1;
  for (size_t i = 0; i < answer.size(); ++i) {
    answer[i] *= prefix;
    prefix *= nums[i];
  }

  // return answer
  return answer;
}