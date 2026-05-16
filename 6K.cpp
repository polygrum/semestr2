#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

long long BinarySearch(const std::vector<long long>& d, long long x) {
  long long low = 0;
  long long high = static_cast<long long>(d.size()) - 1;
  while (low < high) {
    long long mid = (low + high) / 2;
    if (d[mid] <= x) {
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
  std::vector<long long> a(n);
  for (long long i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  reverse(a.begin(), a.end());
  std::vector<long long> d(n + 1);
  std::vector<long long> pos(n + 1, -1);
  std::vector<long long> prev(n);
  long long length = 0;

  pos[0] = -1;
  d[0] = std::numeric_limits<long long>::min();
  for (long long i = 1; i < n + 1; i++) {
    d[i] = std::numeric_limits<long long>::max();
  }
  for (long long i = 0; i < n; i++) {
    long long j = BinarySearch(d, a[i]);
    if (d[j - 1] <= a[i] and a[i] <= d[j]) {
      d[j] = a[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = std::max(length, j);
    }
  }
  std::vector<long long> answer;
  long long p = pos[length];
  while (p != -1) {
    answer.push_back(n - p);
    p = prev[p];
  }
  std::cout << answer.size() << '\n';
  for (long long i : answer) {
    std::cout << i << " ";
  }
}
