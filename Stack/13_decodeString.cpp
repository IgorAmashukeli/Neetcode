#include <cassert>
#include <iostream>
#include <stack>
#include <string>

/**
394. Decode String

Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the
square brackets is being repeated exactly k times. Note that k is guaranteed to
be a positive integer.

You may assume that the input string is always valid; there are no extra white
spaces, square brackets are well-formed, etc. Furthermore, you may assume that
the original data does not contain any digits and that digits are only for those
repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed
105.



Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"
Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"
Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"


Constraints:

1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300].


idea:

when found [, it means that there will be a string that should be
repeated, and it starts from the next symbol, we remember the index
and the number in the stacl

when found ], it means that it is the end of some string and we need to
repeat it the number of times it is said in the stack and the string
to repeat should start from the index, which can be found in the stack too



we understand that any valid input can be represented as follows:

- empty string
- valid1_not_empty valid2_not_empty
- number[valid1]

answer(empty_string) = empty_string

answer(valid1_not_empty valid2_not_empty) =
answer(valid1_not_empty) answer(valid2_not_empty)

answer(number[valid1]) = answer(valid1)...answer(valid1) - number times

Let's proof that the algorithm works correctly:
the output string is correct and stack is empty at the end of string

if string is empty, the algorithm will return empty string
and the stack will be empty, because there will be no loops

Let's suppose, the algorithm works correctly for the strings of size
less than k, let's proof it works correctly for the strings of size k


- valid1_not_empty valid2_not_empty

If algorithm works correctly for the valid1 string and valid2 string
of size m and t, where m < k, t < k and m > 0 and t > 0,
then it will work correctly for the concatenation of the strings of size k = m +
t, because at the end of the valid1, we have correct output and the stack is
empty, we will reuse the stack and we will continue to add to the answer and the
answer will be answer(valid1_not_empty) answer(valid2_not_empty),
because the algorithm for valid2_not_empty works correctly, moreover,
the stack will be empty


- number[valid1]

we will push back number and the start index of valid1,
when found [
and the stack will be: (number, index)

Because, algorithm on valid1 will never pop more than push to the stack
(it works correctly)
and the size of the stack at the start has (number, index),
we will never pop this value
(if we popped it, we pushed less times before that)
Therefore, at the moment of ] the stack will value (number, index)
at the top of the stack.

We pop this value and add valid1 (because we have the correct index to start)
number - 1 times (1 time it is already added, when finished with valid1)
and therefore we will have

answer(number[valid1]) = answer(valid1)...answer(valid1) - number times
and the stack will be empty

Therefore, the algorithm is correct





**/

using namespace std;

class Solution {
private:
  bool is_digit(char element) {
    return element - '0' >= 0 && element - '0' <= 9;
  }

public:
  string decodeString(const string &s) {
    stack<pair<size_t, int>> multies = {};
    string answer = "";
    string cur_number = "";
    for (size_t i = 0; i < s.size(); ++i) {
      if (is_digit(s[i])) {

        cur_number += s[i];

      } else if (s[i] == '[') {

        assert(cur_number != "");
        int number = stoi(cur_number);
        cur_number = "";
        multies.push({answer.size(), number});

      } else if (s[i] == ']') {

        assert(!multies.empty());
        size_t start = multies.top().first;
        int multi = multies.top().second - 1;
        assert(multi >= 0);
        multies.pop();
        string to_repeat = answer.substr(start, answer.size());
        for (int i = 0; i < multi; ++i) {
          answer += to_repeat;
        }
      } else {
        answer += s[i];
      }
    }
    return answer;
  }
};

int main() {
  Solution solution = Solution();
  cout << solution.decodeString("3[z]2[2[y]pq4[2[jk]e1[f]]]ef") << "\n";
}