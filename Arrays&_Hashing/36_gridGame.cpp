/**You are given a 0-indexed 2D array grid of size 2 x n, where grid[r][c]
represents the number of points at position (r, c) on the matrix. Two robots are
playing a game on this matrix.

Both robots initially start at (0, 0) and want to reach (1, n-1). Each robot may
only move to the right ((r, c) to (r, c + 1)) or down ((r, c) to (r + 1, c)).

At the start of the game, the first robot moves from (0, 0) to (1, n-1),
collecting all the points from the cells on its path. For all cells (r, c)
traversed on the path, grid[r][c] is set to 0. Then, the second robot moves from
(0, 0) to (1, n-1), collecting the points on its path. Note that their paths may
intersect with one another.

The first robot wants to minimize the number of points collected by the second
robot. In contrast, the second robot wants to maximize the number of points it
collects. If both robots play optimally, return the number of points collected
by the second robot.



Example 1:


Input: grid = [[2,5,4],[1,5,1]]
Output: 4
Explanation: The optimal path taken by the first robot is shown in red, and the
optimal path taken by the second robot is shown in blue. The cells visited by
the first robot are set to 0. The second robot will collect 0 + 0 + 4 + 0 = 4
points. Example 2:


Input: grid = [[3,3,1],[8,5,2]]
Output: 4
Explanation: The optimal path taken by the first robot is shown in red, and the
optimal path taken by the second robot is shown in blue. The cells visited by
the first robot are set to 0. The second robot will collect 0 + 3 + 1 + 0 = 4
points. Example 3:


Input: grid = [[1,3,1,15],[1,3,3,1]]
Output: 7
Explanation: The optimal path taken by the first robot is shown in red, and the
optimal path taken by the second robot is shown in blue. The cells visited by
the first robot are set to 0. The second robot will collect 0 + 1 + 3 + 3 + 0 =
7 points.


Constraints:

grid.length == 2
n == grid[r].length
1 <= n <= 5 * 10^4
1 <= grid[r][c] <= 10^5

idea: if we draw the answers for the second robot,
we will see, that for each choice of first robot, there is 0 in the middle, and
from that middle to the left the values grow, as to the right, cause to the left
there are part of prefixes of second row, as answer, and to the right -  part of
postfixes of the first. Thus, maximum in each choice is full prefix with this
choice and full postfix.
time: O(n)
space: O(1)


**/

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

long long gridGame(vector<vector<int>> &grid) {
  long long prefix = 0;
  long long postfix = 0;

  // find postfix in first row, except grid[0][0] -> that are two results for
  // first column choice
  // postfix is calculated by first row
  for (size_t i = 0; i + 1 < grid[0].size(); ++i) {
    size_t j = grid[0].size() - i - 1;
    postfix += grid[0][j];
  }

  // find maximum value in each choice and update minimum

  // prefix is calculated by second row
  // postfix is calculated by first row

  // minimum = max long long
  long long min_value = INT64_MAX;

  // iterate through each choice of first robot
  for (size_t i = 0; i < grid[0].size(); ++i) {

    // two possible maximum paths for a second robot
    long long max_value_in_path = max(prefix, postfix);

    // if this choice of first robot is best, update it
    if (max_value_in_path < min_value) {
      min_value = max_value_in_path;
    }

    // on the last iteration, there is nothing to update, return
    if (i + 1 == grid[0].size()) {
      break;
    }

    // if it is not last iteration, update

    // prefix -> add more, starting from i
    prefix += grid[1][i];

    // postfix -> substract more, starting from i + 1
    postfix -= grid[0][i + 1];
  }

  return min_value;
}
