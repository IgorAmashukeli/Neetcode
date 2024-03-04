#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

/**
1209. Remove All Adjacent Duplicates in String II

You are given a string s and an integer k, a k duplicate removal consists of
choosing k adjacent and equal letters from s and removing them, causing the left
and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It is
guaranteed that the answer is unique.



Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation:
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"


Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lowercase English letters.

idea:

create two variables:

stack<pair<char, int>> counts
and
string answer

if stack is empty: we push <str[i], 1>
if stack.top().first == str[i] ->
    if m = stack.top().second + 1 < k ->
        we pop value and
        we push <str[i], m + 1>
    else
        we pop value
if stack.top().firsr != str[i] ->
    we push <str[i], 1>

and we modify the string accordingly
(push some char or pop all k chars)

It is guaranteed that the answer is unique

Therefore, we can do removing in any order.

Therefore, in the stack we always have the partition of the
current prefix of the string by duplicates, where all duplicates of size
== k are removed.

Let's proof this

Iteration 0:

the stack is empty =>
we add counts.push({s[i], 1});


Suppose, for all iterations < i we proved that the counts array contains the
correct answer.

Let's proof for the iteration i

Suppose the stack contains:

<a_1, count_1>, ..., <a_m count_m>

It is the partition of the prefix by duplicates,
where all duplicates of size == k are removed.

Now, there are different cases:
    - stack is empty => there is nothing left after removing all
    the duplicates of size == k in the prefix.
    If there even exists a duplicate substring of size k,
    which started in that prefix, it then ended in that substring
    or has size > k => the remainder should be dealt, but
    it is all in the current suffix

    Therefore, this current value starts new duplicate substring ->
    we just add it: <s[i], 1>
    => we have correct parition


    - stack top value contains <a_m, value> and a_m == s[i] and s + 1 < k
    In that case, the substring, ending on s[i] is not big enough to
    remove, so we just pop <a_m, value> and push <a_m, s + 1>
    => we have correct parition

    - stack top value contains <a_m, value> and a_m == s[i] and value + 1 == k
    In that case, the substring, ending on s[i] is big enough to remove,
    so we only pop <a_m, value>
    => we have correct parition

    - stack top value contains <a_m, value> and a_m == s[i] and value + 1 > k
    This case is no-op, because any time s + 1 == k, we removed <a_m, value>
    and <a_m, value> can never be such that value + 1 == k


    - stack top value contains <a_m, value> and a_m != s[i]
    In that case, he substring, ending on a_m and the substring, starting
    on a_m are different and we can push new char: <s[i], 1>
    => we have correct parition

Therefore after the loop we have a stack with partition
(and therefore a string with subsequence) that have all
the duplicates of size k removed



**/

using namespace std;

class Solution {
public:
  string removeDuplicates(const string &s, int k) {
    stack<pair<char, int>> counts;
    string answer = "";
    for (size_t i = 0; i < s.size(); ++i) {
      if (counts.empty()) {
        counts.push({s[i], 1});
        answer += s[i];
      } else if (counts.top().first == s[i]) {
        int count = counts.top().second;
        counts.pop();
        if (count + 1 < k) {
          counts.push({s[i], count + 1});
          answer += s[i];
        } else {
          for (size_t j = 0; j < count; ++j) {
            answer.pop_back();
          }
        }
      } else {
        counts.push({s[i], 1});
        answer += s[i];
      }
    }
    return answer;
  }
};

int main() {
  Solution solution = Solution();
  cout << solution.removeDuplicates("abcd", 2) << "\n";
}