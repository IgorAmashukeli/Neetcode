#include <iostream>
#include <vector>

/**
735. Asteroid Collision

We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign
represents its direction (positive meaning right, negative meaning left). Each
asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet,
the smaller one will explode. If both are the same size, both will explode. Two
asteroids moving in the same direction will never meet.



Example 1:

Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
Example 2:

Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.
Example 3:

Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide
resulting in 10.


Constraints:

2 <= asteroids.length <= 10^4
-1000 <= asteroids[i] <= 1000
asteroids[i] != 0

idea: use new vector

for each
    if vector is empty or current found asteroid > 0 or top value of the vector
< 0:
       push_back current asteroid value else:

       while top value exists > 0:
          if |top_value| < ast_curr: pop_back
          if |top_value| == as_curr: pop_back + break and
move to next current asteroid
          if |top_value| > as_curr: pop_back + break and
move to next current asterioid
       -- here we are only if we didn't break
       push_back(current_asteroid)



Now, let's proof the algorithm is correct.
First of all, let's note that correct answer has this representation:


(*)
a_1, ..., a_s, b_1, ..., b_m
where a_i < 0
where b_j > 0
where s >= 0 (s can be 0)
where m >= 0 (m can be 0)



It is equivalent to say that all negative asteroids are to the left of the
positive asteroids.

Suppose, this is not true. This means that there exist two asteroids A and B in
result such that A < 0, B > 0 and B is to the left of A.

Let's select the most right of such A asteroids and call it C.
Let's select the most left of such B asteroids and call it D.

Then, it means that C should collide with D.
And C or D should dissapear, but they are present in the result.
This means that the result is not correct.

And therefore, it is contradiction and result always has (*) representation


Let's proof that algorithm is correct by induction.

If size of the input is 1, then result array is empty
=> we push_back a value there anyway => the result is this one
asteroid => the result is correct


Suppose for all size <= k, the algorithm works correctly.
Suppose, we are observing the (k + 1)'th asteroid.
Let's name the last added asteroid in the asteroids, found
by the algorithm as top_value


1) ast_{k + 1} > 0

this asteroid is the last one in the row.
Its direction is right.
Therefore, it never collides with any asteroid.
Therefore, all the collision happens in the first k asteroids.

Therefore, if we add to the ast_{k + 1} to the correct result,
found for the first k asteroids, we will get the correct answer.


2) ast_{k + 1} < 0 and top_value < 0

This means the answer is just

a_1, ..., a_s,

where a_j < 0

Let's proof that the result for k + 1 size is

a_1, ..., a_s, ast_{k + 1}

If top_value < 0, then it means that all right asteroids
were crashed with all the left asteroids from the first k ones.

- First of all, let's proof that all positive values shouldn't be
  added to the result.

  Suppose, there exists the positive value u that should be added to the result.
  Let's select the most right of the positive values among the positive values.
  Let's name it r.
  in the start row of asteroids that should be added to the result.
  In the result, it should be to the right of all negative values
  (a_1, ..., a_s b_1, ..., b_m representation)
  Because, r is the most right of the positive values among the ones
  that should be added to the result, it means all positive to the right of that
  asteroid will not be in the result. Let's name them in their order:
  v_1, ..., v_i
  These were destroyed by some negative asteroids. These asteroids are to the
  right of v_1, ..., v_i, some of them are between v_1, ..., v_i.
  Let's note that the last asteroid in input row among first k is negative.
  (If it is positive, then it will never be destroyed in the algorithm, working
  on first k, which is working correct by induction hypothesis, but it was
  destroyed, because it returned only negative values for the result for the
  first k values).
  These means that ast_{k + 1} goes to the left, following the negative
  asteroids, located to the most right of the input.


  Now, let's prove by induction, that v_1, ..., v_i will be destroyed not by
  ast_{k + 1},

    - For v_i. Suppose, this is not true. Let's name all the negative
    asteroids to the right of v_i as w_1, ..., w_p. ast_{k + 1} follows w_1,
    ..., w_p. This means it can only start to act somehow after w_1, ...., w_p
    acted with v_i. v_i wasn't destroyed by w_1, ..., w_p. This means v_i
    destroyed w_1, ..., w_p. But as we can see this happened before ast_{k + 1}
    started to act somehow. Therefore, if act_{k + 1} didn't move, w_1, ..., w_p
    would have been destroyed. Therefore, they wouldn't have destroyed v_i, when
    we runned the algorithm for the first k values. But these negative are the
    only negative to the right of v_i in the first k values. Therefore, v_i is
    not destroyed in the result, returned by the first k input values. By
    induction hypothesis, only negative values were returned. Contradiction. v_i
    wasn't destroyed by ast_{k + 1}


    - For v_{i - q}. By induction hypothesis, v_{i - q + 1}...v_{i} wasn't
    destroyed by ast_{k + 1} Suppose, v_{i - q} was. Let's name all the negative
    asteroids to the right of v_{i - q} that were not destroyed by the v_{i - q
    + 1}-v_i. They are y_1, ..., y_x ast_{k + 1} follows y_1, ..., y_x. All v_{i
    - q + 1}...v_{i} were not destroyed by ast_{k + 1}. This means that v_{i -
    q} can be the first destroyed by ast_{k + 1}. This means it can only start
    to act somehow after y_1, ...., y_x acted with v_{i - q}. v_{i - q} wasn't
    destroyed by y_1, ..., y_x (ast_{k + 1} destroyed them, we assumed). But
    as we can see this happened before ast_{k + 1} started to act somehow.
    Therefore, if act_{k + 1} didn't move, y_1, ..., y_x would have been
    destroyed. Therefore, they wouldn't have destroyed v_{i - q + 1}, when
    we runned the algorithm for the first k values. But these negative are the
    only negative to the right of v_{i + q + 1} that were not destroyed in the
    first k values. Therefore, v_{i + q + 1} is not destroyed in the result,
    returned by the first k input values. By induction hypothesis, only negative
    values were returned. Contradiction. v_{i + q + 1} wasn't destroyed by
    ast_{k + 1}


  This means that all of v_1...v_i were destroyed not by ast_{k + 1}.
  Moreover, let's prove that some of negative asteroids to the right of r,
  except ast_{k + 1} were not destroyed and that are bigger or equal to r by
  absolute value. Suppose, it is not true. Let's note that before reaching r,
  ast_{k + 1}, as was proved, didn't act. Suppose, this is a situation left
  after all v_1...v_i were destroyed by the negative asteroids, when we run the
  algorithm for first k values:

  e_1, ..., e_j r f_1 ... f_z and f_1...f_z are all negative,
  because all positive to the right of r were destroyed,
  because r is the most right of those, that were not destroyed.

  Then, when added ast_{k + 1}:

  e_1, ..., e_j r f_1 ... f_z ast_{k + 1},
  because, at the moment of destroying the last v_1, ast_{k + 1}
  was just moving to the left and finally reached f_z.


  Suppose, r is not destroyed by f_1, ... f_z in the latter case.
  This means that they are destroyed by r.
  This can only happen, if r > max(f_1, ..., f_z).
  But in that case r can't be destroyed in the first case.

  And the state will be:

  e_1, ..., e_j r

  But r > 0 and is the most right. It will never be destroyed.
  Therefore, output of the algorithm, runned on first k values contains
  positive asteroids. But this is not true. (We are considering such case).

  Therefore, r is destroyed by one of f_1...f_z in the latter case
  Therefore, r is destroyed. r is the most right of not destroyed.
  Contradiction. Therefore, there can't be any positive values in
  the output of the algorithm, runned on k + 1 values for this case also.



- Now after that we state that all the values in k + 1 output should be
negative. Moreover, we proved that ast_{k + 1} didn't do any action.
It never collide with positive. Now, let's prove that the set of all negative
asteroids added to the k output equals to the set of all negative asteroids
added to the k + 1 output in that case Suppose, it is not true.

    - there exists a negative asteroid g in k-th output that shouldn't be in
      k+1th output.
      This means g wasn't destroyed in k-th case, but was destroyed in
      k+1 th case. Suppose, g was destroyed by positive asteroid h. This means h
      was to the left of g.
      This is situation just before h met g:
      r_1 ... r_o h g w_1 ... w_{l + 1}.

      Let's prove, that w_{l + 1} is ast_{k + 1}.

      First of all, ast_{k + 1} should be in the asteroid row anyway.
      If there is no ast_{k + 1}, this means it was destroyed by some positive
      asteroid. But all positive asteroids (as was proved before) were destroyed
      not by ast_{k + 1}. That means, they were destroyed before ast_{k + 1}
      reached them.

      Secondly, ast_{k + 1} can never be to the right of any negative asteroid,
      because the asteroids with the same sign can never be faster if they start
      at the most outlying position.

      If ast_{k + 1} is not the w_{l + 1}, all the asteroids to the right are
      positive. Suppose one of them is M. Because at the start ast_{k + 1} was
      the most left asteroid, it means that ast_{k + 1} reached M at some point
      and none of them was destroyed. This can't be true.

      Therefore the situation is as follows:

      r_1 ... r_o h g w_1 ... ast_{k + 1}

      Now, ast_{k + 1} didn't collide with any positive and didn't do any action
      and just moved to the left.

      If ast_{k + 1} wasn't there (as with kth size input run), the situation
      would have been as follows:

      r_1 ... r_o h g w_1 ... w_{l}

      So h should have been colided with g in k-th case
      Contradiction

    - there exists a negative asteroid g in k+1-th output that shouldn't be in
      kth output. This means g wasn't destroyed in k+1-th case, but was
      destroyed in kth case. Suppose, g was destroyed by positive asteroid h.
      This means h was to the left of g. This is situation just before h met g:

      r_1... r_o h g w_1 ... w_{l}.

      Let's prove that in k+1-th case there also will be a situation:

      r_1... r_o h g w_1 ... w_{l} ast_{k + 1}

      We know that ast_{k + 1} can never cross negative asteroid.
      It also can't cross positive asteroid and can't be destroid.
      Therefore at any time the situation is as follows:

      in k-th case: l_1...l_y
      in k+1-th case: l_1...l_y ast_{k + 1}

          (By induction.
          At first this is true, because
          k+1 th input differs from k-th input only by ast_{k + 1}

          If this is true at some point t_1
          Then at point t_1 + 1

          If something happens, it happens among the first k input
          asteroids.

          Therefore, on any step, the only difference is as follows:

          in k-th case: l_1...l_y
          in k+1-th case: l_1...l_y ast_{k + 1})

      Therefore, there exists this situation:
      r_1... r_o h g w_1 ... w_{l} ast_{k + 1}

      So h should have been colided with g in k+1-th case
      Contradiction


Now, we proved that algorithm on k+1 th iteration
has no positive asteroids and the same negative asteroids
as on k-th iteration.

Therefore, a_1, ..., a_s, ast_{k + 1} is the output
and we need just to push_back the ast_{k + 1} to the output


3) ast_{k + 1} < 0 and top_value > 0

top_value > 0

This means that the output for the first k values looks like this:


a_1, ..., a_s, b_1, ..., b_m

Now, let's consider three different situations.

For all b_i with 1 <= i <= m |b_i| < |ast_{k + 1}|

There exists such b_i that |b_i| < |ast_{k + 1}|
and all b_j with j > i are such that |b_j| = |ast_{k + 1}|

There exists such b_i that |b_i| > |ast_{k + 1}|
and all b_j with j > i are such that |b_j| < |ast_{k + 1}|



Now, let's consider 3 cases of b_i, explained before

3.1) For all b_i with 1 <= i <= m |b_i| < |ast_{k + 1}|

Suppose there are also other positive values in the input row.
According to the output from the algorithm, working on k values,
they are destroyed in algorithm working with the k values by some
negative asteroids to the right of them.

Suppose, u is some positive value and u is destroyed in
algorithm, working with k values.
Suppose, it should be there in the output.
Suppose, u is the most right such value.
It is destroyed by some negative asteroid v.
Then it means that for the k + 1 values, the asteroids are ordered as
follows:

u .... v ... ast_{k + 1}

If v destroyed u, there were no positive values alpha
between u and v such that |alpha| > |v|.
This means v will destroy u, no matter what ast_{k + 1} did
(is destroyed or goes to the left till u, anyway, this u meets v before ast_{k +
1} reaches u). Therefore, u is not in the output.
Therefore, the most right of not destroyed by the algorithm,
running on k + 1 values, that were destroyed by the algorithm,
running on k values, is destroyed by the algorithm,
running on k + 1 values.

Contradiction.

There are no such values that are not destroyed by the algorithm,
running on k + 1 values.

Therefore, none of the destroyed (by the algorithm, working on the first k
values) positive values are in the output of the algorithm, working with the
first k + 1 values.


Now, let's prove that all b_i will be destroyed in the algorithm working with
the first k + 1 values. Suppose, this is not true. This means, there exists a
b_j that will not be destroyed by ane negative asteroid. Let's take the most
right of such value. Let d_1, ... d_J, ast_{k + 1} be all the negative asteroids
to the right of b_j. We assumed that any d_i will not destroy b_j. This means,
all d_1...d_J will be destroyed by b_j. There are no more negative values
between b_j and ast_{k + 1}. If there are positive asteroid P to the right
of b_i and |P| < |ast_{k + 1}|, it will be destroyed by ast_{k + 1}
Now, suppose, |P| >= |ast_{k + 1}|. Let's suppose, P is not destroyed.
Let's take the most right such asteroid.
There are no negative values in the input row between P and ast_{k + 1}.
Then P should have been remained in the output of the algorithm on k-th
value, as one among the most right positive values with no negative to the
right. This means P is among b_1...b_m. But |b_j| < ast_{k + 1} for all i
and therefore |P| < |ast_{k + 1}|. But |P| >= |ast_{k + 1}|. Contradiction.
Therefore, there are no such values between b_i and ast_{k + 1}.
Therefore, b_j and ast_{k + 1} will meet each other. Because, |b_j| < |ast_{k +
1}|, it means, b_j will be destroyed. Contradiction.

Therefore, it means all b_j will be destroyed.

Therefore, all positive values (not b_1...b_m and them also), will
be destroyed by the algorithms, that works with k + 1 values.

Now, let's assume there exists negative value g that was destroyed
in the algorithm with k values, but is not destroyed by the algorithm,
working with k + 1 values. If they were destroyed, they were destroyed by some
positive asteroid h.

This means that there exists a moment, when the asteroid row can be expressed as
follows:

r_1 ... r_o h g w_1 ... w_{l + 1}

and g was destroyed by h.

As we know, ast_{k + 1} destroyed all b_j
All other positive values were destroyed by other negative asteroids.

This means that ast_{k + 1} was never destroyed.

Moreover, we know, if ast_{k + 1} is not destroyed,
it can never be not the last asteroid
(it can't cross negative asteroids, there is no speed up,
it can't cross positive asteroid: they are destroyed by it
(or they destroyed it, but this is not true as we proved)
and at start ast_{k + 1} was the most left asteroid
)

Therefore, w_{l + 1} = ast_{k + 1}
There can be two situations
  - ast_{k + 1} didn't destroy any asteroid at that time.
  This means that all the collision done in the first k
  values are equal to the collision doe in the algorithm,
  runned on the first k+1 values.
  This means that g was destroyed by h in the algorithm,
  runned on the first k + 1 values. Contradiction.

  - ast_{k + 1} destroyed some asteroids at that time.
  If ast_{k + 1} destroyed h, because h is to the
  right of ast_{k + 1} and h can never cross g,
  it means that h destroyed g.
  But in the algorithm, runned first values,
  g destroyed h => |g| >= |h| and h destroyed g =>
  |h| >= |g| => |g| = |h|. But in that case
  h was also destroyed in the algorithm, runned
  on the first k + 1 values. Contradiction.

there doesn't exist negative value g that was destroyed
in the algorithm with k values, but is not destroyed by the algorithm,
working with k + 1 values.

Now, suppose, there exists negative value g that was destroyed
in the algorithm with k + 1 values, but is not destroyed by the algorithm,
working with k values (one of a_1...a_s was destroyed by the algorithm,
working with k + 1 values).
In algorithm, working with k + 1 values, it was destroyed by some
negative value h

This is a moment, when that happened.

Before, we proved that all positive values are destroyed in this
case.
Part of them (b_j) are destroyed by ast_{k + 1}, when |b_j| < |ast_{k + 1}|
for all 1 <= j <= m
Part of them are destroyed by other negative values.
Anyway, none of the positive values destroyed ast_{k + 1}

Let's say that the moment, when g should be destroyed by h
in algorithm, runned with k + 1 values can be represented as such:

r_1 ... r_o h g w_1 ... w_l w_{l + 1}

ast_{k + 1} should be among that values.
(ast_{k + 1} can't cross negative or positive asteroids)
It can't be not the last one. It is the last one.


r_1 ... r_o h g w_1 ... w_l ast_{k + 1}

If there are no asteroids destroyed by ast_{k + 1} to that moment,
it means that all the operations are the same as with the
algorithm, runned with k values.
Therefore, g is also destroyed by h.

If ast_{k + 1} destroyed some of the positive asteroids,
it didn't destroy h.

This means all operations, that happened
in the r_1...r_o h g part of the row will
be the same, if runned with k values.

Therefore, g is also destroyed by h with k values.


Finaly, all negative values that are destroyed in algorithm,
runned on k values are destroyed by algorithm, runned on
k + 1 values. And all negative values that are destroyed in algorithm,
runned on k + 1 values are destroyed by algorithm, runned on
k values. And all positives are destroyed.

Therefore, the result indeed should be a_1...a_s ast_{k + 1}

So, in that case, we need to pop all positive values an push the current
asteroid



3.2)

There exists such b_i that |b_i| = |ast_{k + 1}|
and all b_j with j > i are such that |b_j| < |ast_{k + 1}|


The result should be a_1 ... a_s b_1 ... b_{i - 1}

Let's prove that all other positive values, except b_1...b_m
will be destroyed.

Suppose there are also other positive values in the input row.
According to the output from the algorithm, working on k values,
they are destroyed in algorithm working with the k values by some
negative asteroids to the right of them.

Suppose, this is not true.

Suppose, u is some positive value and u is destroyed in
algorithm, working with k values.
Suppose, it should be there in the output.
Suppose, u is the most right such value.
It is destroyed by some negative asteroid v.
Then it means that for the k + 1 values, the asteroids are ordered as
follows before ast_{k + 1} destroyed:

u .... v ... ast_{k + 1}

If v destroyed u, there were no positive values alpha
between u and v such that |alpha| > |v|.
This means v will destroy u, no matter what ast_{k + 1} did
(is destroyed or goes to the left till u, anyway, this u meets v before ast_{k +
1} reaches u). Therefore, u is not in the output.
Therefore, the most right of not destroyed by the algorithm,
running on k + 1 values, that were destroyed by the algorithm,
running on k values, is destroyed by the algorithm,
running on k + 1 values.


Therefore, all other positive values, except b_1...b_m
will be destroyed.


Now, let's prove b_i...b_m will be destroyed working with
the first k + 1 values. Suppose, this is not true. This means, there exists a
b_j j > i that will not be destroyed by ane negative asteroid. Let's take the
most right of such value. Let d_1, ... d_J, ast_{k + 1} be all the negative
asteroids to the right of b_j. We assumed that any d_i will not destroy b_j.
This means, all d_1...d_J will be destroyed by b_j. There are no more negative
values between b_j and ast_{k + 1}. If there are positive asteroid P to the
right of b_j and |P| < |ast_{k + 1}|, it will be destroyed by ast_{k + 1} Now,
suppose, |P| >= |ast_{k + 1}|. Let's suppose, P is not destroyed. Let's take the
most right such asteroid. There are no negative values in the input row between
P and ast_{k + 1}. Then P should have been remained in the output of the
algorithm on k-th value, as one among the most right positive values with no
negative to the right. This means P is among b_i...b_m. But |b_i| <= ast_{k + 1}
for all i j <= i <= m (|b_i| = |ast_{k + 1}| and for all i_2 > i: |b_{i_2}| <
|ast_{k + 1}| ) and therefore |P| < |ast_{k + 1}|. But |P| >= |ast_{k + 1}|.
Contradiction. Therefore, there are no such values between b_j and ast_{k + 1}.
Therefore, b_j and ast_{k + 1} will meet each other. Because, |b_j| < |ast_{k +
1}|, it means, b_j will be destroyed. Contradiction.


This means all b_i...b_m are destroyed.


Let's prove all b_1...b_{i - 1} will not be destroyed by the algorithm,
working with k + 1 values.
Suppose, one of them, let's take the most right one, say b_u,
is destroyed. Then there exists such negative asteroid n_1 that destroys
b_u.

But in that case it means |n_1| > |b_u|.
But that means, when algorithm is runned on k + 1 values the order was as such:

....b_u n_1...

There can be two situations:

ast_{k + 1} didn't nothing til that moment.
In that case, the situation is similiar to the case, when algorithm
is runned on first k values.

In that case b_u is destroyed also, but it wasn't destroyed in the algorithm.


ast_{k + 1} destroyed other values.
In that case, there can be two more subsituations.

In the first n_1 != ast_{k + 1}

In that case, because ast_{k + 1} can never cross n_1,

all the operations in values ...b_u n_1 in the algorithm, runned on the first
k values, will be the same. And therefore, n_1 will destroy b_u,
but it wasn't destroyed in the algorithm, runned on the first k values.

In the second case n_1 = ast_{k + 1}

But in that case, there are two subsituations again

u = i - 1. We know, that |b_u| < |n_1|. Then |b_{i - 1}| < |ast_{k + 1}|.
But we know, that |b_{i - 1}| = |ast_{k + 1}|

u != i. Then u < i.
But because, b_u is the most right, it means, b_i is not destroyed.
But in that case ast_{k + 1} can't cross b_i and destroy b_u.


Therefore, such b_u doesn't exist.


Therefore, for k + 1 values:

all positive values, except b_1...b_m will be destroyed
Moreover, all b_i...b_m will be destroyed and
all b_1...b_{i - 1} are not destroyed.


Let's prove that the negative values in the resut of the algorithm,
runned on the first k + 1 values are the same as values in the result of
the algorithm, runned on the first k values.

Suppose, this is not true.

Suppose there exists a negative asterod h that is destroyed, when runned
on k values by some positive value g, but not with k + 1.

Therefore, there existed such moment, when asteroid
row can be expresses as follows

r_1....r_c g h w_1...w_{l}

At the start it was as follows:

i_1...i_N g ... h o_1 ... o_M

Now let's consider, how this happened, when algorithm was runned on
first k + 1 values.

At the start it was as follows:

i_1...i_N g ... h o_1 ... o_M ast_{k + 1}

Then there are three perroids:

-before ast_{k + 1}
started to destroy any asteroids

-after ast_{k + 1}
started to destroy asteroids,
but before it was destroyed.

- after ast_{k + 1}
was destroyed

In the first case, ast_{k + 1} didn't act, therefore
it was the same as with k values.

When ast_{k + 1} started to destroy positive values,
the order was the same, but g and h were there in the row

g...h...ast_{k + 1}


Therefore, everything to the left of h was the same, as runned on k values.

When ast_{k + 1} was destroyed, all everything is the same
to the left of h, as runned on k values at the start of such period,
and any other next operation is the same
(all negative to the right of h can't speed up and cross h, all positive
to the right are shifting away of h and between the first asteroid in the row
and h nothing changed, to the way it was, when runned on k values,
because ast_{k + 1} destroyed positive asteroids only to the right of h)


Therefore, when h was shifting by g (in any of this periods),
it was the same as when algorithm was working with first k values.
Therefore, g destroyed h. Contradiction.


Suppose there exists a negative asterod h that is destroyed, when runned
on k + 1 values by some positive value g, but not with k.

So the asteroid row at that moment can be expressed as follows:

r_1....r_c g h w_1...w_{l} without ast_{k + 1}

or as follows

r_1....r_c g h w_1...w_{l} ast_{k + 1}

At the start with k values the order was as follows:

....g...h...

But anyway, every movement between the first asteroid and h
was the same with the situation, when algorithm worked with k values.
(because all positive values, that were not destroyed, but were destroyed,
when algorithm worked with k + 1 values are to the right of h)

Therefore, h was destroyed by g.


Therefore, the result is correct:

a_1 ... a_s b_1 ... b_{i - 1}


3.3)


There exists such b_i that |b_i| > |ast_{k + 1}|
and all b_j with j > i are such that |b_j| < |ast_{k + 1}|


The result should be a_1 ... a_s b_1 ... b_{i}

Let's prove that all other positive values, except b_1...b_m
will be destroyed.

Suppose there are also other positive values in the input row.
According to the output from the algorithm, working on k values,
they are destroyed in algorithm working with the k values by some
negative asteroids to the right of them.

Suppose, this is not true.

Suppose, u is some positive value and u is destroyed in
algorithm, working with k values.
Suppose, it should be there in the output.
Suppose, u is the most right such value.
It is destroyed by some negative asteroid v.
Then it means that for the k + 1 values, the asteroids are ordered as
follows before ast_{k + 1} destroyed:

u .... v ... ast_{k + 1}

If v destroyed u, there were no positive values alpha
between u and v such that |alpha| > |v|.
This means v will destroy u, no matter what ast_{k + 1} did
(is destroyed or goes to the left till u, anyway, this u meets v before ast_{k +
1} reaches u). Therefore, u is not in the output.
Therefore, the most right of not destroyed by the algorithm,
running on k + 1 values, that were destroyed by the algorithm,
running on k values, is destroyed by the algorithm,
running on k + 1 values.


Therefore, all other positive values, except b_1...b_m
will be destroyed.


Now, let's prove b_{i + 1}...b_m will be destroyed working with
the first k + 1 values. Suppose, this is not true. This means, there exists a
b_j j > i that will not be destroyed by ane negative asteroid. Let's take the
most right of such value. Let d_1, ... d_J, ast_{k + 1} be all the negative
asteroids to the right of b_j. We assumed that any d_i will not destroy b_j.
This means, all d_1...d_J will be destroyed by b_j. There are no more negative
values between b_j and ast_{k + 1}. If there are positive asteroid P to the
right of b_j and |P| < |ast_{k + 1}|, it will be destroyed by ast_{k + 1} Now,
suppose, |P| >= |ast_{k + 1}|. Let's suppose, P is not destroyed. Let's take the
most right such asteroid. There are no negative values in the input row between
P and ast_{k + 1}. Then P should have been remained in the output of the
algorithm on k-th value, as one among the most right positive values with no
negative to the right. This means P is among b_{i + 1}...b_m. But |b_{i + 1}| <
ast_{k + 1} for all i j <= i <= m and therefore |P| < |ast_{k + 1}|. But |P| >=
|ast_{k + 1}|. Contradiction. Therefore, there are no such values between b_j
and ast_{k + 1}. Therefore, b_j and ast_{k + 1} will meet each other. Because,
|b_j| < |ast_{k + 1}|, it means, b_j will be destroyed. Contradiction.


This means all b_{i + 1}...b_m are destroyed.


Let's prove all b_1...b_{i} will not be destroyed by the algorithm,
working with k + 1 values.
Suppose, one of them, let's take the most right one, say b_u,
is destroyed. Then there exists such negative asteroid n_1 that destroys
b_u.

But in that case it means |n_1| > |b_u|.
But that means, when algorithm is runned on k + 1 values the order was as such:

....b_u n_1...

There can be two situations:

ast_{k + 1} didn't nothing til that moment.
In that case, the situation is similiar to the case, when algorithm
is runned on first k values.

In that case b_u is destroyed also, but it wasn't destroyed in the algorithm,
when runned on k values.


ast_{k + 1} destroyed other values.
In that case, there can be two more subsituations.

In the first n_1 != ast_{k + 1}

In that case, because ast_{k + 1} can never cross n_1,

all the operations in values ...b_u n_1 in the algorithm, runned on the first
k values, will be the same. And therefore, n_1 will destroy b_u,
but it wasn't destroyed in the algorithm, runned on the first k values.

In the second case n_1 = ast_{k + 1}

But in that case, there are two subsituations again

u = i. We know, that |b_u| < |n_1|. Then |b_i| < |ast_{k + 1}|.
But we know, that |b_i| > |ast_{k + 1}|

u != i. Then u < i.
But because, b_u is the most right, it means, b_i is not destroyed.
But in that case ast_{k + 1} can't cross b_i and destroy b_u.


Therefore, such b_u doesn't exist.


Therefore, for k + 1 values:

all positive values, except b_1...b_m will be destroyed
Moreover, all b_{i+1}...b_m will be destroyed and
all b_1...b_{i} are not destroyed.


Let's prove that the negative values in the resut of the algorithm,
runned on the first k + 1 values are the same as values in the result of
the algorithm, runned on the first k values.

Suppose, this is not true.

Suppose there exists a negative asterod h that is destroyed, when runned
on k values by some positive value g, but not with k + 1.

Therefore, there existed such moment, when asteroid
row can be expresses as follows

r_1....r_c g h w_1...w_{l}

At the start it was as follows:

i_1...i_N g ... h o_1 ... o_M

Now let's consider, how this happened, when algorithm was runned on
first k + 1 values.

At the start it was as follows:

i_1...i_N g ... h o_1 ... o_M ast_{k + 1}

Then there are three perroids:

-before ast_{k + 1}
started to destroy any asteroids

-after ast_{k + 1}
started to destroy asteroids,
but before it was destroyed.

- after ast_{k + 1}
was destroyed

In the first case, ast_{k + 1} didn't act, therefore
it was the same as with k values.

When ast_{k + 1} started to destroy positive values,
the order was the same, but g and h were there in the row

g...h...ast_{k + 1}


Therefore, everything to the left of h was the same, as runned on k values.

When ast_{k + 1} was destroyed, all everything is the same
to the left of h, as runned on k values at the start of such period,
and any other next operation is the same
(all negative to the right of h can't speed up and cross h, all positive
to the right are shifting away of h and between the first asteroid in the row
and h, nothing changed to the way it was, when runned on k values,
because ast_{k + 1} destroyed positive asteroids only to the right of h)


Therefore, when h was shifting by g (in any of this periods),
it was the same as when algorithm was working with first k values.
Therefore, g destroyed h. Contradiction.


Suppose there exists a negative asterod h that is destroyed, when runned
on k + 1 values by some positive value g, but not with k.

So the asteroid row at that moment can be expressed as follows:

r_1....r_c g h w_1...w_{l} without ast_{k + 1}

or as follows

r_1....r_c g h w_1...w_{l} ast_{k + 1}

At the start with k values the order was as follows:

....g...h...

But anyway, every movement between the first asteroid and h
was the same with the situation, when algorithm worked with k values.
(because all positive values, that were not destroyed, but were destroyed,
when algorithm worked with k + 1 values are to the right of h)

Therefore, h was destroyed by g.


Therefore, the result is correct:

a_1 ... a_s b_1 ... b_{i - 1}




















Finally, in all three cases we considered
(from line 103 til this line)
the algorithm is working correct

Therefore, the algorithm is correct


Time complexity.

On any iteration, we either:

- push something to the result (the first branch)
- push something to the result (we didn't break from while loop)
- pop something from the result.

But any value from input of size n was pushed only 1 time.
Therefore, all the pop operations were done no more than n times.

Finally, all the push and pop operations were done no more
than 2n times.

Therefore, the algorithm works in O(n) time

**/

using namespace std;

class Solution {
private:
  bool same_signs(int ast1, int ast2) {
    if (ast1 < 0 && ast2 < 0) {
      return true;
    } else if (ast2 > 0 && ast2 > 0) {
      return true;
    } else {
      return false;
    }
  }

public:
  vector<int> asteroidCollision(vector<int> &asteroids) {
    vector<int> row;
    for (auto asteroid : asteroids) {
      if (row.empty() || asteroid > 0 || row.back() < 0) {
        row.push_back(asteroid);
      } else {
        bool push_flag = true;
        while (!row.empty() && row.back() > 0) {
          if (row.back() < -asteroid) {
            row.pop_back();
          } else if (row.back() == -asteroid) {
            row.pop_back();
            push_flag = false;
            break;
          } else {
            push_flag = false;
            break;
          }
        }
        if (push_flag) {
          row.push_back(asteroid);
        }
      }
    }

    return row;
  }
};

int main() {
  vector<int> input = {-2, 1, 1, -1};
  Solution solution = Solution();
  vector<int> output = solution.asteroidCollision(input);
  for (int value : output) {
    cout << value << " ";
  }
  cout << "\n";
}
