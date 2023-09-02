#include <vector>

using namespace std;

int arraySign(vector<int> &nums) {
  // number of minuses
  int count_neg = 0;
  for (int num : nums) {
    // add number of minuses
    if (num < 0) {
      ++count_neg;

      // encounter 0 => return 0
    } else if (num == 0) {
      return 0;
    }
  }

  // remainder 0 => 1 - 2 * 0 = 1
  // remainder 1 => 1 - 2 * 1 = -1
  return 1 - 2 * (count_neg % 2);
}