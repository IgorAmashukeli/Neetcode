/**
https://leetcode.com/problems/group-anagrams/


Given an array of strings strs, group the anagrams together. You can return
the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.



Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]


Constraints:

1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.

idea:
count letters
create hashmap
put all the values from hashmap to vector of vectors

time: n - size of vector; O(n log n)
space: O(n)

**/
#include <array>
#include <map>
#include <string>
#include <vector>

using namespace std;

array<int, 26> countAnagrams(const string &s) {
  array<int, 26> counts{0};
  for (size_t i = 0; i < s.size(); ++i) {
    counts[s[i] - 'a']++;
  }
  return counts;
}

vector<vector<string>> groupAnagrams(vector<string> &strs) {
  vector<vector<string>> answer;
  // map:
  // key: array<int, 26> - the type of anagram
  // value: vector<string> - all the anagrams
  map<array<int, 26>, vector<string>> mapping;
  for (size_t i = 0; i < strs.size(); ++i) {
    mapping[countAnagrams(strs[i])].push_back(strs[i]);
  }

  // put map to vector of vectors again
  for (const auto &[key, value] : mapping) {
    answer.push_back(value);
  }

  return answer;
}