/**Given two strings s and t, return true if s is a subsequence of t, or false
otherwise.

A subsequence of a string is a new string that is formed from the original
string by deleting some (can be none) of the characters without disturbing the
relative positions of the remaining characters. (i.e., "ace" is a subsequence of
"abcde" while "aec" is not).



Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true
Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false


Constraints:

0 <= s.length <= 100
0 <= t.length <= 10^4
s and t consist only of lowercase English letters.

first solution (without follow up): two pointers techique:
i - s pointer
j - t pointer
go through t string
if s[i] = t[j] -> shift j
time: O(|T|)
space: O(1)


second solution (follow up) :
create a vector:
index : <char> - 'a'
value : vector of positions, where this character can be
how to find S string in T?
for the first character in S we just find the first value : position
(and check if it is not empty)

if we know the value : position for the i-th character, we can find the value :
position for the second using binary search: we will find the first position >=
index found on previous iteration


Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >=
109, and you want to check one by one to see if t has its subsequence. In this
scenario, how would you change your code?**/

#include <string>
#include <vector>

using namespace std;

// first solution: two pointers : O(|T|)
class TwoPointersSolution {
public:
  bool isSubsequence(const string &s, const string &t) {
    size_t j = 0;

    // iterate over t
    for (size_t i = 0; i < t.size(); ++i) {

      // s was fully iterated -> found s as a subsequence
      if (j == s.size()) {
        return true;
      }

      // found another s element in t -> shift s index
      if (t[i] == s[j]) {
        j++;
      }
    }
    return j == s.size();
  }
};

enum { NOT_FOUND = -2 };

// second solution : vector of vector of indicies + binary search
class HashMapBinarySearchSolution {
public:
  // preprocessing positions vector
  vector<vector<int>> preprocess(const string &str) {
    vector<vector<int>> positions;

    positions.resize(26);

    for (size_t i = 0; i < str.size(); ++i) {
      positions[str[i] - 'a'].push_back(i);
    }

    return positions;
  }

  // left bound binary search
  int findIndex(const vector<int> &positions, int prev_i) {
    // there are no positions at all -> return NOT_FOUND
    if (positions.size() == 0) {
      return NOT_FOUND;
    }

    // left index
    size_t left = 0;

    // right index
    size_t right = positions.size();

    int found_position = NOT_FOUND;

    // binary search
    while (left < right) {
      int mid = left + (right - left) / 2;

      // not valid position
      if (positions[mid] <= prev_i) {
        left = mid + 1;
      } else {

        // valid position, let's remember and try to find better
        found_position = positions[mid];
        right = mid;
      }
    }

    // if left = right is valid, remember this as best
    if (left < positions.size() && positions[right] > prev_i) {
      found_position = positions[right];
    }

    // return the index
    return found_position;
  }

  bool isSubsequence(const string &s, const string &t) {

    // find positions
    vector<vector<int>> positions = preprocess(t);

    int prev_i = -1;
    for (char chr : s) {

      // find index for s_i
      int cur_i = findIndex(positions[chr - 'a'], prev_i);
      if (cur_i == NOT_FOUND) {
        return false;
      }
      prev_i = cur_i;
    }

    return true;
  }
};