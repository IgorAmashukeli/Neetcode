#include <string>

using namespace std;

/**Write a function that reverses a string. The input string is given as an
array of characters s.

You must do this by modifying the input array in-place with O(1) extra memory.



Example 1:

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
Example 2:

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]


Constraints:

1 <= s.length <= 105
s[i] is a printable ascii character.


idea: straightforward merging
**/

string mergeAlternately(string word1, string word2) {
  // result
  string result = "";

  // three pointers: for word1, word2 and result
  size_t i, j, k;
  i = j = k = 0;

  // merge all letters
  while (i != word1.size() || j != word2.size()) {

    // order of the first word
    if ((i < word1.size() && j < word2.size() && k % 2 == 0) ||
        (j == word2.size())) {
      result += word1[i];
      ++i;
      ++k;

      // order of the second word
    } else if ((i < word1.size() && j < word2.size() && k % 2 == 1) ||
               (i == word1.size())) {
      result += word2[j];
      ++j;
      ++k;
    }
  }

  return result;
}