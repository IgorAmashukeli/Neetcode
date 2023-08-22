/**Given an array of integers nums, sort the array in ascending order and return
it.

You must solve the problem without using any built-in functions in O(nlog(n))
time complexity and with the smallest space complexity possible.



Example 1:

Input: nums = [5,2,3,1]
Output: [1,2,3,5]
Explanation: After sorting the array, the positions of some numbers are not
changed (for example, 2 and 3), while the positions of other numbers are changed
(for example, 1 and 5). Example 2:

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
Explanation: Note that the values of nums are not necessairly unique.


Constraints:

1 <= nums.length <= 5 * 10^4
-5 * 104 <= nums[i] <= 5 * 10^4

idea: simple Merge Sort with buffer
time: O(n log n)
space: O(n)
**/

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// merge [i, left_end) and [j, right_end)
void merge(vector<int> &nums, vector<int> &buffer, size_t i, size_t left_end,
           size_t j, size_t right_end) {

  size_t k = 0;
  size_t start = i;

  // merge untill reach left_end or right_end
  while (i < left_end || j < right_end) {
    // all ends are not reached and left is less, or right end is reached =>
    // choose left
    if ((i < left_end && j < right_end && nums[i] < nums[j]) ||
        j >= right_end) {
      buffer[k] = nums[i];
      ++i;
      ++k;
      // otherwise choose right
    } else {
      buffer[k] = nums[j];
      ++j;
      ++k;
    }
  }

  // now k equals buffer size, we can copy from buffer back to array again

  for (size_t s = start; s < start + k; ++s) {
    nums[s] = buffer[s - start];
  }
}

// mergeSort [left, right)
void mergeSort(vector<int> &nums, vector<int> &buffer, size_t left,
               size_t right) {

  // empty or singleton part, nothing to do
  if (right - left <= 1) {
    return;
  }

  // mid value, remember about overflowing
  size_t mid = left + (right - left) / 2;

  // sort left part
  mergeSort(nums, buffer, left, mid);

  // sort right part
  mergeSort(nums, buffer, mid, right);

  // merge
  merge(nums, buffer, left, mid, mid, right);
}

// mergeSort
vector<int> sortArray(vector<int> &nums) {
  vector<int> buffer;
  buffer.resize(nums.size());

  // mergeSort [0, nums.size())
  mergeSort(nums, buffer, 0, nums.size());
  return buffer;
}

int main() {
  vector<int> nums = {5, 2, 7, 3};
  vector<int> buffer = sortArray(nums);
  for (size_t i = 0; i < nums.size(); ++i) {
    cout << nums[i] << " ";
  }
  cout << "\n";
}