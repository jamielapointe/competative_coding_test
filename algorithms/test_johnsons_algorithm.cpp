#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>
#include <string_view>

#include "config.h"
#include "johnsons_algorithm.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace std;
using algorithms::johnsons_algorithm::Directed_Graph;
using algorithms::johnsons_algorithm::johnsons_algorithm;

static std::unique_ptr<Directed_Graph> read_data(std::string_view fname) {
  ifstream data_file(fname.data());
  string line;
  getline(data_file, line);
  istringstream ss(line);
  int total_nodes{0};
  ss >> total_nodes;
  int total_edges{0};
  ss >> total_edges;
  auto graph = make_unique<Directed_Graph>(total_nodes, total_edges);
  for (; getline(data_file, line);) {
    istringstream ss1(line);
    int head_node_key{0};
    ss1 >> head_node_key;
    int tail_node_key{0};
    ss1 >> tail_node_key;
    int edge_weight{0};
    ss1 >> edge_weight;

    graph->add_edge(head_node_key, tail_node_key, edge_weight);
  }
  return graph;
}

TEST(JohnsonsAlgorithmTest, Test00) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  // Test a negative cycle
  auto graph = make_unique<Directed_Graph>(5, 5);
  graph->add_edge(1, 2, 5);
  graph->add_edge(2, 3, 1);
  graph->add_edge(2, 4, 2);
  graph->add_edge(3, 5, 1);
  graph->add_edge(4, 6, 2);
  graph->add_edge(6, 5, -3);
  graph->add_edge(5, 4, -1);
  auto result = johnsons_algorithm(graph);
  EXPECT_FALSE(result.is_valid);
}

TEST(JohnsonsAlgorithmTest, TestG1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/johnson_alg_g1.txt");
  string const full_path = base_dir + fname;
  auto graph = read_data(full_path);
  auto result = johnsons_algorithm(graph);
  EXPECT_FALSE(result.is_valid);
}

TEST(JohnsonsAlgorithmTest, TestG2) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/johnson_alg_g2.txt");
  string const full_path = base_dir + fname;
  auto graph = read_data(full_path);
  auto result = johnsons_algorithm(graph);
  EXPECT_FALSE(result.is_valid);
}

TEST(JohnsonsAlgorithmTest, TestG3) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/johnson_alg_g3.txt");
  string const full_path = base_dir + fname;
  auto graph = read_data(full_path);
  auto result = johnsons_algorithm(graph);
  EXPECT_TRUE(result.is_valid);
  EXPECT_EQ(result.shortest_path, -19);
}

// I believe this is currently running out of memory; will need a slightly
// different strategy for very large networks...
// TEST(JohnsonsAlgorithmTest, TestLarge) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
//   string const base_dir(EXECUTABLE_BASE_DIR);
//   string const fname("/data/johnson_alg_large.txt");
//   string const full_path = base_dir + fname;
//   auto graph = read_data(full_path);
//   auto result = johnsons_algorithm(graph);
//   EXPECT_TRUE(result.is_valid);
//   EXPECT_EQ(result.shortest_path, -6);
// }

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
