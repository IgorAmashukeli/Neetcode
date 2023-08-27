/*Given a string s, find two disjoint palindromic subsequences of s such that
the product of their lengths is maximized. The two subsequences are disjoint if
they do not both pick a character at the same index.

Return the maximum possible product of the lengths of the two palindromic
subsequences.

A subsequence is a string that can be derived from another string by deleting
some or no characters without changing the order of the remaining characters. A
string is palindromic if it reads the same forward and backward.



Example 1:

example-1
Input: s = "leetcodecom"
Output: 9
Explanation: An optimal solution is to choose "ete" for the 1st subsequence and
"cdc" for the 2nd subsequence. The product of their lengths is: 3 * 3 = 9.
Example 2:

Input: s = "bb"
Output: 1
Explanation: An optimal solution is to choose "b" (the first character) for the
1st subsequence and "b" (the second character) for the 2nd subsequence. The
product of their lengths is: 1 * 1 = 1. Example 3:

Input: s = "accbcaxxcxx"
Output: 25
Explanation: An optimal solution is to choose "accca" for the 1st subsequence
and "xxcxx" for the 2nd subsequence. The product of their lengths is: 5 * 5
= 25.


Constraints:

2 <= s.length <= 12
s consists of lowercase English letters only.

idea: simple backtracking, can be further optimized by bitmasks
time: O(2^(2 * n) * n)
space: O(2^n)

***/

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// check if string is palindrom
bool isPalindrom(const string &str) {

  // empty string is palindrom
  if (str.size() == 0) {
    return true;
  }

  // iterate until i != str.size() / 2 and check if string is palindrom
  for (size_t i = 0; i <= str.size() / 2; ++i) {
    size_t j = str.size() - i - 1;
    if (str[i] != str[j]) {
      return false;
    }
  }

  return true;
}

void backtracking(int &index, const string &s, string &str,
                  unordered_set<int> &set,
                  unordered_map<string, unordered_set<int>> &answer, size_t i) {

  // if end of backtracking and found string is palindrom, add to answer return
  // we also use index to distinguish between equal strings
  if (i == s.size() && isPalindrom(str)) {
    answer[str + std::to_string(index)] = set;
    ++index;
    return;

    // if end of backtracking and not a palindrom, return
  } else if (i == s.size()) {
    return;
  }

  // branch, where s[i] is added

  // add s[i]
  str += s[i];
  // insert i index
  set.insert(i);
  // recursion
  backtracking(index, s, str, set, answer, i + 1);

  // branch, where s[i] is not added

  // backtracking -> restore str and set
  str.pop_back();
  set.erase(i);

  // recursion
  backtracking(index, s, str, set, answer, i + 1);
}

// creates str and set to contain results, prepare answer unordered map with all
// the answers find all subsequences
unordered_map<string, unordered_set<int>> findSubseqs(const string &s) {
  unordered_map<string, unordered_set<int>> answer;
  string str;
  unordered_set<int> set;
  int index = 0;

  // call backtracking with index 0
  backtracking(index, s, str, set, answer, 0);
  return answer;
}

// returns if two sets intersects
bool intersection(const unordered_set<int> &st1,
                  const unordered_set<int> &st2) {

  // iterate over all elements in st1 and check if such exists in st2
  for (int el : st1) {

    // if element from st1 is in st2 -> st1 and st2 are intersected
    if (st2.contains(el)) {
      return true;
    }
  }

  // all elements from st1 are not in st2 -> they are not intersected
  return false;
}

// get size of string except digits
size_t getSize(const string &str) {
  size_t size = 0;
  for (char el : str) {
    if (el - '0' < 0 || el - '0' > 9) {
      size++;
    }
  }
  return size;
}

int maxProduct(const string &s) {

  // key : palindrom, value - set of indicies, where palindrom was found
  unordered_map<string, unordered_set<int>> subseqs = findSubseqs(s);

  // s.size() >= 2 => max_product >= 1
  int max_product = 1;

  //
  for (const auto &[str1, st1] : subseqs) {
    for (const auto &[str2, st2] : subseqs) {

      // calculate product of two strings
      int product = getSize(str1) * getSize(str2);

      // if this product is bigger, then found and this palindroms don't
      // intersect update of max product
      if (product > max_product && !intersection(st1, st2)) {
        max_product = product;
      }
    }
  }

  // return max product
  return max_product;
}

int main() {
  string s = "accbcaxxcxx";
  cout << maxProduct(s) << "\n";
}