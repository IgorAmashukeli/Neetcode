#include <iostream>
#include <stack>

using namespace std;

class MonotonousStack {
public:
  MonotonousStack() {}

  void push(int elem, size_t index) {
    if (stack_.empty() || elem < stack_.top().first) {
      stack_.push({elem, index});
    }
  }

  pair<int, size_t> pop() {
    pair<int, size_t> value = stack_.top();
    stack_.pop();
    return value;
  }

  pair<int, size_t> top() { return stack_.top(); }

private:
  stack<pair<int, size_t>> stack_;
};

class MinStack {
public:
  MinStack() {}

  void push(int val) {
    size_t size = stack_.size();
    stack_.push(val);
    monotonous_stack_.push(val, size);
  }

  void pop() {
    stack_.pop();
    size_t size = stack_.size();
    size_t to_delete = monotonous_stack_.top().second;
    if (size == to_delete) {
      monotonous_stack_.pop();
    }
  }

  int top() { return stack_.top(); }

  int getMin() { return monotonous_stack_.top().first; }

private:
  stack<int> stack_;
  MonotonousStack monotonous_stack_;
};

int main() {
  MinStack minStack = MinStack();
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  cout << minStack.getMin() << "\n"; // return -3
  minStack.pop();
  cout << minStack.top() << "\n";    // return 0
  cout << minStack.getMin() << "\n"; // return -2
}