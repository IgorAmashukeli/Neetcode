#include <iostream>
#include <vector>

// You are given an array prices where prices[i] is the price of a given stock
// on the ith day.

// You want to maximize your profit by choosing a single day to buy one stock
// and choosing a different day in the future to sell that stock.

// Return the maximum profit you can achieve from this transaction. If you
// cannot achieve any profit, return 0.

// Example 1:

// Input: prices = [7,1,5,3,6,4]
// Output: 5
// Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit =
// 6-1 = 5. Note that buying on day 2 and selling on day 1 is not allowed
// because you must buy before you sell. Example 2:

// Input: prices = [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transactions are done and the max profit = 0.

// Constraints:

// 1 <= prices.length <= 105
// 0 <= prices[i] <= 104

// idea: sliding window:
// if a[r] - a[l] > max_value -> update max_value to a[r] - a[l]
// if a[r] < a[l] -> l = r; r++;
// else r++;

// Proof that the algorithm is correct:
// Suppose, the algorithm is not correct and the found_answer is not the best
// there exists l_0 < r_0 such that a[r_0] - a[l_0] > found_answer
// then it means that it was skipped
// We see that r pointer iterates over all elements in the array a
// It means, at some point r will be equal to r0
// Let's consider this moment. Let l_1 be the left pointer at that moment.
// Because a[r_0] - a[l_0] is the maximum number and such number wasn't found,
// but (l_1, r_0) are the two pointers that were seen, therefore,
// a[r_0] - a[l_0] > a[r_0] - a[l_1] => a[l_1] > a[l_0]
//
// We can guarantee, that l_1 can't be < l_0
// Suppose, it is not true and l_1 < l_0. Then at some point r pointer was at
// l_0. Suppose, the l pointer at this time was l_2. If a[l_2] <= a[l_0], left
// pointer can never be shifted to the l_0, because left pointer always moves to
// the point, where it decreases or it doesn't move (we shift it to r only if
// a[r] < a[l]) => a[l_2] >= a[l_0], then it means that a[l_2] > a[l_0].
// But this means, that after that iteration left pointer should have been
// shifted to l_0. And at the moment, when r pointer was equal to r_0, left
// pointer was also equal to l_0. Therefore, l_1 = l_0 and this is contradiction
// Therefore, l1 can't be < l_0
//
// Now, let's consider l_1 > l_0. Let's prove it can't be so either.
// If l_1 is the position of the pointer, when r pointer is equal to r_0,
// then it means that it was shifted to that position from some point.
// It couldn't be shifted from point l_0, because a[l_0] < a[l_1].
// It couldn't be shifted from any point after l_0, because l pointer, if
// shifted after l_0, can only decrease in a value, and a[l pointer] will be
// less than a[l_0]. Therefore, l pointer was shifted to l_1 from a place < l_0.
// Then, it means, it was shifted from some point l_3, such that a[l_3] > a[l_1]
// and l_3 < l_1.
// Let's prove, it can't be so. If it was shifted from some point l_3 such that
// l_3 < l_1 and a[l_3] > a[l_1]. Let's consider the moment, when r pointer was
// at point l_0. That moment was before the moment, r pointer was at point l_1,
// because l_0 < l_1, and therefore, the left pointer at that moment (l_4) was
// before the left pointer at the moment, when r pointer was at the point l_1
// (and this is denoted as l_3) Therefore l3 < l4. But, to not move to pointer
// l_0, a[l_4] should be <= a[l_0]. Therefore, a[l_4] <= a[l_0], but then a[l_4]
// <= a[l_0] < a[l_1] => a[l_4] < a[l_1]. But l pointer was shifted to the l_1
// point, but it always decreases in a value or stays the same. Therefore,
// a[l_4] > a[l_0]. Therefore, left pointer should have been moved to l_0.
// But a[l_0] < a[l_1]. Therefore, it should have never moved to l_1.
// Contradiction => it can't be shifted to l_1 from some point l_3, such that
// a[l_3] > a[l_1] and l_3 < l_1. Therefore, l_1 can't be > l_0. Therefore, l_1
// can't be < l_0 and l_1 can't be > l_0 Therefore, l_1 = l_0 Therefore, we will
// find the right pair.

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    if (prices.empty()) {
      return 0;
    }

    size_t l = 0;
    size_t r = 0;
    int max_found = 0;
    while (r < prices.size()) {
      if (prices[r] - prices[l] > max_found) {
        max_found = prices[r] - prices[l];
      }
      if (prices[r] < prices[l]) {
        l = r;
      }
      r++;
    }

    return max_found;
  }
};

int main() {
  vector<int> prices = {7, 6, 4, 3, 1};
  cout << Solution().maxProfit(prices) << "\n";
}