/**Given a 2D matrix matrix, handle multiple queries of the following type:

Calculate the sum of the elements of matrix inside the rectangle defined by its
upper left corner (row1, col1) and lower right corner (row2, col2). Implement
the NumMatrix class:

NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the
elements of matrix inside the rectangle defined by its upper left corner (row1,
col1) and lower right corner (row2, col2). You must design an algorithm where
sumRegion works on O(1) time complexity.



Example 1:


Input
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3,
0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]] Output [null, 8, 11, 12]

Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0,
1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]); numMatrix.sumRegion(2, 1, 4, 3); //
return 8 (i.e sum of the red rectangle) numMatrix.sumRegion(1, 1, 2, 2); //
return 11 (i.e sum of the green rectangle) numMatrix.sumRegion(1, 2, 2, 4); //
return 12 (i.e sum of the blue rectangle)


Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^4 <= matrix[i][j] <= 10^4
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 10^4 calls will be made to sumRegion


idea:
find rectangle prefixes, using left and up prefixes
(rectangle prefix is left prefix + up prefix + diagonaly-previous rectangle
prefix - current cell, cause we don't need to add it twice)


for rectangle there are 3 situations
1) corner up-left rectangle - it is prefix
2) not 1, but border up rectangle - we need to subtract up one from big prefix
3) not 1, but border left rectangle - we need to subtract left one from big
prefix 4) center rectangle - we need to subtract up and left ones from big
prefix and add left-up rectangle, cause we don't need to subtract it twice)

time: preprocessing : O(m * n), sumRegion: O(1)

space: O(m * n)

.**/

#include <cstddef>
#include <vector>

using namespace std;

class NumMatrix {
public:
  NumMatrix(vector<vector<int>> &matrix) {

    // calculate left prefixes
    left_prefixes_.resize(matrix.size());
    for (size_t i = 0; i < matrix.size(); ++i) {
      left_prefixes_[i].resize(matrix[i].size());
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        left_prefixes_[i][j] = matrix[i][j];

        // add prefix from previous column
        if (j > 0) {
          left_prefixes_[i][j] += left_prefixes_[i][j - 1];
        }
      }
    }

    // calculate up prefixes
    up_prefixes_.resize(matrix.size());
    for (size_t i = 0; i < matrix.size(); ++i) {
      up_prefixes_[i].resize(matrix[i].size());
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        up_prefixes_[i][j] = matrix[i][j];

        // add prefix from previous row
        if (i > 0) {
          up_prefixes_[i][j] += up_prefixes_[i - 1][j];
        }
      }
    }

    // calculate rectangle prefixes
    prefixes_.resize(matrix.size());
    for (size_t i = 0; i < matrix.size(); ++i) {
      prefixes_[i].resize(matrix[i].size());
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        // calculate this row and column prefixes
        prefixes_[i][j] =
            left_prefixes_[i][j] + up_prefixes_[i][j] - matrix[i][j];

        // add prefixes from previous rectangle, if it exists
        if (i != 0 && j != 0) {
          prefixes_[i][j] += prefixes_[i - 1][j - 1];
        }
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    int bigPrefix = prefixes_[row2][col2];

    // region is prefix itself
    if (row1 == 0 && col1 == 0) {
      return bigPrefix;
    }

    // left part should be cut
    if (row1 == 0) {

      return bigPrefix - prefixes_[row2][col1 - 1];
    }

    // up part should be cut
    if (col1 == 0) {
      return bigPrefix - prefixes_[row1 - 1][col2];
    }

    // left and up parts should be cut
    // intersection of left and up shouldn't be cut twice => adding it
    return bigPrefix - prefixes_[row2][col1 - 1] - prefixes_[row1 - 1][col2] +
           prefixes_[row1 - 1][col1 - 1];
  }

private:
  vector<vector<int>> left_prefixes_;
  vector<vector<int>> up_prefixes_;
  vector<vector<int>> prefixes_;
};