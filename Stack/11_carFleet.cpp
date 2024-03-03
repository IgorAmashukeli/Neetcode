#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

/**
853. Car Fleet

There are n cars going to the same destination along a one-lane road. The
destination is target miles away.

You are given two integer array position and speed, both of length n, where
position[i] is the position of the ith car and speed[i] is the speed of the ith
car (in miles per hour).

A car can never pass another car ahead of it, but it can catch up to it and
drive bumper to bumper at the same speed. The faster car will slow down to match
the slower car's speed. The distance between these two cars is ignored (i.e.,
they are assumed to have the same position).

A car fleet is some non-empty set of cars driving at the same position and same
speed. Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point, it will still
be considered as one car fleet.

Return the number of car fleets that will arrive at the destination.



Example 1:

Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each
other at 12. The car starting at 0 does not catch up to any other car, so it is
a fleet by itself. The cars starting at 5 (speed 1) and 3 (speed 3) become a
fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches
target. Note that no other cars meet these fleets before the destination, so the
answer is 3. Example 2:

Input: target = 10, position = [3], speed = [3]
Output: 1
Explanation: There is only one car, hence there is only one fleet.
Example 3:

Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Explanation:
The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet, meeting each
other at 4. The fleet moves at speed 2. Then, the fleet (speed 2) and the car
starting at 4 (speed 1) become one fleet, meeting each other at 6. The fleet
moves at speed 1 until it reaches target.


Constraints:

n == position.length == speed.length
1 <= n <= 10^5
0 < target <= 10^6
0 <= position[i] < target
All the values of position are unique.
0 < speed[i] <= 10^6


idea: sort by position, scan from back and
use a stack:
if new time is higer than one of the previous group,
add the index to the stack, otherwise don't add


Proof of correctness.

Suppose, we have two input arrays (after sorting)

s_1, ..., s_k
v_1, ..., v_k


Let's proof by induction that for all iteration i

if the input array is:

s_i, ..., s_k
v_i, ..., v_k

then stack has the correct number of fleets
and each of the fleets has the index u of the speed
at which it came to the target, and u-th car is in this fleet


Base of induction:
s_k
v_k

the stack is empty and we just added k.
One car will come to the target with speed v_k
and k-th car is in the only fleet
and the number of fleets is 1


Step of induction:

Suppose, we found the correct answer for
all j > i

Now for j = i:

s_i, ..., s_k
v_i, ..., v_k

As we know, the stack contains all the
indices of cars for which the speed of
that car is the speed at which this car
comes to the target.

This means, that the top of the stack
contains the index of the car with which speed it
comes to the target.

Now, suppose this speed is v_u and it's start position
is s_u.
let's denote t_u = (target - s_u) / v_u.
We know, that v_u is the speed at which fleet comes to the target.
v_u is the speed of the u-th car at the start.
Therefore, u-th car never changed it's speed.
Therefore, the time, when u-th car and the fleet comes to the target
can be calculated as (target - s_u) / v_u.
Because u-th car is in the next fleet and t_u car comes
to the target at time t_u, this means that all the fleet comes
at target at time t_u.


Let's denote t_i' as (target - s_i) / v_i

Let's denote t_i as the time, when i-th car comes to the target
Suppose, y_1, ..., y_k are the positions at which i-th car
slows down.
Suppose, v_i_1, ..., v_i_k are the speeds that changes at that position,
where for all j 1 <= j <= k v_i_j < v_i
If k = 0 => the car never slow downs and t_i = t_i'

If k > 0:
if k = 1 => t_i = (y_1 - s_i) / v_i + (target - y_k)/ v_i_k

Let's denote 0 as (\sum_{j = 1}^{0} (y_{j + 1} - y_j)),
because there are no terms in this sum => because k = 1 => k - 1 = 0
=> 0 can be denoted as (\sum_{j = 1}^{k - 1} (y_{j + 1} - y_j))

if k = 1 => t_i = (y_1 - s_i) / v_i + (\sum_{j = 1}^{k - 1} (y_{j + 1} - y_j)) /
v_i_j + (target - y_k)/ v_i_k

If k > 1 => t_i = t_i = (y_1 - s_i) / v_i + (\sum_{j = 1}^{k - 1} (y_{j + 1} -
y_j)) / v_i_j + (target - y_k)/ v_i_k also

Therefore, if k >= 1:

t_i = (y_1 - s_i) / v_i + (\sum_{j = 1}^{k - 1} (y_{j + 1} - y_j)) / v_i_j +
(target - y_k)/ v_i_k


If k >= 1:

Because, v_i_j < v_i: t_i > (y_1 - s_i) / v_i +
(\sum_{j = 1}^{k - 1} (y_{j + 1} - y_j)) / v_i +
+ (target - y_k)/ v_i = (target -
s_i)/ v_i = t_i


Therefore, if k >= 1 t_i > t_i'
If k = 0, then t_i = t_i'

Therefore, in general: t_i >= t_i'


All the cars at the start are at different positions.
Therefore, if one car a reaches its first car b at point s in time t
it means that (s - s_a) = t * v_a and (s - s_b) = t * v_b_m,
where v_b_m is some slowdown speed of car b
Then (s - s_a) = (s - s_b) / v_b_m * v_a
s_a < s_b => (s - s_b) < (s - s_a)
Therefore, (s - s_b) < (s - s_b) / v_b_m * v_a
Therefore, v_b_m < v_a
Therefore, car a will slow down its speed, when reaches a car



-- if t_i' > t_u
    t_i >= t_i' > t_u.
    Therefore t_i > t_u and this means that i-th car will come
    to the fleet at time t_i, but all the fleet will
    come at target at time t_u.
    This means that the i-th car is not in the fleet.
    Therefore, i-th car is another fleet.
    Therefore, we push i-th car to the stack.
    Now, there is correct number of fleets and i-th car speed
    is the speed at which this car comes to the target and i-th car
    is in this fleet.

-- if t_i' <= t_u
    Suppose, i-th car comes to the finish before t_u car.
    In that case there exists two cars j and j + 1 such that j car
    passes j+1 car
    (suppose, this is not true, in that case i is always before i+1,
    i+1 is always before i+2, ..., u-1 is always before u and therefore,
    i is always before u and i comes to the finish before u, and we assumed
    that u comes to the finish before i, contradiction).
    But that means that there exists a car that passes the car ahead of it.
    But this can never happen. Contradiction.

    Therefore, i-th car comes to the finish after or at the same time as t_u
    car. t_i >= t_u

    We also now that t_i >= t_i'

    Suppose, t_i = t_i'
    In that case k = 0
    That means that i-th car will never slow down its speed
    That means that i-th car will never meet a car
    (everytime it meets the car, it slows down the speed,
    it was proven before)
    Therefore, it means that i-th car will not meet i+1 car
    Therefore, it means that i-th car will not meet i+1 car at target
    That means that i-th car will come to the finish before i+1 car
    That means that i-th car will come to the finish before u-th car
    (u-th car comes at the same time i+1-th car comes to the finish by
    induction, because we assumed that u-th car is in the next fleet) Therefore,
    t_i > t_u Therefore, because t_i = t_i' => t_i' > t_u

    But in our case: t_i' <= t_u. Contradiction


    Therefore, t_i > t_i'. That means that k >= 1
    That means that i-th car meets i+1 car
    That means that i-th car comes to the finish with i+1 car
    That means that i-th car comes to the finish with the next fleet
    That means that the i-th car is in the next fleet.
    Therefore, we don't push i-th car to the stack.
    And the correct number of fleets remains
    And the u-th car speed is the speed at which u-th car comes to the target
    and u-th car is in the fleet with i+1 and i-th car (current fleet)

Therefore, by proof by induction,

for i = k:

s_1, ..., s_k
v_1, ..., v_k

stack has the correct number of fleets
and each of the fleets has the index u of the speed
at which it came to the target, and u-th car is in this fleet

=> stack size is the answer and we return it

**/

