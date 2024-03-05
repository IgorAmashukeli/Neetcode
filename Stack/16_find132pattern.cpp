#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <stack>
#include <vector>

/**
456. 132 Pattern

Given an array of n integers nums, a 132 pattern is a subsequence of three
integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k]
< nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.



Example 1:

Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.
Example 2:

Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:

Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3,
0] and [-1, 2, 0].


Constraints:

n == nums.length
1 <= n <= 2 * 10^5
-10^9 <= nums[i] <= 10^9


idea:

find mins on all prefixes (mins[s] = min value in prefix, ending on arr[s])
find prev_greater for the array - using MonotonicStack

scan array from right to the left
suppose u is the current value
let arr[k] = u

suppose, prev_greater[k] = index
if index != - 1:

let arr[j] = arr[index]

if index != 0:

let arr[i] = mins[index - 1]

if arr[i] < arr[k] < arr[j] => return true

If we left the loop => return false


Let' proof of correctness of the algorithm:

If found value => returned true =>
it is obvious that aforesaid triple is correct one

If didn't find value => returned false =>
let's proof that there is no such triple that we are searching


Let's assume that this is not true.

Then there exists such triple i_0, j_0, k_0
i_0 < j_0 < k_0
arr[i_0] < arr[k_0] < arr[j_0]

Let's take arr[k_0]

This value was looked, when scanning for the triple in the algorithm
But we didn't return true
This can be due to different reasons:

1 reason: prev_greater[k_0] = -1
In that case there is no previous greater value to arr[k_0]
In that case arr[j_0] <= arr[k_0]
Contradiction with the fact that arr[k_0] < arr[j_0]

2 reason: prev_greater[k_0] = 0
In that case, the only previous greater element is arr[0]
(because, if there exists other such element, index will be > 0)
Therefore, j_0 must be equal to 0
Therefore, j_0 = 0
Therefore, i_0 < j_0 = 0 => i_0 < 0
Contradiction with the fact that i_0 is correct index

3 reason:
j_1 = prev_greater[k_0]
mins[j_1 - 1] >= arr[k_0] or arr[k_0] >= prev_greater[k_0]
But the last can't be true (prev_greater[k_0] < arr[k_0])
Therefore this means that mins[j_1 - 1] >= arr[k_0]
We also know that
arr[i_0] < arr[j_0] < arr[k_0]

That means: arr[i_0] < arr[k_0] and arr[k_0] <= mins[j_1 - 1]
Therefore arr[i_0] < mins[j_1 - 1]


j_1 is prev_greater and j_0 is greater and j_0 < k_0
In that case j_0 <= j_1 (if j_0 > j_1, than j_1 can't be prev greater,
because prev_greater is the first to the left of k_0 that is greater)
Therefore j_0 - 1 <= j_1 - 1


We know that min function works like this:
min(a, b) <= a => min(mins[i - 1], nums[i]) <= mins[i - 1]
We know that mins[i] = min(mins[i - 1], nums[i]) <= mins[i - 1]
Therefore mins[i] <= mins[i - 1]
By induction for all u and v such that v >= u: mins[u] <= mins[v]
(for v = u that is obvious truth: mins[u] <= mins[u]
 for v = u + 1, u = v - 1 => we have mins[v] <= mins[v- 1], we proved it before
 for v > r we proved, now for v = r:
 mins[r] <= mins[r - 1] - we proved
 mins[r - 1] <= mins[u], because r - 1 < r => induction hypothesis
 => mins[r] <= mins[i]
 Therefore, for all v >= u: mins[u] <= mins[v]
 )
Therefore mins[j_1 - 1] <= mins[j_0 - 1]

Therefore: arr[i_0] < mins[j_0 - 1]

i_0 < j_0 => i_0 <= j_0 - 1

Therefore: i_0 in {0, ..., j_0 - 1}
Therefore mins[j_0 - 1] <= arr[i_0]

Therefore : arr[i_0] < mins[j_0 - 1]
        and arr[i_0] >= mins[j_0 - 1]

Contradiction



Therefore, all reasons, while true wasn' returned are controversial
Therefore in that case true was returned for arr[k_0]
But we assumed it wasn't

Contradiction.

Therefore, there is no such triple that we are searching, when we returned false

Therefore:

returned true => there is such triple
returned false => there is no such triple

Therefore: returned true <=> there is such triple

Therefore the algorithm is correct

For monotonic stack, it has n pushes => it has <= n pops
Therefore the time complexity for the loop with monotonic pushes
is O(n)
All other loops are also O(n)

Therefore, the algorithm is correct and time complexity is O(n)

**/

using namespace std;

class MonotonicStack {
public:
  MonotonicStack(){};
  int push(int value, size_t index) {

    while (!stack_.empty() && stack_.top().first <= value) {
      stack_.pop();
    }

    int top_ind;
    if (stack_.empty()) {
      top_ind = -1;
    } else {
      top_ind = stack_.top().second;
    }

    stack_.push({value, index});

    return top_ind;
  }

