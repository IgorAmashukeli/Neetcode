#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

/**
You are given an integer array height of length n. There are n vertical lines
drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the
container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Example 1:

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array
[1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the
container can contain is 49. Example 2:

Input: height = [1,1]
Output: 1


idea:

two pointers: left and right
update area (to maxarea), when found bigger

But no need to search for all pairs (l, r), cause there are set of observations
true:

First of all:

Let l be selected. Let r be selected.
Let h[l] < h[r]. Then S = min(h[l], h[r]) * (r - l)
That means, S(l, r) = h[l] * (r - l)
That means, if l stays the same, h[l] stays the same
That means that all pairs l, i, where i < r shouldn't be considered
(cause (i - l) will be less) and min(h[l], h[i]) <= h[l]
=> S(l, i) = h[l] * (i - l) <= S(l, r)
now we can check all pairs, when left is l + 1
Similarly, if h[l] > h[r], we can skip O(n) pairs

=> the solution with two pointers is correct and works in O(n)



**/

using namespace std;

int Area(vector<int> &heights, int i, int j) {

  // the water can be bigger than min of heights
  int height = min(heights[i], heights[j]);

  int distance = abs(i - j);

  return height * distance;
}

int maxArea(vector<int> &heights) {
  int i = 0;
  int j = heights.size() - 1;
  int max_area = 0;

  while (i < j) {
    int area = Area(heights, i, j);
    if (area > max_area) {
      max_area = area;
    }
    if (heights[i] < heights[j]) {
      i++;
    } else {
      j--;
    }
  }

  return max_area;
}

int main() {
  vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  int max_area = maxArea(heights);
}