/**
https://leetcode.com/problems/unique-length-3-palindromic-subsequences/


Given a string s, return the number of unique palindromes of length three
that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is
still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string
with some characters (can be none) deleted without changing the relative order
of the remaining characters.

For example, "ace" is a subsequence of "abcde".


Example 1:

Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")
Example 2:

Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".
Example 3:

Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")


Constraints:

3 <= s.length <= 10^5
s consists of only lowercase English letters.


idea:

1) hashmap to find positions of characters
2) iteration over edge center possible candidates, with checking if such exist
3) check is done using consecutive binary search

time: O(n)
space: O(n)

**/

#include <string>
#include <unordered_map>
#include <vector>

enum { NOT_FOUND = -2 };

using namespace std;

// lbound binary search
int findIndex(const vector<int> &positions, int prev_i) {
  // there are no positions at all -> return NOT_FOUND
  if (positions.size() == 0) {
    return NOT_FOUND;
  }

  // left index
  size_t left = 0;

  // right index
  size_t right = positions.size();

  int found_position = NOT_FOUND;

  // binary search
  while (left < right) {
    int mid = left + (right - left) / 2;

    // not valid position
    if (positions[mid] <= prev_i) {
      left = mid + 1;
    } else {

      // valid position, let's remember and try to find better
      found_position = positions[mid];
      right = mid;
    }
  }

  // if left = right is valid, remember this as best
  if (left < positions.size() && positions[right] > prev_i) {
    found_position = positions[right];
  }

  // return the index
  return found_position;
}

bool existsSubsequence(unordered_map<char, vector<int>> &positions, char edge,
                       char center) {
  int first = positions[edge][0];
  int second = findIndex(positions[center], first);
  if (second == NOT_FOUND) {
    return false;
  }

  int last = findIndex(positions[edge], second);
  if (last == NOT_FOUND) {
    return false;
  }

  return true;
}

int countPalindromicSubsequence(const string &s) {

  // positions of each character
  unordered_map<char, vector<int>> positions;
  for (size_t i = 0; i < positions.size(); ++i) {
    positions[s[i]].push_back(i);
  }

  // count number of palindroms
  int count = 0;
  for (const auto &[ch, vec] : positions) {
    for (const auto &[ch2, vec] : positions) {
      if (existsSubsequence(positions, ch, ch2)) {
        ++count;
      }
    }
  }

  return count;
}