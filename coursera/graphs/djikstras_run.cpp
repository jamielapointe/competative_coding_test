
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string_view>

#include "dijkstras_shortest_path.h"
#include "utilities.h"

using namespace std;
using namespace algorithms;
using namespace algorithms::dijkstra_shortest_path;

static Unordered_Graph read_data(std::string_view fname) {
  ifstream data_file(fname.data());
  // allow the counting of new line characters
  data_file.unsetf(std::ios_base::skipws);
  // count the new lines with a C++ STL algorithm
  auto num_nodes = std::count(std::istream_iterator<char>(data_file), std::istream_iterator<char>(), '\n');
  Unordered_Graph graph(static_cast<std::size_t>(num_nodes));
  data_file.clear();            // clear the EOF flag
  data_file.seekg(0);           // go to start of file
  assert(data_file.is_open());  // NOLINT
  assert(data_file.good());     // NOLINT
  const string space = "\t \r\n";
  const string comma = ",";
  for (std::string line; std::getline(data_file, line);) {
    std::istringstream ss(line);
    Node::Key_T head_node_key{0};
    Node::Key_T tail_node_key{0};
    Edge::Weight_T edge_weight{0};
    ss >> head_node_key;
    --head_node_key;  // switch from 1 to 0 base indexing
    Node head_node{.id = head_node_key, .label = to_string(head_node_key)};

    // loop through the rest of the line getting tail,weight pairs add these edges to the graph as we do
    string rest_of_line = ss.str();
    size_t next = 0;
    size_t current = 0;
    next = rest_of_line.find_first_of(space);
    current = next + 1;
    while ((next = rest_of_line.find_first_of(space, current)) == current) {
      current = next + 1;
    }
    while (next != string::npos) {
      std::istringstream ss_node_weight(rest_of_line.substr(current, next - current));
      char tmp_char{};
      ss >> tail_node_key;
      --tail_node_key;  // switch from 1 to 0 base indexing
      ss >> tmp_char;
      ss >> edge_weight;
      Node tail_node{.id = tail_node_key, .label = to_string(tail_node_key)};
      graph.add_edge(head_node, tail_node, edge_weight);

      current = next + 1;
      while ((next = rest_of_line.find_first_of(space, current)) == current) {
        current = next + 1;
      }
    }
    (void)next;  // for debugging
  }
  data_file.close();
  return graph;
}

static void test_coursera_graph() {
  // Coursera Quiz for SCC graph
  cout << endl << endl;
  cout << "Coursera Quiz Dijkstra's Algorithm:" << endl;

  std::string const fname("data/dijkstraData.txt");
  Unordered_Graph graph = read_data(fname);
  Node::Key_T root_key{0};

  // Find the shortest paths from the source to all other reachable nodes
  auto distances = dijkstra(graph, root_key);

  // Print all of the distances from the root node
  std::vector<int> list_of_nodes{7, 37, 59, 82, 99, 115, 133, 165, 188, 197};  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  for (auto const& node_key : list_of_nodes) {
    std::cout << distances.at(static_cast<size_t>(node_key - 1)) << ",";
  }
  std::cout << std::endl;
}

static void test_simple_graph0() {
  cout << endl << endl;
  cout << "Simple Graph Test 0:" << endl;

  std::string const fname("data/simple_graph0.txt");
  Unordered_Graph graph = read_data(fname);
  Node::Key_T root_key{0};

  const std::vector<algorithms::dijkstra_shortest_path::Edge::Weight_T> expected_distances{
      0,    // Frankfurt to Frankfurt
      85,   // Frankfurt to Mannheim
      217,  // Frankfurt to Würzburg
      173,  // Frankfurt to Kassel
      165,  // Frankfurt to Karlsruhe
      320,  // Frankfurt to Nürnberg
      403,  // Frankfurt to Erfurt
      487,  // Frankfurt to München
      415,  // Frankfurt to Augsburg
      503   // Frankfurt to Stuttgart
  };

  // Find the shortest paths from the source to all other reachable nodes
  const auto distances = dijkstra(graph, root_key);

  test_containers_equal(distances, expected_distances);
}

static void test_simple_graph1() {
  cout << endl << endl;
  cout << "Simple Graph Test 1:" << endl;

  std::string const fname("data/simple_graph1.txt");
  Unordered_Graph graph = read_data(fname);
  Node::Key_T root_key{0};

  const std::vector<algorithms::dijkstra_shortest_path::Edge::Weight_T> expected_distances{
      0,   //
      4,   //
      12,  //
      19,  //
      21,  //
      11,  //
      9,   //
      8,   //
      14   //
  };

  // Find the shortest paths from the source to all other reachable nodes
  const auto distances = dijkstra(graph, root_key);

  test_containers_equal(distances, expected_distances);
}

int main() {
  test_simple_graph0();
  test_simple_graph1();
  test_coursera_graph();

  return 0;
}
