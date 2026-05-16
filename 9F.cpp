#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class Graph {
  int v_;
  std::vector<std::vector<long long>> cap_;
  std::vector<std::vector<int>> index_;

 public:
  explicit Graph(int v) : v_(v) {
    cap_.assign(v, std::vector(v, 0LL));
    index_.assign(v, std::vector(v, 0));
  }

  void AddEdge(int v1, int v2, int c, int index) {
    cap_[--v1][--v2] += c;
    cap_[v2][v1] += c;
    index_[v1][v2] = index;
    index_[v2][v1] = index;
  }

  auto EdmondsKarp() {
    auto res = cap_;

    std::vector parent(v_, -1);
    while (true) {
      std::fill(parent.begin(), parent.end(), -1);

      std::queue<int> q;
      q.push(0);
      parent[0] = 0;

      while (!q.empty() && parent[v_ - 1] == -1) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < v_; i++) {
          if (res[v][i] > 0 && parent[i] == -1) {
            parent[i] = v;
            q.push(i);
          }
        }
      }
      if (parent[v_ - 1] == -1) {
        std::vector<bool> is_left(v_);
        for (int i = 0; i < v_; i++) {
          is_left[i] = parent[i] != -1;
        }
        return is_left;
      }

      long long path_flow = std::numeric_limits<long long>::max();
      for (auto i = v_ - 1; i != 0; i = parent[i]) {
        path_flow = std::min(path_flow, res[parent[i]][i]);
      }
      for (auto i = v_ - 1; i != 0; i = parent[i]) {
        res[parent[i]][i] -= path_flow;
        res[i][parent[i]] += path_flow;
      }
    }
  }

  void FindCut(const std::vector<bool>& is_left) {
    long long cut_sum = 0;
    std::vector<int> cut;
    for (int v = 0; v < v_; v++) {
      for (int u = 0; u < v_; u++) {
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
    int v1;
    int v2;
    int c;
    std::cin >> v1 >> v2 >> c;
    g.AddEdge(v1, v2, c, i + 1);
  }
  g.FindCut(g.EdmondsKarp());
}