  void pop() { stack_.pop(); }

private:
  stack<pair<int, size_t>> stack_;
};

class Solution {
public:
  bool find132pattern(vector<int> &nums) {

    vector<int> mins(nums.size());
    for (size_t i = 0; i < nums.size(); ++i) {
      if (i == 0) {
        mins[i] = nums[i];
      } else {
        mins[i] = min(mins[i - 1], nums[i]);
      }
    }

    MonotonicStack monotonicStack = MonotonicStack();
    vector<int> prev_greater(nums.size());
    for (size_t i = 0; i < nums.size(); ++i) {
      prev_greater[i] = monotonicStack.push(nums[i], i);
    }

    for (size_t i = 0; i < nums.size(); ++i) {
      size_t j = nums.size() - i - 1;
      int last = nums[j];
      int middle_index = prev_greater[j];
      if (middle_index <= 0) {
        // middle_index = -1 - no prev greater
        // middle_index = 0 - no min to the left prev greater
        continue;
      }
      int middle = nums[middle_index];
      int first = mins[middle_index - 1];

      if (first < last && last < middle) {
        return true;
      }
    }

    return false;
  }
};

bool int_greater_equal(int a, int b) { return a >= b; }

bool int_less_equal(int a, int b) { return a <= b; }

class MonotonicStack2 {
public:
  MonotonicStack2(bool (*func)(int, int)) { order_ = func; }
  int push(int element, size_t index) {

    while (!stack_.empty() && order_(element, stack_.top().first)) {
      stack_.pop();
    }
    int next;
    if (stack_.empty()) {
      next = -1;
    } else {
      next = stack_.top().second;
    }

    stack_.push({element, index});
    return next;
  }

private:
  stack<pair<int, size_t>> stack_;
  bool (*order_)(int, int);
};

class Solution2 {
public:
  bool find132pattern(vector<int> &nums) {
    stack<int> answer;
    for (size_t i = 0; i < nums.size(); ++i) {
      if (answer.empty()) {
        answer.push(nums[i]);
      } else if (answer.size() == 1 && nums[i] < answer.top()) {
        answer.pop();
        answer.push(nums[i]);
      } else if (answer.size() == 1 && nums[i] > answer.top()) {
        answer.push(nums[i]);
      } else if (answer.size() == 2 && nums[i] > answer.top()) {
        answer.pop();
        answer.push(nums[i]);
      } else if (answer.size() == 2 && nums[i] < answer.top()) {
        int prev = answer.top();
        answer.pop();
        int prevprev = answer.top();
        if (prevprev < nums[i]) {
          return true;
        }
        answer.push(prev);
      }
    }
    vector<int> next_greater(nums.size());
    vector<int> next_smaller(nums.size());
    MonotonicStack2 greaterStack = MonotonicStack2(int_greater_equal);
    MonotonicStack2 lessStack = MonotonicStack2(int_less_equal);
    for (size_t i = 0; i < nums.size(); ++i) {
      size_t j = nums.size() - i - 1;
      next_greater[j] = greaterStack.push(nums[j], j);
      next_smaller[j] = lessStack.push(nums[j], j);
    }
    for (size_t i = 0; i < nums.size(); ++i) {
      if (next_greater[i] != -1 && next_smaller[next_greater[i]] != -1 &&
          nums[next_smaller[next_greater[i]]] > nums[i]) {
        return true;
      }
    }
    reverse(nums.begin(), nums.end());
    vector<int> next_greater2(nums.size());
    vector<int> next_smaller2(nums.size());
    MonotonicStack2 greaterStack2 = MonotonicStack2(int_greater_equal);
    MonotonicStack2 lessStack2 = MonotonicStack2(int_less_equal);
    for (size_t i = 0; i < nums.size(); ++i) {
      size_t j = nums.size() - i - 1;
      next_greater2[j] = greaterStack2.push(nums[j], j);
      next_smaller2[j] = lessStack2.push(nums[j], j);
    }
    for (size_t i = 0; i < nums.size(); ++i) {
      if (next_greater2[i] != -1 && next_smaller2[next_greater2[i]] != -1 &&
          nums[next_smaller2[next_greater2[i]]] < nums[i]) {
        return true;
      }
    }
    return false;
  }
};

int main() {
  while (true) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2); // Adjust range as needed

    // Generate a random size for the vector (up to 30)
    std::uniform_int_distribution<> size_dis(1, 6);
    int vector_size = size_dis(gen);

    // Create the vector and fill it with random integers
    std::vector<int> random_vector;
    random_vector.reserve(
        vector_size); // Optional, to avoid reallocation if possible

    for (int i = 0; i < vector_size; ++i) {
      random_vector.push_back(dis(gen));
    }
    Solution solution = Solution();
    Solution2 solution2 = Solution2();
    if (solution.find132pattern(random_vector) !=
        solution2.find132pattern(random_vector)) {
      reverse(random_vector.begin(), random_vector.end());
      for (auto elem : random_vector) {
        cout << elem << ", ";
      }
      cout << "\n";
      break;
    }
  }
}