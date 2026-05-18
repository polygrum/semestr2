#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class Graph {
  int sz_;
  std::vector<std::vector<long long>> cap_;
  std::vector<std::vector<int>> index_;

 public:
  explicit Graph(int sz) : sz_(sz) {
    cap_.assign(sz, std::vector(sz, 0LL));
    index_.assign(sz, std::vector(sz, 0));
  }

  void AddEdge(int u, int v, int cap, int index) {
    cap_[--u][--v] += cap;
    cap_[v][u] += cap;
    index_[u][v] = index;
    index_[v][u] = index;
  }

  auto EdmondsKarp() {
    auto res = cap_;

    std::vector parent(sz_, -1);
    while (true) {
      std::fill(parent.begin(), parent.end(), -1);

      std::queue<int> q;
      q.push(0);
      parent[0] = 0;

      while (!q.empty() && parent[sz_ - 1] == -1) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < sz_; i++) {
          if (res[v][i] > 0 && parent[i] == -1) {
            parent[i] = v;
            q.push(i);
          }
        }
      }
      if (parent[sz_ - 1] == -1) {
        std::vector<bool> is_left(sz_);
        for (int i = 0; i < sz_; i++) {
          is_left[i] = parent[i] != -1;
        }
        return is_left;
      }

      long long path_flow = std::numeric_limits<long long>::max();
      for (auto i = sz_ - 1; i != 0; i = parent[i]) {
        path_flow = std::min(path_flow, res[parent[i]][i]);
      }
      for (auto i = sz_ - 1; i != 0; i = parent[i]) {
        res[parent[i]][i] -= path_flow;
        res[i][parent[i]] += path_flow;
      }
    }
  }

  void FindCut(const std::vector<bool>& is_left) {
    long long cut_sum = 0;
    std::vector<int> cut;
    for (int v = 0; v < sz_; v++) {
      for (int u = 0; u < sz_; u++) {
        if (cap_[v][u] != 0 && is_left[v] && !is_left[u]) {
          cut_sum += cap_[v][u];
          cut.push_back(index_[v][u]);
        }
      }
    }
    std::cout << cut.size() << " " << cut_sum << '\n';
    std::sort(cut.begin(), cut.end());
    for (int i : cut) {
      std::cout << i << ' ';
    }
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    g.AddEdge(u, v, c, i + 1);
  }
  g.FindCut(g.EdmondsKarp());
}
