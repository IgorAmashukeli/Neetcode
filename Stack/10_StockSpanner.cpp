#include <cstddef>
#include <iostream>
#include <stack>
#include <utility>

/**
901. Online Stock Span

Design an algorithm that collects daily price quotes for some stock and returns
the span of that stock's price for the current day.

The span of the stock's price in one day is the maximum number of consecutive
days (starting from that day and going backward) for which the stock price was
less than or equal to the price of that day.

For example, if the prices of the stock in the last four days is [7,2,1,2] and
the price of the stock today is 2, then the span of today is 4 because starting
from today, the price of the stock was less than or equal 2 for 4 consecutive
days. Also, if the prices of the stock in the last four days is [7,34,1,2] and
the price of the stock today is 8, then the span of today is 3 because starting
from today, the price of the stock was less than or equal 8 for 3 consecutive
days. Implement the StockSpanner class:

StockSpanner() Initializes the object of the class.
int next(int price) Returns the span of the stock's price given that today's
price is price.


Example 1:

Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]

Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including
today's price of 75) were less than or equal to today's price.
stockSpanner.next(85);  // return 6


Constraints:

1 <= price <= 10^5
At most 10^4 calls will be made to next.


idea: MonotonousStack + online algorithm + current_index

We increment the current index on each iteration to keep
the number of the element in the sequence

Monotonous Stack is a stack with pairs: values and indices.

If stack is empty after while loop of pops, we return curr_index + 1
If stack is not empty after while loop pf pops, we return curr_index -
stack.top() index

Let's proof that on each iteration we return the correct count.

- On the first iteration, the stack is empty and we
return curr_index + 1 = 0 + 1 = 1.

The number of days, when there values, <= than current values
is 1. It is this current day.


- Suppose, for all iterations < j we returned correct value.
Suppose, we know on i-th iteration

From the previous problem:

- If stack is empty after while loop of pops, there are no
values, higher than current value. In that case,
all values from 0 to index are <= than current value.
Therefore, the answer is index + 1

- If stack is not empty after while loop of pops, there is
value on the top of the stack, from previous problem,
this values is the nearest value that is > than current
Suppose this value has index j.
Then in that case: arr[j+1]...arr[i] are the values that
are <= than arr[i] => the number of such values is i - j - 1 + 1
= i - j = curr_index - stack.top() index

Therefore, in all cases the answer is correct.



**/

using namespace std;

class MonotonousStack {
public:
  MonotonousStack() {}

  int push(int element, size_t index) {
    while (!stack_.empty() && stack_.top().first <= element) {
      stack_.pop();
    }

    int count;
    if (stack_.empty()) {
      count = index + 1;
    } else {
      count = index - stack_.top().second;
    }
    stack_.push({element, index});

    return count;
  }

private:
  stack<pair<int, int>> stack_;
};

class StockSpanner {
public:
  StockSpanner() : current_index(0), monotonousStack({}) {}

  int next(int price) {
    int count = monotonousStack.push(price, current_index);
    current_index++;
    return count;
  }

private:
  int current_index;
  MonotonousStack monotonousStack;
};

int main() {

  StockSpanner stockSpanner = StockSpanner();
  cout << stockSpanner.next(31) << "\n";
  cout << stockSpanner.next(41) << "\n";
  cout << stockSpanner.next(48) << "\n";
  cout << stockSpanner.next(59) << "\n";
  cout << stockSpanner.next(79) << "\n";
}