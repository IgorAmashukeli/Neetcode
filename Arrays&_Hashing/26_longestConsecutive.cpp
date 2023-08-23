/**Given an unsorted array of integers nums, return the length of the longest
consecutive elements sequence.

You must write an algorithm that runs in O(n) time.



Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
Therefore its length is 4. Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9


Constraints:

0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

idea: find start element of consequent sequence
time: O(n)
space: O(n)

**/

#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int longestConsecutive(const vector<int> &nums) {

  // set of elements
  unordered_set<int> elements;
  for (size_t i = 0; i < nums.size(); ++i) {
    elements.insert(nums[i]);
  }

  // set of start elements
  unordered_set<int> start_elements;
  for (size_t i = 0; i < nums.size(); ++i) {
    if (!elements.contains(nums[i] - 1)) {
      start_elements.insert(nums[i]);
    }
  }

  // try to find consequent sequnce
  int longest_length = 1;
  for (int start_value : start_elements) {
    int cur_value = start_value;
    int length = 1;

    // find the length of sequence
    while (elements.contains(cur_value)) {
      ++cur_value;
      ++length;
    }

    // if sequence is biggest, update maximum
    if (length > longest_length) {
      longest_length = length;
    }
  }

  return longest_length;
}