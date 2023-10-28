#include <iostream>
#include <vector>

using namespace std;

/**Given an integer array nums, move all 0's to the end of it while maintaining
the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.



Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]


Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1


Follow up: Could you minimize the total number of operations done?

idea: two pointers:
 1) from start
 2) from non-zero elements
first pointer (i) shifts only if written new value
second pointer (j) shifts everytime

Therefore, i <= j => there is no coliision
We can swap two elements, cause:
if i == j => then nothing changes
if i < j => nums[i] starts being correct value
nums[j] now is some strange value
(but j will never reach nums[j] and will not copy this to the start)
(when i reaches this value, new nums[j_new] will replace it)
(it will be either new value or 0, which is true)
**/

void moveZeroes(vector<int> &nums) {
  size_t i = 0;
  size_t j = 0;

  // copy non-zero elements to the start
  // and copy zeroes to the elements, where there were non-zeroes
  while (j != nums.size()) {
    if (nums[j] != 0) {
      swap(nums[i], nums[j]);
      ++i;
    }
    ++j;
  }
}
