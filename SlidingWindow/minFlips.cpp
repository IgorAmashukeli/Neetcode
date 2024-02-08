#include <iostream>
#include <string>

/**
1888. Minimum Number of Flips to Make the Binary String Alternating
You are given a binary string s. You are allowed to perform two types of
operations on the string in any sequence:

Type-1: Remove the character at the start of the string s and append it to the
end of the string. Type-2: Pick any character in s and flip its value, i.e., if
its value is '0' it becomes '1' and vice-versa. Return the minimum number of
type-2 operations you need to perform such that s becomes alternating.

The string is called alternating if no two adjacent characters are equal.

For example, the strings "010" and "1010" are alternating, while the string
"0100" is not.


Example 1:

Input: s = "111000"
Output: 2
Explanation: Use the first operation two times to make s = "100011".
Then, use the second operation on the third and sixth elements to make s =
"101010". Example 2:

Input: s = "010"
Output: 0
Explanation: The string is already alternating.
Example 3:

Input: s = "1110"
Output: 1
Explanation: Use the second operation on the second element to make s = "1010".


Constraints:

1 <= s.length <= 10^5
s[i] is either '0' or '1'.

idea : first type operations have this set of results:

a_1...a_n -> a_2...a_n a_1 -> a_3 ... a_n a_1 a_2 -> ... -> a_n a_1 ... a_n

On each of them, we can find the number of operations needed to convert it into
01010... or to 10101... and choose the minimum one, and then update global
minimum.

For a_1...a_n we calculated it straightforward, using for loop
For all other configurations we use the previous two answers, modifying it,
according the parity of the size of the string and the value of the bit,
that we are shifting in O(1). Therefore, the time is O(n)

The explanations are given in comments below.


**/

using namespace std;

class Solution {
public:
  void inc(size_t &i, size_t size) {
    if (i + 1 < size) {
      ++i;
    } else {
      i = 0;
    }
  }

  int minFlips(const string &s) {
    int min_flips = s.size() + 1;
    if (s.size() == 1) {
      return 0;
    }

    int zero_starting_flips = 0;
    int one_starting_flips = 0;
    for (size_t i = 0; i < s.size(); ++i) {
      // if i % 2 == 0 in zero_starting alternation s[i] = 0
      // if i % 2 == 1 in zero_stating alternation s[i] = 1
      if (((i % 2 == 0) && (s[i] == '1')) || ((i % 2 == 1) && (s[i] == '0'))) {
        zero_starting_flips++;
        // if i % 2 == 0 in one_starting alternation s[i] = 1
        // if i % 2 == 1 in one_starting alternation s[i] = 0
      } else {
        one_starting_flips++;
      }
    }

    size_t j = 0;
    bool first_cycle = true;
    while (j != 0 || first_cycle) {
      for (size_t i = j; i < s.size(); i++) {
        cout << s[i];
      }
      for (size_t i = 0; i < j; i++) {
        cout << s[i];
      }
      cout << " " << zero_starting_flips << " " << one_starting_flips << "\n";
      if (j > 0) {
        first_cycle = false;
      }

      if (min(zero_starting_flips, one_starting_flips) < min_flips) {
        min_flips = min(zero_starting_flips, one_starting_flips);
      }

      // zero_starting
      // if s[j] == 0, we needed to flip it, because it was for one starting
      // if (s.size()) % 2 == 0 => nothing changes, in one_starting we needed to
      // flip => now need in the end of zero starting and if don't needed => now
      // don't need if (s.size() % 2 == 1) => if s[j] == 0, we needed to flip,
      // now don't need if s[j] == 1, we didn't needed to flip, we need
      // => s.size() % 2 == 0 => 0
      //    s.size() % 2 == 1 && s[j] == 0 => -1
      //    s.size() % 2 == 1 && s[j] == 1 =>  1
      //
      //
      // one_starting
      // if s[j] == 1, we needed to flip it, because it was for zero starting
      // if (s.size()) % 2 == 0 => nothing changes, in zero_starting we needed
      // to flip => now need in the end of one starting and if don't needed =>
      // now don't need if (s.size() % 2 == 1) => if s[j] == 0, we didn't need
      // to flip, we need to flip if s[j] == 1, we flipped, now we don't need
      // => s.size() % 2 == 0 =>  0
      //    s.size() % 2 == 1 && s[j] == 0 =>  1
      //    s.size() % 2 == 1 && s[j] == 1 => -1

      int zero_to_flip = 0;
      int one_to_flip = 0;
      if ((s.size() % 2 == 1) && (s[j] == '0')) {
        zero_to_flip = -1;
        one_to_flip = 1;
      } else if ((s.size() % 2 == 1) && (s[j] == '1')) {
        zero_to_flip = 1;
        one_to_flip = -1;
      }

      int old_zero_starting_flips = zero_starting_flips;
      zero_starting_flips = one_starting_flips + zero_to_flip;
      one_starting_flips = old_zero_starting_flips + one_to_flip;

      inc(j, s.size());
    }

    return min_flips;
  }
};

int main() { cout << Solution().minFlips("1110") << "\n"; }