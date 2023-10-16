/**
You are given an array of strings ideas that represents a list of names to be
used in the process of naming a company. The process of naming a company is as
follows:

Choose 2 distinct names from ideas, call them ideaA and ideaB.
Swap the first letters of ideaA and ideaB with each other.
If both of the new names are not found in the original ideas, then the name
ideaA ideaB (the concatenation of ideaA and ideaB, separated by a space) is a
valid company name. Otherwise, it is not a valid name. Return the number of
distinct valid names for the company.



Example 1:

Input: ideas = ["coffee","donuts","time","toffee"]
Output: 6
Explanation: The following selections are valid:
- ("coffee", "donuts"): The company name created is "doffee conuts".
- ("donuts", "coffee"): The company name created is "conuts doffee".
- ("donuts", "time"): The company name created is "tonuts dime".
- ("donuts", "toffee"): The company name created is "tonuts doffee".
- ("time", "donuts"): The company name created is "dime tonuts".
- ("toffee", "donuts"): The company name created is "doffee tonuts".
Therefore, there are a total of 6 distinct company names.

The following are some examples of invalid selections:
- ("coffee", "time"): The name "toffee" formed after swapping already exists in
the original array.
- ("time", "toffee"): Both names are still the same after swapping and exist in
the original array.
- ("coffee", "toffee"): Both names formed after swapping already exist in the
original array. Example 2:

Input: ideas = ["lack","back"]
Output: 0
Explanation: There are no valid selections. Therefore, 0 is returned.


Constraints:

2 <= ideas.length <= 5 * 10^4
1 <= ideas[i].length <= 10
ideas[i] consists of lowercase English letters.
All the strings in ideas are unique.


idea:
(hash map start letter -> hash set of end suffix) of size 26
for each two letters x and y and X and Y sets:
  calculate (X.size() - XY.size()) * (Y.size() - XY.size())

**/

#include <array>
#include <cstddef>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int COUNT = 26;

size_t intersection_size(const unordered_set<string> &a,
                         const unordered_set<string> &b) {
  size_t count = 0;
  for (const auto &elem : a) {
    if (b.contains(elem)) {
      count += 1;
    }
  }
  return count;
}

long long distinctNames(vector<string> &ideas) {
  // all strings
  unordered_set all_values(ideas.begin(), ideas.end());
  unordered_set<char> all_starts;
  for (const auto &elem : all_values) {
    all_starts.insert(elem[0]);
  }

  // all endings
  unordered_set<string> all_endings;
  for (const auto &elem : all_values) {
    all_endings.insert(elem.substr(1));
  }

  // contained endings and not contained
  unordered_map<char, unordered_set<string>> endings;
  for (const auto &elem : all_endings) {
    for (char start_chr : all_starts) {
      string start_str = "0";
      start_str[0] = start_chr;
      if (all_values.contains(start_str + elem)) {
        endings[start_chr].insert(elem);
      }
    }
  }

  long long count = 0;

  for (char x : all_starts) {
    for (char y : all_starts) {
      long long x_size = endings[x].size();
      long long y_size = endings[y].size();
      long long common = intersection_size(endings[x], endings[y]);
      count += (x_size - common) * (y_size - common);
    }
  }

  return count;
}