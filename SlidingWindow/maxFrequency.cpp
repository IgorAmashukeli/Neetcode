#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**1838. Frequency of the Most Frequent Element


The frequency of an element is the number of times it occurs in an array.

You are given an integer array nums and an integer k. In one operation, you can
choose an index of nums and increment the element at that index by 1.

Return the maximum possible frequency of an element after performing at most k
operations.



Example 1:

Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two
times to make nums = [4,4,4]. 4 has a frequency of 3. Example 2:

Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a
frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a
frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a
frequency of 2. Example 3:

Input: nums = [3,9,6], k = 2
Output: 1


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= k <= 105


idea: sorting + two pointers (as in characterReplacement) + prefix sums


Proof of the correctness of algorithm

The algorithm should find the subsequence with the maximum size that can be
incremented k times to have the same values.

1) In any subsequence if you increment all elements to the maximum value only,
the answer will be the same
 - you can't change to value, less than the maximum, because there are only
increments and the maximum value should increase or stay the same
 - if you can change some subsequence of size S to the value A, bigger than the
maximum M in the subsequence, using K increments, you can change to the value M,
using K - (A - M) * S increments. If K was valid (<=k), K - (A - M) * S is also
valid (<=k). Therefore, if the answer is size S, but the value is A > M, then
changing all values to maximum in any subsequence, you can find the same S
answer (the same subsequence)

2) After sorting, if you incremement all elements to the most right value only,
the answer will be the same.

The most right value of subsequence is the biggest value in subsequence after
sorting
=> use the "1) statement"

3) After sorting, if the answer is S and is found among changing the most right
value in subsequences, you can find the answer S, searching only for subarrays
(there are n!/(n - k)!k! subsequences and only n(n + 1)/2 subarrays)


- Suppose, there was an answer of size S:
a_{i_1}, a_{i_2}, ..., a_{i_{S - 1}}, a_{i_S}

where i_1 < i_2 < ... < i_S

 - First of all, let's consider the subsequence:
a_{i_1}, a_{i_2}, ..., a_{i_{S - 1}}, a_{i_{S - 1} + 1}

The size is also S and now
In the first subsequence we incremented first S - 1 elements on:
a_{i_S} - a_{i_1} + a_{i_S} - a_{i_2} + ... + a_{i_S} - a_{i_{S - 1}} = (n - 1)
* a_{i_S} - Summ_{t = 1}^{S - 1}(a_{i_t}) In the second subsequence we increment
first S - 1 elements on: a_{i_S} - a_{i_1} + a_{i_S} - a_{i_2} + ... + a_{i_S} -
a_{i_{S - 1}} = (n - 1) * a_{i_{S - 1} + 1} - Summ_{t = 1}^{S - 1}(a_{i_t})

Because, the array is sorted, a_{i_{S - 1}} < a_{i_S}. Therefore, a_{i_{S - 1} +
1} <= a_{i_S}

Therefore, (n - 1) * a_{i_S} - Summ_{t = 1}^{S - 1}(a_{i_t}) >= (n - 1) *
a_{i_{S - 1} + 1} - Summ_{k = t}^{S - 1}(a_{i_t}).

Therefore, if k >= (n - 1) * a_{i_S} - Summ_{t = 1}^{S - 1}(a_{i_t}),
then k >= (n - 1) * a_{i_{S - 1} + 1} - Summ_{t = 1}^{S - 1}(a_{i_t})

Therefore, a_{i_1}, a_{i_2}, ..., a_{i_{S - 1}}, a_{i_{S - 1} + 1} is also a
valid answer of size S

Now, also let's consider the subsequence:
a_{i_{S - 1} - (S - 2)}, a_{i_{S - 1} - (S - 3)}, ..., a_{i_{S - 1} - 1},
a_{i_{S - 1}}, a_{i_{S - 1} + 1}

In the previouse subsequence, the incremement sum was
 1 + Summ_{t = 1}^{S - 1} a_{i_{S - 1} + 1} - a_{i_t}
Now, the increment sum is
 1 + Summ_{t = 1}^{S - 1} a_{i_{S - 1} + 1} - a_{i_{S - 1} - {S - t - 1}}

 a_{i_{S - 1}} <= a_{i_{S - 1} - {S - (S - 1) - 1}}, because {S - (S - 1) - 1} =
0 Because, i_{S - 2} is to the left of i_{S - 1}, but not nessesarily
subsequent, therefore, i_{S - 2} <= i_{S - 1} - 1 Because array is sorted:
 a_{i_{S - 2}} <= a_{i_{S - 1} - 1}
 Similarly, i_{S - 3} <= i_{S - 2} - 1 <= i_{S - 1} - 1 - 1 = i_{S - 1} - 2
 Because array is sorted:
 a_{i_{S - 3}} <= a_{i_{S - 1} - 2}
 and so on, by induction:
 a_{i_t} <= a_{i_{S - 1} - {S - t - 1}}, where t is in [1, S - 1]

 Therefore,
 1 + Summ_{t = 1}^{S - 1} a_{i_{S - 1} + 1} - a_{i_t} >=
 1 + Summ_{t = 1}^{S - 1} a_{i_{S - 1} + 1} - a_{i_{S - 1} - {S - t - 1}}