using namespace std;

class Solution {
private:
  void sort_position(vector<int> &a, vector<int> &b) {
    vector<pair<size_t, int>> b_ind(b.size());
    for (size_t i = 0; i < b_ind.size(); ++i) {
      b_ind[i] = {i, b[i]};
    }

    sort(b_ind.begin(), b_ind.end(), [&a](const auto &left, const auto &right) {
      return a[left.first] < a[right.first];
    });

    for (size_t i = 0; i < b_ind.size(); ++i) {
      b[i] = b_ind[i].second;
    }

    sort(a.begin(), a.end());
  }

public:
  int carFleet(int target, vector<int> &position, vector<int> &speed) {
    // sort position and speed, according to position
    sort_position(position, speed);
    stack<int> fleets = {};
    for (size_t i = 0; i < position.size(); ++i) {
      size_t j = position.size() - i - 1;

      if (fleets.empty()) {
        fleets.push(j);
      } else {
        size_t previous_index = fleets.top();
        int64_t dist_prev_speed_cur =
            static_cast<int64_t>((target - position[previous_index])) *
            static_cast<int64_t>(speed[j]);
        int64_t dist_cur_speed_prev =
            static_cast<int64_t>((target - position[j])) *
            static_cast<int64_t>(speed[previous_index]);

        if (dist_cur_speed_prev > dist_prev_speed_cur) {
          // equivalent to time_cur > time_prev in terms of proportion
          // it is better to use multiplication than convert to float
          // and do division for the time
          fleets.push(j);
        }
      }
    }
    return static_cast<int>(fleets.size());
  }
};

int main() {
  Solution solution = Solution();
  int target = 10;
  vector<int> position = {6, 8};
  vector<int> speed = {3, 2};
  int count = solution.carFleet(target, position, speed);
  cout << count << "\n";
}