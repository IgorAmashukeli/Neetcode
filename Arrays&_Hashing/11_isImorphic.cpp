/**
https://leetcode.com/problems/isomorphic-strings/

Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get
t.

All occurrences of a character must be replaced with another character while
preserving the order of characters. No two characters may map to the same
character, but a character may map to itself.



Example 1:

Input: s = "egg", t = "add"
Output: true
Example 2:

Input: s = "foo", t = "bar"
Output: false
Example 3:

Input: s = "paper", t = "title"
Output: true


Constraints:

1 <= s.length <= 5 * 10^4
t.length == s.length
s and t consist of any valid ascii character.

idea: create encoding of strings
check encodings are the same

time: O(|s| + |t|)
space: O(|s| + |t|)
**/

#include <cstddef>
#include <string>
#include <unordered_map>

using namespace std;

bool isIsomorphic(const string &s, const string &t) {
  // strings have different size
  if (s.size() != t.size()) {
    return false;
  }

  size_t s_code = 0;
  size_t t_code = 0;
  unordered_map<char, size_t> s_encoding;
  unordered_map<char, size_t> t_encoding;

  // encoding s and t
  for (size_t i = 0; i < s.size(); ++i) {
    if (s_encoding.find(s[i]) == s_encoding.end()) {
      s_encoding.insert({s[i], s_code});
      s_code++;
    }

    if (t_encoding.find(t[i]) == t_encoding.end()) {
      t_encoding.insert({t[i], t_code});
      t_code++;
    }

    // if codes are different -> they are not isomorphic

    if (s_encoding[s[i]] != t_encoding[t[i]]) {
      return false;
    }
  }

  // check the last code value
  return true;
}