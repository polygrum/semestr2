#include <iostream>
#include <queue>
#include <vector>

class Graph {
  std::vector<std::vector<std::pair<int, long long>>> edges_;
  int vertices_;

 public:
  explicit Graph(int vertices) : vertices_(vertices) {
    edges_.resize(vertices);
  }

  void AddEdge(int u, int v, long long c) {
    edges_[u].emplace_back(v, c);
    edges_[v].emplace_back(u, c);
  }

  void Djikstra(int s) {
    const long long cInf = 2009000999;
    std::vector dist(vertices_, cInf);
    dist[s] = 0;
    std::priority_queue<std::pair<long long, int>> closest;
    closest.emplace(0, s);
    while (!closest.empty()) {
      long long len = -closest.top().first;
      int v = closest.top().second;
      closest.pop();
      if (len > dist[v]) {
        continue;
      }
      for (auto x : edges_[v]) {
        if (dist[x.first] > dist[v] + x.second) {
          dist[x.first] = dist[v] + x.second;
          closest.emplace(-dist[x.first], x.first);
        }
      }
    }
    for (int i = 0; i < vertices_; ++i) {
      std::cout << dist[i] << " ";
    }
    std::cout << '\n';
  }
};

int main() {
  int t;
  std::cin >> t;
  while (t-- != 0) {
    int n;
    int m;
    int u;
    int v;
    long long c;
    std::cin >> n >> m;
    Graph g(n);
    while (m-- != 0) {
      std::cin >> u >> v >> c;
      g.AddEdge(u, v, c);
    }
    int s;
    std::cin >> s;
    g.Djikstra(s);
  }
}