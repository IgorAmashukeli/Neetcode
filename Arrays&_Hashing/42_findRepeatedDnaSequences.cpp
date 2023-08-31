/**The DNA sequence is composed of a series of nucleotides abbreviated as 'A',
'C', 'G', and 'T'.

For example, "ACGAATTCCG" is a DNA sequence.
When studying DNA, it is useful to identify repeated sequences within the DNA.

Given a string s that represents a DNA sequence, return all the 10-letter-long
sequences (substrings) that occur more than once in a DNA molecule. You may
return the answer in any order.



Example 1:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]
Example 2:

Input: s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]


Constraints:

1 <= s.length <= 10^5
s[i] is either 'A', 'C', 'G', or 'T'.

idea: hashMap to store strings
time: O(10 * n)
space: O(n)


**/

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> findRepeatedDnaSequences(string &s) {
  // vector for answer
  vector<string> answer;

  // counts
  unordered_map<string, int> substring_counts;

  // first substring
  string substring = s.substr(0, 10);

  // iterate through other substrings
  for (size_t i = 10; i < s.size(); ++i) {

    // if there is such substring and it was found before, pushback it
    if (substring_counts.contains(substring) &&
        substring_counts[substring] == 1) {
      answer.push_back(substring);
    }

    // update counts
    substring_counts[substring]++;

    // update string
    substring = substring.substr(1);
    substring.push_back(s[i]);
  }

  // if there is such substring and it was found before, pushback it
  if (substring_counts.contains(substring) &&
      substring_counts[substring] == 1) {
    answer.push_back(substring);
  }

  return answer;
}