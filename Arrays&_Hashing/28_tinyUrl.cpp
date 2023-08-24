/**Note: This is a companion problem to the System Design problem: Design
TinyURL. TinyURL is a URL shortening service where you enter a URL such as
https://leetcode.com/problems/design-tinyurl and it returns a short URL such as
http://tinyurl.com/4e9iAk. Design a class to encode a URL and decode a tiny URL.

There is no restriction on how your encode/decode algorithm should work. You
just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can
be decoded to the original URL.

Implement the Solution class:

Solution() Initializes the object of the system.
String encode(String longUrl) Returns a tiny URL for the given longUrl.
String decode(String shortUrl) Returns the original long URL for the given
shortUrl. It is guaranteed that the given shortUrl was encoded by the same
object.


Example 1:

Input: url = "https://leetcode.com/problems/design-tinyurl"
Output: "https://leetcode.com/problems/design-tinyurl"

Explanation:
Solution obj = new Solution();
string tiny = obj.encode(url); // returns the encoded tiny url.
string ans = obj.decode(tiny); // returns the original url after decoding it.


Constraints:

1 <= url.length <= 10^4
url is guranteed to be a valid URL.


idea: simple usage of unordered_map
time: average O(1)
space: O(n)


**/

#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
  // Encodes a URL to a shortened URL.
  string encode(string longUrl) {

    // if there is no such url -> create one and store
    if (!encoding_.contains(longUrl)) {
      encoding_[longUrl] = current_string_;
      // change next int code
      ++current_index_;

      // create current string code
      current_string_ = "http://tinyurl.com/" + to_string(current_index_);

      // store in decoding
      decoding_[current_string_] = longUrl;
    }

    // return encoding
    return encoding_[longUrl];
  }

  // Decodes a shortened URL to its original URL.
  string decode(string shortUrl) {
    assert(decoding_.contains(shortUrl));
    return decoding_[shortUrl];
  }

private:
  unordered_map<string, string> encoding_;
  unordered_map<string, string> decoding_;
  int current_index_{0};
  string current_string_{"0"};
};