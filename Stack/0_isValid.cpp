#include <ios>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

/**
20. Valid Parentheses
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.


Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false


Constraints:

1 <= s.length <= 10^4
s consists of parentheses only '()[]{}'.


Idea and proof of correctnes:

idea: use stack of char to store all the brackets there

- if open bracket found : push
- if close bracket found : try to pop : if can't => return false;
if the top result before pop was not the paired => return false;

- In the end return, whether the stack is empty or not

Proof of correctness:

a)

String is valid (definition by induction), if:

 - it is empty string
 - it is one from the list:
      - valid1 (valid2)
      - valid1 {valid2}
      - valid3 [valid2]

b) Let's prove : string is valid <=> algorithm returns true

1) =>

Let's proof: valid => algorithm returns true

- empty string is valid. For empty string the algorithm does no loop iterations
and returns balance.empty(); The balance stack is empty. Therefore, it returns
true

- suppose, algorithm returns true on valid1 and valid2
Now, let's prove it returns true on the
 "valid1 (valid2)", "valid1 {valid2}", "valid1 [valid2]" strings

 Suppose, it is not true.
 Then, it returns false.
   - if the stack wasn't empty after all iterations. On each iteration
    (if no return happened, an no return happened, cause we returned after the
loop) we pushed and popped something to the stack. It means that stack is not
empty <=> the string has different number of close and open brackets But valid1
and valid2 (because, algorithm returned true for them) had the same number of
close and open brackets => "valid1 (valid2)", "valid1 {valid2}", "valid1
[valid2]" also have the same number of open and close brackets, contradiction



   - if the stack was empty before some iteration:
      - the iteration was at valid1, but then it means valid1 is not valid,
        contradiction

      - the iteration was at '('/'{'/'[', but at that moment, we are pushing a
bracket to the stack, contradiction

      - the iteration was at valid2 and it was at closing bracket (otherwise, it
is ok), then it means that that for valid2 the "#open - #close" is -1 (after
"valid1", the "#open - #close" is 0, at position i, the "#open - #close" of
"valid2" is less than "#open - #close" of "(valid2"/"{valid2"/"[valid2" on 1,
therefore the "#open - #close" of valid2 should be 0 - 1 = -1) and it is not
valid but this can't be true, contradiction

      - the iteration was ')'/'}'/']', but then it means,
        that the "#open - #close" of "valid1(valid2)"/"valid1 {valid2}"/"valid1
[valid2]" is -1.
        => the "#open - #close" of "(valid2)"/"{valid2}"/"[valid2]" is -1
        => the "#open - #close" of "valid2" should
        also be -1, which means, balance stack should be empty before the end of
loop for valid2 and valid2 is not valid string, contradiction

    therefore, in all cases we have contradiction =>
    contradiction

    - if the stack contained the wrong open bracket at some iteration
      - if it was valid1, it means, it should have happened for valid1, but
valid1 is valid, contradiction

      - it happened at '('/'{'/'[', but at that moment, we are pushing a bracket
to the stack, contradiction

      - it was at valid2 and it was at closing bracket (otherwise, we are
pushing), then
          - the paired string is '('/'{'/'[' (the one before valid2)
            but then, it means, that the "#open - #close" after this iteration
is 0 (because, we found the closing bracket for the first bracket (because, all
following were popped) in "(valid2)"/"{valid2}"/"[bracket2]", and before that
the balance was 0 => after this iteration is 0)

            this means, "#open - #close" for the valid2 after this iteration was
- 1, but then valid2 is not valid, contradiction

          - the paired bracket is a bracket from valid2, but this means,
          the only difference in push/pop history for this iteration i is:
                in "(valid2)"/"{valid2}"/"[valid2]" :
                     pushed first bracket,
                     action 1
                     action 2
                     ...
                     action i
                in "valid2":
                     action 1
                     action 2
                     ...
                     action i
          Let's prove this by induction:
              if action 1 is push, then it is the same for both strings
              if action 1 is pop, then valid2 is not valid, contradiction

              suppose, the actions are the same for all actions until j

              if action j + 1 is push, then it is the same for both strings
              if action j + 1 is pop, then because, all actions before were the
same, the stack for "(valid2)"/"{valid2}"/"[valid2]" is:
                  -"("/"{"/"[" ; br1; br2; br3; ...; br_k;
              and the stack for "valid2" is:
                  - br1; br2; br3; ....; br_k;
              if k is 0, then stack is empty for valid2 at some iteration,
contradiction if k is not 0, then we will compare the current bracket with br_k
in both cases (in "valid2" and in "(valid2)"/"{valid2}"/"[valid2]") and the
result of comparison will be the same
              => the action j + 1 is the same

          Therefore, if the paired bracket is not the same in
"(valid2)"/"{valid2}"/"[valid2]", it is not the same in "valid2", but then
"valid2" should be not valid contradiction

      Therefore, it can't happen at closing bracket of valid2,
      contradiction


      - it was at ')'/'}'/']' bracket. Because, the action history is the same
      for "valid2" and "(valid2)"/"{valid2}"/"[valid2]" (as was proved before)
      then it means, that the only bracket to pop should be '('/'{'/'['
      but open and close brackets are the same, there should be no problem,
      contradiction


    Therefore, we have contradiction in all cases =>
    contradiction

Therefore, the stack wasn't empty, the stack at any iteration or after
and we didn't have unpaired brackets. Therefore, the algorithm couldn't return
false. Contradiction. The algorithm should return true


2) <=


Let's prove : the algorithm returns true => the string is valid

Suppose, the algorithm returned true, but the string was not valid.
The algorithm returned true
=> therefore
- the number of open and close brackets was the same
- the balance was never <= 0 for any moment
- there are no wrongly paired brackets

Let's prove, the string can be formed as the patterned defined before
If the string is empty, then it aligns with pattern, defined before.

If the string is not empty, let's take the last bracket.
It can't be open bracket (otherwise, the last push will make the stack empty)
It is close bracket.

Now, let's consider, the bracket that was matched with it.
It is some open bracket at position i.

Because, in the end the stack was empty, before adding this open
bracket, the stack was also empty
(otherwise, we needed, to pop something after popping this open bracket,
and this stack is not empty)

This means, that for all the brackets before i, the stack is empty
and moreover, it was empty on each iteration and there was no unpaired brackets
Let's call this string beta.

Now, let's consider, the string "alpha" between the found open and last close
brackets

All actions, historis and states of the stack are the
are the same for "(alpha)"/"{alpha}"/"[alpha]" and "alpha"

the only two differences in push/pop history for this iteration are
pushed first bracket and popped last bracket, that are
present in "(alpha)"/"{alpha}"/"[alpha]" and not present in "alpha":

                in "(alpha)"/"{alpha}"/"[alpha]" :
                     pushed first bracket,
                     action 1
                     action 2
                     ...
                     action i
                     ...
                     action n
                     popped last bracket

                in "alpha":
                     action 1
                     action 2
                     ...
                     action i
                     ...
                     action n

Let's prove this by induction:
              if action 1 is push, then it is the same for both strings
              if action 1 is pop, then it means '('/'{'/'[' are paired
              with the first element of alpha, but then
              it means that '('/'{'/'[' was removed before the
              ')'/'}'/']' last iteration and ')'/'}'/']' was paired
              with some bracket in alpha and '('/'{'/'[' is not the one
              it was paired with,
              contradiction => the action can't be pop

              if action j + 1 is push, then it is the same for both strings
              if action j + 1 is pop, then because, all actions before were the
same, the stack for "(alpha)"/"{alpha}"/"[alpha]" is:
                  -"("/"{"/"[" ; br1; br2; br3; ...; br_k;
              and the stack for "alpha" is:
                  - br1; br2; br3; ....; br_k;
              if k is 0, then stack is empty for alpha at some iteration,
contradiction if k is not 0, then we will compare the current bracket with br_k
in both cases (in "alpha" and in "(alpha)"/"{alpha}"/"[alpha]") and the
result of comparison will be the same
              => the action j + 1 is the same


Therefore, it means, that all brackets in alpha were paired with themselves,
this means, that the number of open/close was equal,
they were paired the same way as in "(alpha)"/"{bracket}"/"[bracket]" =>
they were paired correctly
Moreover, the balance couldn't be zero in any close iteration of alpha.
Suppose, it was 0, it means, it was 1 in "(alpha)"/"{bracket}"/"[bracket]" at
some iteration

But, because, all the brackets were paired correctly,
it means that the bracket at that iteration was paired with the first bracket.

But the first bracket is paired with the last, not with the one from alpha,
contradiction.

Therefore, it means, that all brackets were paired correctly, the balance was
empty after all iterations and never was <= 0 on any iteration.


Now, the initial string can be expressed as
 "beta (alpha)"/"beta {alpha}"/ "beta [alpha]",

By induction, let's prove the initial string was valid.
The string of size 0 is valid.
Now, suppose, all strings with the size, less than initial,
that have the same properties ( all brackets were paired correctly, the balance
was empty after all iterations and never was <= 0 on any iteration) are valid.

We proved, that alpha and beta have the same properties.
Therefore, they are valid.

Therefore, the string can be reprsented in the form:
"valid1 (valid2)"/"valid1 {valid2}"/ "valid1 [valid2]"

Therefore, the initial string is valid


3) Finally, we proved, that
string is valid <=> algorithm returns true.

Moreover, the algortithm does O(1) on each iteration.

Therefore, it is correct O(n) algorithm.







**/

using namespace std;

class Solution {
public:
  bool isValid(const string &s) {
    unordered_map<char, char> open_close = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    unordered_map<char, char> close_open = {{')', '('}, {']', '['}, {'}', '{'}};
    stack<char> balance;
    for (size_t i = 0; i < s.size(); ++i) {
      if (open_close.contains(s[i])) {
        balance.push(s[i]);
      } else if (close_open.contains(s[i])) {
        if (balance.empty()) {
          return false;
        } else if (balance.top() != close_open[s[i]]) {
          return false;
        } else {
          balance.pop();
        }
      }
    }
    return balance.empty();
  }
};

int main() {
  Solution solution;
  string s;
  getline(cin, s);
  cout << boolalpha << solution.isValid(s) << "\n";
}