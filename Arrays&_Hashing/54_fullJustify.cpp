/**
https://leetcode.com/problems/text-justification/

Given an array of strings words and a width maxWidth, format the text such
that each line has exactly maxWidth characters and is fully (left and right)
justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line does not divide evenly between words, the empty slots
on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is
inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters
only. Each word's length is guaranteed to be greater than 0 and not exceed
maxWidth. The input array words contains at least one word.


Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."],
maxWidth = 16 Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall be",
because the last line must be left-justified instead of fully-justified. Note
that the second line is also left-justified because it contains only one word.
Example 3:

Input: words =
["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"],
maxWidth = 20 Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]


Constraints:

1 <= words.length <= 300
1 <= words[i].length <= 20
words[i] consists of only English letters and symbols.
1 <= maxWidth <= 100
words[i].length <= maxWidth

Straightforward
**/

#include <string>
#include <vector>

using namespace std;

/*find number of lines and number of words in each line using greedy approach*/
vector<int> findCounts(vector<string> &words, int maxWidth) {
  // number of words in each line
  vector<int> counts;
  // current length of words, concatenated together
  size_t cur_len = 0;
  // current number of words
  size_t count_packed_in_line = 0;

  // packing all words
  for (size_t i = 0; i < words.size(); ++i) {
    // updating variables
    cur_len += words[i].size();
    ++count_packed_in_line;

    // too long string for maxWidth
    if (cur_len + (count_packed_in_line - 1) > maxWidth) {
      // save previous value
      counts.push_back(count_packed_in_line - 1);

      // current length for next string contains one word
      cur_len = words[i].size();
      count_packed_in_line = 1;

      // last word to add
    }
    if (i + 1 == words.size()) {
      counts.push_back(count_packed_in_line);
    }
  }

  return counts;
}

vector<string> fullJustify(vector<string> &words, int maxWidth) {
  // answer
  vector<string> answer;
  // find counts
  vector<int> counts = findCounts(words, maxWidth);
  answer.resize(counts.size());

  size_t index = 0;

  // create answer
  for (size_t i = 0; i < counts.size(); ++i) {

    // last row
    if (i + 1 == counts.size()) {
      size_t count = words.size() - index;

      for (size_t j = index; j < count; ++j) {
        // add word
        answer[i] += words[index + j];

        // add spaces after last word
        if (j + 1 == count) {
          // last space is everything it needs to be filled to satisfy maxWidth
          // constraint
          size_t last_space_size = maxWidth - answer[i].size();
          for (size_t k = 0; k < last_space_size; ++k) {
            answer[i] += " ";
          }

          // add spaces after non-last word
        } else {
          answer[i] += " ";
        }
      }

      // non-last row
    } else {
      size_t count = counts[i];
      // only one word => no spaces
      if (count == 1) {
        answer[i] += words[index];

        // last space is everything it needs to be filled to satisfy maxWidth
        // constraint
        size_t last_space_size = maxWidth - answer[i].size();
        for (size_t k = 0; k < last_space_size; ++k) {
          answer[i] += " ";
        }

        // more than one word
      } else {
        // number of spaces left
        size_t overall_space_size = maxWidth;
        for (size_t j = 0; j < count; ++j) {
          overall_space_size -= words[index + j].size();
        }

        // number of spaces between each word, distribute evenly
        size_t space_between = overall_space_size / (count - 1);

        // there are remainders
        size_t remainder = overall_space_size % (count - 1);

        // create line
        for (size_t j = 0; j < count; ++j) {

          // add word
          answer[i] += words[index + j];

          // non-last word should have space
          if (j + 1 != count) {

            // add spaces
            for (size_t k = 0; k < space_between; ++k) {
              answer[i] += " ";
            }

            // add 1 more space if remainder is not zero
            if (remainder != 0) {
              answer[i] += " ";
              --remainder;
            }
          }
        }
      }
      // shift to the next row word
      index += count;
    }
  }

  return answer;
}

int main() {}