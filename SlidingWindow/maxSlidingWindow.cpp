#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

/**
239. Sliding Window Maximum
You are given an array of integers nums, there is a sliding window of size k
which is moving from the very left of the array to the very right. You can only
see the k numbers in the window. Each time the sliding window moves right by one
position.

Return the max sliding window.



Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]


Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length

We can use map (binary search red black tree) of unordered sets of positions of
elements when we shift a sliding window:
- the position is added to the set (if it was empty)
- the position is removed from the set, if the set is empty

the biggest element of a sliding window is map.begin()->first

The algorithm works in O(n log n)
**/

class Solution {

public:
  vector<int> maxSlidingWindow(const vector<int> &nums, int k) {
    if (k > nums.size()) {
      return {};
    }
    vector<int> answer;
    map<int, unordered_set<size_t>, greater<int>> positions;
    for (size_t i = 0; i < k; ++i) {
      if (!positions.contains(nums[i])) {
        positions[nums[i]] = {i};
      } else {
        positions[nums[i]].insert(i);
      }
    }

    size_t i = 0;
    while (i + k < nums.size()) {
      answer.push_back(positions.begin()->first);
      positions[nums[i + k]].insert(i + k);
      positions[nums[i]].erase(i);
      if (positions[nums[i]].empty()) {
        positions.erase(nums[i]);
      }
      ++i;
    }
    answer.push_back(positions.begin()->first);

    return answer;
  }
};

int main() {
  vector<int> input = {1};
  int k = 1;
  vector<int> answers = Solution().maxSlidingWindow(input, k);
  for (int answer : answers) {
    cout << answer << " ";
  }
  cout << "\n";
}