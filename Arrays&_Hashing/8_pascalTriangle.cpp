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