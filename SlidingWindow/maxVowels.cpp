#include <string>
#include <unordered_set>

/**
1456. Maximum Number of Vowels in a Substring of Given Length

Given a string s and an integer k, return the maximum number of vowel letters in
any substring of s with length k.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.



Example 1:

Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
Example 2:

Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
Example 3:

Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.


Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.
1 <= k <= s.length

idea: simple sliding window

**/

using namespace std;

class Solution {
public:
  int maxVowels(const string &s, int k) {
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    size_t i = 0;
    int count = 0;
    int max_count = 0;
    for (size_t t = 0; t < k; ++t) {
      if (vowels.contains(s[t])) {
        count++;
      }
    }
    while (i + k < s.size()) {
      if (count > max_count) {
        max_count = count;
      }
      if (vowels.contains(s[i + k])) {
        count++;
      }
      if (vowels.contains(s[i])) {
        count--;
      }
      ++i;
    }

    if (count > max_count) {
      max_count = count;
    }

    return max_count;
  }
};

int main() {}