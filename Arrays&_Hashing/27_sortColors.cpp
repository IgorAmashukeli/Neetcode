/**Given an array nums with n objects colored red, white, or blue, sort them
in-place so that objects of the same color are adjacent, with the colors in the
order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and
blue, respectively.

You must solve this problem without using the library's sort function.



Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]


Constraints:

n == nums.length
1 <= n <= 300
nums[i] is either 0, 1, or 2.


Follow up: Could you come up with a one-pass algorithm using only constant extra
space?

idea: bucket sort with k = 3
time: O(n)
space: O(k) = O(1)
**/

#include <cstddef>
#include <vector>

using namespace std;

void sortColors(vector<int> &nums) {
  size_t count_red = 0;
  size_t count_white = 0;
  size_t count_blue = 0;

  // count colors
  for (size_t i = 0; i < nums.size(); ++i) {
    if (nums[i] == 0) {
      count_red++;
    } else if (nums[i] == 1) {
      count_white++;
    } else if (nums[i] == 2) {
      count_blue++;
    }
  }

  for (size_t i = 0; i < count_red; ++i) {
    nums[i] = 0;
  }

  for (size_t i = count_red; i < count_red + count_white; ++i) {
    nums[i] = 1;
  }

  for (size_t i = count_red + count_white;
       i < count_red + count_white + count_blue; ++i) {
    nums[i] = 2;
  }
}