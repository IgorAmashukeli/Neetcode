#include <cstddef>
#include <iostream>
#include <stack>
#include <vector>

/**
739. Daily Temperatures


Given an array of integers temperatures represents the daily temperatures,
return an array answer such that answer[i] is the number of days you have to
wait after the ith day to get a warmer temperature. If there is no future day
for which this is possible, keep answer[i] == 0 instead.



Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]


Constraints:

1 <= temperatures.length <= 10^5
30 <= temperatures[i] <= 100


idea: next greater problem

Monotonous Stack of pairs value + index + reverse scan

proof of correctness:

Let's proof that on any iteration in push function
of MonotonousStack after while loop with pop calls
stack can either
    - be empty, when there are no next greater value
    - contain at the top the next greater value with its index


Proof by induction:

- on the first iteration: the stack is empty at start =>
it is empty after loop. Moreover, there are no next greater
value for the last element in array. Therefore, the previous
statement holds

- Suppose, this feature holds for all indices > j
  The function push was called on arr[j].

  Suppose, there are no value k such that
  k > j and arr[k] > arr[j]
  Suppose, the state of the stack is as follows:
  a_1...a_m, m >= 0
  Then, because on previous iterations we pushed
  only arr[s], where s > j, then it means
  that for all i 1 <= i <= m a_i <= arr[j]
  Therefore, all of them will be popped.
  Therefore, the stack will be empty


  Suppose, there is a value k such that
  k > j and arr[k] > arr[j]
  Let's select the value with lowest index t:
  suppose arr[t] > arr[j] and t is the smallest
  such index.
  This means, that for all j < r < t:
  arr[r] <= arr[j]
  (because t is the lowest index, for which
  arr[t] > arr[j]).
  Therefore arr[t] > arr[r]
  Therefore for all r : j < r < t, when pushing
  arr[r], arr[t] is not popped.

  Therefore, when arr[j] is pushed, arr[t] is in the stack.
  Therefore, the stack looks like this:

  arr[t] a_1...a_m

  For all i 1 <= i <= m a_i is arr[r], where j < r < t
  for all such r: arr[r] <= arr[j].
  Therefore, all arr[r] are removed => therefore
  after the loop the stack looks like this:

  arr[t]


  Therefore, we proved, that the algorithm works correctly.


  Time complexity:

  On each iteration we do push to Monotonous Stack.
  Each push to Monotonous Stack we have push and pops to the stack
  Each value from n-size input is pushed to the stack only once.
  Therefore, there are no more than n push calls.
  Therefore, there are no more than n pop calls.
  Therefore, the time complexity is O(n)








**/

using namespace std;

class MonotonousStack {
public:
  MonotonousStack() {}
  size_t push(int element, size_t index) {
    while (!stack_.empty() && stack_.top().first <= element) {
      stack_.pop();
    }
    size_t difference;
    if (stack_.empty()) {
      difference = 0;
    } else {
      difference = stack_.top().second - index;
    }

    stack_.push({element, index});
    return difference;
  }

private:
  stack<pair<int, size_t>> stack_;
};

class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    vector<int> answer;
    answer.resize(temperatures.size());

    MonotonousStack monotonousStack = MonotonousStack();

    for (size_t i = 0; i < temperatures.size(); ++i) {
      size_t j = answer.size() - i - 1;
      size_t difference = monotonousStack.push(temperatures[j], j);
      answer[j] = difference;
    }

    return answer;
  }
};

int main() {
  vector<int> temperatures = {30, 60, 90};
  Solution solution = Solution();
  vector<int> answer = solution.dailyTemperatures(temperatures);
  for (int element : answer) {
    cout << element << " ";
  }
  cout << "\n";
}