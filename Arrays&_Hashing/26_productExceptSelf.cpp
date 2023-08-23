#include <cstddef>
#include <vector>

using namespace std;

vector<int> productExceptSelf(vector<int> &nums) {
  vector<int> answer;

  // if nums vector is empty, return empty answer
  if (nums.size() == 0) {
    return answer;
  }

  // calculate sufixes
  answer.resize(nums.size());
  answer[nums.size() - 1] = 1;
  for (size_t i = 1; i < nums.size(); ++i) {
    size_t j = nums.size() - i - 1;
    answer[j] = answer[j + 1] * nums[j + 1];
  }

  // now answer[j] = sufix from j + 1 to n - 1

  // multiply by prefix
  // prefix on i iteration equals prefix from 0 to i - 1
  // (if i == 0 => prefix equals 1)
  int prefix = 1;
  for (size_t i = 0; i < answer.size(); ++i) {
    answer[i] *= prefix;
    prefix *= nums[i];
  }

  // return answer
  return answer;
}