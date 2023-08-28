/**Given two strings needle and haystack, return the index of the first
occurrence of needle in haystack, or -1 if needle is not part of haystack.



Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.


Constraints:

1 <= haystack.length, needle.length <= 10^4
haystack and needle consist of only lowercase English characters.

idea:
create deque (it is possible to pushback and popfront in O(1)) for current
substring check each substring of needle size if it is equal to needle return
the first index when equal or -1

time: O(needle.size() + haystack.size())
space: O(neelde.size())
**/

#include <cassert>
#include <deque>
#include <string>

using namespace std;

// check if current substring (represented as deque is the same as needle
// string)
bool equal(const deque<char> &substring, const string &needle) {
  assert(substring.size() == needle.size());

  // element-wise comparison
  size_t i = 0;
  for (char elem : substring) {

    // failure => return false
    if (needle[i] != elem) {
      return false;
    }
    ++i;
  }

  // element-wise comparison was true
  return true;
}

int strStr(const string &haystack, const string &needle) {
  // check sizes
  if (needle.size() > haystack.size()) {
    return -1;
  }

  // initialization of current substring
  deque<char> cur_substring;
  for (size_t i = 0; i < needle.size(); ++i) {
    cur_substring.push_back(haystack[i]);
  }

  for (size_t i = needle.size(); i < haystack.size(); ++i) {

    // if current substring is needle
    if (equal(cur_substring, needle)) {
      return i - needle.size();
    }

    // update
    cur_substring.push_back(haystack[i]);
    cur_substring.pop_front();
  }

  // check last substring
  if (equal(cur_substring, needle)) {
    return haystack.size() - needle.size();
  }

  return -1;
}