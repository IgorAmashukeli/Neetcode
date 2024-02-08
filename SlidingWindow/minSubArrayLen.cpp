#include <iostream>
#include <vector>

using namespace std;

/**209. Minimum Size Subarray Sum
Given an array of positive integers nums and a positive integer target, return
the minimal length of a subarray whose sum is greater than or equal to target.
If there is no such subarray, return 0 instead.



Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem
constraint. Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0


Constraints:

1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4


Follow up: If you have figured out the O(n) solution, try coding another
solution of which the time complexity is O(n log(n)).


O(n) idea:

two pointers,
if not enough sum: shift right
if enough sum: shift left

Proof that the algorithm is correct:

Suppose, the algorithm is not correct.
Then it means that there exists a subarray a[i]...a[j] such that it is smallest
one and sum up to A >= target and it was skipped

It can be skipped in two cases:

- left pointer l was < i and right pointer was shifted from j to j + 1
- right pointer r was < j and left pointer was shifted from i to i + 1

In the first situation:

Right pointer was shifted => a[l] + ... + a[j] < target
the integers are positive =>
=> a[i] + ... + a[j] < target
=> a[i]...a[j] can't be a correct answer


Left pointer was shifted => It means that a[i] + ... + a[r] >= target
and moreover, a[i]...a[r] is less than a[i]...a[j].
Therefore, a[i]...a[j] can't be a correct answer. It is too big



**/

class Solution {
public:
  int minSubArrayLen(int target, vector<int> &nums) {
    size_t left = 0;
    size_t right = 0;
    int summa = nums[left];
    bool found = false;
    int min_size = nums.size() + 1;
    while (right < nums.size()) {
      if (summa < target) {
        if (right + 1 < nums.size()) {
          summa += nums[right + 1];
        }
        ++right;
      } else {
        if (right - left + 1 < min_size) {
          min_size = right - left + 1;
          found = true;
        }
        summa -= nums[left];
        ++left;
      }
    }

    if (!found) {
      return 0;
    }

    return min_size;
  }
};

int main() {
  vector<int> a = {1, 1, 1, 1, 1, 1, 1, 1};
  cout << Solution().minSubArrayLen(11, a) << "\n";
}