#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
658. Find K Closest Elements

Given a sorted integer array arr, two integers k and x, return the k closest
integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b


Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]


Constraints:

1 <= k <= arr.length
1 <= arr.length <= 10^4
arr is sorted in ascending order.
-10^4 <= arr[i], x <= 10^4


idea :
1) binary search for the closest element to x_ind
2) if found => center is mid

3) if not found
=> x can't have distance of 2 to all of them
(on the last iteration left <= x_ind < right and also left <= mid < right
after that either left := mid + 1 or right := mid
if left := mid + 1 assigning happened => because mid < right => mid + 1 <= right
=> new left <= right if right := mid assigning happened => because left <= mid
=> left <= new right and not true that new left < new right => new left == new
right if right - left > 2 => it was as such: left ... mid ... right and there
was something between left and right (because if left ... mid right => then
right - (left + right) / 2 < (left + right) / 2 - left  => left + right < 2 *
((left + right)/ 2), where division is rounding down => therefore it can't be
so)
=> if left : = mid + 1 => left < right, because there is something between mid
and right if right := mid => left < right, because mid can't be equal to left,
when there are indcicies between left and right.

Therefore, right - left <= 2 => therefore x_ind = left or x_ind = left + 1
if  new right = mid => x_ind = new left or new_left + 1
if  new left = mid + 1 => x_ind = mid or mid - 1 => x = new left - 1 or new left
- 2

=> find the first closest center in [left - 2,
left + 1] (the first means the smallest index, because this is requirement)
(sometimes left is >= arr.size() => find min(left, arr.size() - 1))
sometimes left - 2 < 0 or left + 1 > arr.size()
(increment and decrement with checks, and left is size_t => don't subtract from
it)

4) after center is found, count = 1
until count != k
shift left, then right (left first if possible) (not expanding the array
boundaries) and select the closest one

it is obvious that these are the closest to the center => are closest to x


**/

class Solution {
private:
  tuple<size_t, size_t, bool> binarySearch(vector<int> &arr, int x) {
    size_t left = 0;
    size_t right = arr.size();
    size_t mid;
    bool found = false;
    while (left < right) {
      mid = left + (right - left) / 2;
      if (arr[mid] == x) {
        found = true;
        break;
      } else if (arr[mid] > x) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return {left, mid, found};
  }

  int find_center(const vector<int> &arr, tuple<size_t, size_t, bool> &tuple_,
                  int x) {
    int center = 0;
    if (!get<2>(tuple_)) {
      size_t min_ind = get<0>(tuple_);
      size_t max_ind = min(get<0>(tuple_), arr.size() - 1);
      if (min_ind > 0) {
        min_ind--;
        if (min_ind > 0) {
          min_ind--;
        }
      }
      if (max_ind + 1 < arr.size()) {
        max_ind++;
      }
      center = 0;
      int min_dist = arr[arr.size() - 1] - arr[0] + 1;
      for (size_t i = min_ind; i <= max_ind; ++i) {
        if (abs(arr[i] - x) < min_dist) {
          min_dist = abs(arr[i] - x);
          center = i;
        }
      }
    } else {
      center = get<1>(tuple_);
    }
    return center;
  }

public:
  vector<int> findClosestElements(vector<int> &arr, int k, int x) {
    tuple<size_t, size_t, bool> tuple_ = binarySearch(arr, x);
    int center = find_center(arr, tuple_, x);

    size_t l = center;
    size_t r = center;
    int count = 1;
    while (count != k) {
      if (l > 0 && r + 1 < arr.size() &&
          abs(arr[l - 1] - x) <= abs(arr[r + 1] - x)) {
        l--;
      } else if (l > 0 && r + 1 < arr.size()) {
        r++;
      } else if (l > 0) {
        l--;
      } else if (r + 1 < arr.size()) {
        r++;
      }
      ++count;
    }
    vector<int> subarr(arr.begin() + l, arr.begin() + r + 1);
    return subarr;
  }
};

int main() {
  vector<int> a = {3, 5, 8, 10};
  int k = 2;
  int x = 15;
  vector<int> b = Solution().findClosestElements(a, k, x);
  for (const auto elem : b) {
    cout << elem << " ";
  }
  cout << "\n";
}