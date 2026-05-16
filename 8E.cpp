#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

class Graph {
  std::vector<std::vector<std::pair<int, long long>>> edges_;
  int vertices_;

 public:
  explicit Graph(int vertices) : vertices_(vertices) {
    edges_.resize(vertices);
  }

  void AddEdge(int u, int v, long long c) { edges_[u].emplace_back(v, c); }

  void FordBellman() {
    const long long cInf = std::numeric_limits<long long>::max();
    std::vector dp(vertices_ + 1, std::vector(vertices_, cInf));
    std::vector dparents(vertices_ + 1, std::vector(vertices_, -1));
    for (int u = 0; u < vertices_; ++u) {
      dp[0][u] = 0;
    }
    for (int l = 0; l < vertices_; ++l) {
      for (int v = 0; v < vertices_; ++v) {
        if (dp[l + 1][v] > dp[l][v]) {
          dp[l + 1][v] = dp[l][v];
          dparents[l + 1][v] = v;
        }
        if (dp[l][v] < cInf) {
          for (auto& e : edges_[v]) {
            if (dp[l + 1][e.first] > dp[l][v] + e.second) {
              dp[l + 1][e.first] = dp[l][v] + e.second;
              dparents[l + 1][e.first] = v;
            }
          }
        }
      }
    }
    int updated = -1;
    for (int v = 0; v < vertices_; ++v) {
      if (dp[vertices_][v] != dp[vertices_ - 1][v]) {
        updated = v;
        break;
      }
    }
    if (updated == -1) {
      std::cout << "NO";
      return;
    }
    std::cout << "YES" << '\n';
    std::vector path(1, updated);
    int current = updated;
    for (int v = vertices_; v > 0; --v) {
      current = dparents[v][current];
      path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    std::unordered_map<int, int> last_index;

    for (int i = 0; i < static_cast<int>(path.size()); i++) {
      if (last_index.find(path[i]) != last_index.end()) {
        int start = last_index[path[i]];
        int end = i;

        std::cout << (end - start + 1) << '\n';

        for (int j = start; j <= end; j++) {
          std::cout << path[j] + 1 << ' ';
        }
        std::cout << '\n';
        return;
      }
      last_index[path[i]] = i;
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);
  const int cBig = 100000;
  for (int u = 0; u < n; ++u) {
    for (int v = 0; v < n; ++v) {
      int c;
      std::cin >> c;
      if (c != cBig) {
        g.AddEdge(u, v, c);
      }
    }
  }
  g.FordBellman();
}