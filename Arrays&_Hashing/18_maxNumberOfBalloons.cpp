/**
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

Given a string text, you want to use the characters of text to form as many
instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of
instances that can be formed.

Example 1:



Input: text = "nlaebolko"
Output: 1
Example 2:



Input: text = "loonbalxballpoon"
Output: 2
Example 3:

Input: text = "leetcode"
Output: 0


Constraints:

1 <= text.length <= 10^4
text consists of lower case English letters only.


idea:

- find all counts
- counts of "l" and "o" decreased by 2
- find the minimum number of count "b", "a", "l", "o", "n"
- return the minimum number

time: O(n)
space: O(1)
**/

#include <array>
#include <cstddef>
#include <string>

using namespace std;

int maxNumberOfBalloons(const string &text) {
  // count each letter in "balloon"
  array<size_t, 5> counts = {0, 0, 0, 0, 0};
  for (size_t i = 0; i < text.size(); ++i) {
    switch (text[i]) {
    case 'b':
      counts[0]++;
      break;
    case 'a':
      counts[1]++;
      break;
    case 'l':
      counts[2]++;
      break;
    case 'o':
      counts[3]++;
      break;
    case 'n':
      counts[4]++;
      break;
    default:
      break;
    }
  }

  // l and o are double
  counts[2] /= 2;
  counts[3] /= 2;

  size_t min_count = text.size();

  for (size_t i = 0; i < counts.size(); ++i) {
    if (counts[i] < min_count) {
      min_count = counts[i];
    }
  }

  return min_count;
}