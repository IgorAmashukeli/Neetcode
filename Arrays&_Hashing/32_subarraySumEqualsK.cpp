#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

int subArraySum(const vector<int> &nums, int K) {
  // key: prefixsum, value: number of such prefix sums
  unordered_map<int, int> sum_counts;

  // number of subArrays with sum K
  int count = 0;

  // current prefix sum
  int prefix_sum = 0;

  for (size_t i = 0; i < nums.size(); ++i) {

    // update counts of this prefix sum
    sum_counts[prefix_sum]++;

    // check if sum_counts contains prefix_sum
    if (sum_counts.contains(prefix_sum - K)) {
      ++count;
    }

    // update prefix sum
    prefix_sum += nums[i];
  }

  return count;
}