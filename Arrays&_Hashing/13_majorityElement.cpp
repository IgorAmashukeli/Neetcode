/**
https://leetcode.com/problems/majority-element/

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You
may assume that the majority element always exists in the array.



Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2


Constraints:

n == nums.length
1 <= n <= 5 * 10^4
-109 <= nums[i] <= 10^9

idea: Boyer - Moore priority algorithm
proof of correctness:
We use two variables

-the maxfreq candidate
-the frequency

Let's proof that all elements after i-th iterations will be paired
The only element that is not paired is the element that will be stored in
maxfreq candidate, and we have frequency copies of unpaired element

i = 0 =>
maxfreq candidate = nums[0]
frequency = 1

all elements are nums[0], all other elements are paired
nums[0] is not paired so far, and number of copies is 1

i -> i + 1 =>
if frequency was 0 => by induction all previous elements, except maxfreq
cand are paired and there are 0 copies of unpaired maxfreq cand => all elements
are paired now we meet nums[i + 1], it is not paired => and the copy of unpaired
is 1

=> induction is true =>

if frequncy was > 0 => by induction all previous elements, except maxfreq
cand are paired and there are frequency copies of unpaired maxfreq cand



if maxfreq cand = nums[i + 1] => the number of copies of maxfreq cand should be
increased and we do so in algorithm

=> induction is true


if maxfreq cand != nums[i + 1] => the number of copies of maxfreq cand should be
decreased cause we pair maxfreq cand with nums[i + 1] => we do so in algorithm

 => induction is true

In the end we have maxfreq equal the element, that can't be paired and all
others can be paired But the only element, that can't be paired is majority
element, cause it is guaranteed, it exists

=> maxfreq cand = majority element


time: O(n)
space: O(1)


Follow-up: Could you solve the problem in linear time and in O(1) space?**/

#include <cstdint>
#include <vector>

using namespace std;

int majorityElement(vector<int> &nums) {
  // it is guaranteed, that nums[i] is in [-10^9, 10^9] range
  int unpaired = INT32_MIN;

  // the number of unpaired copies
  int unpaired_copies = 0;

  for (size_t i = 0; i < nums.size(); ++i) {
    // all the element are paired with non equal
    if (unpaired_copies == 0) {
      // we create new unpaired, the count of unpaired is 1
      unpaired = nums[i];
      unpaired_copies = 1;
      // we found another copy of unpaired element
    } else if (unpaired == nums[i]) {
      unpaired_copies++;
      // we cross out one pair of non equal elements
    } else {
      unpaired_copies--;
    }
  }

  // unpaired store the only not paired element
  // it is guaranteed, we have majority element
  // => unpaired = majority element

  return unpaired;
}