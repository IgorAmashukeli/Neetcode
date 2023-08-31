/**There are n dominoes in a line, and we place each domino vertically upright.
In the beginning, we simultaneously push some of the dominoes either to the left
or to the right.

After each second, each domino that is falling to the left pushes the adjacent
domino on the left. Similarly, the dominoes falling to the right push their
adjacent dominoes standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays
still due to the balance of the forces.

For the purposes of this question, we will consider that a falling domino
expends no additional force to a falling or already fallen domino.

You are given a string dominoes representing the initial state where:

dominoes[i] = 'L', if the ith domino has been pushed to the left,
dominoes[i] = 'R', if the ith domino has been pushed to the right, and
dominoes[i] = '.', if the ith domino has not been pushed.
Return a string representing the final state.



Example 1:

Input: dominoes = "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.
Example 2:


Input: dominoes = ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."


Constraints:

n == dominoes.length
1 <= n <= 10^5
dominoes[i] is either 'L', 'R', or '.'.

idea: straightforward making dominoes, when found L -> go backwards
time: O(n)
space: O(1)

**/

#include <cstddef>
#include <string>

using namespace std;

// go backwards to make L
void makeL(string &answer, char prevPush, size_t prevPushIndex,
           size_t curPushIndex) {
  // previous symbol is L or . : everything before L should fall down to the
  // left
  if (prevPush == 'L' || prevPush == '.') {
    for (size_t j = prevPushIndex; j <= curPushIndex; ++j) {
      answer[j] = 'L';
    }

    // previous symbol is R: only the right half should fall down to the left
  } else {
    size_t mid = prevPushIndex + (curPushIndex - prevPushIndex) / 2;
    for (size_t j = mid + 1; j <= curPushIndex; ++j) {
      answer[j] = 'L';
    }

    // (curPushIndex - prevPushIndex) % 2 == 0 <=>
    // (size between prevPush and curPush is odd)
    // => exists balanced domino, put it there
    if ((curPushIndex - prevPushIndex) % 2 == 0) {
      answer[mid] = '.';
    }
  }
}

string pushDominoes(const string &dominoes) {
  // answer variable
  string answer = dominoes;

  // previous symbol to push
  char prevPush = '.';

  // current symbol to push
  char curPush = '.';

  // index of previous push symbol
  size_t prevPushIndex = 0;

  // index of current push symbol
  size_t curPushIndex = 0;

  // iterate through dominoes
  for (size_t i = 0; i < dominoes.size(); ++i) {
    // found "->""
    // update all states
    if (dominoes[i] == 'R') {

      // save previous
      prevPush = curPush;
      prevPushIndex = curPushIndex;

      // assign current
      curPush = 'R';
      curPushIndex = i;

      // found "<-"
      // update all states
    } else if (dominoes[i] == 'L') {

      // save previous
      prevPush = curPush;
      prevPushIndex = curPushIndex;

      // assign current
      curPush = 'L';
      curPushIndex = i;

      // found "."
      // update all states only if current push was L
      // (otherwise do nothing)
    } else if (dominoes[i] == '.') {
      if (curPush == 'L') {
        prevPush = curPush;
        prevPushIndex = curPushIndex;

        // assign current
        curPush = '.';
        curPushIndex = i;
      }
      // else curPush == 'R' or '.'
      // if curPush == '.' => there is nothing to change
      // if curPush == 'R' => we don't need to change also
    }

    // if curPush was "->" or ".", start making curPush
    if (curPush == 'R' || curPush == '.') {
      answer[i] = curPush;

      // if found "<-", start making L in prevous chunck
    } else if (curPush == 'L') {
      makeL(answer, prevPush, prevPushIndex, curPushIndex);
    }
  }

  // return answer
  return answer;
}