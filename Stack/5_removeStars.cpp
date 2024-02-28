#include <algorithm>
#include <cassert>
#include <cstddef>
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

Solution1 idea:
have balance value
scan the string from the right to left
if balance == 0 and value != "*", add it to the string
else if value == "*", balance ++
else if value != "*", balance --


Let's prove that if we reverse the result, it will be correct.

We need to prove that the strings will be the same,
if we remove from first star and the left char next to it
and so on and if we do the algorithm with balance.


1) In the balace algorithm we never add the '*' symbols

2) Let's prove we never add wrong symbols and add all correct symbols.

Let's prove by induction.

When we are scanning from the right to the left and find the first non-star,
and balance is 0, it means, we found no stars before. By algorithm A, there
can't be any stars that we are going to use to remove it. Therefore, we need to
add it to the final result. If balance is > 0, it means that there were stars to
the right. Moreover, the next element to this non-star is star (otherwise it is
not the fist non-star element). In algorithm A, this non-star element can't be
removed by stars to the left of it. When we reach this star to the right of it,
we will remove this element as the one that is previous to it. Threfore, it
should be removed by star and therefore shouldn't be added to the final result.



Let's name the scanning from the left to the right algorithm
(one that we need to do in requirements of the problem and one that is
implemented in Linked List Solution2 as algorithm A
)

These symbols can't be removed (there are no stars to the right of them)


Now, let's look at some middle non-star symbol "a".
Suppose, balance = d
At the start, balance = 0
It was incremented everytime we met "*"
It was decremented everytime we met non-star and balance was > 0
It stayed the same everytime we met non-star and balance was 0

By induction, all the symbols added to the final string, were correct
and all correct symbols so far were added to the final string.

These means, that if we exclude the symbols that we added to the final string,
among all other symbols:
- balance was incremented everytime we met "*"
- balance was decremented everytime we met non-star

Therefore, d = (#star elements among non-added) - (#non-star elements among
non-added)

Suppose, d = 0
This means that (#star elements among non-added) = (#non-star elements among
non-added)

Because, each star removes a non-star element,
it means that the number of elements removed by these stars should be equal
to the number of stars found so far. Suppose, this number is k

Therefore, now the number of non-star non-added elements so far is k.
By induction, all added elements are the elements that will not be removed
by the algorithm A and all the elements
to the right of "a" that will not be removed by the algorithm A are all added
elements.

Therefore, it means that all non-added elements are the elements removed so far
by the algorithm A and all the elements removed so far by the algorithm A are
the elements non-added

Suppose "a" shouldn't be added to the final result. In the final result
all the elements are the ones that are not removed.
This means that "a" should be removed by the algorithm A
This means there exists a star to the right of "a" that should remove this "a"
So far we removed the number of elements equal to the number of found stars.
And all other stars are to the left of these elements. Therefore,
they can't be removed with the stars to the left of "a". Because non-star
should be not to the right, but to the left of stars. These means, that all
these elements were removed by the stars to the right and according to the
induction hypothesis, they were correctly removed. Therefore, for all stars to
the right of "a" all the non-star elements were removed. For all stars to the
left of "a", they can't remove "a". Therefore, there is no star such that we
need to remove "a". Therefore, "a" shouldn't be removed. Therefore it should be
added to the final result.


Therefore, if balance is 0, non-star element should be added to the final
result.

Now, suppose, the balance is > 0
This means (#star elements among non-added) > (# non-star elements among
non-added)

Suppose "a" should be added to the final result. In the final result all the
elements are the ones that are not removed. This means that "a" shouldn't be
removed by the algorithm A.

    - If all non-star elements that should be removed by
    the algorithm A with the stars to the right of "a", then the number of the
    non-star elements removed should be equal to the number of stars to the
rights. This means that the number of non-star elements among non-added should
be equal to the number of stars to the right. But this is not true. This means
that there exists a star to the right of "a", for which there should be an
element to add to the final result, but it wasn't added so far. And therefore,
it should be added with the elements starting with the "a" and more to the left.
Let's take the most left such star. Let's name this star V. For all the stars to
the right all the elements removed by Algorithm A are to the right of "a". This
is the most left star for which in Algorithm A we can possibly delete "a".

    - Suppose, the non-star element to add with this star is to the right of
"a". By induction hypothesis, all elements to the right of "a", that need to be
    added, are added. Therefore, it can't be true.

    - Now, let's suppose, this element
    is to the left of "a". It is some element "b". Suppose, we are running
algorithm A and reached this star V. And we move to the right to delete the
non-star element. This element is "b". Because, in initial string, the order was
as such: "b"...."a"...."star V" and now the order is "b""star V", it means that
"a" is removed by some star to the left of V. But V is the most left star for
which in Algorithm A we can possibly delete "a". Thefore, it can't be true.

    - Finally, the only element to remove with star "V" is element "a"


Therefore, "a" shouldn't be added to the final result.



Therefore, given that for all non-star elements to the right of "a",
- if balance is 0, we need to add it to the final result
- if balance is > 0, we don't need to add it to the final result
we proved that for the non-star element "a" itself
- if balance is 0, we need to add it to the final result
- if balance is > 0, we don't need to add it to the final result.

And also, for the first non-star element
- if balance is 0, we need to add it to the final result
- if balance is > 0, we don't need to add it to the final result



Therefore, for all elements in the string:
- if balance is 0, we need to add it to the final result
- if balance is > 0, we don't need to add it to the final result

Therefore, all elements, added to the final result are the ones that are not
removed. And they added from the right to the left. After revese, these are all
the non-removed elements from the initial string in the correct order.
Therefore, this is the result of algorithm A and we can remove it




Solution2 idea: use linked list and remove all * and left non-star
from left to right, manipulating with pointers. It is basically the algorithm A

Both algoritms work in O(n). But the first operate with consequent memory, while
the second works with pointers that are stored in different parts of memory.
For CPU cash the first one is better.

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

class Solution2 {
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

class Solution {
public:
  string removeStars(const string &s) {
    int balance = 0;
    string answer = "";
    for (size_t i = 0; i < s.size(); ++i) {
      size_t j = s.size() - i - 1;
      if (s[j] != '*' && balance == 0) {
        answer += s[j];
      } else {
        if (s[j] == '*') {
          balance++;
        } else {
          balance--;
        }
      }
    }
    reverse(answer.begin(), answer.end());
    return answer;
  }
};

int main() {
  Solution solution = Solution();
  cout << solution.removeStars("erase*****") << "\n";
}