/**
https://leetcode.com/problems/sort-colors/

Given an array nums with n objects colored red, white, or blue, sort them
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

idea:
The Dutch national flag problem!

unsymmetric three!!! pointer technique remove_if to both sides
 - l pointer - all elements to the left are zeroes
 - r pointer - all elements to the right are twos
 - i pointer - current value to change with left or right portion

 - we mantain:
 everything in [l, r] should be 1

 First statement:
 l pointer will always encounter 0 or 1, cause i already looked to the same
value. If the value was 2, we put in the right portion of array.

 r pointer can encounter 1, 2 or 0!!!!, cause i is to the left of r, and we
could not reach this value to put it in the left portion of array.

 i pointer can encouter 0, 1 or 2

 Therefore wrong solution:

 while (mid <= r) do:

 - nums[mid] = 0 -> swap with l, increment l, mid
 - nums[mid] = 1 -> increment mid
 - nums[mid] = 2 -> swap with r, decrement r, mid

cause, 0 getting inside of the middle part from right will destroy mantaining
condition therefore, we need to propogate it again to l part and not increment
mid pointer

Therefore correct solution:

while (mid <= r) do:

 - nums[mid] = 0 -> swap with l, increment l, mid
 - nums[mid] = 1 -> increment mid
 - nums[mid] = 2 -> swap with r, decrement r


average time: O(n)
space: O(k) = O(1)
number of linear passes: 1
**/

#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;

void sortColors(vector<int> &nums) {
  if (nums.size() == 0) {
    return;
  }
  int l = 0;
  int m = 0;
  int r = nums.size() - 1;
  while (m <= r) {
    if (nums[m] == 0) {
      swap(nums[l], nums[m]);
      ++l;
      ++m;
    } else if (nums[m] == 1) {
      ++m;
    } else if (nums[m] == 2) {
      swap(nums[m], nums[r]);
      --r;
    }
  }
}