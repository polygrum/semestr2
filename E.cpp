#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  int w;
  int n;
  std::cin >> n >> w;
  std::vector<int> weights(n);
  std::vector<int> costs(n);
  for (int i = 0; i < n; i++) {
    std::cin >> weights[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> costs[i];
  }
  std::vector dp(n, std::vector(w + 1, 0));
  if (weights[0] <= w) {
    dp[0][weights[0]] = costs[0];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < w + 1; j++) {
      dp[i][j] =
          j >= weights[i]
              ? std::max(dp[i - 1][j - weights[i]] + costs[i], dp[i - 1][j])
              : dp[i - 1][j];
    }
  }
  int max = 0;
  int max_index = 0;
  for (int i = 1; i < w + 1; i++) {
    if (dp[n - 1][i] > max) {
      max = dp[n - 1][i];
      max_index = i;
    }
  }
  std::vector<int> needed;
  int current_index = max_index;
  for (int i = n - 1; i > 0; i--) {
    if (dp[i][current_index] > dp[i - 1][current_index]) {
      needed.push_back(i + 1);
      current_index -= weights[i];
    }
  }
  if (dp[0][current_index] != 0) {
    needed.push_back(1);
  }
  std::sort(needed.begin(), needed.end());
  for (auto i : needed) {
    std::cout << i << '\n';
  }
}