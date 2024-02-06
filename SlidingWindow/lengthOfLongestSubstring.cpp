#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

/* Longest Substring Without Repeating Characters
Given a string s, find the length of the longest
substring
 without repeating characters.



Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a
substring.


Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces

idea:
two pointers:
 when there are repeating characters in string shift left
 when there are no repeating characters in string shift right

Let's prove that we won't skip the longest substring.
Let's assume, we skipped the substring a_i...a_j, where j - i > 1 and it is the
largest string Then, it means, we skipped it. Two situation can happen
- Left pointer was < i and we moved right from j to j + 1
- Right pointer was < j and we moved left from i to i + 1

First situation:
In the first situation, we moved right pointer from j to j + 1.
This means that there are no repeating characters in a[l]...a[i]...a[j].
Therefore, there exists a string with no repeating characters a[l]...a[j]
with the size, bigger than a size of a[i]...a[j].
Therefore, a[i]...a[j] is not the biggest substring with no repeating
characters.

Second situation:
In the second situation, we moved left pointer from i to i + 1.
It means that in a[l]...a[r] (which equals to a[i]...a[r]) there are repeating
characters. Therefore, there are repeating characters in a[i]...a[j]. Therefore,
a[i]...a[j] is not the biggest substring with no repeating characters.

*/

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(const string &s) {
    if (s.size() == 0) {
      return 0;
    }

    unordered_set<char> letters = {s[0]};
    size_t left = 0;
    size_t right = 1;
    int longest = 1;
    while (right != s.size()) {
      if (letters.contains(s[right])) {
        letters.erase(s[left]);
        left++;
      } else {
        if (static_cast<int>(right - left) + 1 > longest) {
          longest = static_cast<int>(right - left) + 1;
        }
        letters.insert(s[right]);
        right++;
      }
    }

    return longest;
  }
};

int main() {
  string s = "bbbbb";
  cout << Solution().lengthOfLongestSubstring(s) << "\n";
}