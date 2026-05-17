#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  long long answer = 0;
  for (int left = 1; left < n / 5 + 1; left++) {
    std::vector dp(left, std::vector(n + 1, 0LL));
    std::vector prefix(left, std::vector(n + 1, 0LL));
    for (int i = 0; i < left; i++) {
      prefix[i][0] = 1;
    }
    for (int j = 1; j < n + 1; j++) {
        if (j >= left) {
          dp[0][j] = prefix[0][j - left];
        }
      for (int i = 1; i < left; i++) {
        if (j >= left + i) {
          dp[i][j] = prefix[i][j - i - left];
        }
        prefix[i][j] = prefix[i - 1][j] + dp[i - 1][j];
      }
    }
    if (left >= 2) {
      answer += dp[left - 2][n];
    }
    answer += dp[left - 1][n];
  }
  for (int i = 1; i < (n + 1) / 2; i++) {
    if (i > (n - i) / 2) {
      answer++;
    }
  }
  answer++;
  for (int right = 2 * (n / 5); right < n; right++) {
    for (int i = right / 2 + 1; i < n - i - right; i++) {
      if (i < n - i - right and n - i - right < right) {
        answer++;
      }
    }
  }
  if (n <= 1) {
    std::cout << 1;
  } else {
    std::cout << answer;
  }
}
