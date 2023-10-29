#include <iostream>
#include <vector>

/**

You are given a 0-indexed array nums of distinct integers. You want to rearrange
the elements in the array such that every element in the rearranged array is not
equal to the average of its neighbors.

More formally, the rearranged array should have the property such that for every
i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2 is not
equal to nums[i].

Return any rearrangement of nums that meets the requirements.



Example 1:

Input: nums = [1,2,3,4,5]
Output: [1,2,4,5,3]
Explanation:
When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.
Example 2:

Input: nums = [6,2,0,9,7]
Output: [9,7,6,2,0]
Explanation:
When i=1, nums[i] = 7, and the average of its neighbors is (9+6) / 2 = 7.5.
When i=2, nums[i] = 6, and the average of its neighbors is (7+2) / 2 = 4.5.
When i=3, nums[i] = 2, and the average of its neighbors is (6+0) / 2 = 3.


Constraints:

3 <= nums.length <= 10^5
0 <= nums[i] <= 10^5


idea:

we have an array:
[a_1 a_2 a_3 ..... a_n]

Let's first learn how to fix one triple of elements:

suppose we have one tripple:

(k, (k + m) / 2, m)

how to fix this? let's swap (k + m) / 2 with m
then it will be

(k, m, (k + m) / 2)
let's proof this triple is fixed:

Suppose it is not fixed:

(k + (k + m) / 2) / 2 = m
=>
k + (k + m) / 2 = 2m
=>
2k + (k + m) = 4m
=>
3k = 3m
=>
k = m
but elements are distinct (said in the task)

=> pair is fixed

but maybe something was broken after we fix the pair

let's first look to the right part of the pair

we had:

(a_{t - 1}, a_{t}, a_{t + 1})
we changed this to
(a_{t - 1}, a_{t + 1}, a_{t})

If pair is to the right and doesn't contain a_{t} or a_{t + 1}
=> it is not broken

now let's look to those that contain

1) (a_{t + 1}, a_{t}, a_{t + 2})
suppose it is broken
that means that
a_{t} = a_{t + 1} + a_{t + 2}
that means that
(m + k) / 2 = (m + a_{t + 2}) / 2
that means that
m + k = m + a_{t + 2}

that means that

k = a_{t + 2}

but a_{t - 1} = k

=> a_{t - 1} = a_{t + 2}
but elements are distinct => it is not broken


2) (a_{t + 1}, a_{t + 2}, a_{t + 3})
this one could be broken, let's fix it the same way:

we swap a_{t + 2} and a_{t + 3} and it is now fixed
and a_{t + 2} and a_{t + 3} are not included in
(a_{t - 1}, a_{t}, a_{t + 1}) => we didn't break it


Now we do til the end of array, now every triple to the right is fixed
(if the last triple is one or two elements, and others are out of bounce,
nothing to fix) (we fix all pairs, while they exis)

Now we fixed all to the right
But suppose now we broke something to the left
of (a_{t - 1}, a_t, a_{t + 1})
it couldn't be (a_{t - 3}, a_{t - 2}, a_{t - 1})
because we didn't change a_{t - 1}

=> we could break (a_{t - 2}, a_{t - 1}, a_{t + 1})


Thus we conducted that as we were fixing to the right, the only triple on the
left to be broken is (a_{t - 2}, a_{t - 1}, a_{t + 1})

Now let's do similarly, as we did to the right:
let's change a_{t - 2} and a_{t - 1}

Now, similarly (a_{t - 3}, a_{t - 1}, a_{t - 2})
can't be broken
(cause this means: a_{t - 1} = (a_{t - 3} + a_{t - 2}) / 2
but a_{t - 1} is (a_{t - 2} + a_{t + 1}) / 2, cause the triple
(a_{t - 2}, a_{t - 1}, a_{t + 1}) is broken
=> a_{t - 3} = a_{t - 1}
which is contradiction

that means the only pair to the left to be broken
is (a_{t - 4}, a_{t - 3}, a_{t - 1})
let's fix it similarly (swapping a_{t - 4}, a_{t - 3})

the previous pair couldn't be broken, cause it doesn't contain
a_{t - 4} or a_{t - 3}

Therefore we can continue changing it to the left

Now the only problem can be to the right of
(a_{t - 2}, a_{t - 1}, a_{t + 1})
we changed a_{t - 2} and a_{t - 1}
that the only pairs that could be broken
is (a_{t - 1}, a_{t + 1}, a_{t})
let's return their names:
it is (k, m, (k + m) / 2)
let's a_{t - 2} be x
=> we had triple (x, k, m)
it is broken => k = (x + m) / 2
=> 2k = x + m
=> x = 2k - m
now we fix it:
(k, x, m)
now let's look at may be broken pair:

(x, m, (k + m) /2)
suppose it is broken:

m = (x + (k + m)/2) / 2
=>
2m = x + (k + m) / 2
=>
4m = 2x + k + m
2x = 3m - k
from previous formula: x = 2k - m
=> 2x = 4k - 2m
=> we have:
2x = 3m - k
2x = 4k - 2m
=> 3m - k = 4k - 2m
=> 5k = 5m
=> k = m
=> contradictions

=> all pairs to the right after going to the left also fixed

=> everything is fixed
=> we solved the task





**/

using namespace std;

vector<int> rearrangeArray(vector<int> &nums) {
  for (size_t i = 0; i < nums.size(); ++i) {
    if (i > 0 && i + 1 < nums.size() &&
        2 * nums[i] == nums[i - 1] + nums[i + 1]) {
      swap(nums[i], nums[i + 1]);
    }
  }

  for (size_t i = 0; i < nums.size(); ++i) {
    size_t j = nums.size() - i - 1;
    if (j > 0 && j + 1 < nums.size() &&
        2 * nums[j] == nums[j - 1] + nums[j + 1]) {
      swap(nums[j], nums[j - 1]);
    }
  }
  return nums;
}

int main() {
  vector<int> nums = {6, 2, 0, 9, 7};
  nums = rearrangeArray(nums);
  for (size_t i = 0; i < nums.size(); ++i) {
    cout << nums[i] << " ";
  }
  cout << "\n";
}