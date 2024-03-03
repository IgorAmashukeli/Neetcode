#include <string>
#include <vector>

/**
71. Simplify Path
Given a string path, which is an absolute path (starting with a slash '/') to a
file or directory in a Unix-style file system, convert it to the simplified
canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a
double period '..' refers to the directory up a level, and any multiple
consecutive slashes (i.e. '//') are treated as a single slash '/'. For this
problem, any other format of periods such as '...' are treated as file/directory
names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to
the target file or directory (i.e., no period '.' or double period '..') Return
the simplified canonical path.



Example 1:

Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
Example 2:

Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root
level is the highest level you can go. Example 3:

Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by
a single one.


Constraints:

1 <= path.length <= 3000
path consists of English letters, digits, period '.', slash '/' or '_'.
path is a valid absolute Unix path.

idea:

- do linear scan
- when found a directory (not slashes), append to the cur_dir string
- when found a slash or
after the scan we know that there was no '/' at the end of path
(otherwise, if there was scan, we already did the same in the loop on
the last iteration)
it means that directory was found and
there are four cases:
-directory is empty - it means we found a first clash
or double clash - then we do nothing
-directory is "." - it means we stay in the same directory
- then we do nothing
-directory is ".." - it means we need to go to the previous directory
if there is a previous directory (path_stack of strings is not empty)
-directory is some name - it means we need to add this directory
to the stack

In the end we have a stack of directories
we create a string with slashes between and return it





**/

using namespace std;

#define PROCESS()                                                              \
  do {                                                                         \
    if (cur_dir == "..") {                                                     \
      if (!path_stack.empty()) {                                               \
        path_stack.pop_back();                                                 \
      }                                                                        \
    } else if (cur_dir != "" && cur_dir != ".") {                              \
      path_stack.push_back(cur_dir);                                           \
    }                                                                          \
  } while (false);

class Solution {
public:
  string simplifyPath(const string &path) {
    string cur_dir = "";
    vector<string> path_stack;
    for (size_t i = 0; i < path.size(); ++i) {
      if (path[i] != '/') {
        cur_dir += path[i];
      } else {
        PROCESS();
        cur_dir = "";
      }
    }
    if (!path.empty() && path[path.size() - 1] != '/') {
      PROCESS();
    }

    string answer = "/";
    for (size_t i = 0; i < path_stack.size(); ++i) {
      answer += path_stack[i];
      if (i + 1 < path_stack.size()) {
        answer += '/';
      }
    }
    return answer;
  }
};