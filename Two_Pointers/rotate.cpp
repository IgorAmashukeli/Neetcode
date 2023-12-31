#include <algorithm>
#include <iostream>
#include <vector>

/**Given an integer array nums, rotate the array to the right by k steps, where
k is non-negative.



Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]


Constraints:

1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5


Follow up:

Try to come up with as many solutions as you can. There are at least three
different ways to solve this problem. Could you do it in-place with O(1) extra
space?


idea: three different solutions:

first solution (rotate)

1) if k < n / 2 =>
 - swap first k with the last k
 - now we need to swap middle n - 2 * k with last k
    - reverse last k
    - reverse middle n - 2 * k
    - reverse last n - k
2) if k > n / 2
 - swap first n - k with the last n - l
 - now we need to swap fist n - k with the middle n - 2 * k
     - reverse first k
     - reverse middle n - 2 * k
     - reverse first n - k


another solution (rotate3)
let's observe that we need to swap first k with last n - k
    - reverse first k
    - reverse last n - k
    - reverse all elements


another solution (rotate2)
again let's observe that we need to swap first k with last n - k
    do recursive swapping
you need two functions for this

first function is equalSwap: swap two ranges of equal sizes together
    - this one is straigtforward

second function is bigSwap: swap two ranges of different sizes together
    - this one divides into cases
    - first: len1 < len2:
    [ ] [                ]
    Then swap first len1 with last len1, using equal swap
    [ ] [             ][ ]
    then observe, we need to swap the first with the second: do bigSwap on them

    - second: len1 > len2:
    [                 ][ ]
    Then swap len2 with last len2, using equal swap
    [ ] [             ][ ]
    then observe, we need to swap the second with the third: do bigSwap on them



**/

using namespace std;

// rotate array to the right
// first way to do it
// swap then reverse
void rotate(vector<int> &nums, int k) {
  k = k % nums.size();
  // nothing to do
  if (k == nums.size() || k == 0) {
    return;
  }

  // if k is less than a half of array
  // example
  // 1 2 3 4 5 6 7 8 9 10
  // k = 3
  if (k * 2 < nums.size()) {

    // swap k from the both sides
    // 8 9 10 4 5 6 7 1 2 3
    for (size_t i = 0; i < k; ++i) {
      swap(nums[i], nums[nums.size() - k + i]);
    }

    // reverse last k
    // 8 9 10 4 5 6 7 3 2 1
    for (size_t i = 0; i < k / 2; ++i) {
      swap(nums[nums.size() - k + i], nums[nums.size() - i - 1]);
    }

    // reverse middle n - 2k
    // 8 9 10 7 6 5 4 3 2 1
    for (size_t i = 0; i < (nums.size() - 2 * k) / 2; ++i) {
      swap(nums[k + i], nums[nums.size() - k - i - 1]);
    }

    // reverse last n - k (thus middle n - 2k and last k)
    // 8 9 10 1 2 3 4 5 6 7
    for (size_t i = 0; i < (nums.size() - k) / 2; ++i) {
      swap(nums[k + i], nums[nums.size() - i - 1]);
    }

    // if k is bigger than a half, n - k is less than a half
    // example
    // 1 2 3 4 5 6 7 8 9 10
    // k = 7
  } else {

    // example t = 3
    size_t t = nums.size() - k;

    // swap t from both sides
    // 8 9 10 4 5 6 7 1 2 3
    for (size_t i = 0; i < t; ++i) {
      swap(nums[i], nums[nums.size() - t + i]);
    }

    // reverse first t
    // 10 9 8 4 5 6 7 1 2 3
    for (size_t i = 0; i < t / 2; ++i) {
      swap(nums[i], nums[t - i - 1]);
    }

    // reverse middle n - 2 * t
    // 10 9 8 7 6 5 4 1 2 3
    for (size_t i = 0; i < (nums.size() - 2 * t) / 2; ++i) {
      swap(nums[t + i], nums[nums.size() - t - i - 1]);
    }

    // reverse first n - t
    // 4 5 6 7 8 9 10 1 2 3
    for (size_t i = 0; i < (nums.size() - t) / 2; ++i) {
      swap(nums[i], nums[nums.size() - t - i - 1]);
    }
  }
}

// swap of two equal chuncks of array
void equalSwap(vector<int> &nums, int len, int i, int j) {
  for (size_t k = 0; k < len; ++k) {
    swap(nums[i + k], nums[j + k]);
  }
}

void bigSwap(vector<int> &nums, int i, int len1, int j, int len2) {
  // if equal => do equal swap
  if (len1 == len2) {
    equalSwap(nums, len1, i, j);
    return;
  }

  // if first array is bigger than the second
  if (len1 > len2) {
    equalSwap(nums, len2, i, j);
    return bigSwap(nums, i + len2, len1 - len2, j, len2);
  }

  // if first array is smaller than the second
  if (len1 < len2) {
    equalSwap(nums, len1, i, j + len2 - len1);
    return bigSwap(nums, i, len1, j, len2 - len1);
  }
}

// second way to do it
// rotate with recursive swaps
void rotate2(vector<int> &nums, int k) {
  k = k % nums.size();

  // nothing to do
  if (k == nums.size() || k == 0) {
    return;
  }

  bigSwap(nums, 0, nums.size() - k, nums.size() - k, k);
}

// third way to do it
// no swaps, only reverses
void rotate3(vector<int> &nums, int k) {
  k = k % nums.size();

  // nothing to do
  if (k == 0 || k == nums.size()) {
    return;
  }

  // reverse array
  reverse(nums.begin(), nums.end());

  // reverse first k elements
  reverse(nums.begin(), nums.begin() + k);

  // reverse last n - k elements
  reverse(nums.begin() + k, nums.end());
}

int main() {
  vector<int> nums = {1};
  int k = 2;
  rotate3(nums, k);
  for (size_t i = 0; i < nums.size(); ++i) {
    cout << nums[i] << " ";
  }
  cout << "\n";
}