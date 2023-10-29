/**You are given an array of integers nums and an integer target.

Return the number of non-empty subsequences of nums such that the sum of the
minimum and maximum element on it is less or equal to target. Since the answer
may be too large, return it modulo 109 + 7.



Example 1:

Input: nums = [3,5,6,7], target = 9
Output: 4
Explanation: There are 4 subsequences that satisfy the condition.
[3] -> Min value + max value <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)
Example 2:

Input: nums = [3,3,6,8], target = 10
Output: 6
Explanation: There are 6 subsequences that satisfy the condition. (nums can have
repeated numbers). [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6] Example 3:

Input: nums = [2,3,3,4,6,7], target = 12
Output: 61
Explanation: There are 63 non-empty subsequences, two of them do not satisfy the
condition ([6,7], [7]). Number of valid subsequences (63 - 2 = 61).


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= target <= 10^6

idea: time: 0(n log n)
      space: O(1)
min + max <= target => max <= target - min
sort the array
select min (in the loop)
and for each value of min find the number of elements
that can be there in the set
if it is k => 2^k is the number of sets
(don't forget that empty set is not included)
use fast calculation of exponent or go from
the biggest min, and increase k, so you
don't need to recalculate 2^k from start
don't forget to use modulo

**/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numSubseq(vector<int> &nums, int target) {
  // modulo
  int modulo = 1'000'000'000 + 7;

  // count
  int count = 0;

  // sort values
  sort(nums.begin(), nums.end());

  int previous_others = 0;
  int previous_power = 1;

  int left = nums.size() - 1;

  while (nums[left] + nums[left] > target) {
    --left;
  }

  if (left < 0) {
    return 0;
  }

  // right index
  int right = left;

  // iterate over nums
  for (; left >= 0; --left) {
    int value = nums[left];

    // max value that can be added to the subsequence
    int max = target - value;

    // find index of this value
    while (right + 1 < nums.size() && nums[right + 1] <= max) {
      ++right;
    }

    // there are elements, not bigger than minimum
    // such that we can take them into subsequence
    // number of such elements
    int others = right - left;

    // count += 2^others

    // power = 2^others

    // but we already has previous value

    int power = previous_power;

    for (int i = 0; i < others - previous_others; ++i) {
      power %= modulo;
      power += power;
      power %= modulo;
    }

    previous_others = others;
    previous_power = power;

    count %= modulo;
    count += power;
    count %= modulo;
  }

  return count;
}

int main() {
  vector<int> nums = {1};
  int target = 1;
  cout << numSubseq(nums, target) << "\n";
}