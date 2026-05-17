#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int vertices_;
  std::vector<std::vector<int>> edges_;
  std::vector<std::vector<int>> edge_index_;
  std::vector<int> t_in_;
  std::vector<int> ret_;
  std::vector<int> bridges_;

  void Dfs(int v, int& time, int parent_edge) {
    time++;
    t_in_[v] = time;
    ret_[v] = time;
    for (int i = 0; i < static_cast<int>(edges_[v].size()); i++) {
      int u = edges_[v][i];
      int edge_id = edge_index_[v][i];
      if (edge_id == parent_edge) {
        continue;
      }

      if (t_in_[u] != -1) {
        ret_[v] = std::min(ret_[v], t_in_[u]);
      } else {
        Dfs(u, time, edge_id);
        ret_[v] = std::min(ret_[v], ret_[u]);
        if (ret_[u] > t_in_[v]) {
          bridges_.push_back(edge_index_[v][i]);
        }
      }
    }
  }

 public:
  explicit Graph(int n) : vertices_(n) {
    edges_.resize(n);
    edge_index_.resize(n);
    t_in_.assign(n, -1);
    ret_.resize(n);
    bridges_ = std::vector<int>();
  }

  void AddEdge(int u, int v, int index) {
    edges_[u].push_back(v);
    edges_[v].push_back(u);
    edge_index_[u].push_back(index);
    edge_index_[v].push_back(index);
  }

  std::vector<int> GetCuts() {
    int time = 0;
    for (int i = 0; i < vertices_; i++) {
      if (t_in_[i] == -1) {
        Dfs(i, time, -2);
      }
    }
    std::sort(bridges_.begin(), bridges_.end());
    std::cout << bridges_.size() << '\n';
    for (int bridge : bridges_) {
      std::cout << bridge << ' ';
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);
  int r;
  std::cin >> r;
  int u;
  int v;
  for (int i = 0; i < r; i++) {
    std::cin >> u >> v;
    g.AddEdge(u - 1, v - 1, i + 1);
  }
  g.GetCuts();
}