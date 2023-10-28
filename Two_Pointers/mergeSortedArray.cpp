#include <algorithm>
#include <iostream>
#include <vector>

/**You are given two integer arrays nums1 and nums2, sorted in non-decreasing
order, and two integers m and n, representing the number of elements in nums1
and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be
stored inside the array nums1. To accommodate this, nums1 has a length of m + n,
where the first m elements denote the elements that should be merged, and the
last n elements are set to 0 and should be ignored. nums2 has a length of n.



Example 1:

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming
from nums1. Example 2:

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].
Example 3:

Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to
ensure the merge result can fit in nums1.


Constraints:

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-10^9 <= nums1[i], nums2[j] <= 10^9


Follow up: Can you come up with an algorithm that runs in O(m + n) time?

idea: O(1) memory, O(m + n) time

reverse first m elements in nums1

then start writing result in nums1, going from the end,
copying from nums1 and nums2, using two pointers

Let's proof that there could never be a collision problem with three pointers
Suppose,
i is pointer for the first array to read, going from the m - 1 position to 0
j is pointer for the second array to read, going from the 0 position to n - 1
k is pointer for the first array to write, going from the m + n - 1 position to
0

Only 2 pointer that can collide are i and k, cause j is pointer for the second
array These 2 pointers can collide if and only if k starts being less or equal
than i, thus erasing not copied elements from nums1.

Let's consider 2 cases.
1) 2 array was already completely copied to the nums1
2) 2 array wasn't completely copied to the nums1

1) If 2 array was already completely copied to the nums1, then
if k starts being equal to i, then all the elements will not change

That means the 2 array will stay the same and therefore the output will be
correct (in reversed order, then we will reverse it again)


2) If 2 array wasn't completely copied to the nums1, then
if k starts being equal or less than i, that means, that there are
k + 1 elements (0...k) to copy from the first array
and > 0 elements to copy from the second array.
But there are exactly k + 1 (0...k) places left.
All other (k+1...m+n-1) places are used and used correctly (in reversed order)
That means there is no place for m + n ordered elements.
But this is not true, cause there are m + n elements at the start.
Therefore this can never happen

That means that the output is always correct.
**/

using namespace std;

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {

  // nothing to merge
  if (n == 0) {
    return;
  }

  // nothing in nums1
  if (m == 0) {
    for (int i = 0; i < n; ++i) {
      nums1[i] = nums2[i];
    }
  }

  // reversing nums1
  for (int l = 0; l < m / 2; ++l) {
    swap(nums1[l], nums1[m - l - 1]);
  }

  // indicies of nums1, nums2 and result array nums1
  int i = m - 1;
  int j = 0;
  int k = m + n - 1;

  while (k >= 0) {

    // copying from nums1
    if ((i >= 0 && j < n && nums1[i] <= nums2[j]) || (j >= n)) {
      nums1[k] = nums1[i];
      --i;
      --k;

      // copying from nums2
    } else if ((i >= 0 && j < n && nums1[i] >= nums2[j]) || (i <= 0)) {
      nums1[k] = nums2[j];
      ++j;
      --k;
    }
  }

  // reversing nums1
  for (int l = 0; l < (m + n) / 2; ++l) {
    swap(nums1[l], nums1[m + n - l - 1]);
  }
}

int main() {
  vector<int> nums1 = {0};
  vector<int> nums2 = {1};
  int m = 1;
  int n = 1;
  merge(nums1, m, nums2, n);
  for (int i = 0; i < m + n; ++i) {
    cout << nums1[i] << " ";
  }
  cout << "\n";
}