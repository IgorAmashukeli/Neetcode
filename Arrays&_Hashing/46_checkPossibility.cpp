/**Given an array nums with n integers, your task is to check if it could become
non-decreasing by modifying at most one element.

We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i
(0-based) such that (0 <= i <= n - 2).



Example 1:

Input: nums = [4,2,3]
Output: true
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:

Input: nums = [4,2,1]
Output: false
Explanation: You cannot get a non-decreasing array by modifying at most one
element.


Constraints:

n == nums.length
1 <= n <= 10^4
-10^5 <= nums[i] <= 10^5

idea: count number of wrong ordered
0 => ok
> 1 => not ok
1 => check if we can correct it: either decrease first, or increase second

time: O(n)
space: O(1)

**/

#include <vector>

using namespace std;

bool checkPossibility(vector<int> &nums) {
  // count number of wrong ordered consecutive pairs
  int count = 0;

  // index of first element in wrong ordered consecutive pair
  // (if the pair is single)
  int dec_ind = 0;

  // iteration through nums
  for (size_t i = 0; i + 1 < nums.size(); ++i) {

    // find wrong ordered pair
    if (nums[i] > nums[i + 1]) {

      // remember the start index
      dec_ind = i;

      // count number of wrong ordered consecutive pairs
      count++;
    }
  }

  // if the number is > 1 => we can't change two numbers
  // changing one will not eliminate all the wrong ordered pairs
  if (count > 1) {
    return false;
  }

  // if the number is 0 => there is nothing to do
  if (count == 0) {
    return true;
  }

  // there is one wrong ordered consecutive pair

  // it is in the start of array =>
  // => put array[0] = array[1]
  if (dec_ind == 0) {
    return true;
  }

  // it is in the end of array =>
  // => put array[n - 2] = array[n - 1]
  if (dec_ind + 1 == nums.size() - 1) {
    return true;
  }

  // it is in the middle
  // => we put either array[i] = array[i - 1]
  // or array[i + 1] = array[i + 2]

  // we can't increase and decrease more
  // then we check, which way makes the tuple correct ordered

  // first way is OK
  if (nums[dec_ind - 1] <= nums[dec_ind + 1]) {
    return true;
  }

  if (nums[dec_ind] <= nums[dec_ind + 2]) {
    return true;
  }

  // we can't do both ways => false
  return false;
}