#include <deque>
#include <iostream>
#include <string>

/**
402. Remove K Digits

Given string num representing a non-negative integer num, and an integer k,
return the smallest possible integer after removing k digits from num.



Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219
which is the smallest. Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output
must not contain leading zeroes. Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing
which is 0.


Constraints:

1 <= k <= num.length <= 10^5
num consists of only digits.
num does not have any leading zeros except for the zero itself.

idea:

Suppose, A_1, ..., A_N

Let's say M = N - K
M numbers should remain after K removed
A_1...A_N

the first is number among A_1...A_{K + 1},
because if I choose A_{K + 2} or bigger, then among A_{K + 3}...A_N
will remain <= N - K - 3 + 1 = N - K - 2 = M - 2 numbers
and after choosing 1st number, there should be >= M - 1 number

the second number is among A_2...A_{K + 2},
because if I choose A_{K + 3} or bigger, then among A_{K + 4}...A_N
will remain N - K - 4 + 1 = N - K - 3 = M - 3 numbers
and after choosing the 1st and 2nd numbers, there should be >= M - 2 numbers
Moreover, you can't choose A_1, because then we can't choose the first value

the third number is among A_3...A_{K + 3},
because if I choose A_{K + 4} or bigger, then among A_{K + 5}...A_N
will remain N - K - 5 + 1 = N - K - 4 = M - 4 numbers
and after choosing the 1st, 2nd and 3rd numbers, there should be >= M - 3
numbers
Moreover, you can't choose A_1 or A_2, because then we can't choose the first
and the second value

etc

Moreover, if all numbers are choosen minimal, then the answer is minimal

(because, we allowed to choose the number of size M with leading zeroes
and remove all them after and therefore we just can choose minimal number)

Suppose, this is not true, then it means that there exists a number
C_1...C_M that is less than number B_1...B_M, where B_i is the minimum for each
number.

Because, C is correct number, C is also selected among K + 1 window
for each number

Therefore, C_1 is from the first window, and B_1 is minimum there and so on
=> B_1 <= C_1...B_M <= C_M

Moreover, there exists such j that B_M < C_M
Let's select the smallest such j
=> for all i bigger j: C_i = B_i

=> C_1...C_{j - 1} C_j...C_M = B_1...B_{j - 1} C_j...C_M
It is obvious that C_j...C_M > B_j...B_M

Therefore, C_1...C_{j - 1} C_j...C_M > B_1...B_{j - 1} C_j...C_M
Therefore, C > B. Contradiction.



Therefore, we just need to choose the minimum in each K + 1 window
For that we can use Monotonous Deque.

It will always have minimum value of the K + 1 window

The correctness of the Monotonous Deque was proved before.
But the only difference is now we use min
and also we pop_front the min value in min function, because we don't need
this minimum more, because there can't be the same exact <char, size_t>
pair used for different digits

As we know, in Monotonous Deque we push_back each value one time,
therefore, we can't pop it twice

Therefore, the time complexity is O(n)

**/

using namespace std;

class MonotonousDeque {
public:
  MonotonousDeque() {}

  void push(size_t index, int element) {
    while (!deque_.empty() && deque_.back().second > element) {
      deque_.pop_back();
    }
    deque_.push_back({index, element});
  }

  void pop(size_t max_size) {
    if (deque_.back().first - deque_.front().first >= max_size) {
      deque_.pop_front();
    }
  }

  int min() {

    int value = deque_.front().second;
    deque_.pop_front();
    return value;
  }

private:
  deque<pair<size_t, int>> deque_;
};

class Solution {
public:
  string removeKdigits(const string &num, int k) {
    if (k == num.size()) {
      return "0";
    }
    string answer = "";
    MonotonousDeque monotonous_deque;
    for (size_t i = 0; i <= static_cast<size_t>(k); ++i) {
      monotonous_deque.push(i, num[i] - '0');
    }
    size_t i = k + 1;
    bool start = true;
    int cur_digit = (monotonous_deque.min() + '0');
    if (cur_digit != '0' || !start) {
      answer += cur_digit;
      start = false;
    }
    while (i < num.size()) {
      monotonous_deque.push(i, num[i] - '0');
      monotonous_deque.pop(k + 1);
      int cur_digit = (monotonous_deque.min() + '0');
      if (cur_digit != '0' || !start) {
        answer += cur_digit;
        start = false;
      }
      i++;
    }

    if (answer == "") {
      return "0";
    }
    return answer;
  }
};

int main() {
  Solution solution = Solution();
  cout << solution.removeKdigits("1432219", 3) << "\n";
}