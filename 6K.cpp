#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

long long BinarySearch(const std::vector<long long>& array, long long target) {
  long long low = 0;
  long long high = static_cast<long long>(array.size()) - 1;
  while (low < high) {
    long long mid = (low + high) / 2;
    if (array[mid] <= target) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}

int main() {
  long long n;
  std::cin >> n;
  std::vector<long long> sequence(n);
  for (long long i = 0; i < n; i++) {
    std::cin >> sequence[i];
  }
  reverse(sequence.begin(), sequence.end());
  std::vector<long long> subseq(n + 1);
  std::vector<long long> pos(n + 1, -1);
  std::vector<long long> prev(n);
  long long length = 0;

  pos[0] = -1;
  subseq[0] = std::numeric_limits<long long>::min();
  for (long long i = 1; i < n + 1; i++) {
    subseq[i] = std::numeric_limits<long long>::max();
  }
  for (long long i = 0; i < n; i++) {
    long long j = BinarySearch(subseq, sequence[i]);
    if (subseq[j - 1] <= sequence[i] and sequence[i] <= subseq[j]) {
      subseq[j] = sequence[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = std::max(length, j);
    }
  }
  std::vector<long long> answer;
  long long cur = pos[length];
  while (cur != -1) {
    answer.push_back(n - cur);
    cur = prev[cur];
  }
  std::cout << answer.size() << '\n';
  for (long long i : answer) {
    std::cout << i << " ";
  }
}
