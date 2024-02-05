#include <algorithm>
#include <iostream>
#include <vector>

/**
You are given an array people where people[i] is the weight of the ith person,
and an infinite number of boats where each boat can carry a maximum weight of
limit. Each boat carries at most two people at the same time, provided the sum
of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.



Example 1:

Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
Example 2:

Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
Example 3:

Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)


Constraints:

1 <= people.length <= 5 * 10^4
1 <= people[i] <= limit <= 3 * 10^4


idea:

sort array and try to pair element
there are two pointers: left and right
and two values cosidered left and right

(if size is 1, the answer is obvious: 1 (
    single human on a boat is ok due to condition and there are no two elements)
if size > 1 and first two elements together can't form a pair,
then no one can make a pair (it will have more weight),
and this one element can float as a single))



if left_value + right_value > limit
we skip it and it will be single
we shift right pointer
we increment counter


if left_value + right_value <= limit
we pair them in a boat
we shift left and right pointer
we increment counter

after l = r was considered, we leave

and return counter

Let's proof this will return the minimum number of boats
Let's suppose it is not true
That means there exist another way to ship people with less number of boats

Suppose from the algorithm
we had a_1, a_2, a_3, a_4, ..., a_i-3, a_i-2, a_i-1, a_i, a_i+1, a_i+2, ...,
a_n-3, a_n-2, a_n-1, a_n is the sorted array Now let's consider that S is the
number of singles and P is the number of pairs, found by this algorithm

Now let's consider that there is another answer {S*, P*}, which is the best one

That means that S* + P* < S + P

If S* >= S and P* >= P, then S* + P* >= S + P, which is contradiction
=> S* < S or P* < P

Moreover, S* + 2 * P* = S + 2 * P,
because there are people.size() people in the array

If S = S* + 2k => S* + 2P* = S* + 2k + 2P
=> 2P* - 2P = 2k => P* - P = k

If P = P* + t => S* + 2 * P* = S + 2 * (P* + t)
=> S* - S = 2t

Therefore there can be 2 cases:

1) S - S* = 2k; P* - P = k
2) P - P* = t; S* - S = 2t

In the first case S + P - (S* + P*) = S - S* - (P* - P) = 2k - k = k
In the second case S + P - (S* + P*) = P - P* - (S* - S) = t - 2t = -t < 0
But S + P > S* + P*

So there can be only the first case
In the first case, as we can see, there are more pairs and less singles

In the output we have P pairs
In the answer we have P* pairs
Let's take min element in each of P* pairs
and create a multiset of these elements
(they are on their positions)

It is sequence b

Let's take max element in each of P* pairs
and create a miltiset of these elements
(they are on their positions)

It is sequence c

we know that
b_1 + c_1 <= k
b_2 + c_2 <= k
...
b_P* + c_P* <= k


Now let's proof that if we sort those elements,
d_1, ..., d_P*, d_{P*+1}, ...., d_2P*,

d_1 + d_2P* <= k
d_2 + d_{2P*-1} <= k
d_3 + d_{2P*-2} <= k
...
d_P* + d_{P*+1} <= k

Suppose it is not true
Let's find the last inequality that failed:

d_{P* - i} + d_{P* + i + 1} > k
(there is + 1, because if you look to the inequalities,
you will find that there is 1 2P* - 0; 2 2p* - 1 and so on)

that means that
d_{P* + i} can be pairs (may be) with
all smaller elements: d_1, ..., d_{P* - i - 1}
that means that

But all bigger elements than (d_{P* + i + 1}) can't be pairs with
d_{P* - i} two

How many elements we mentioned that can't have pairs only among
d_1, ..., d_{P* - i - 1}?

We mentioned d_{P* + i + 1}, ... d_{2P*}
That is P* - i elements

There is no injection from set with P* - i to set of P* - i - 1 elements

Therefore there is no last inequality that failed

Therefore we found solution such that:

d_1 + d_2P* <= k
d_2 + d_{2P*-1} <= k
d_3 + d_{2P*-2} <= k
...
d_P* + d_{P*+1} <= k



Now let's observe that if we decrease (shift to the left
in initial array a) all d_1, ..., d_P*
we again will get correct solution
(cause all inequalities will be again true)

That means, that there is solution:

a_1 + d_2P* <= k
a_2 + d_{2P* - 1} <= k
a_3 + d_{2P* - 2} <= k
...
a_P* + d_{P*+1} <= k



Now we observe that
a_P* <= d_{P* + 1}, cause we decreased

d_P* <= d_{P*+1}, because d is sorted

That means that a_P* is less than d_{P*+1}

Now, let's increase (shift to the right) d_2P* til it is possible
(next element in array can't be included to the boat)

Let's call this value a_last_1

Now, let's increase (until) d_{2P*-1} til it is possible, but before a_{last_1}
We know that d_{2P* - 1} before (in array) d_2P*
and d_2P* before a_{last_1}
=> d_{2P* - 1} before (in array) a_{last_1} => so at least one such value
(d_{2P*-1} exists)

Let's call this value a_{last_2}

...

Let's do this procedure for all a

=>

we will get


a_1 + a_{last_1} <= k
a_2 + a_{last_2} <= k
a_3 + a_{last_3} <= k
...
a_P* + d_{last_P*} <= k


We know, P < P*

Let's take P first values:

a_1 + a_{last_1} <= k
...
a_P + a_{last_2} <= k

Let's observe that in algorithm output we have a_1, ..., a_P
in pairs (we put in pairs first values)
and we found maximum for each pair just by procedure above
(find the first possible(satisfying inequality a_i + a_{last_i})
 such value a_{last_i} that it is before than a_{last_{i - 1}})

That means our algorithm found all those first pairs

P* > P => P* >= P + 1
=> there exists pair with number (P + 1) in correct answer
a_{P + 1} is value after a_{P}

a_{last_{P+1}} is before a_{last_P} by procedure

Our algorithm reaches a_{last_{P+1}} and could find
such a_{last_{P+1}} searching starting from a_{last_P},
because it didn't give it in output (only first P pairs)

But according to the procedure, such value exists.

CONTRADICTION

Therefore P* can't be less than P

S* can't be less than S (we proved that before,
otherwise, P + S < P* + S*)

=> P* + S* can't be less than P + S

=> There doesn't exist smaller solution

**/

using namespace std;

int numRescueBoats(vector<int> &people, int limit) {
  // sort the array
  sort(people.begin(), people.end());

  int l = 0;
  int r = people.size() - 1;
  int count = 0;

  // all people are singles
  if (people.size() == 1 || people[0] + people[1] > limit) {
    return people.size();
  }

  // if r is less that every pair and single found
  while (l <= r) {

    // if l == r =>
    // people[l] <= limit by conditions
    // people[l] + people[r] = 2people[l] can be <= limit and > limit
    // in both cases l becomes bigger than r and count++
    // => everything is fines

    // if small and big can't form a pair, we take big as a single
    if (people[l] + people[r] > limit) {
      --r;
      ++count;

      // if small and big can form a pair, we take them as a pair
    } else {
      ++l;
      --r;
      ++count;
    }
  }

  return count;
}

int main() {

  vector<int> people = {3, 2, 2, 1};
  int limit = 3;
  cout << numRescueBoats(people, limit) << "\n";
}