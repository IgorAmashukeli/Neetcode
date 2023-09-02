/**Given a string s, partition the string into one or more substrings such that
the characters in each substring are unique. That is, no letter appears in a
single substring more than once.

Return the minimum number of substrings in such a partition.

Note that each character should belong to exactly one substring in a partition.



Example 1:

Input: s = "abacaba"
Output: 4
Explanation:
Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
It can be shown that 4 is the minimum number of substrings needed.
Example 2:

Input: s = "ssssss"
Output: 6
Explanation:
The only valid partition is ("s","s","s","s","s","s").


Constraints:

1 <= s.length <= 10^5
s consists of only English lowercase letters.

idea: greedy growing, until found dubplicate by hashSet

correctness:

suppose, there is way to do it better, with less number of divisions
Suppose, this number is k
The divisions are at positions i_1, ..., i_k
Then, there is no duplicates in a_0 - a_{i_1}
If there are more elements with no duplicates after a_{i_1},
our answer will have index_1 > i_1.
In general, index_1 >= i_1
It can't be < i_1, otherwise it means a_0 - a{i_1} has duplicates,
but it hasn't, cause it was a correct way to divide

Then, index_s >= i_s
By induction index_{s-1} >= i_{s-1}
If index_{s - 1} >= i_s => index_{s} >= i_s
Otherwise, i_{s - 1} <= index_{s-1} <= i_s
Suppose, index_s < i_s
=>
i_{s - 1} <= index_{s_1} <= index_{s} < i_s
That means [a_{index_{s_1}}...a_{index_{s} + 1}] has duplicates
That means  [a_{i_{s-1}} ... a_{i_s}] has duplicates
That means, that was invalid way to divide
Contradiction


time: O(n)
space: O(26) = O(1)
**/

#include <string>
#include <unordered_set>

using namespace std;

int partitionString(string s) {
  // letters of the current substring
  unordered_set<char> letters;

  // number of substrings that were divided
  // initially non empty
  int count = 1;

  // iterate through string
  for (char chr : s) {

    // if char was met => restore letters, new division
    if (letters.contains(chr)) {
      letters = {};
      ++count;
    }

    // add letter
    letters.insert(chr);
  }

  return count;
}