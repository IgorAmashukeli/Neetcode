#include <cassert>
#include <cstddef>
#include <iostream>
#include <stack>
#include <tuple>
#include <unordered_map>

/**
895. Maximum Frequency Stack
Design a stack-like data structure to push elements to the stack and pop the
most frequent element from the stack.

Implement the FreqStack class:

FreqStack() constructs an empty frequency stack.
void push(int val) pushes an integer val onto the top of the stack.
int pop() removes and returns the most frequent element in the stack.
If there is a tie for the most frequent element, the element closest to the
stack's top is removed and returned.


Example 1:

Input
["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop",
"pop", "pop"]
[[], [5], [7], [5], [7], [4], [5], [], [], [], []]
Output
[null, null, null, null, null, null, null, 5, 7, 5, 4]

Explanation
FreqStack freqStack = new FreqStack();
freqStack.push(5); // The stack is [5]
freqStack.push(7); // The stack is [5,7]
freqStack.push(5); // The stack is [5,7,5]
freqStack.push(7); // The stack is [5,7,5,7]
freqStack.push(4); // The stack is [5,7,5,7,4]
freqStack.push(5); // The stack is [5,7,5,7,4,5]
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes
[5,7,5,7,4]. freqStack.pop();   // return 7, as 5 and 7 is the most frequent,
but 7 is closest to the top. The stack becomes [5,7,5,4]. freqStack.pop();   //
return 5, as 5 is the most frequent. The stack becomes [5,7,4]. freqStack.pop();
// return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top.
The stack becomes [5,7].


Constraints:

0 <= val <= 10^9
At most 2 * 10^4 calls will be made to push and pop.
It is guaranteed that there will be at least one element in the stack before
calling pop.

idea:

max_freq:
 when push new value and its freq start to be > max_freq => increment max_freq
 when pop value and its freq start to be < max_freq => decrement max_freq

unordered_map of counts: when push new value => add count of such value
                         when pop most freq value => decrement count of such
value

unordered_map of stacks:
when push new value => add value to the stack of
the current count + 1

when pop most freq value => take unordered_map of stack and pop the value from
most freq stack

**/

using namespace std;

class FreqStack {
public:
  FreqStack() {}

  void push(int val) {
    if (!counts_.contains(val)) {
      counts_[val] = 1;
      values_[1].push(val);
      if (max_freq_ == 0) {
        max_freq_ = 1;
      }
    } else {
      counts_[val]++;
      values_[counts_[val]].push(val);
      if (max_freq_ < counts_[val]) {
        max_freq_ = counts_[val];
      }
    }
  }

  int pop() {
    assert(max_freq_ != 0);
    assert(!values_[max_freq_].empty());
    int value = values_[max_freq_].top();
    counts_[value]--;
    if (counts_[value] == 0) {
      counts_.erase(value);
    }
    values_[max_freq_].pop();
    if (values_[max_freq_].empty()) {
      values_.erase(max_freq_);
      max_freq_--;
    }
    return value;
  }

private:
  unordered_map<int, size_t> counts_ = {};
  unordered_map<int, stack<int>> values_ = {};
  size_t max_freq_ = 0;
};

int main() {
  FreqStack freqStack = FreqStack();
  freqStack.push(5);               // The stack is [5]
  freqStack.push(7);               // The stack is [5,7]
  freqStack.push(5);               // The stack is [5,7,5]
  freqStack.push(7);               // The stack is [5,7,5,7]
  freqStack.push(4);               // The stack is [5,7,5,7,4]
  freqStack.push(5);               // The stack is [5,7,5,7,4,5]
  cout << freqStack.pop() << "\n"; // return 5, as 5 is the most frequent. The
                                   // stack becomes [5,7,5,7,4].
  cout << freqStack.pop()
       << "\n"; // return 7, as 5 and 7 is the most frequent, but 7 is
                // closest to the top. The stack becomes [5,7,5,4].
  cout << freqStack.pop() << "\n"; // return 5, as 5 is the most frequent. The
                                   // stack becomes [5,7,4].
  cout << freqStack.pop()
       << "\n"; // return 4, as 4, 5 and 7 is the most frequent, but 4 is
                // closest to the top. The stack becomes [5,7].
}