Therefore, if k >= 1 + Summ_{t = 1}^{S - 1} a_{i_{S - 1} + 1} - a_{i_t}, then
k >= 1 + Summ_{t = 1}^{S - 1} a_{i_{S - 1} + 1} - a_{i_{S - 1} - {S - t - 1}}

Therefore, subsequence a_{i_{S - 1} - (S - 2)}, a_{i_{S - 1} - (S - 3)}, ...,
a_{i_{S - 1} - 1}, a_{i_{S - 1}}, a_{i_{S - 1} + 1} is also a valid answer of
size S

But this subsequence is subsequent. The subsequent subsequence is subarray.

Therefore, after sorting, there is no need to search all subsequent, only
subarrays is ok.


3) All the O(n) subarrays, searched, using the algorithm with the two ponters,
is ok, and you will find the correct maximum subarray of size S.

Let's prove it.
Suppose, we are skipped one of the subarrays with the maximum answer.
And the answer is subarray a[i]...a[j]

It can happen in two cases:
 - left pointer was < i and right pointer was shifted from j to j + 1
 - right pointer was < j and left pointer was shifted from i to i + 1

 Let's consider the first case:

 Suppose, the left pointer was l, l < i and right pointer was shifted from j to
j + 1.
Because, the right pointer was shifted, the subarray was valid
(nums[right] * size - summa <= k) (summa is calculated correctly on a fly, using
prefix sums, and subtracting left value, when moving left). Because l < i, the
size of a[l]...a[i]...a[r] is bigger than size of a[i]...a[j]. Therefore,
a[i]...a[j] can't be the answer with the maximum size. Contradiction.

Threfore the first case can't happen.


Now let's consider the second case:

Suppose, the right pointer was r, r < j and left pointer was shifted from i to i
+ 1.

Because, left pointer was shifted, a[i]...a[r] is invalid:

k < a[r] - a[r - 1] + a[r] - a[r - 2] + ... + a[r] - a[i] = (r - i)a[r] -
Summ_{t = i}^{r - 1} a[t] [#]

We suppose that a[i]...a[j] is valid.

This means, we assume:

k >= a[j] - a[j - 1] + a[j] - a[j - 2] + ... + a[j] - a[i] = (j - i)a[j] -
Summ_{t = i}^{j - 1} a[t] [*]

In particular, from [#] and [*]

a[j] - a[j - 1] + a[j] - a[j - 2] + ... + a[j] - a[i] = (j - i)a[j] -
Summ_{t = i}^{j - 1} a[t] < a[r] - a[r - 1] + a[r] - a[r - 2] + ... + a[r] -
a[i] = (r - i)a[r] - Summ_{t = i}^{r - 1} a[t]

It means:

(j - i) a[j] - (r - i) a[r] < Summ_{t = i}^{j - 1} a[t] - Summ_{t = i}^{r - 1}

It means:

(j - i) a[j] - (r - i) a[r] < Summ_{t = r}^{j - 1} a[t]

Because array is sorted and r < j : a[r] < a[j] =>

(j - i) a[j] - (r - i) a[j] < (j - i) a[j] - (r - i) a[r] < Summ_{t = r}^{j - 1}
a[t]

Therefore:

(j - r)a[j] < Summ_{t = r}^{j - 1} a[t]

Therefore: a[j] - a[r] + a[j] - a[r + 1] + ... a[j] - a[j - 1] < 0

But, a[j] - a[r] > 0; ... a[j] > a[j - 1] and, thus a[j] - a[r] + a[j] - a[r +
1] + ... a[j] - a[j - 1] > 0

Therefore, it is contradiction and a[i]...a[j] is not valid answer.


4) Finally, using prefix sums and updating it (subtracting the a[left] and
adding a[right + 1]) we can in O(1) check the condition on each iteration.

Therefore, after sorting the algorithms runs in 0(n).

Therefore, algorithms runs in O(n long n)

**/

class Solution {
public:
  int maxFrequency(vector<int> &nums, int k) {
    if (nums.empty()) {
      return 0;
    }
    sort(nums.begin(), nums.end());
    size_t left = 0;
    size_t right = 0;
    int max_freq = 0;
    long long summa = nums[left];
    while (right < nums.size()) {
      long long size = right - left + 1;
      if (nums[right] * size - summa > k) {
        summa -= nums[left];
        left++;
      } else {
        if (size > max_freq) {
          max_freq = size;
        }

        if (right + 1 < nums.size()) {
          summa += nums[right + 1];
        }
        right++;
      }
    }
    return max_freq;
  }
};

int main() {
  vector<int> a = {40, 95, 44, 37, 41, 52, 07, 52, 87, 64, 40,
                   14, 41, 33, 12, 34, 80, 07, 80, 44, 10, 9};
  int k = 7925;
  cout << Solution().maxFrequency(a, k) << "\n";
}