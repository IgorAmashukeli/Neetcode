/**
https://leetcode.com/problems/length-of-last-word/

Given a string s consisting of words and spaces, return the length of the
last word in the string.

A word is a maximal
substring
 consisting of non-space characters only.



Example 1:

Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
Example 2:

Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.
Example 3:

Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.


Constraints:

1 <= s.length <= 10^4
s consists of only English letters and spaces ' '.
There will be at least one word in s.

idea: use bool state variable
time: O(n)
space: O(1)
**/

#include <string>

using namespace std;

int lengthOfLastWord(const string &s) {

  // if current symbol is space
  bool space_flag = false;

  // the last word length
  int last_length = 0;

  // current word length
  int cur_length = 0;

  // iterate over the string
  for (size_t i = 0; i < s.size(); ++i) {

    // space started
    if (s[i] == ' ' && !space_flag) {

      // save last length
      last_length = cur_length;

      // restore cur length for future parts
      cur_length = 0;

      // change flag to space
      space_flag = true;
    } else if (s[i] != ' ') {
      // add up to the length of current word
      cur_length += 1;

      // change flag to non-space
      space_flag = false;
    }
  }

  // change cur length to length of exactly last word
  if (!space_flag) {
    last_length = cur_length;
  }

  return last_length;
}