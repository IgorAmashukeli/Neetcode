#include <string>

using namespace std;

string mergeAlternately(string word1, string word2) {
  // result
  string result = "";

  // three pointers: for word1, word2 and result
  size_t i, j, k;
  i = j = k = 0;

  // merge all letters
  while (i != word1.size() || j != word2.size()) {

    // order of the first word
    if ((i < word1.size() && j < word2.size() && k % 2 == 0) ||
        (j == word2.size())) {
      result += word1[i];
      ++i;
      ++k;

      // order of the second word
    } else if ((i < word1.size() && j < word2.size() && k % 2 == 1) ||
               (i == word1.size())) {
      result += word2[j];
      ++j;
      ++k;
    }
  }

  return result;
}