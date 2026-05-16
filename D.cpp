#include <algorithm>
#include <iostream>
#include <vector>

class DirGraph {
  int vertices_;
  std::vector<std::vector<int>> edges_;
  std::vector<std::vector<int>> r_edges_;
  std::vector<bool> used_;
  std::vector<int> components_;

  void ClearUsed() {
    for (int i = 0; i < vertices_; i++) {
      used_[i] = false;
    }
  }

  void DfsUp(int v, std::vector<int>& order) {
    used_[v] = true;
    for (auto u : edges_[v]) {
      if (!used_[u]) {
        DfsUp(u, order);
      }
    }
    order.push_back(v);
  }
  void DfsDown(int v, std::vector<int>& component) {
    used_[v] = true;
    component.push_back(v);
    for (auto u : r_edges_[v]) {
      if (!used_[u]) {
        DfsDown(u, component);
      }
    }
  }

 public:
  explicit DirGraph(int n) : vertices_(n) {
    edges_.resize(n);
    r_edges_.resize(n);
    used_.resize(n);
    components_.assign(n, 0);
  }

  void AddEdge(int u, int v) {
    edges_[u].push_back(v);
    r_edges_[v].push_back(u);
  }

  void AssignComponents() {
    std::vector<int> order;
    for (int i = 0; i < vertices_; i++) {
      if (!used_[i]) {
        DfsUp(i, order);
      }
    }
    std::reverse(order.begin(), order.end());
    ClearUsed();
    int comp_number = 0;
    for (auto v : order) {
      if (!used_[v]) {
        comp_number++;
        std::vector<int> component;
        DfsDown(v, component);
        for (auto u : component) {
          components_[u] = comp_number;
        }
      }
    }
    std::cout << comp_number << '\n';
    for (auto v : components_) {
      std::cout << v << ' ';
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  DirGraph dg(n);
  int r;
  std::cin >> r;
  int u;
  int v;
  for (int i = 0; i < r; i++) {
    std::cin >> u >> v;
    dg.AddEdge(u - 1, v - 1);
  }
  dg.AssignComponents();
}