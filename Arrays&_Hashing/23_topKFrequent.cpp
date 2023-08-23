/**Given an integer array nums and an integer k, return the k most frequent
elements. You may return the answer in any order.



Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]


Constraints:

1 <= nums.length <= 10^5
-104 <= nums[i] <= 10^4
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.


Follow up: Your algorithm's time complexity must be better than O(n log n),
where n is the array's size.


idea: find counts, using hashmap, restore reversed counts: 2D vector,
get k values, going backwards
time: O(n)
space: O(n)
**/

#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k) {

  // simple counts
  unordered_map<int, int> counts;
  for (size_t i = 0; i < nums.size(); ++i) {
    counts[nums[i]]++;
  }

  // reversed counts, has size O(|nums.size()|)
  vector<vector<int>> reversed_counts;
  reversed_counts.resize(nums.size() + 1);
  for (const auto &[elem, count] : counts) {
    reversed_counts[count].push_back(elem);
  }

  // top k frequent elements

  // going backwards from most frequent to less frequent, pushback to answer
  vector<int> answer;

  for (size_t i = 0; i < reversed_counts.size(); ++i) {
    size_t j = reversed_counts.size() - i - 1;

    // found all k elements
    if (k == 0) {
      break;
    }

    for (int elem : reversed_counts[j]) {
      // found all k elements
      if (k == 0) {
        break;
      }

      // add element to answer
      answer.push_back(elem);
      --k;
    }
  }

  return answer;
}