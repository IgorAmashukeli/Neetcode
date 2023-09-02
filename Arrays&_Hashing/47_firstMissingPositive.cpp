/**Given an unsorted integer array nums, return the smallest missing positive
integer.

You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary
space.



Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.


Constraints:

1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1

idea:

1) only values [1, n + 1] could be first missing
(cause, otherwise array contains more than n values)

2) iterate from 1 to n, check if value exists in vector, increment,
otherwise return this missing value

3) to save the values in [1, n], we notice it is just almoust [0, n - 1] range,
=> we will use indicies

4) the only values to encode are positive => non positive are no interest

5) first we unify all non positive to be -1

6) now we have -1 and positives

7) now for each existing index i in range 0 - n-1 we need to change the a[i]
to mark it

8) we change a[i] to - a[i] - 1
now, positive will be <-1 (there is no overflow, because of complementary code),
-1 will be 0

9) to avoid changing twice, we check, if the value to change is already < -1 or
0
=> it means it was changed before

10) if we encounter changed value and want to restore original to try to modify
by the index, we do inverse -k-1

11) after modifying the array, we can find first missing positive

**/

#include <cassert>
#include <vector>

using namespace std;

// decode
int decode(int value) {
  if (value < -1 || value == 0) {
    value = -value - 1;
  }
  return value;
}

// encode
void insert(vector<int> &nums, int value) {
  int index = value - 1;

  nums[index] = -nums[index] - 1;
}

bool find(vector<int> &nums, int value) {
  int index = value - 1;
  return (nums[index] < -1 || nums[index] == 0);
}

int firstMissingPositive(vector<int> &nums) {

  // convert all non-positive to -1
  // we are not interested in them
  for (size_t i = 0; i < nums.size(); ++i) {
    if (nums[i] <= 0) {
      nums[i] = -1;
    }
  }

  // now we have -1 for all non-positive and positive
  // idea: range is [-2^32 - 1, 2^32]
  // => mapping k -> - k - 1 is legal for positive numbers
  // -1 -> - (-1) - 1 is 0
  //
  // each number in range [1, n] is "kind of index"
  // => by a_i we get index a_i - 1 => a[a_i - 1] is value
  // we mark this value by mapping to - k - 1
  // if the value is already -k-1 (< -1 or 0) => then we do nothing
  // if out a_i is suddenly -k-1 or 0 => we get original a_i
  // by doing -k - 1 again (-0 - 1 = -1; -(-k-1)-1 = k)
  // thus, we will not mark twice
  // marking value doesn't overlap with values range, which
  // is either positive or -1
  // if we encounter -1, we do noting
  // if we encounter positive > n, we do nothing
  // => if we encounter 0, original value was -1 => we do nothing

  int n = nums.size();

  for (size_t i = 0; i < nums.size(); ++i) {
    // get original value (-1 or positive)
    int cur_value = decode(nums[i]);

    // do nothing
    if (cur_value == -1 || cur_value > n) {
      continue;
    }

    // now value is in range [1, n], it is index
    assert(cur_value >= 1 && cur_value < n);

    // now encode the value by this index

    if (!find(nums, cur_value)) {
      insert(nums, cur_value);
    }
  }

  // now let's find the first missing positive value:

  // iterate
  int first_missing = 1;
  for (; first_missing < n + 1; ++first_missing) {
    if (!find(nums, first_missing)) {
      return first_missing;
    }
  }

  // now first missing is n + 1 => all [1, n] were in array => answer is n + 1
  assert(first_missing == n + 1);

  return first_missing;
}