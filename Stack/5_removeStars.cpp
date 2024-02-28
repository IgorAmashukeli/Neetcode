#include <cassert>
#include <iostream>
#include <memory>
#include <string>

/**
You are given a string s, which contains stars *.

In one operation, you can:

Choose a star in s.
Remove the closest non-star character to its left, as well as remove the star
itself. Return the string after all stars have been removed.

Note:

The input will be generated such that the operation is always possible.
It can be shown that the resulting string will always be unique.


Example 1:

Input: s = "leet**cod*e"
Output: "lecoe"
Explanation: Performing the removals from left to right:
- The closest character to the 1st star is 't' in "leet**cod*e". s becomes
"lee*cod*e".
- The closest character to the 2nd star is 'e' in "lee*cod*e". s becomes
"lecod*e".
- The closest character to the 3rd star is 'd' in "lecod*e". s becomes "lecoe".
There are no more stars, so we return "lecoe".
Example 2:

Input: s = "erase*****"
Output: ""
Explanation: The entire string is removed, so we return an empty string.


Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters and stars *.
The operation above can be performed on s.

Solution2 idea: use linked list and remove all * and left non-star
from left to right, manipulating with pointers

**/

using namespace std;

struct List {
  List(char value) {
    value_ = value;
    next_ = nullptr;
    prev_ = nullptr;
  }
  char value_;
  List *next_;
  List *prev_;
};

class Solution {
public:
  List *stringToList(const string &s) {
    List *head = nullptr;
    List *prev = nullptr;
    for (size_t i = 0; i < s.size(); ++i) {
      List *cur = new List(s[i]);
      if (i == 0) {
        head = cur;
      } else if (i > 0) {
        cur->prev_ = prev;
        prev->next_ = cur;
      }
      prev = cur;
    }
    return head;
  }

  string ListToString(List *head) {
    string answer = "";
    while (head != nullptr) {
      answer += head->value_;
      head = head->next_;
    }
    return answer;
  }

  void deleteList(List *head) {
    List *tmp;
    while (head != nullptr) {
      tmp = head->next_;
      delete head;
      head = tmp;
    }
  }

  List *removeStar(List *cur, List *&head) {
    List *prev = cur->prev_;
    assert(prev != nullptr);
    List *prev_prev = prev->prev_;
    List *next = cur->next_;
    if (prev_prev != nullptr) {
      prev_prev->next_ = next;
    }
    if (next != nullptr) {
      next->prev_ = prev_prev;
    }
    delete cur;
    if (prev == head) {
      head = next;
    }
    delete prev;
    return next;
  }

  List *removeStars(List *head, size_t size) {
    List *cur = head;
    while (cur != nullptr) {
      if (cur->value_ == '*') {
        cur = removeStar(cur, head);
        size -= 2;
        continue;
      }
      cur = cur->next_;
    }
    if (size > 0) {
      return head;
    } else {
      return nullptr;
    }
  }

  string removeStars(const string &s) {
    List *head = stringToList(s);
    List *head2 = removeStars(head, s.size());
    string answer = ListToString(head2);
    deleteList(head2);
    return answer;
  }
};

int main() {
  Solution solution = Solution();
  cout << solution.removeStars("u*ensso****x*q") << "\n";
}