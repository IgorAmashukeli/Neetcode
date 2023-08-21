#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int> &nums, int val) {
  // if nums is empty, answer is 0
  if (nums.size() == 0) {
    return 0;
  }

  // find first non-value position in nums
  int i = 0;
  int j = nums.size() - 1;
  while (j > 0 && nums[j] == val) {
    --j;
  }

  // swap value with non-value, if found
  while (i < j) {
    // if i is val and j is non value -> swap
    if (nums[i] == val && nums[j] != val) {
      swap(nums[i], nums[j]);
      i++;
      j--;
      // if i is is val -> j--;
    } else if (nums[i] == val) {
      j--;
      // if j is non val -> i ++
    } else {
      i++;
    }
  }

  // find nums[k] = val
  size_t k = 0;
  while (k < nums.size() && nums[k] != val) {
    ++k;
  }

  return k;
}
