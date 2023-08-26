/**You are given n rectangles represented by a 0-indexed 2D integer array
rectangles, where rectangles[i] = [widthi, heighti] denotes the width and height
of the ith rectangle.

Two rectangles i and j (i < j) are considered interchangeable if they have the
same width-to-height ratio. More formally, two rectangles are interchangeable if
widthi/heighti == widthj/heightj (using decimal division, not integer division).

Return the number of pairs of interchangeable rectangles in rectangles.



Example 1:

Input: rectangles = [[4,8],[3,6],[10,20],[15,30]]
Output: 6
Explanation: The following are the interchangeable pairs of rectangles by index
(0-indexed):
- Rectangle 0 with rectangle 1: 4/8 == 3/6.
- Rectangle 0 with rectangle 2: 4/8 == 10/20.
- Rectangle 0 with rectangle 3: 4/8 == 15/30.
- Rectangle 1 with rectangle 2: 3/6 == 10/20.
- Rectangle 1 with rectangle 3: 3/6 == 15/30.
- Rectangle 2 with rectangle 3: 10/20 == 15/30.
Example 2:

Input: rectangles = [[4,5],[7,8]]
Output: 0
Explanation: There are no interchangeable pairs of rectangles.


Constraints:

n == rectangles.length
1 <= n <= 10^5
rectangles[i].length == 2
1 <= width_i, height_i <= 10^5

idea: map of Rational number, straightforward count of groups
time: O(n log n)
space: O(n)

**/

#include <map>
#include <vector>

using namespace std;

class RationalNumber {
public:
  RationalNumber(long long num, long long den) {
    num_ = num;
    den_ = den;
    num_ /= gcd(num, den);
    den_ /= gcd(num, den);
  }

  long gcd(long long a, long long b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }

  bool operator<(const RationalNumber &other) const {
    long long A = get_num();
    long long B = get_den();
    long long C = other.get_num();
    long long D = other.get_den();
    return (A * D < B * C);
  }

  bool operator==(const RationalNumber &other) const {
    long long A = get_num();
    long long B = get_den();
    long long C = other.get_num();
    long long D = other.get_den();
    return (A * D == B * C);
  }

  long long get_num() const { return num_; }

  long long get_den() const { return den_; }

private:
  long long num_;
  long long den_;
};

long long interchangeableRectangles(vector<vector<int>> &rectangles) {
  map<RationalNumber, long long> groups;
  for (const auto &rectangle : rectangles) {
    groups[RationalNumber(rectangle[0], rectangle[1])]++;
  }

  long long pair_count = 0;
  for (const auto &[rect, group] : groups) {

    pair_count += (group * (group - 1) / 2);
  }

  return pair_count;
}
