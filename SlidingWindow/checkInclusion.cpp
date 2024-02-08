#include <ios>
#include <iostream>
#include <string>
#include <unordered_map>

/**
567. Permutation in String

Given two strings s1 and s2, return true if s2 contains a permutation of s1, or
false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.



Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false


Constraints:

1 <= s1.length, s2.length <= 104
s1 and s2 consist of lowercase English letters.


idea : sliding window + unordered map
**/

using namespace std;

class Solution {
public:
  bool checkInclusion(const string &s1, const string &s2) {
    if (s1.size() > s2.size()) {
      return false;
    }
    unordered_map<char, int> s1_map;
    unordered_map<char, int> s2_map;
    for (char elem : s1) {
      s1_map[elem]++;
    }
    for (char elem : s2.substr(0, s1.size())) {
      s2_map[elem]++;
    }
    size_t i = 0;
    while (i + s1.size() < s2.size()) {
      if (s1_map == s2_map) {
        return true;
      }
      s2_map[s2[i + s1.size()]] += 1;
      s2_map[s2[i]] -= 1;
      if (s2_map[s2[i]] == 0) {
        s2_map.erase(s2[i]);
      }
      ++i;
    }

    return s1_map == s2_map;
  }
};

int main() {
  cout << boolalpha << Solution().checkInclusion("ab", "eidbaooo") << "\n";
}