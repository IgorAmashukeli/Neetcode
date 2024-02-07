#include <algorithm>
#include <iostream>
#include <unordered_map>

/**424.
Longest Repeating Character Replacement

You are given a string s and an integer k. You can choose any character of the
string and change it to any other uppercase English character. You can perform
this operation at most k times.

Return the length of the longest substring containing the same letter you can
get after performing the above operations.



Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.


Constraints:

1 <= s.length <= 105
s consists of only uppercase English letters.
0 <= k <= s.length

idea: sliding window:
 - find the maximum frequent letter in the window, check if there enough other
letters to replace
 - if enough, update size, shift right pointer
 - else: shift left pointer

Proof that the algoritm will find the substring that has the longest repeating
letters. Suppose, it is not true and there exists a string such that it starts
from i to j and it is longer than the result found. There exist two situations,
why this can happen.

- left pointer was < i and j was shifted from j to j + 1
- right pointer was < j and i was shifted from i to i + 1

Let's show, both of them can't happen.
1) Suppose, left pointer was < i and j was shifted from j to j + 1.
   Left pointer was not shifted, it means that the string l...i...j was
   so that we can replace other letters to get the substring with the same
characters. But in this case, l...i...j is bigger than i...j => i...j is not the
biggest string to replace

2) Suppose, right pointer was < j and i was shifted from i to i + 1.
Then, let's consider three pointers: i, r and j:
i.....r.....j
Let denote the frequency of element a in the interval [k, s] as freq_{a}{[k, s]}
Let denote the frequency of the most frequent element in the interval [k, s] as
freq_{[k, s]}{[k, s]} It is obvious: freq_{a}{[k, s]} <= freq_{[k, s]}{[k, s]}
for all elements a. [#] Moreover, freq_{a}{[k, s]} = freq_{a}{[k, l]} +
freq_{a}{[l + 1, s]}, when k <= l <= s [$] It is also obvious, freq_{a}{[k, s]}
<= (s - k + 1) [*] Left pointer was shifted. These means that k < (r - i + 1) -
freq_{[i, r]}{[i, r]} (Because this is the condition to shift left pointer).
Let's note that:
(j - i + 1) - freq_{[i, j]}{[i, j]} =
= j - r + r - i + 1 - freq_{[i, j]}{[i, r]} - freq_{[i - j]}{[r + 1, j]} =  [$]
= (j - (r + 1) + 1) + (i - r + 1) - freq_{[i, j]}{[i, r]} - freq_{[i - j]}{[r +
1, j]} = = (i - r + 1) - freq_{[i, j]}{[i, r]} + (j - (r + 1) + 1) - freq_{[i -
j]}{[r + 1, j]} >= [*]
>= (i - r + 1) - freq_{[i, j]}{[i, r]} >= [#] >= (i - r + 1) - freq_{[i, r]}{[i,
r]} > k

Therefore: (j - i + 1) - freq_{[i, j]}{[i, j]} > k
Therefore: k < (j - i + 1) - freq_{[i, j]}{[i, j]}
By [#], for all a: k < (j - i + 1) - freq_{a}{[i, j]}
Therefore: k + freq_{a}{[i, j]} < (j - i + 1) = size([i, j])
Therefore, any k replacement of to value a + all the values a in [i, j] is less
than size([i, j]) Therefore, after any replacement of at most k values to any
value a, the [i, j] will not convert to a...a Therefore, it can't be the answer.
Contradiction


Therefore, both situations can't happen.
Therefore, the algorithm is correct and run in 0(26 * n)
**/

using namespace std;

class Solution {
public:
  unordered_map<char, int> createCounts() {
    unordered_map<char, int> counts;
    for (size_t i = 0; i < 26; ++i) {
      counts[i + 'A'] = 0;
    }
    return counts;
  }

  int findMaxElement(unordered_map<char, int> &counts) {
    int max = 0;
    pair<char, int> answer;
    for (const auto &elem : counts) {
      if (elem.second > max) {
        max = elem.second;
        answer = elem;
      }
    }

    return answer.second;
  }

  int characterReplacement(const string &str, int k) {
    size_t left = 0;
    size_t right = 0;
    int max_size = 0;
    unordered_map<char, int> counts = createCounts();
    counts[str[0]] = 1;
    while (right < str.size()) {
      int max_count = findMaxElement(counts);
      int size = right - left + 1;
      if (size - max_count > k) {
        counts[str[left]]--;
        left++;
      } else {
        if (size > max_size) {
          max_size = size;
        }
        if (right + 1 < str.size()) {
          counts[str[right + 1]]++;
        }
        right++;
      }
    }
    return max_size;
  }
};

int main() { cout << Solution().characterReplacement("AAAAAA", 1) << "\n"; }
