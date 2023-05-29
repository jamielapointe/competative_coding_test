#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string_view>
#include <vector>

#include "config.h"
#include "prims_minimum_spanning_tree.h"

using namespace std;
using namespace algorithms::prims_minimum_spanning_tree;

struct Data_Table_Row {
  int64_t weight{0};
  int64_t length{0};
  int64_t difference{0};
  double ratio{0.0};
};

static bool sort_table_difference(Data_Table_Row const& row1, Data_Table_Row const& row2) {
  if (row1.difference > row2.difference) {
    return true;
  }

  if (row1.difference == row2.difference) {
    if (row1.weight > row2.weight) {
      return true;
    }
  }

  return false;
}

static bool sort_table_ratio(Data_Table_Row const& row1, Data_Table_Row const& row2) {
  if (row1.ratio > row2.ratio) {
    return true;
  }
  return false;
}

static int64_t compute_weighted_completion_time(vector<Data_Table_Row> const& table) {
  int64_t completion_time{0};
  int64_t weighted_completion_time{0};
  int64_t sum_weighted_completion_time{0};
  for (auto const& row : table) {
    completion_time += row.length;
    weighted_completion_time = completion_time * row.weight;
    sum_weighted_completion_time += weighted_completion_time;
  }
  return sum_weighted_completion_time;
}

static void process_data(string_view fname) {
  ifstream data_file{fname.data()};
  string line;
  getline(data_file, line);
  int number_of_lines{0};
  istringstream ss(line);
  ss >> number_of_lines;
  vector<Data_Table_Row> table;
  table.reserve(static_cast<size_t>(number_of_lines));

  for (; getline(data_file, line);) {
    istringstream ss1(line);
    Data_Table_Row row{};
    ss1 >> row.weight;
    ss1 >> row.length;
    row.difference = row.weight - row.length;
    assert(row.length != 0);
    row.ratio = static_cast<double>(row.weight) / static_cast<double>(row.length);
    table.push_back(row);
  }

  vector<Data_Table_Row> table_ratio(table);

  sort(table.begin(), table.end(), sort_table_difference);
  cout << "The answer to #1: " << compute_weighted_completion_time(table) << "\n";

  sort(table_ratio.begin(), table_ratio.end(), sort_table_ratio);
  cout << "The answer to #2: " << compute_weighted_completion_time(table_ratio) << "\n";
}

static Unordered_Graph read_prim_mst_data(std::string_view fname) {
  ifstream data_file(fname.data());
  string line;
  getline(data_file, line);
  int number_nodes{0};
  int number_edges{0};
  istringstream ss0{line};
  ss0 >> number_nodes;
  ss0 >> number_edges;
  assert(number_nodes > 1);
  assert(number_edges > 0);
  Unordered_Graph graph(number_nodes, number_edges);
  for (; getline(data_file, line);) {
    istringstream ss1(line);
    Node::Key_T head_node_key{0};
    Node::Key_T tail_node_key{0};
    Edge::Weight_T edge_weight{0};

    ss1 >> head_node_key;
    --head_node_key;  // switch from 1 to 0 base indexing
    Node head_node{.id = head_node_key};

    ss1 >> tail_node_key;
    --tail_node_key;  // switch from 1 to 0 base indexing
    Node tail_node{.id = tail_node_key};

    ss1 >> edge_weight;

    graph.add_edge(head_node, tail_node, edge_weight);
  }
  data_file.close();
  return graph;
}

static void test_coursera_prim_mst(std::string_view test_data_path) {
  auto graph = read_prim_mst_data(test_data_path);

  // Coursera Quiz for constructing Prim's MST (minimum spanning tree)
  cout << "The answer to #3 - total cost: ";
  auto total_cost = prims_min_mst(graph);
  cout << total_cost << "\n";
}

static void run_coursera() {
  cout << "Coursera Quiz - Course 2 Week 3\n";

  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/jobs.txt");
  string const full_path = base_dir + fname;
  process_data(full_path);

  string const fname2("/data/edges.txt");
  string const full_path2 = base_dir + fname2;
  test_coursera_prim_mst(full_path2);
}

int main() {
  run_coursera();

  return 0;
}
