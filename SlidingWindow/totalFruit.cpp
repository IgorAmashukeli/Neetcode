#include <iostream>
#include <unordered_map>
#include <vector>

/**
904. Fruit Into Baskets

You are visiting a farm that has a single row of fruit trees arranged from left
to right. The trees are represented by an integer array fruits where fruits[i]
is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some
strict rules that you must follow:

You only have two baskets, and each basket can only hold a single type of fruit.
There is no limit on the amount of fruit each basket can hold. Starting from any
tree of your choice, you must pick exactly one fruit from every tree (including
the start tree) while moving to the right. The picked fruits must fit in one of
your baskets. Once you reach a tree with fruit that cannot fit in your baskets,
you must stop. Given the integer array fruits, return the maximum number of
fruits you can pick.



Example 1:

Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.
Example 2:

Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].
Example 3:

Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].


Constraints:

1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length

idea : two pointers like in character replacement (condition to shift left is
when unordered_map size is 3)

Proof of the correctness of the algorithm

Suppose, the algorithm is not correct. It means, that there exists a subarray
a[i], ..., a[j] such that it is the maximum subarray and it consists of only two
types of fruits and it was skipped by two pointers technique algorithm.

If it was skipped, it means either of two cases:

- left pointer was l < i and right pointer was shifted from j to j + 1
- right pointer was r < j and left pointer was shifted from i to i + 1

Let's consider the first situation.
Right pointer was shifted, according to the code, it means that
a[l]...a[i]...a[j] was a correct subarray with only two types.
Because l < i, a[l]...a[i]...a[j] is longer than a[i]...a[j].
Therefore, a[i]...a[j] can't be considered as the answer. Contradiction. This
situation can't happen.


Now, let's consider the second situation.
Left pointer was shifted, according to the code, it means taht
a[i]...a[r] was not a correct subarray. It consisted of at least 3 types.
This means that a[i]...a[j] is also invalid subarray and consists of 3 types.
Thereofe, it can't be an answer to the problem. Contradiction. This situation
can't happen.

Therefore, the algorithm will find the correct answer.

**/

using namespace std;

class Solution {
public:
  int totalFruit(vector<int> &fruits) {
    size_t left = 0;
    size_t right = 0;
    int max_size = 0;
    unordered_map<int, int> fruit_types = {{fruits[left], 1}};
    while (right < fruits.size()) {
      int size = right - left + 1;
      if (fruit_types.size() == 3) {
        fruit_types[fruits[left]]--;
        if (fruit_types[fruits[left]] == 0) {
          fruit_types.erase(fruits[left]);
        }
        left++;
      } else {
        if (size > max_size) {
          max_size = size;
        }

        if (right + 1 < fruits.size()) {
          fruit_types[fruits[right + 1]]++;
        }

        right++;
      }
    }

    return max_size;
  }
};

int main() {
  vector<int> a = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
  cout << Solution().totalFruit(a) << "\n";
}