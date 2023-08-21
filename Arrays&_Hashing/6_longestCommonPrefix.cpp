/**Write a function to find the longest common prefix string amongst an array of
strings.

If there is no common prefix, return an empty string "".



Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.


Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters.


first solution: divide and conquer
divide vector in two parts
find common prefix in each part
return common prefix of both parts


time:
Suppose,
M - is the size of the vector
N - is the size of each of the biggest string
Then, time complexity is O(N * log M)
space: O(N * log M)


second solution:
checking  O(N * M)

**/

#include <string>
#include <vector>

using namespace std;

class DivideAndConquerSolution {
public:
  // common prefix of 2 strings
  string longestCommonPrefix(const string &s_1, const string &s_2,
                             string &common_prefix) {
    common_prefix = "";
    // if one of the string is empty, prefix is empty
    if (s_1.size() == 0 || s_2.size() == 0) {
      return common_prefix;
    }

    size_t i = 0;
    while (i < s_1.size() && i < s_2.size() && s_1[i] == s_2[i]) {
      common_prefix.push_back(s_1[i]);
      i++;
    }
    return common_prefix;
  }

  // l never equals r
  // (at first call, we call only in case of non empty string)
  // (at recursion call, we never call, when l == r)
  string longestCommonPrefix(const vector<string> &strs, size_t l, size_t r,
                             string &answer) {
    if (r - l == 1) {
      return strs[l];
    }

    size_t mid = l + (r - l) / 2;

    if ((l != mid) && (mid != r)) {
      string str_left = longestCommonPrefix(strs, l, mid, answer);
      string str_right = longestCommonPrefix(strs, mid, r, answer);
      return longestCommonPrefix(str_left, str_right, answer);
    }

    else if (l == mid) {
      return longestCommonPrefix(strs, mid, r, answer);
    }

    else {
      return longestCommonPrefix(strs, l, mid, answer);
    }
  }

  string longestCommonPrefix(const vector<string> &strs) {
    if (strs.size() == 0) {
      return "";
    }
    string answer;
    return longestCommonPrefix(strs, 0, strs.size(), answer);
  }
};

class SimpleSolution {
public:
  size_t findShortest(const vector<string> &strs) {
    size_t shortest = strs[0].size();
    size_t short_id = 0;
    for (size_t i = 0; i < strs.size(); ++i) {
      if (strs[i].size() < shortest) {
        shortest = strs[i].size();
        short_id = i;
      }
    }
    return short_id;
  }

  string longestCommonPrefix(const vector<string> &strs) {
    if (strs.size() == 0) {
      return "";
    }
    size_t shortest_id = findShortest(strs);
    string answer = strs[shortest_id];
    for (size_t i = 0; i < strs.size(); ++i) {
      if (i != shortest_id) {
        for (size_t j = 0; j < strs[j].size(); ++j) {
          if (strs[i][j] != answer[j]) {
            answer = strs[i].substr(0, j);
            break;
          }
        }
      }
    }

    return answer;
  }
};
