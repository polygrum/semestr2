#include <iostream>
#include <vector>

class DuoGraph {
  int v1_;
  int v2_;
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
  DuoGraph(int v1, int v2) : v1_(v1), v2_(v2) {
    adj_.resize(v1 + v2);
    used_.resize(v1 + v2);
    match_.assign(v1 + v2, -1);
  }

  void AddEdge(int l, int r) {
    adj_[l].push_back(r);
    adj_[r].push_back(l);
  }

  void Pair() {
    for (int i = 0; i < v1_; i++) {
      used_.assign(v1_ + v2_, false);
      Dfs(i);
    }
    int count = 0;
    for (int i = v1_; i < v1_ + v2_; i++) {
      if (match_[i] != -1) {
        count++;
      }
    }
    std::cout << count << '\n';
    for (int i = v1_; i < v1_ + v2_; i++) {
      if (match_[i] != -1) {
        std::cout << match_[i] + 1 << " " << i - v1_ + 1 << '\n';
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