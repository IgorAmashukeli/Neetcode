#include <ios>
#include <iostream>
#include <unordered_set>
#include <vector>

// 219. Contains Duplicate II

// Given an integer array nums and an integer k, return true if there are two
// distinct indices i and j in the array such that nums[i] == nums[j] and abs(i
// - j) <= k.

// Example 1:

// Input: nums = [1,2,3,1], k = 3
// Output: true
// Example 2:

// Input: nums = [1,0,1,1], k = 1
// Output: true
// Example 3:

// Input: nums = [1,2,3,1,2,3], k = 2
//  Output: false

// Constraints:

// 1 <= nums.length <= 10^5
//-10^9 <= nums[i] <= 10^9
//  0 <= k <= 10^5

// idea: use sliding window of unordered set of size k + 1

using namespace std;

class Solution {
public:
  bool containsNearbyDuplicate(vector<int> &nums, int k) {
    unordered_set<int> slide(nums.begin(),
                             min(nums.end(), nums.begin() + k + 1));
    size_t i = 0;
    while (i + k + 1 < nums.size()) {
      if (static_cast<int>(slide.size()) < k + 1) {
        return true;
      }
      slide.erase(nums[i]);
      slide.insert(nums[i + k + 1]);
      ++i;
    }

    return slide.size() < min(static_cast<size_t>(k + 1), nums.size() - i);
  }
};

int main() {
  vector<int> a = {1, 2, 3, 1, 2, 3};
  int k = 2;
  cout << boolalpha << Solution().containsNearbyDuplicate(a, k) << "\n";
}