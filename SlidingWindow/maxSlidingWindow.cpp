#include <deque>
#include <iostream>
#include <map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
239. Sliding Window Maximum
You are given an array of integers nums, there is a sliding window of size k
which is moving from the very left of the array to the very right. You can only
see the k numbers in the window. Each time the sliding window moves right by one
position.

Return the max sliding window.



Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]


Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length


Soltuion 2

We can use map (binary search red black tree) of unordered sets of positions of
elements when we shift a sliding window:
- the position is added to the set (if it was empty)
- the position is removed from the set, if the set is empty

the biggest element of a sliding window is map.begin()->first

The algorithm works in O(n log n)

Solution:

idea:

Monotonous_deque:

when pushing back: we pop back all smaller values and push back to the deque
when poping front: we check, whether the indicies are >= than k,
  if yes, we pop back, otherwise, we don't
when getting max value: we return the first value

Algorithm:

- push_back all first k values to Monotonous_deque
- scan the array
  for each iteration:
    push_back the current value to Monotonous_deque
    pop_front the Monotonous_deque

Proof of correctness and of time:

Suppose, a_1, ..., a_n is an array
Then,
the first window is a_0, ..., a_{k - 1}
the last window is a_{n - k + 1}, .., a_{n}
the current window is a_{i}, ..., a_{i + k - 1}

1)
-- at any iteration, Monotonous_deque is not empty

-- at any iteration, Monotonous_deque has at least a_{i + k - 1} in memory.
-- that is obvious: push_back of Monotonous_deque always pushes a_{i + k - 1} at
iteration i anywa

Therefore,

2)
-- at any iteration i, Monotonous_deque doesn't have any values, that are not
in the i-th window
at iteration i, if the last element pushed is a_{i + k - 1}.

Therefore, all the elements, after a_{i + k - 1} are not in the deque.

If there exists an element to the left of a_{i} (say a_{j}, j + 1 <= i),
then the difference between
i + k - 1 and j is i + k - 1 - j = i - j + k - 1 >= 1 + k - 1 = k
=> the algorithm does pop_front

3)

-- at any iteration i, Monotonous_deque is ordered in decreasing order.

by induction: before iteration 0, this is true, it is empty
suppose, it is true before iteration i

On the iteration i, at first we have the values:

u_1, ..., u_s

They are ordered in decreasing order.

Suppose, a[i] < u_s => we don't remove anything => the result is u_1, ..., u_s,
a[i] Suppose, a[i] >= u_1 => we remove everything => the result is a[i] Suppose,
there exists j such that u_j > a[i] >= u_{j + 1} => we remove everything, that
is >= than a[i]: the result is u_1, ..., u_j, a[i]

In all cases, the result is in decreasing order


4)

-- From all previous statements, it is clear,
that at iteration i
- there exists something in the front of deque
- the value there is the biggest in the deque
- all the values there are from the i-th window


-- Suppose, there exists a value that is from i-th window, but which is bigger
that the value returned by max function


Let's proof, it is not true:

There is no such value.

Suppose, after iteration j, there exists a value, that is bigger then
max value, found by function in MonotonousDeque in current window

Suppose, the value, found by function is a[j].

Suppose, the value, which is bigger is to the right of the array : a[s], s > j
a[s] > a[j].

When it was pushed, it was bigger than a[j], then a[j] and all elements bigger
than a[j], but less than a[s] should have been removed. They weren't.
Contradiction.

Suppose, the value, which is bigger is to the left of the array : a[s], s < j
a[s] > a[j].

Let's consider the last such value. (the value with the biggest index s < j such
that a[s] > a[j])

It was removed.
There are two reasons
a ) it was removed, when some value bigger was pushed after

Suppose, this value is a[t].
  - If t > j, then, when pushing a[t], we should have been removed
a[j] and all the values, bigger than a[j], but less than a[t],
    but it wasn't removed

  - If t < j, then, a[s] is not the last such value, contradiction

b) it was removed, because the distance between a[s] and a[m + k - 1]
was bigger than k for some m <= i (It was removed by one of the already done
pop_front()).

But this mean, that m + k - 1 - s >= k for m <= i
=> i + k - 1 - s > = m + k - 1 - s >= k => i + k - 1 - s >= k
T=> i - 1 >= s => s <= i - 1 => a[s] is not in the current window, contradiction


Therefore, each time we found a correct value


5)

Finally, let's think about the time complexity of the algorithm.
It is obvious, that the number of operations is sum of all push_backs,
pop_front and pop_backs.

The number of push_backs is not bigger than the number of elements O(n).
The number of pop_backs + pop_fronts is not bigger than the number of
push_backs.

Therefore, the overall complexity is O(n)







**/

class Solution2 {

public:
  vector<int> maxSlidingWindow(const vector<int> &nums, int k) {
    if (k > nums.size()) {
      return {};
    }
    vector<int> answer;
    map<int, unordered_set<size_t>, greater<int>> positions;
    for (size_t i = 0; i < k; ++i) {
      if (!positions.contains(nums[i])) {
        positions[nums[i]] = {i};
      } else {
        positions[nums[i]].insert(i);
      }
    }

    size_t i = 0;
    while (i + k < nums.size()) {
      answer.push_back(positions.begin()->first);
      positions[nums[i + k]].insert(i + k);
      positions[nums[i]].erase(i);
      if (positions[nums[i]].empty()) {
        positions.erase(nums[i]);
      }
      ++i;
    }
    answer.push_back(positions.begin()->first);

    return answer;
  }
};

class MonotonousDeque {
public:
  MonotonousDeque() {}

  void push(size_t index, int element) {
    while (!deque_.empty() && deque_.back().second <= element) {
      deque_.pop_back();
    }
    deque_.push_back({index, element});
  }

  void pop(size_t max_size) {
    if (deque_.back().first - deque_.front().first >= max_size) {
      deque_.pop_front();
    }
  }

  int max() { return deque_.front().second; }

private:
  deque<pair<size_t, int>> deque_;
};

class Solution {

public:
  vector<int> maxSlidingWindow(const vector<int> &nums, int k) {
    vector<int> answer = {};
    MonotonousDeque window = {};
    for (size_t i = 0; i < k; ++i) {
      window.push(i, nums[i]);
    }
    for (size_t i = k; i < nums.size(); ++i) {
      answer.push_back(window.max());
      window.push(i, nums[i]);
      window.pop(k);
    }
    answer.push_back(window.max());
    return answer;
  }
};

int main() {
  vector<int> input = {1};
  int k = 1;
  vector<int> answers = Solution2().maxSlidingWindow(input, k);
  for (int answer : answers) {
    cout << answer << " ";
  }
  cout << "\n";
}