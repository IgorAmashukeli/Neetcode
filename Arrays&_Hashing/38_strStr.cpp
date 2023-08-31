/**Given two strings needle and haystack, return the index of the first
occurrence of needle in haystack, or -1 if needle is not part of haystack.



Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.


Constraints:

1 <= haystack.length, needle.length <= 10^4
haystack and needle consist of only lowercase English characters.

first solution idea:
create deque (it is possible to pushback and popfront in O(1)) for current
substring check each substring of needle size if it is equal to needle return
the first index when equal or -1

time: O(needle.size() * haystack.size())
space: O(neelde.size())

second solution idea: Knuth-Morris-Pratt

idea: find prefix function, do Knuth-Morris-Prath

Explanation:

Let S be a string

Definition of prefix function:
pi[i] = max{k | k = 0...i s[0...k-1] = s[i - (k-1)...i]}
(for each prefix of s of size i, pi[i] is the size of maximum prefix A of prefix
s[0...i] equal to sufix B of this prefix s[0...i]  (A = B))



Statement 0:


pi[0] = 0

Proof:

pi[0] = max{k | k = 0 | s[0...0-1] = s[i+1...i]}
=>

pi[0] = max{k | k = 0 | empty string = empty string}

=>

pi[0] = 0

End of proof





Statement 1

Let S be a string of size n

pi[i] >= 0
&
pi[i] < n

Proof:
By definition pi[i] >= 0
By definition pi[i] <= i.
Therefore, pi[n - 1] <= n - 1
Therefore, maximum possible value of pi[i] is n - 1
Therefore, pi[i] >= 0 & pi[i] < n

End of proof






Statement 2:

pi[i + 1] <= pi[i] + 1

Proof:

Suppose
pi[i + 1] = m + 1

By definition:
s[0...m] = s[i + 1 - m...i + 1]

i + 1 - m = i - (m - 1)
Therefore:
s[0...m] = s[i - (m - 1)...i + 1]

In particular (taking a substring in both part):
s[0...m-1] = s[i - (m - 1)...i]

That means that m - 1 \in {k | k = 0...i s[0...k-1] = s[i - (k-1)...i]}
Therefore max{k | k = 0...i s[0...k-1] = s[i - (k-1)...i]} >= m - 1
Therefore pi[i] >= m - 1
Therefore pi[i] >= pi[i + 1] - 1
Therefore pi[i + 1] <= pi[i] + 1

End of proof








Statement 3

If s[i + 1] = s[pi[i]] => pi[i + 1] = pi[i] + 1

Proof:

1) By statement 1:
pi[i] >= 0 & pi[i] < n => pi[i] is a valid index for string s

2) Suppose, pi[i] = m

By definition

s[0...m-1] = s[i - (m-1)...i]


Also, s[i + 1] = s[pi[i]] = s[m]
=> s[m] = s[i + 1]

Moreover, using concatenation
=> s[0...m] = s[i - (m-1)...i+1]

=> s[0...m] = s[i + 1 - m ... i+1]

=> s[0...(m + 1) - 1] = s[i + 1 - (m + 1 - 1)...i + 1]

=> m + 1 \in {k | k = 0...i + 1 s[0...k-1] = s[i + 1 - (k-1)...i + 1]}

=> m + 1 <= pi[i + 1]

=> pi[i + 1] >= m + 1

=> pi[i + 1] >= pi[i] + 1

3) By Statement 2:
pi[i + 1] <= pi[i] + 1

Moreover, pi[i + 1] >= pi[i] + 1

Therefore, pi[i + 1] = pi[i]

End of proof








Statement 4

If s[i + 1] != s[pi[i]] => pi[i + 1] < pi[i] + 1

Proof:

Suppose, pi[i] = m =>

By definition
s[0...m-1] = s[i - (m - 1)...i]
=>
s[0...m-1] = s[i + 1 - (m + 1 - 1)...i]


Therefore,
s[0...m-1] = s[i + 1 - (m+1 - 1)...i]
s[m] != s[i + 1]

=> s[0...(m + 1) - 1] != s[i + 1 - (m+1 - 1)...i+1]
(otherwise, s[m] = s[i + 1])

=> m + 1 \notin {k | k = 0...i s[0...k-1] = s[i - (k-1)...i]}

=> pi[i + 1] != m + 1
=> pi[i + 1] != pi[i] + 1

By statement 2, pi[i] <= pi[i] + 1

=> pi[i + 1] < pi[i] + 1

End of proof





Statement 5

If s[i + 1] != s[pi[i]]
&
j = max{k >= 0 & k < pi[i] | s[0...k-1] = s[i - (k-1)...i] & s[i + 1] = s[k]}

=> pi[i + 1] = j + 1

Proof

j = max{k >= 0 & k < pi[i] | s[0...k-1] = s[i - (k-1)...i] & s[i + 1] = s[k]}

=>

j = max{k >= 0 & k < pi[i] | s[0...k] = s[i - (k - 1)...i + 1]}

=>

j + 1 = max{k > 0 & k <= pi[i] | s[0...k-1] = s[i + 1 - (k-1)...i + 1]}

=>

j + 1 = max{k >= 0 & k < pi[i] + 1 | s[0...k-1] = s[i + 1 - (k-1)...i + 1]}

By definition of pi:

pi[i + 1] = max{k : 0...j + 1 | s[0...k-1] = s[i + 1 - (k-1)...i + 1]}

By statement 4:

pi[i + 1] < pi[i] + 1

=>

pi[i + 1] = max{k >= 0 & k < pi[i] + 1 | s[0...k-1] = s[i + 1 - (k-1)...i + 1]}

Therefore, pi[i + 1] = j

End of proof




Statement 6

If s[i + 1] != s[pi[i]]

&

{k >= 0 & k < pi[i] | s[0...k-1] = s[i - (k-1)...i] & s[i + 1] = s[k]} is empty

=> pi[i + 1] = 0

Proof:

s[i + 1] != s[pi[i]]

{k >= 0 & k < pi[i] | s[0...k-1] = s[i - (k-1)...i] & s[i + 1] = s[k]} is empty
=> for all k >= 0 & k < pi[i]: s[i + 1] != s[k]

=> for all k >= 0 & k <= pi[i]: s[i + 1] != s[k]

{k | k = 0...pi[i] | s[0...k] = s[i+1 - (k)... i+1]} is empty, cause s[k] !=
s[i+1] for all k >= 0 & k <= pi[i]}

=> {k | k = 1...pi[i]+1 | s[0...k-1] = s[i+1 - (k - 1) ... i+1]} is empty

=> for all k = 1...pi[i] + 1 : pi[i + 1] != k
but pi[i + 1] <= pi[i] + 1 & pi[i + 1] >= 0

=> pi[i + 1] = 0

End of proof







Statement 7

pi[0] = 0

If s[i + 1] = s[pi[i]] =>

pi[i + 1] = pi[i] + 1

Else:

A = {k | k >= 0 & k < pi[i] | s[0...k-1] = s[i - (k-1)...i] & s[i + 1] = s[k]}

pi[i + 1] = max A, A is not empty
pi[i + 1] = 0, otherwise

Proof:

Statement 0 + Statement 3 + Statement 5 + Statement 6

End of Proof




Statement 8

Algorithm

```
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
          j = pi[j - 1];
        }
        if (s[i] == s[j]) {
          j++;
        }
        pi[i] = j;
    }
    return pi;
}
```
correctly finds pi for each i



Proof:
pi[0] = 0 => OK
for pi[i + 1] algorithm will check for s[i + 1] = s[pi[i]]
(in code there is check on: s[i] = s[pi[i]])
If it is true =>
   "while" will have zero iteration
   "if" will have one iteration
   it will assign pi[i + 1] = pi[i] + 1 => OK
If it is false && A is empty =>
   code will end, when j == 0
   (it can't end, when s[i] != s[j], cause A is empty)
   and "if" will have zero iterations, cause s[i] != s[j]
   => pi[i + 1] = 0 => OK
If it is false && A is not empty =>
   code will go and try to iterate through j's.
   Let's check that while loop iteration is correct.

   Suppose, on some iteration of while loop:
   we already know, that s[0...j - 1] = s[i - (j-1)...i],
   but s[i + 1] != s[j] => j couldn't be an answer.

   For this j we need to find the maximum value k < j,
   such that s[0...k-1] = s[i - (k-1)...i]..

   We need to find max{k | k = 0...j-1 s[0...k-1] = s[i - (k-1)...i]}
   By definition, it is pi[j - 1]

   => the next value to check is pi[j - 1]

   when the value is found, two cases can happen:
        either j = 0, either s[j] = s[i + 1]
          If the first is true =>
          that means, even the set is not empty,
          the max found string is empty => the answer should be incremented by
          1, cause s[i + 1] = s[j], which is happening in "if" statement

          If the fist is false =>
          that means, the max found string j is the length of
          s[0...k-1] = s[i - (k-1)...i], and + 1, because s[i + 1] = s[j],
          which is happening in "if statement"


Statement 9:

Algorithm

```
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
          j = pi[j - 1];
        }
        if (s[i] == s[j]) {
          j++;
        }
        pi[i] = j;
    }
    return pi;
}
```

is O(n)


Proof:

On each for iteration, j increments, stays the same or decreases.
Therefore, max j is n - 1.
On each while iteration, j decreases.

Suppose, there are >= n of "while" iterations overall.
Therefore, j was decreased on at least n. And increased on at least n - 1.
Therefore, j became less than 0. Contradiction.


There are < n "while" iterations overall.
Therefore time complexity of algorithm is O(n)


Statement 10

Knuth Moris Pratt algorithm:

vector<size_t> KMP(const string &P, const string &T) {
    int pl_sz = P.size();
    int n_sz = T.size();


    vector<size_t> answers;


    // "" is everywhere inside P
    if (n_sz == 0) {
      answer.resize(n_sz);
      for (size_t i = 0; i < n_sz) {
        answer[i] = i;
      }
      return answer;
    }



    vector<int> prefix_function = prefixFunction(P + "#" + T);
    for (int i = 0; i < pl_sz; ++i) {
      if (prefix_function[n_sz + i + 1] == n_sz) {
        answers.push_back(i - n_sz - 1);
      }
    }

    return -1;
  }

correctly finds the start positions of occurences of "S" in "T" in O(|S| +
|T|) time

Proof:
If P size is 0 => it returns array with all indicies
Otherwise:

Algorithm finds the max-sufixes equal max-prefix of prefix-substring of P +
'#' + T, starting from T[0], that has size as P. Thus, it finds string that
starts somewhere at T and ends somewhere in T (at the end of prefix-substring)
that matches S. Therefore, algorithm finds the start position of occurences
of "S" in "T".

for loop runs in O(n)
prefix function calculation is O(n)

Therefore, Knuth Moris Pratt algorithm finds the start positions of
occurences of "S" in "T" in O(|S| + |T|) time

...



**/

