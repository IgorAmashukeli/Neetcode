#include <cassert>
#include <cstddef>
#include <ios>
#include <iostream>
#include <stack>
#include <vector>

/**
946. Validate Stack Sequences

Given two integer arrays pushed and popped each with distinct values, return
true if this could have been the result of a sequence of push and pop operations
on an initially empty stack, or false otherwise.


Example 1:

Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4),
pop() -> 4,
push(5),
pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
Example 2:

Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.


Constraints:

1 <= pushed.length <= 1000
0 <= pushed[i] <= 1000
All the elements of pushed are unique.
popped.length == pushed.length
popped is a permutation of pushed.

idea and proof of correctness: explained in code comments


**/

using namespace std;

class Solution {
public:
  bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
    size_t i = 0, j = 0;
    stack<int> test = {};
    while (i != popped.size()) {
      // i != popped.size() => we didn't pop everything
      // it is not the end => we need to do some operations

      if (test.empty() || popped[i] != test.top()) {

        // stack.empty() => the stack size is empty => we can't pop =>
        // we can only push
        // popped[i] != stack.top()
        // => the top element is not the one we can pop now
        // => we can only push
        // in both cases we can only push
        // we need to do some operations =>
        // we need to push

        if (j < pushed.size()) {

          // j < pushed.size() =>
          // the pushed array wasn't exhausted
          // we can push

          test.push(pushed[j]); // we push
          j++;                  // we mark that we pushed an element

        } else {

          // if j == pushed.size() => we pushed
          // n times => everything is pushed
          // but we need to push, because we can't pop
          // we can't neither push nor pop

          // upper we explained why in case
          // stack.empty() || popped[i] != stack.top()
          // we need to push

          // below we explain why in case
          // stack.size() != 0 && popped[i] == stack.top()
          // we need to pop

          // therefore, if we reached this branch
          // on all previous iterations we did the only possible operation
          // there exists only one possible order to check
          // and this order is wrong
          // therefore, the whole two input arrays were in wrong order
          // we need to return false

          return false;
        }
      } else {
        // the stack size is not 0 and the last element in the stack
        // is equal to the one we can pop
        // pushed and popped have unique values
        // if we push now on iteration, say, s, we can't do pop on any other
        // iteration and popped index will remain on i suppose, we can't do pop
        // and index is after i before iteration k
        // => on iteration k index is on i, we can't do pop, because
        // => because pushed array has unique values =>
        // stack.top(){iteration s} != stack.top(){iteration k} and
        // popped[i] == stack.top(){iteration s}
        // => popped[i] != stack.top(){iteration k}
        // => we can't pop
        // => we will push on each iteration
        // => we will reach the end of pushed array
        // but we will not reach the end of popped array
        // and we will need to pop, but we will not be able to
        // => this is wrong order of operation to validate the stack
        // => therefore, we need to choose another order
        // => we can't not to pop
        // => we pop

        test.pop(); // we pop
        i++;        // we mark the popped array
      }
    }
    // if reached this point: i++ is done n times
    // therefore test.pop() is done n times
    // there can't be more than n push
    // therefore, there were n pushes
    // everything was pushed and popped
    // the stack is empty
    assert(test.empty());

    // everything was correct

    return true;
  }
};

int main() {
  vector<int> pushed = {1, 2, 3};
  vector<int> popped = {3, 2, 1};
  Solution solution = Solution();
  cout << boolalpha << solution.validateStackSequences(pushed, popped) << "\n";
}
