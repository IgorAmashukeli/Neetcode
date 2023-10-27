#include <cctype>
#include <iostream>
#include <string>

/**125. Valid Palindrome

A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.



Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.


Constraints:

1 <= s.length <= 2 * 10^5
s consists only of printable ASCII characters

idea: two pointers, while checking non-alpha-numeric and doing tolower
**/

using namespace std;

/**check if letter is alphanumeric**/
bool isAlphaNumeric(char chr) {
  return (chr - '0' >= 0 && chr - '0' <= 9) ||
         (chr - 'a' >= 0 && chr - 'a' <= 25) ||
         (chr - 'A' >= 0 && chr - 'A' <= 25);
}

bool isPalindrome(const string &s) {

  // empty string
  if (s.size() == 0) {
    return true;
  }

  size_t left = 0;
  size_t right = s.size() - 1;

  while (left < right) {

    cout << left << " " << right << "\n";

    // skip non-alphanumeric
    if (!isAlphaNumeric(s[left]) || !isAlphaNumeric(s[right])) {
      if (!isAlphaNumeric(s[left])) {
        left++;
      }
      if (!isAlphaNumeric(s[right])) {
        right--;
      }
      // found problem with palindrome - skip
    } else if (tolower(s[left]) != tolower(s[right])) {
      return false;

      // shift to the next
    } else {
      left++;
      right--;
    }
  }

  return true;
}

int main() { cout << isPalindrome("A man, a plan, a canal: Panama") << "\n"; }