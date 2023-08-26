/**You are given a 0-indexed string s of even length n. The string consists of
exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.

A string is called balanced if and only if:

It is the empty string, or
It can be written as AB, where both A and B are balanced strings, or
It can be written as [C], where C is a balanced string.
You may swap the brackets at any two indices any number of times.

Return the minimum number of swaps to make s balanced.



Example 1:

Input: s = "][]["
Output: 1
Explanation: You can make the string balanced by swapping index 0 with index 3.
The resulting string is "[[]]".
Example 2:

Input: s = "]]][[["
Output: 2
Explanation: You can do the following to make the string balanced:
- Swap index 0 with index 4. s = "[]][][".
- Swap index 1 with index 5. s = "[[][]]".
The resulting string is "[[][]]".
Example 3:

Input: s = "[]"
Output: 0
Explanation: The string is already balanced.


Constraints:

n == s.length
2 <= n <= 10^6
n is even.
s[i] is either '[' or ']'.
The number of opening brackets '[' equals n / 2, and the number of closing
brackets ']' equals n / 2.

idea:
count maximum number of unpaired ']',
if 0 => answer is 0,
if 2k => answer is k,
if 2k + 1 => answer is k + 1

proof of correctness:

1) First statement:
If number of unpaired ']' is 0, the string is valid, the result is 0, obviously
2) Second statement:

If the string is actually ']]]..]]  [[[..[[' and the wing has 2k parenthesis,
we can make it valid in k swaps

Proof: do this: '[[[...]]] [[[...]]]'
swap edge left and edge right k parenthesis, and do not move middle k
parenthesis, then the answer is valid string, cause left and right wing are
k-nested valid strings

3) Third statement:

If the string is actually ']]]..]]  [[[..[[' and the wing has 2k + 1
parenthesis, we can make it valid in k + 1 swaps

Proof: do this '[  [[[...]]] [[[...]]] ]'
swap edge left and edge right k + 1 parenthesis, and do not move middle k + 1
parenthesis, then the answer is valud string, cause left and right wing are k -
nested valid strings, and the this valid string inside '[ ]' is also valid

4) Fourth statement:

If the string is actually ']]]..]]  [[[..[[' and the wing has 2k parenthesis,
we can't make it valid less then in k steps and if the wing has 2k + 1
parenthesis, we can't make it valid less then in k + 1 steps

Proof:
1) It is obvious, we won't do unnecessary swaps inside one wing
2) If we do k - t, where t > 0 swaps in first case, left wing will contain k - t
open and k + t closed once, which means, we have more closed, than open at
position 2k, which means string is not valid 3) If we do k + 1 - t, where t > 0
swaps in first case, left wing will contain k + 1 - t open and k + t closed
once, t > 0
=>
t >= 1
=>
1 - t <= 0
=>
k + t > k >= k + 1 - t
=> which means, we have more closed, than open at position 2k + 1, which means
string is not valid

5) Fifth statement:

If parenthesis is not valid, we can find the number of pairs of matched,
remove them, and get ]]]]....[[[[ pattern

Proof:
Number of open and closed in matched pairs is the same. Therefore,
after removing all the pairs, we get the same number of closed and open
None of open can go before close, otherwise, it will be a match.
Therefore we have 2k or 2k + 1 number of closed, then the same number of open

6) Sixth statement:

The minimum number of swaps doesn't change after removing all matched pairs

Proof:

TO DO((((

7) Seventh statement:

The number of minimum swaps equals the number of swaps in ]]]]...[[[[,
which equals k in case of 2k-wing, and which equals k + 1 in case of 2k +
1-wing.

time: O(n)
space: O(1)

**/

#include <string>

using namespace std;

int minSwaps(const string &s) {
  int balance = 0;
  int min_balance = 0;
  for (char a : s) {
    if (a == '[') {
      balance += 1;
    } else {
      balance -= 1;
    }
    if (balance < min_balance) {
      min_balance = balance;
    }
  }

  // string is valid => return 0
  if (min_balance == 0) {
    return 0;
  }

  // the left wing of ]]]]...[[[[ has 2k parenthesis
  // => number of swaps is k
  if (min_balance % 2 == 0) {
    return (-min_balance) / 2;

    // the right wing of ]]]]...[[[[ has 2k + 1 parenthesis
    // => number of swaps is k + 1
  } else {
    return (-min_balance) / 2 + 1;
  }
}