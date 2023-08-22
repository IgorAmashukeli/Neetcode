/**The next greater element of some element x in an array is the first greater
element that is to the right of x in the same array.

You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1
is a subset of nums2.

For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j]
and determine the next greater element of nums2[j] in nums2. If there is no next
greater element, then the answer for this query is -1.

Return an array ans of length nums1.length such that ans[i] is the next greater
element as described above.



Example 1:

Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the
answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the
answer is -1. Example 2:

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the
answer is -1.


Constraints:

1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 104
All integers in nums1 and nums2 are unique.
All the integers of nums1 also appear in nums2.


idea:

1) to find the position of nums1[i], we use hashmap

2) find next greater is typical daily temperature task
solution: Monotonous Decreasing stack + going backwards

Follow up: Could you find an O(nums1.length + nums2.length) solution?

time: O(|nums1| + |nums2|)
space: O(|nums2|)
**/

#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// each element is pushed and popped only once => monotonous stack is linear,
// when doing push + pop operations in some sequence

// 1) monotonous stack
// 2) going reverse and pushing to the stack sequentially
// 3) getting difference between the index and stack_.top()
// will give you distance to the next bigger value (if it exists, otherwise 0)
// cause stack will contain previous value, bigger than current
// (if found even bigger previous, and one was popped, it is again bigger)
// (if found smaller, bigger will not be popped)
// => bigger will not be popped, if it exists
class MonotonousStack {
public:
  MonotonousStack() = default;
  int push(int index, std::vector<int> &input) {

    // pop all elements, until found bigger
    while (!stack_.empty() && input[index] >= input[stack_.top()]) {
      stack_.pop();
    }
    // stack is empty => push
    if (stack_.size() == 0) {
      stack_.push(index);
      return 0;
    }

    // find the distance between topmost value and this value
    int dist = stack_.top() - index;

    // push
    stack_.push(index);

    // return distance
    return dist;
  }
  void pop() { stack_.pop(); }

private:
  std::stack<int> stack_;
};

vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {

  MonotonousStack monotonous_stack = MonotonousStack();
  // for each value (they are unique), it contais the value of next greater
  // element
  unordered_map<int, int> nextGreaterValue;

  // find next greater
  for (size_t i = 0; i < nums2.size(); ++i) {

    // get distance
    int dist = monotonous_stack.push(i, nums2);
    if (dist == 0) {
      nextGreaterValue[nums2[i]] = -1;
    } else {
      nextGreaterValue[nums2[i]] = nums2[i + dist];
    }
  }

  for (size_t i = 0; i < nums1.size(); ++i) {
    nums1[i] = nextGreaterValue[nums1[i]];
  }

  return nums1;
}