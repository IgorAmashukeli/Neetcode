/**
https://leetcode.com/problems/pascals-triangle/

Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above
it as shown:

Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above
it as shown:

Example 1:

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
Example 2:

Input: numRows = 1
Output: [[1]]


Constraints:

1 <= numRows <= 30

idea: straightforward calculation
time: O(n^2)
space: O(1)
**/

#include <cstddef>
#include <vector>

using namespace std;

vector<vector<int>> generate(int numRows) {
  vector<vector<int>> pascal_triangles;
  pascal_triangles.resize(numRows);
  for (size_t i = 0; i < pascal_triangles.size(); ++i) {
    pascal_triangles[i].resize(i + 1);
  }
  pascal_triangles[0] = {1};
  for (size_t i = 1; i < pascal_triangles.size(); ++i) {
    pascal_triangles[i][0] = 1;
    for (size_t j = 1; j + 1 < pascal_triangles[i].size(); ++j) {
      pascal_triangles[i][j] =
          pascal_triangles[i - 1][j - 1] + pascal_triangles[i - 1][j];
    }
    pascal_triangles[i][i] = 1;
  }
  return pascal_triangles;
}