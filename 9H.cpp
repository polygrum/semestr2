#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int from;
  int to;
  int c;
  int flow;
  int index;

  Edge(int from, int to, int c, int index)
      : from(from), to(to), c(c), flow(0), index(index) {}
};

class Graph {
  int v_;
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> adj_;
  std::vector<int> dist_;
  std::vector<int> next_;
  long long total_flow_{0};
  const int cInf = std::numeric_limits<int>::max();

  bool Bfs() {
    std::fill(dist_.begin(), dist_.end(), cInf);
    std::queue<int> q;
    q.push(0);
    dist_[0] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto edge_index : adj_[v]) {
        auto uv = edges_[edge_index];
        if (uv.c > uv.flow && dist_[uv.to] == cInf) {
          dist_[uv.to] = dist_[uv.from] + 1;
          q.push(uv.to);
        }
      }
    }
    return dist_[v_ - 1] != cInf;
  }

  int Dfs(int u, int bottleneck) {
    if (u == v_ - 1 || bottleneck == 0) {
      return bottleneck;
    }
    while (next_[u] < static_cast<int>(adj_[u].size())) {
      auto& uv = edges_[adj_[u][next_[u]]];
      if (dist_[uv.to] == dist_[u] + 1) {
        int flow = Dfs(uv.to, std::min(bottleneck, (uv.c - uv.flow)));
        if (flow != 0) {
          uv.flow += flow;
          edges_[adj_[u][next_[u]] ^ 1].flow -= flow;
          return flow;
        }
      }
      next_[u]++;
    }
    return 0;
  }

 public:
  explicit Graph(int v) : v_(v), adj_(v), dist_(v, 0), next_(v, 0) {}

  void AddEdge(int v, int u, int c, int index) {
    adj_[v].push_back(static_cast<int>(edges_.size()));
    edges_.emplace_back(v, u, c, index);
    adj_[u].push_back(static_cast<int>(edges_.size()));
    edges_.emplace_back(u, v, 0, index);
  }

  void Dinic() {
    while (Bfs()) {
      std::fill(next_.begin(), next_.end(), 0);
      while (int added = Dfs(0, cInf)) {
        total_flow_ += added;
      }
    }
  }

  void PrintFlow() {
    std::cout << total_flow_ << '\n';
    std::vector<int> edges_flow(edges_.size() / 2);
    for (int i = 0; i < static_cast<int>(edges_.size()); i += 2) {
      edges_flow[edges_[i].index] = edges_[i].flow;
    }
    for (auto edge_flow : edges_flow) {
      std::cout << edge_flow << '\n';
    }
  }
};

int main() {
  const int cMax = 29;
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n);
  std::vector<int> v(m);
  std::vector<int> u(m);
  std::vector<int> c(m);
  for (int i = 0; i < m; i++) {
    std::cin >> v[i] >> u[i] >> c[i];
  }

  for (int i = cMax; i >= 0; i--) {
    bool flag = false;
    for (int j = 0; j < m; j++) {
      if (1 << (i + 1) > c[j] + 1 && c[j] >= (1 << i) - 1) {
        g.AddEdge(--v[j], --u[j], c[j], j);
        flag = true;
      }
    }
    if (flag) {
      g.Dinic();
    }
  }
  g.PrintFlow();
}