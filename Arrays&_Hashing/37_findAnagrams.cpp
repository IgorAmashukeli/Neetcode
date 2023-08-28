/**Given two strings s and p, return an array of all the start indices of p's
anagrams in s. You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.



Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".


Constraints:

1 <= s.length, p.length <= 3 * 10^4
s and p consist of lowercase English letters.

idea:
check two anagrams with the help of vector of counts of size 26,
update this vector on each iteration

time: O(s.size())
space: O(t.size())

**/

#include <string>
#include <vector>

using namespace std;

vector<int> findAnagrams(string s, string p) {
  // check if p.size() > s.size()
  vector<int> answer;
  if (p.size() > s.size()) {
    return answer;
  }

  // find counts of string p
  vector<int> p_count(26, 0);
  for (char chr : p) {
    p_count[chr - 'a']++;
  }

  // find first substring counts
  vector<int> anagram_count(26, 0);
  for (size_t i = 0; i < p.size(); ++i) {
    anagram_count[s[i] - 'a']++;
  }

  for (size_t i = p.size(); i < s.size(); ++i) {
    // check this substring, and add to answer
    if (anagram_count == p_count) {
      answer.push_back(i - p.size());
    }

    // add s[i]
    anagram_count[s[i] - 'a']++;

    // remove s[i - p.size()]
    anagram_count[s[i - p.size()] - 'a']--;
  }

  // check the last substring, and add to answer
  if (anagram_count == p_count) {
    answer.push_back(s.size() - p.size());
  }

  return answer;
}