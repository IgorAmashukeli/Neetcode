/**
https://leetcode.com/problems/word-pattern/

Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter
in pattern and a non-empty word in s.



Example 1:

Input: pattern = "abba", s = "dog cat cat dog"
Output: true
Example 2:

Input: pattern = "abba", s = "dog cat cat fish"
Output: false
Example 3:

Input: pattern = "aaaa", s = "dog cat cat dog"
Output: false


Constraints:

1 <= pattern.length <= 300
pattern contains only lower-case English letters.
1 <= s.length <= 3000
s contains only lowercase English letters and spaces ' '.
s does not contain any leading or trailing spaces.
All the words in s are separated by a single space.

idea: two hasmaps and checking if they are similar
time: O(|pattern| + |s|)
space: O(|pattern| + |s|)
**/

#include <cstddef>
#include <ios>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool wordPattern(const string &pattern, const string &s) {
  size_t index = 0;

  // encoding of strings
  unordered_map<string, size_t> string_indicies;

  // encoding of char
  unordered_map<char, size_t> pattern_indicies;

  // cur string in string
  string cur_string;

  // index for string
  size_t j = 0;

  // iteration over pattern and s with two pointers
  for (size_t i = 0; i < pattern.size(); ++i) {

    // skip spaces
    while (j < s.size() && s[j] == ' ') {
      j++;
    }

    // read current word from string
    while (j < s.size() && s[j] != ' ') {
      cur_string += s[j];
      j++;
    }

    // if it is last word and not last char of pattern
    if (j == s.size() && i + 1 != pattern.size()) {
      return false;
    }

    std::cout << i << " " << j << "\n";

    // if not contains both -> ok -> update index
    if (!string_indicies.contains(cur_string) &&
        !pattern_indicies.contains(pattern[i])) {
      string_indicies[cur_string] = index;
      pattern_indicies[pattern[i]] = index;
      ++index;

      // if contains both and equal -> ok
    } else if (string_indicies.contains(cur_string) &&
               pattern_indicies.contains(pattern[i]) &&
               string_indicies[cur_string] == pattern_indicies[pattern[i]]) {

      // update current string
      cur_string = "";

      // otherwise -> false
    } else {
      return false;
    }

    // update current string
    cur_string = "";
  }

  // all indicies and strings proccessed
  return (j == s.size());
}
