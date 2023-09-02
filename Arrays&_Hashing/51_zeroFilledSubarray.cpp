/**Given an integer array nums, return the number of subarrays filled with 0.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [1,3,0,0,2,0,0,4]
Output: 6
Explanation:
There are 4 occurrences of [0] as a subarray.
There are 2 occurrences of [0,0] as a subarray.
There is no occurrence of a subarray with a size more than 2 filled with 0.
Therefore, we return 6. Example 2:

Input: nums = [0,0,0,2,0,0]
Output: 9
Explanation:
There are 5 occurrences of [0] as a subarray.
There are 3 occurrences of [0,0] as a subarray.
There is 1 occurrence of [0,0,0] as a subarray.
There is no occurrence of a subarray with a size more than 3 filled with 0.
Therefore, we return 9. Example 3:

Input: nums = [2,10,2019]
Output: 0
Explanation: There is no subarray filled with 0. Therefore, we return 0.


Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

idea:
for each zero full subarray count number of zeroes
for each k-length subarray full of zeroes, number of subarrays
is k * (k + 1) / 2

time: O(n)
space: O(1)


**/

#include <cstddef>
#include <sys/types.h>
#include <vector>

using namespace std;

long long zeroFilledSubarray(vector<int> &nums) {
  // number of subarrays
  u_int64_t count = 0;

  // state variable
  bool isZero = true;

  // count of zeroes in current subarray
  u_int64_t current_count = 0;

  // iterate through arrays
  for (size_t i = 0; i < nums.size(); ++i) {

    // found zero
    if (nums[i] == 0) {

      // update state, if needed
      if (!isZero) {
        isZero = true;
      }

      // add to count
      current_count += 1;

      // found non-zero
    } else {

      // first non-zero
      if (isZero) {
        // update state
        isZero = false;

        // add the number of subarrays in this subarray
        count += (current_count * (current_count + 1)) / 2;

        // restore variable for next zero subarrays
        current_count = 0;
      }
    }
  }

  // add the number of subarrays, if last values were zeroes
  if (isZero) {
    count += (current_count * (current_count + 1)) / 2;
  }

  return count;
}