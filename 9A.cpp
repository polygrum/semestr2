#include <iostream>
#include <vector>

class DuoGraph {
  int left_sz_;
  int right_sz_;
  std::vector<std::vector<int>> adj_;
  std::vector<bool> used_;
  std::vector<int> match_;

  bool Dfs(int v) {
    if (used_[v]) {
      return false;
    }
    used_[v] = true;
    for (auto u : adj_[v]) {
      if (match_[u] == -1 || Dfs(match_[u])) {
        match_[u] = v;
        return true;
      }
    }
    return false;
  }

public:
  DuoGraph(int left_sz, int right_sz) : left_sz_(left_sz), right_sz_(right_sz) {
    adj_.resize(left_sz + right_sz);
    used_.resize(left_sz + right_sz);
    match_.assign(left_sz + right_sz, -1);
  }

  void AddEdge(int l, int r) {
    adj_[l].push_back(r);
    adj_[r].push_back(l);
  }

  void Pair() {
    for (int i = 0; i < left_sz_; i++) {
      used_.assign(left_sz_ + right_sz_, false);
      Dfs(i);
    }
    int count = 0;
    for (int i = left_sz_; i < left_sz_ + right_sz_; i++) {
      if (match_[i] != -1) {
        count++;
      }
    }
    std::cout << count << '\n';
    for (int i = left_sz_; i < left_sz_ + right_sz_; i++) {
      if (match_[i] != -1) {
        std::cout << match_[i] + 1 << " " << i - left_sz_ + 1 << '\n';
      }
    }
  }
};

int main() {
  int l;
  int r;
  std::cin >> l >> r;
  DuoGraph g(l, r);
  for (int i = 0; i < l; i++) {
    int n;
    while (std::cin >> n && n != 0) {
      g.AddEdge(i, n - 1 + l);
    }
  }
  g.Pair();
}
