/**Given a list of non-negative integers nums, arrange them such that they form
the largest number and return it.

Since the result may be very large, so you need to return a string instead of an
integer.



Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"


Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 10^9

idea:
there is an order: a_i >s a_j <=> a_ia_j is bigger number than a_ja_i
we can sort array in decreasing order, according to this definition.

Thus, we will get the largest number we can get, rearranging array.

(cause, if it is not true and there exist larger value, we can state that larger
value has two different integers a_i and a_j such that a_i >s a_j in answer and
a_i <s a_j in larger value. Moreover, there exist k and r that a_k >s a_r in
answer and a_k <s a_r in larger value and a_k and a_r are consecutive in larger
value. If a_i and a_j are consecutive: k = i and r = j. Else, a_k and a_r are
located between (including a_i and a_j) a_i and a_j in larger value. (If they
don't exist, a_i >=s ... >=s a_j => a_i >=s a_j => contradiction)


)
**/
#include <algorithm>
#include <cstdint>
#include <vector>

#include <string>

using namespace std;

// sort in decreasing lexicographical order
void sortLargest(vector<int> &nums) {
  sort(nums.begin(), nums.end(), [](int &elem1, int &elem2) {
    string elem1_str = to_string(elem1);
    string elem2_str = to_string(elem2);
    string elem1_go_first = elem1_str + elem2_str;
    string elem2_go_first = elem2_str + elem1_str;
    uint64_t elem1_elem2 = stoull(elem1_go_first);
    uint64_t elem2_elem1 = stoull(elem1_go_first);

    return elem1_elem2 > elem2_elem1;
  });
}

string largestNumber(vector<int> &nums) {
  // sort in lexicogrpahical order
  sortLargest(nums);
  string answer;

  // get answer
  bool leading = true;
  for (int num : nums) {
    // skip leading zeroes
    if (num == 0 && leading) {
      continue;
    } else {
      answer += to_string(num);
      leading = false;
    }
  }

  // nums is not empty => it can only happen if answer is 0
  if (answer == "") {
    answer = "0";
  }

  return answer;
}