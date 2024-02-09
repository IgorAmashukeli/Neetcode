#include <iostream>
#include <string>
#include <unordered_map>

/**
76. Minimum Window Substring
Given two strings s and t of lengths m and n respectively, return the minimum
window substring of s such that every character in t (including duplicates) is
included in the window. If there is no such substring, return the empty string
"".

The testcases will be generated such that the answer is unique.



Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from
string t. Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.


Constraints:

m == s.length
n == t.length
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.


Follow up: Could you find an algorithm that runs in O(m + n) time?

idea: two pointers + unordered map to represent t and s substrings of size <=
52, updating s_map to check if substring of s is valid, we check in O(1), that
t_map includes in s_map (for each char in t_map, it is in s_map and it's count
in t_map is not bigger than corresponding count in t_map)

Two pointer techinque:
if t_map contains in s_map -> shift left
else -> shift right

Let's proof that all the answer is correct
Suppose, there exists a substring a[i]...a[j] that is skipped and is minimal and
t_map includes s_map It was skipped due to two situations:

- left pointer l was < i and right pointer was shifted from j to j + 1
- right pointer r was < j and left pointer was shifted from i to i + 1

- In the first situation, right pointer was shifted, it means t_map doesn't
contain in s_map for l...i...j => it doesn't contain in i...j too.
- In the second situation, left pointer was shifted, it means t_map includes in
s_map for i...r => it means it is smaller than i...j and i...j can't be an
answer

Therefore, the algorithm is correct.

**/

using namespace std;

class Solution {
private:
  bool includes(const unordered_map<char, int> &t_map,
                const unordered_map<char, int> &s_map) {
    for (const auto &[elem, t_count] : t_map) {
      if (!s_map.contains(elem)) {
        return false;
      } else {
        if (t_count > s_map.find(elem)->second) {
          return false;
        }
      }
    }
    return true;
  }

public:
  string minWindow(const string &s, const string &t) {
    int min_window = s.size() + 1;
    int left_min = -1;
    int right_min = -1;
    size_t m = s.size();
    size_t n = t.size();
    if (m < n) {
      return "";
    }
    unordered_map<char, int> t_map;
    for (size_t i = 0; i < n; ++i) {
      t_map[t[i]]++;
    }
    unordered_map<char, int> s_map;
    s_map = {{s[0], 1}};
    size_t left = 0;
    size_t right = 0;
    while (right < s.size()) {
      if (!includes(t_map, s_map)) {
        if (right + 1 < s.size()) {
          s_map[s[right + 1]]++;
        }
        right++;
      } else {
        if (right - left + 1 < min_window) {
          min_window = right - left + 1;
          left_min = left;
          right_min = right;
        }
        s_map[s[left]]--;
        left++;
      }
    }
    if (left_min != -1) {
      return s.substr(left_min, right_min - left_min + 1);
    } else {
      return "";
    }
  }
};

int main() { cout << Solution().minWindow("abc", "b") << "\n"; }