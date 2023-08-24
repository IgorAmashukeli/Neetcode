/**There is a rectangular brick wall in front of you with n rows of bricks. The
ith row has some number of bricks each of the same height (i.e., one unit) but
they can be of different widths. The total width of each row is the same.

Draw a vertical line from the top to the bottom and cross the least bricks. If
your line goes through the edge of a brick, then the brick is not considered as
crossed. You cannot draw a line just along one of the two vertical edges of the
wall, in which case the line will obviously cross no bricks.

Given the 2D array wall that contains the information about the wall, return the
minimum number of crossed bricks after drawing such a vertical line.

Input: wall = [[1,2,2,1],[3,1,2],[1,3,2],[2,4],[3,1,2],[1,3,1,1]]
Output: 2
Example 2:

Input: wall = [[1],[1],[1]]
Output: 3


Constraints:

n == wall.length
1 <= n <= 10^4
1 <= wall[i].length <= 10^4
1 <= sum(wall[i].length) <= 2 * 10^4
sum(wall[i]) is the same for each row i.
1 <= wall[i][j] <= 2^31 - 1


idea: slightly better, than a brute force solution

Instead of checking each column to get the number of crosses,
we go through each row and remember positions of gaps

Thus, we get not O(n * width), but O(number of bricks),
which is actuall O(n * width)

time: O(nuber of bricks)
space: O(sum(wall[i]))
**/

#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

int leastBricks(vector<vector<int>> &wall) {

  // map of gaps positions to counts
  unordered_map<int, int> gaps_counts;

  // iterate through wall
  for (size_t i = 0; i < wall.size(); ++i) {

    // prefix sum, to get position
    int position = 0;

    // iterate through row, except last brick end position (it is end line)
    for (size_t j = 0; j + 1 < wall[i].size(); ++j) {

      // get position
      position += wall[i][j];

      // increment count of this position
      gaps_counts[position]++;
    }
  }

  // max gap count
  int max_gap_count = 0;

  for (const auto &[gap, count] : gaps_counts) {
    if (count > max_gap_count) {
      max_gap_count = count;
    }
  }

  // min cross = number of rows - max gap count
  return wall.size() - max_gap_count;
}