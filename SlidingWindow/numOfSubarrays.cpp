#include <iostream>
#include <vector>

/* 1343. Number of Sub-arrays of Size K and Average Greater than or Equal to
Threshold

Given an array of integers arr and two integers k and threshold, return the
number of sub-arrays of size k and average greater than or equal to threshold.



Example 1:

Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
Output: 3
Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6
respectively. All other sub-arrays of size 3 have averages less than 4 (the
threshold). Example 2:

Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
Output: 6
Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note
that averages are not integers.


Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^4
1 <= k <= arr.length
0 <= threshold <= 10^4

idea : sliding window of size k with summa update and threshold/mean check

 */

using namespace std;

class Solution {
public:
  int numOfSubarrays(vector<int> &arr, int k, int threshold) {
    int summa = 0;
    if (static_cast<size_t>(k) > arr.size()) {
      return 0;
    }
    size_t i = 0;
    summa = 0;
    for (size_t i = 0; i < k; ++i) {
      summa += arr[i];
    }
    int count = 0;
    while (i + k < arr.size()) {
      if (summa >= threshold * k) {
        count += 1;
      }
      summa -= arr[i];
      summa += arr[i + k];
      ++i;
    }

    if (summa >= threshold * k) {
      count += 1;
    }

    return count;
  }
};

int main() {
  vector<int> arr = {2, 2, 2, 2, 5, 5, 5, 8};
  int k = 3;
  int threshold = 4;
  cout << Solution().numOfSubarrays(arr, k, threshold) << "\n";
}