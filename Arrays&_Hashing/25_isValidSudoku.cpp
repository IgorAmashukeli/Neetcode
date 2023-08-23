/**Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without
repetition. Note:

A Sudoku board (partially filled) could be valid but is not necessarily
solvable. Only the filled cells need to be validated according to the mentioned
rules.

Input: board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
Example 2:

Input: board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being
modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is
invalid.


Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.


idea: straightforward
time: O(1)
space: O(1)
**/

#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// check if some entity contains valid symbols
bool checkValidSymbols(const unordered_set<char> &allowed_chars,
                       const unordered_map<char, int> &counts) {
  for (const auto &[chr, count] : counts) {

    // some strange symbol
    if (!allowed_chars.contains(chr)) {
      return false;
    }

    // repetition of 1-9
    if (chr != '.' && count > 1) {
      return false;
    }
  }

  return true;
}

// check rows
bool checkRows(const vector<vector<char>> &board,
               const unordered_set<char> &allowed_chars) {

  // iterate through rows
  for (size_t i = 0; i < 9; ++i) {
    unordered_map<char, int> counts;

    // get counts in this row
    for (size_t j = 0; j < 9; ++j) {
      ++counts[board[i][j]];
    }

    // row was not valid
    if (!checkValidSymbols(allowed_chars, counts)) {
      return false;
    }
  }

  return true;
}

// check columns
bool checkColumns(const vector<vector<char>> &board,
                  const unordered_set<char> &allowed_chars) {

  // iterate through columns
  for (size_t i = 0; i < 9; ++i) {
    unordered_map<char, int> counts;

    // get counts in this column
    for (size_t j = 0; j < 9; ++j) {
      ++counts[board[j][i]];
    }

    // column was not valid
    if (!checkValidSymbols(allowed_chars, counts)) {
      return false;
    }
  }

  return true;
}

// check grid
bool checkGrids(const vector<vector<char>> &board,
                const unordered_set<char> &allowed_chars) {

  // iterate through grids
  for (size_t i = 0; i < 9; ++i) {
    // row start of a grid
    int row = (i / 3) * 3;

    // column start of a grid
    int column = (i % 3) * 3;

    unordered_map<char, int> counts;

    // get counts from grid
    for (size_t j = 0; j < 3; ++j) {

      // update columns
      for (size_t k = 0; k < 3; ++k) {

        ++counts[board[row + j][column + k]];
      }
    }

    // grid was not valid
    if (!checkValidSymbols(allowed_chars, counts)) {
      return false;
    }
  }

  return true;
}

// check rows, check columns, check grids
bool isValidSudoku(const vector<vector<char>> &board) {
  unordered_set<char> allowed_chars = {'0', '1', '2', '3', '4', '5',
                                       '6', '7', '8', '9', '.'};
  if (!checkRows(board, allowed_chars)) {
    return false;
  }

  if (!checkColumns(board, allowed_chars)) {
    return false;
  }

  if (!checkGrids(board, allowed_chars)) {
    return false;
  }

  return true;
}