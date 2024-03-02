#include <iostream>
#include <string>
#include <vector>

/**
22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.



Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]


Constraints:

1 <= n <= 8

idea: backtracking
- we can add "(" only if 2 * open_counter < size brackets created
- we can add ")" only if open_counter > close_counter

Proof of correctness.
From the task about checking the string parenthesis for validity,
we know:

-the string is valid <=>
    - the number of open brackets equal to the number of close brackets
    - the number of close brackets is less than number of open in any prefix
    - the pair brackets have the same type

All the brackets have the same type in our example.

Therefore:

-the string is valid <=>
    - the number of open brackets equal to the number of close brackets
    - the number of close brackets is less or equal than number of open in any
prefix

Therefore,

- If in prefix, created by adding ")" the number of close brackets >
than the number of open => this branch is not ok => in current prefix we exclude
the situation, when number of ")" is >= than the number of "("


- If in prefix, created by adding "(" the number of open brackets > size / 2
=> this branch is not ok => in current prefix we exclude the situation, when
number of "(" is <= number of ")"


Therefore, we excluded only non-valid sequences

Let's proof that we excluded all non-valid sequence.

Suppose, there exists a sequence, which is non-valid, but wasn't deleted.
Suppose, the number of close brackets is bigger than the number of open in any
prefix. Let's consider the least such bracket. close > open; open >= 0 => close
> 0 => close + open >= 1
=> it has at least one bracket.
Let's consider the prefix without the last added bracket.

Now it close <= open
(because it was the least one with close > open)
Because, we deleted only one bracket, now close = open.
Therefore, it was close bracket.
Now open == close. Now we only have a call to add an open bracket,
because
 if (open > close) {
    backtracking(answer, new_str, size, open, close + 1);
 }
will never be called.
So, the only bracket added will be open one. Contradiction.


Therefore, it means, in all prefixes close <= open
Therefore, in the last prefix (in all string): close < open
(because, otherwise, if close = open and for all prefixes close <= open, the
string is valid)

Therefore, it means, open > close => open > n / 2
Let's consder the last prefix, for which this wasn't true
Because, after adding one bracket opne > n / 2 and before that open <= n / 2,
it means, that open = n / 2 in this prefix and we added open bracket.

Now, open = n / 2. Now we only have a call to add a close bracket, because

 if (open * 2 < size) {
    backtracking(answer, new_str, size, open + 1, close);
 }
 will never be called.



**/

using namespace std;

class Solution {
public:
  void backtracking(vector<string> &answer, string &str, size_t size,
                    size_t open, size_t close) {
    if (str.size() < size) {
      string new_str = str + '(';
      if (open * 2 < size) {
        backtracking(answer, new_str, size, open + 1, close);
      }
      new_str = str + ')';
      if (open > close) {
        backtracking(answer, new_str, size, open, close + 1);
      }
    } else {
      answer.push_back(str);
      return;
    }
  }

  vector<string> generateParenthesis(int n) {
    vector<string> answer;
    string str = "";
    backtracking(answer, str, 2 * n, 0, 0);
    return answer;
  }
};

int main() {
  vector<string> answer = Solution().generateParenthesis(8);
  for (auto &elem : answer) {
    cout << elem << " ";
  }
  cout << "\n";
}