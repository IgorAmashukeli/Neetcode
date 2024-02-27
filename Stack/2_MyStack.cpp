#include <iostream>
#include <queue>

/**
225. Implement Stack using Queues

Implement a last-in-first-out (LIFO) stack using only two queues. The
implemented stack should support all the functions of a normal stack (push, top,
pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.
Notes:

You must use only standard operations of a queue, which means that only push to
back, peek/pop from front, size and is empty operations are valid. Depending on
your language, the queue may not be supported natively. You may simulate a queue
using a list or deque (double-ended queue) as long as you use only a queue's
standard operations.


Example 1:

Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]

Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False


Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, top, and empty.
All the calls to pop and top are valid.


Follow-up: Can you implement the stack using only one queue?

2 queues:
empty: if both are empty
top: front from non-empty
pop: pop from non-empty
push: push to empty, pop everything from non-empty and push to the queue
with one element only one by one (the order now is correct):

non_empty : a_1,...,a_k
empty :

non_empty : a_1,...,a_k
empty : a_{k + 1}

non_empty : a_1, ..., a_{k - 1}
empty : a_{k}, a_{k + 1}

non_empty : a_1, ..., a_{k - 2}
empty : a_{k - 2}, a_{k}, a_{k + 1}

...

non_empty :
empty : a_1, ..., a_{k + 1}


1 queue:
empty: is queue empty?
top: take front value
pop: take front value and pop front it
push:

push to the queue and then size - 1 times pop_front and push_back this popped
value the order should be correct:

after push: a_{k + 1}, a_1, ..., a_{k}

one iteration: a_{k}, a_{k + 1}, a_1, ..., a_{k - 1}
second iteration : a_{k - 1}, a_{k}, a_{k + 1}, a_1, ..., a_{k - 2}
...
i-th iteration: a_{k - i + 1}, ..., a_{k}, a_{k + 1}, a_1, ..., a_{k - i}
...
k-th iteration: a_{1}, ..., a_{k}, a_{k + 1}




**/

using namespace std;

class MyStack {
public:
  MyStack() {}

  void push(int x) {
    if (queue1_.empty()) {
      queue1_.push(x);
      while (!queue2_.empty()) {
        int value = queue2_.front();
        queue2_.pop();
        queue1_.push(value);
      }
    } else if (queue2_.empty()) {
      queue2_.push(x);
      while (!queue1_.empty()) {
        int value = queue1_.front();
        queue1_.pop();
        queue2_.push(value);
      }
    }
  }

  int pop() {
    if (queue1_.empty()) {
      int value = queue2_.front();
      queue2_.pop();
      return value;
    } else {
      int value = queue1_.front();
      queue1_.pop();
      return value;
    }
  }

  int top() {
    if (queue1_.empty()) {
      return queue2_.front();
    } else {
      return queue1_.front();
    }
  }

  bool empty() { return queue1_.empty() && queue2_.empty(); }

private:
  queue<int> queue1_;
  queue<int> queue2_;
};

class MyStack2 {
public:
  MyStack2() {}

  void push(int x) {
    queue_.push(x);
    for (size_t i = 0; i + 1 < queue_.size(); ++i) {
      int value = queue_.front();
      queue_.pop();
      queue_.push(value);
    }
  }

  int pop() {
    int value = queue_.front();
    queue_.pop();
    return value;
  }

  int top() { return queue_.front(); }

  bool empty() { return queue_.empty(); }

private:
  queue<int> queue_;
};

int main() {
  MyStack2 myStack;
  myStack.push(1);
  myStack.push(2);
  cout << myStack.top() << "\n";
  cout << myStack.pop() << "\n";
  myStack.empty();
}