/**
https://leetcode.com/problems/can-place-flowers/

You have a long flowerbed in which some of the plots are planted, and some
are not. However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and
1 means not empty, and an integer n, return true if n new flowers can be planted
in the flowerbed without violating the no-adjacent-flowers rule and false
otherwise.



Example 1:

Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
Example 2:

Input: flowerbed = [1,0,0,0,1], n = 2
Output: false


Constraints:

1 <= flowerbed.length <= 2 * 10^4
flowerbed[i] is 0 or 1.
There are no two adjacent flowers in flowerbed.
0 <= n <= flowerbed.length

idea: put 1 instead of zero, if we can
(cause,
for each 10000...00001, the best solution is 10101...10101
for each 000...001, the best solution is 101...101
if flowerbed is 000..000 and even, the best solution is 101...010
if flowerbed is 000..000 and odd, the best solution is 101...101
)
time: O(n)
space: O(1)

**/

#include <cstddef>
#include <vector>

using namespace std;

bool canPlaceFlowers(vector<int> &flowerbed, int n) {
  int count = 0;

  // iterate
  for (size_t i = 0; i < flowerbed.size(); ++i) {
    // if valid
    if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) &&
        (i + 1 == flowerbed.size() || flowerbed[i + 1] == 0)) {
      // put
      flowerbed[i] = 1;

      // increase number of put
      count++;
    }
  }

  // check if number of put is at least the number of required
  return count >= n;
}