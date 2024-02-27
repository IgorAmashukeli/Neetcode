#include <iostream>
#include <stack>

/**
155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element
in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.



Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2


Constraints:

-2^31 <= val <= 2^31 - 1
Methods pop, top and getMin operations will always be called on non-empty
stacks. At most 3 * 10^4 calls will be made to push, pop, top, and getMin.

Idea: store two stacks: just stack and MonotonousStack of int and size_t

MonotonousStack pushes the value with index if and only if it is less than the
current top or stack is empty

Therefore, MonotonousStack always remembers the current minimum at the top
If the current value is less than the top, it is the minimum, otherwise, the top
will be the minimum

Therefore:
top just returns the top value from stack
getMin returns the top value from MonotonousStack

To remember, when to pop values from MonotonousStack, we have second
element of pairs - indices, when this element was found
It is the size of the main stack before the push to the main stack

At any push to min_stack, we push to the stack the value
and push to the MonotonousStack the value with index (the class will save it
as current minimum, if it is less then the top value of MonotonousStack)

At any pop to min_stack, we pop the value from the stack
and we check, whether the MonotonousStack index is equal to the current size of
the stack. If equal, we pop the pair from MonotonousStack, otherwise we do
nothing


Let's prove that the current top of MonotonousStack is minimum.
When min_stack is empty, it is true (no top of MonotonousStack exists)
Suppose, it was true after some operations done.
Suppose, now we want to do another operation to min_stack.

1) push:

the current minimum is at the top of MonotonousStack
now we have element x, we push it to the stack.
the top of MonotonousStack y is the minimum in the stack before push.
After push the minimum is min(x, y)
So

- if x < y, x = min(x, y) we push x to the MonotonousStack and
MonotonousStack again has the minimum = x at the top

- if x >= y, y = min(x, y) we don't push x to the MonotonousStack and
MonotonousStack again has the minimum = y at the top


2) pop:

the current minimum (x, index) is at the top of MonotonousStack.



a)

If x is unique in the stack, then it means that the only x added
to the MonotonousStack is the current top of the MonotonousStack.

when it was added the last time, the size of the stack was index,
but, because the stack is LIFO,
it was last added, when the stack contained everything it contains now,
except this x (because, the elements below x were added before and elements (now
deleted) upper were added after x)

This means, the number of the elements below is index.
When we popped x from stack, the size of the stack is also index.
Therefore, according to the algorithm, we delete x.

x was the only x in the stack.
According to the fact that in all previois operation,
the top of the MonotonousStack contained the correct minimum,
when we pushed the value below the x, it also contained the correct minimum.

But at the time we pushed it, all the value below it, were already added and
nothing more as it is now after popping of x.

Therefore, the stack has the same state as it had at the time of that push
and the MonotonousStack also has the same value as it had at the time.
(because, we never delete more values from MonotonousStack then from stack and
our new current top wasn't deleted)

Therefore, this top value is a correct mimimum value.



b)

If x is not unique value in the stack, it means, there are also other values
in the stack, that are equal to x.

Let's prove we couldn't add the (x, index) pair after the first value of x

Because, by induction, everything was correct, it means that it was correct
at the moment of last!! pushing of the first!! x to the stack.
When, we did this we pushed it with the size of the stack before push to the
stack. After that the MonotonousStack contained x.

After that we pushed more values or popped something of the pushed after.
But we never popped this x (it is last pushing of this x)
We could push more x or pop them.
But because, the top value of the MonotonousStack was always correct and
we always had this first x inside the stack,
it means the MonotonousStack always contained x at the top.
Because, we can't add dupicates of x to MonotonousStack and because if
we deleted x at least once, we had no x on the top of MonotonousStack
with x in stack as the mimimum.
If we pushed the value less than x to the stack, we pushed something less than x
to the MonotonousStack, but then deleted.

But we never deleted (x, index) from the MonotonousStack
and never pushed duplicates.

This means that (x, index) was added only once, when the stack size was equal to
the size of the stack below the first value of index.

Because there exists more than one value of x,
the last value of x is more to the top of the stack.
Therefore, after removing of the current value from stack,
it can't be the only x in the stack and the size of the stack
will be more than index. Therefore, our algorithm will not pop
(x, index) from MonotonousStack.

The current minimum will be assigned to x again.
The new real minimum can't be high than x (x is in the stack)
The new real minimum can't be low than x. This value
was also among the values before pop and then the current minimum
at that point should have been low than x. But it was x.

Therefore, the real minimum is also x. Therefore,
the current minimum equals to the minimum assigned by the algorithm





Therefore, the algorithm is correct and all functions work in O(1)









**/

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