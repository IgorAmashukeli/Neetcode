#include <cstddef>
#include <ios>
#include <iostream>
#include <string>

/**Given a string s, return true if the s can be palindrome after deleting at
most one character from it.



Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false


Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.

idea:
if it is palindrome => at most one can be deleted
if it is not a palindrome:

- go from left and go from right
- found first two different letters






Statement:

a) if either one of them is deleted and result is a palindrome,
it can be reduced to a palindrome with removing one element.

b) if either one of them is deleted and result is not a palindrome,
it can't be reduced to a palindrome with removing one element.

Proof:
The first part is obvious.
Let's proof the second one.

This is the palindrome:

a_1, ... a_[n/2], [maybe central element], a_[n/2 + 1], ..., a_n

Another char can be added to/after [a_1, ... a_[n/2]] or to [a_[n/2 + 1], ...,
a_n] Suppose, it was added. It doesn't matter to which side (it is similar
proofs, let's consider only the left one) Suppose one of the letters was added
to the left part:

a_1, ..., a_[i], ... a[n - i], ...., a_[n]

a_1 = a_[n]
a_2 = a_[n - 1]
...
...
a_[i - 1] = a_[n - i + 1]
a_[i] != a[n - i]


Suppose, a_[i] or a_[n - i] is not the letter to remove.
(Here it couldn't be a_[n - i], cause the letter was added to the left part)

Then it is other a_[i - k] or a_[i + k], where k > 0

If it is a_[i + k], then after removing a_[i + k], we created palindrome
=> a_[i] = a_[n - i] again, but it is false

If it is a_[i - k], then let's observe some statements

1) a_[1], ..., a_[i - 1] == a_[n - i + 1], ..., a_[n] reversed,
because a_[i], a[j] is the first pair with different values by definition

2) a_[1], ..., a_[i - k - 1], a_[i - k + 1], ..., a_[i] == a_[n - i + 1], ...,
a_[n] reversed, because there are i - 1 letters in the left part and i - 1
letters in the right part and after deleting a_[i - k] we created palindrome

=> therefore combining these two together
a_[1], ..., a_[i - 1] == a_[1], ..., a_[i - k - 1], a_[i - k + 1], ..., a_[i]

But that means by definition
a[i - k] == a_[i - k + 1]
...
a[i - 1] == a[i]

But that means, a_[i - k]...a_[i] is the same letter.
But that means, removing a_[i - k] or a_[i] will change
the string from being a_[1], ..., a_[i - k - 1], <k letters> a[i + 1]...a[n]
to a_[1], ..., a_[i - k - 1], <k - 1 letters> a[i + 1]...a[n]
That mens, removing a_[i - k] is the same as removing a_[i]
Therefore, we can remove a_[i]





Therefore, we check three possible ways:
- it is palindrome
- we can delete the first left letter, that is not the same as the right one,
while doing two pointers
- we can delete the first right letter, that is not the same as the left one,
while doing two pointers
**/

using namespace std;

/**
tries to skip left or right part char and move to next if palindrome
condition fails counts the number of failures
the number should be <= 1
**/
bool skip_palindrome(const string &s, size_t left, size_t right, bool is_left) {
  // count number of times left != right
  int count = 0;

  // s[left] == s[right] is obvious
  // left > right doesn't mean left is in the left part and right in the right
  while (left < right) {

    // palindrome condition is true
    if (s[left] == s[right]) {
      left++;
      right--;

      // palindrome condition is false
    } else {

      // palindrome condition was false before => answer is false
      if (count >= 1) {
        return false;
      }

      // left element to delete
      if (is_left) {
        left++;

        // right element to delete
      } else {
        right--;
      }
      count++;
    }
  }

  return true;
}

bool validPalindrome(const string &s) {
  // size > 1 => no need to check empty string

  // checking both conditions
  return skip_palindrome(s, 0, s.size() - 1, false) ||
         skip_palindrome(s, 0, s.size() - 1, true);
}