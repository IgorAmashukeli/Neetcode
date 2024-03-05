#include <cstddef>
#include <stack>
#include <tuple>
#include <unordered_map>

using namespace std;

class FreqStack {
public:
  FreqStack() {}

  void push(int val) {
    if (!counts_.contains(val)) {
      counts_[val] = 1;
    } else {
      counts_[val]++;
    }
    if (stack_.empty()) {
      stack_.push({val, val, 1});
    } else {
      tuple<int, int, size_t> top_tuple = stack_.top();
      int max_freq_val = get<1>(top_tuple);
      size_t max_freq_freq = get<2>(top_tuple);
      if (max_freq_val == val || counts_[val] >= max_freq_freq) {
        stack_.push({val, val, counts_[val]});
      } else {
        stack_.push({val, max_freq_val, max_freq_freq});
      }
    }
  }

  int pop() {
    int val = get<1>(stack_.top());
    stack_.pop();
    counts_[val]--;
    if (counts_[val] == 0) {
      counts_.erase(val);
    }
    return val;
  }

private:
  unordered_map<int, size_t> counts_;
  stack<tuple<int, int, size_t>> stack_;
};

int main() { FreqStack freqStack = FreqStack(); }