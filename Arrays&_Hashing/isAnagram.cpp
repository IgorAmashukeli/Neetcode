/**Given two strings s and t, return true if t is an anagram of s, and false
otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.



Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false


Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.


Follow up: What if the inputs contain Unicode characters? How would you adapt
your solution to such a case?
idea: use array to count each character
follow up answer: use hash map instead
time: O(n)
space: O(n)
**/

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>

using namespace std;

void countChars(const string &str, array<int, 26> &str_count) {
  // creating array of counts
  for (char chr : str) {
    str_count[chr - 'a']++;
  }
}

bool isEqualCounts(const array<int, 26> &a_count,
                   const array<int, 26> &b_count) {
  // compare two arrays, counting chars
  for (size_t i = 0; i < 26; ++i) {
    if (a_count[i] != b_count[i]) {
      return false;
    }
  }
  return true;
}

bool isAnagram(const string &a, const string &b) {
  // check sizes of strings
  if (a.size() != b.size()) {
    return false;
  }

  // counting string a and string b
  array<int, 26> a_count{0};
  array<int, 26> b_count{0};
  countChars(a, a_count);
  countChars(b, b_count);
  return isEqualCounts(a_count, b_count);
}
