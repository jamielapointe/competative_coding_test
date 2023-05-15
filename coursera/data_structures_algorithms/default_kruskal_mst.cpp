#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// This program prints the edges of the Minimum Spanning Tree. The graph is represented as an adjacency list where each edge is an object with u, v, and weight.
// The make_set, find_set and union_sets functions are the standard Disjoint Set Union (DSU) operations. The MinimumSpanningTree function is the implementation
// of the Kruskal's algorithm where we sort the edges by weight and add them to the MST if they don't form a cycle (i.e., their endpoints are not in the same
// disjoint set).

struct Edge {
  int u, v, weight;
  bool operator<(Edge const& other) { return weight < other.weight; }
};

vector<int> parent, rank;

void make_set(int v) {
  parent[v] = v;
  rank[v] = 0;
}

int find_set(int v) {
  if (v == parent[v]) return v;
  return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (rank[a] < rank[b]) swap(a, b);
    parent[b] = a;
    if (rank[a] == rank[b]) rank[a]++;
  }
}

void MinimumSpanningTree(int nodes, vector<Edge> edges) {
  sort(edges.begin(), edges.end());

  for (int i = 0; i < nodes; i++) make_set(i);

  for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
      cout << e.u << " " << e.v << "\n";
      union_sets(e.u, e.v);
    }
  }
}

int main() {
  int nodes = 5;
  vector<Edge> edges = {
      {0, 1, 10}, {0, 2, 5}, {1, 2, 4}, {1, 3, 7}, {2, 3, 8}, {3, 4, 6},
  };

  parent.resize(nodes);
  rank.resize(nodes);
  MinimumSpanningTree(nodes, edges);

  return 0;
}
