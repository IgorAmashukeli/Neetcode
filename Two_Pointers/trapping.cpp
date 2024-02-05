#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it can trap after raining.

// Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
// Explanation: The above elevation map (black section) is represented by array
// [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section)
// are being trapped. Example 2:

// Input: height = [4,2,0,3,2,5]
// Output: 9

// Constraints:

// n == height.length
// 1 <= n <= 2 * 104
// 0 <= height[i] <= 105

// idea :
// find array of next greater
// find array of next prev
// for each i
// find max prev greater and max next greater step by step
// (if left <= right, move left, otherwise move right)

// 1) using this techinque, you can guarantee the [left, right] interval is only
// one trap at the first iteration.
//
// (because if there were two traps, it means
// that there exists mid element such that mid element >= left or mid element >=
// right) (but if there exists such element, then, when one one of the pointers
// was at this mid element and it was shifted. if it was the smallest one, then
// the element to which it was shifted was higher (because it is prev greater or
// next greater), and another pointer is also higher than the mid, because we
// are shifting the smallest one, according to the rules. therefore, after that
// left >= mid and right >= mid and it will be as such until the end. It is
// contradiction. Therefore, [left, right] contains only one trap.
//
//
// Moreover, each interval is the highest possible trap.
// We know, that one of the borders is the max shifted, because it has no (prev
// or next) greater elements. And another one can't be shifted, because after
// first while loop, we shift it to the right/left, if it was higher.
//
// Moreover, after founding the first interval, the next, the third etc
// iteration can find interval only with one trap contained and it will be to
// the right of the first, it is not overlapping. Suppose, the next interval is
// overlapping with one of the previous ones (if the left border of current
// equals the right border of the previous, it doesn't imply that they are
// overlapping). Then, it can't start in the middle of the first one in the
// overlapping sequence: if it starts with the middle element of the first
// interval, then we shifted to this element, skipping the right border, which
// is higher than the middle, or we shifted from right border to the smaller
// element, which we can't do, according to the rules. Therefore, the left
// element of the current interval is <= than the left border of the first
// interval in the sequence of the overlapping intervals.
// Therefore, the first interval contains in the current, therefore it is not
// the highest possible, but we proved, it is the highest possible one.
// Contradiction.
//
// Therefore, on each iteration we will find the highest possible and only one
// trap for this element, after that we will shift the i pointer after the right
// border of the interval to find the next interval/trap
// All traps are not overlapping.
// Therefore, we will find the splitting to the union of not overlapping max
// traps.
// Then, we sum up the water in each interval (we find the water level, using
// minimum between two borders and subtract it from each element)
// The summa is the answer. Moreover, we will iterate over each interval <= 2
// times: to find it and to find the summa.
//
// Summing it up, the algorithm is correct and finds the result in O(n) time and
// O(n) space
// (O(n) space is needed for monotonous stacks and prevGreater, nextGreater
// arrays)
//
using namespace std;

class MonotonousStack {
public:
  MonotonousStack() {}

  int push(size_t index, int value) {
    while (!stack_.empty() && value >= stack_.top().second) {
      stack_.pop();
    }
    int returning_value;

    if (stack_.empty()) {
      returning_value = -1;
    } else {
      returning_value = stack_.top().first;
    }

    stack_.push({index, value});

    return returning_value;
  }

private:
  stack<pair<size_t, int>> stack_;
};

vector<int> nextGreater(const vector<int> &a) {
  MonotonousStack stack = MonotonousStack();
  vector<int> b = a;
  for (size_t i = 0; i < a.size(); ++i) {
    size_t j = a.size() - i - 1;
    b[j] = stack.push(j, a[j]);
  }
  return b;
}

vector<int> prevGreater(const vector<int> &a) {
  MonotonousStack stack = MonotonousStack();
  vector<int> b = a;
  for (size_t i = 0; i < a.size(); ++i) {
    b[i] = stack.push(i, a[i]);
  }
  return b;
}

class Solution {
private:
  int find_size(vector<int> &height, size_t left, size_t right) {
    int sum = 0;
    int water_level = min(height[left], height[right]);
    for (size_t i = left; i < right; ++i) {
      sum += max(0, water_level - height[i]);
    }
    return sum;
  }

public:
  int trap(vector<int> &height) {
    vector<int> prevs = prevGreater(height);
    vector<int> nexts = nextGreater(height);
    size_t i = 0;
    int sum = 0;

    while (i < height.size()) {
      int prev = prevs[i];
      int next = nexts[i];

      if (prev == -1 || next == -1) {
        i++;
        continue;
      }

      while (prevs[prev] != -1 && nexts[next] != -1) {
        if (height[prev] <= height[next]) {
          prev = prevs[prev];
        } else {
          next = nexts[next];
        }
      }
      cout << prev << " " << i << " " << next << "\n";
      if (prevs[prev] == -1) {
        while (nexts[next] != -1 && height[prev] > height[next]) {
          next = nexts[next];
        }
      } else {
        while (prevs[prev] != -1 && height[next] > height[prev]) {
          prev = prevs[prev];
        }
      }
      cout << prev << " " << i << " " << next << "\n";
      sum += find_size(height, prev, next);
      i = next + 1;
    }

    return sum;
  }
};

int main() {
  Solution solution = Solution();
  vector<int> height = {2, 6, 3, 8, 2, 7, 2, 5, 0};
  cout << solution.trap(height) << "\n";
}