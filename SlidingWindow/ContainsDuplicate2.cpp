#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  bool containsNearbyDuplicate(vector<int> &nums, int k) {
    unordered_set<int> slide(nums.begin(), min(nums.end(), nums.begin() + k));
    size_t i = 0;
    while (i + k < nums.size()) {
      if (static_cast<int>(slide.size()) < k) {
        return true;
      }
      slide.erase(nums[i]);
      slide.insert(nums[i + k]);
      ++i;
    }

    return slide.size() < min(static_cast<size_t>(k), nums.size() - i);
  }
};

int main() {
  vector<int> a = {1, 2, 3, 1};
  int k = 3;
  cout << Solution().containsNearbyDuplicate(a, k) << "\n";
}