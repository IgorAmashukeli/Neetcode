#include <iostream>
#include <stack>
#include <string>
#include <vector>

/**
150. Evaluate Reverse Polish Notation

You are given an array of strings tokens that represents an arithmetic
expression in a Reverse Polish Notation.

Evaluate the expression. Return an integer that represents the value of the
expression.

Note that:

The valid operators are '+', '-', '*', and '/'.
Each operand may be an integer or another expression.
The division between two integers always truncates toward zero.
There will not be any division by zero.
The input represents a valid arithmetic expression in a reverse polish notation.
The answer and all the intermediate calculations can be represented in a 32-bit
integer.


Example 1:

Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22


Constraints:

1 <= tokens.length <= 10^4
tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the
range [-200, 200].

idea: use stack

Proof of correctness:


Let's define the reverse Polish Notation expression.

["a"] is a RPN
if [a_1, .., a_k] and [b_1, ..., b_m] are RPN, then
[a_1, .., a_k, b_1, ..., b_m, "+"]
[a_1, .., a_k, b_1, ..., b_m, "-"]
[a_1, .., a_k, b_1, ..., b_m, "*"]
[a_1, .., a_k, b_1, ..., b_m, "/"] are also RPN

eval(["a"]) = a
eval([a_1, .., a_k, b_1, ..., b_m, "+"]) = eval([a_1, .., a_k]) + eval([b_1,
..., b_m]) eval([a_1, .., a_k, b_1, ..., b_m, "-"]) = eval([a_1, .., a_k]) -
eval([b_1, ..., b_m]) eval([a_1, .., a_k, b_1, ..., b_m, "*"]) = eval([a_1, ..,
a_k]) * eval([b_1, ..., b_m]) eval([a_1, .., a_k, b_1, ..., b_m, "/"]) =
eval([a_1, .., a_k]) / eval([b_1, ..., b_m])


We are given a correct RPN. Our task is to evaluate it
Algorithm.
Scan the RPN.
If found a number, add the number to the stack
If found an operation, pop two previous values of the stack and push the result
of the operation. The top value in the stack is the result.


Let's prove that algorithm works correctly.
It always has one value in the stack and this value is the evaluation of RPN

1) If the RPN is ["a"], then algorithm will push the value to the stack
and the top value in the stack is "a", which is indeed the evaluation of RPN


2)
Let's assume, the algorithm works correctly for any RPN with size < k + m + 1
Let's prove, it works correctly for any RPN with size k + m + 1

RPN is represented with such an array: [a_1, .., a_k, b_1, ..., b_m, operation]

When algorithm reached a_k and moved to b_1, we know, that [a_1, ..., a_k]
is a correct RPN of size k. The algorithm works correctly with it.
Therefore, the stack contains eval(a_1, .., a_k)

Because, [b_1, ..., b_m] is a correct RPN of size m.
If the stack was empty, we would have the eval(b_1, ..., b_m) value only in the
stack Now we will have eval(a_1, .., a_k), eval(b_1, ..., b_m)

 We can prove this by induction:
 - the first operation is always push, because [b_1, ..., b_m] is a correct RPN
 - the state of the stack with empty stack : b_1
 - the state of the stack with eval(a_1, .., a_k): eval(a_1, .., a_k), b_1

 - suppose for operation < i the only difference is the first value
 - now, let's draw the state of the stacks before the i-the operation:
      - with empty: u_1, ..., u_t           // these are some t values
      - with eval(a_1, .., a_k): eval(a_1, .., a_k) u_1, ..., u_t

 - if i-th operation is "push number b_i"
      - with empty: u_1, ..., u_t, b_j
      - with eval(a_1, .., a_k): eval(a_1, .., a_k) u_1, ..., u_t, b_j

- if i-th operation is "make operation with b_i sign"
  Then, because [b_1, ..., b_m] is a correct RPN and algorithm works correctly
with m-size RPN, we can say that t >= 2. Let's say t = s + 2 (Otherwise, if t <
2, the algorithm will pop from empty and crash and this is contradiction with
correctness of the algorithm on the m-size RPN)
      - with empty : u_1, ..., u_s, b_j (u_{s+1}, u_{s+2})
      - with eval(a_1, .., a_k) : u_1, ..., u_s, b_j(u_{s+1}, u_{s+2})

  Therefore, for the last operation, the algorithms also works as follows:

  the state of the stack in our case is: eval(a_1, .., a_k) eval(b_1, ..., b_m)

  After the stack will have op (eval(a_1, .., a_k), eval(b_1, ..., b_m))
  = eval([a_1, .., a_k, b_1, ..., b_m, op])


  Therefore, the algorithm works correctly with the RPN of size m + k + 1

  Therefore, the algorithm correctly evaluates the RPN
**/

using namespace std;

class Solution {
private:
  void do_operation(stack<int> &values, int (*func)(int, int)) {
    int top_value = values.top();
    values.pop();
    int top_two_value = values.top();
    values.pop();
    int result = func(top_two_value, top_value);
    values.push(result);
  }

public:
  int evalRPN(vector<string> &tokens) {
    stack<int> values;
    for (size_t i = 0; i < tokens.size(); ++i) {
      if (tokens[i] == "+") {
        do_operation(values, [](int a, int b) { return a + b; });
      } else if (tokens[i] == "*") {
        do_operation(values, [](int a, int b) { return a * b; });
      } else if (tokens[i] == "-") {
        do_operation(values, [](int a, int b) { return a - b; });
      } else if (tokens[i] == "/") {
        do_operation(values, [](int a, int b) { return a / b; });
      } else {
        values.push(stoi(tokens[i]));
      }
    }
    return values.top();
  }
};

int main() {
  vector<string> input = {"10", "6", "9",  "3", "+", "-11", "*",
                          "/",  "*", "17", "+", "5", "+"};
  cout << Solution().evalRPN(input) << "\n";
}