#include <cassert>
#include <deque>
#include <string>
#include <vector>

using namespace std;

class DequeSolution {

  // check if current substring (represented as deque is the same as needle
  // string)
  bool equal(const deque<char> &substring, const string &needle) {
    assert(substring.size() == needle.size());

    // element-wise comparison
    size_t i = 0;
    for (char elem : substring) {

      // failure => return false
      if (needle[i] != elem) {
        return false;
      }
      ++i;
    }

    // element-wise comparison was true
    return true;
  }

  int strStr(const string &haystack, const string &needle) {
    // check sizes
    if (needle.size() > haystack.size()) {
      return -1;
    }

    // initialization of current substring
    deque<char> cur_substring;
    for (size_t i = 0; i < needle.size(); ++i) {
      cur_substring.push_back(haystack[i]);
    }

    for (size_t i = needle.size(); i < haystack.size(); ++i) {

      // if current substring is needle
      if (equal(cur_substring, needle)) {
        return i - needle.size();
      }

      // update
      cur_substring.push_back(haystack[i]);
      cur_substring.pop_front();
    }

    // check last substring
    if (equal(cur_substring, needle)) {
      return haystack.size() - needle.size();
    }

    return -1;
  }
};

class KnuthMorrisSolution {
  // prefix function calculation
  vector<int> prefixFunction(string s) {
    int n = (int)s.length();
    // pi[0] = 0
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
      // first candidate for pi[i] is pi[i - 1] + 1
      int j = pi[i - 1];

      // find real candidate, if exists
      while (j > 0 && s[i] != s[j]) {
        j = pi[j - 1];
      }

      // if found, add the count of last character s[i]
      if (s[i] == s[j]) {
        j++;
      }

      // store the value of prefix function
      pi[i] = j;
    }
    return pi;
  }

  int strStr(const string &haystack, const string &needle) {
    int hay_size = haystack.size();
    int need_size = needle.size();

    // "" is inside haystack
    if (need_size == 0) {
      return 0;
    }

    vector<int> prefix_function = prefixFunction(needle + "#" + haystack);
    for (int i = 0; i < hay_size; ++i) {
      // needle.size() + '#' + i
      // if this prefix_function is the size of neelde
      // => the maximal sufix is equal to maximal prefix, which is needle,
      // cause, the prefix with size needle, starting from 0 position is needle
      if (prefix_function[need_size + i + 1] == need_size) {

        // get starting position
        // end is i => i - (need_size - 1) is start
        return i - (need_size - 1);
      }
    }

    return -1;
  }
};