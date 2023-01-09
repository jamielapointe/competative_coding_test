
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>

#include "dijkstras_shortest_path.h"

using namespace std;
using namespace algorithms;
using namespace algorithms::dijkstra_shortest_path;

inline Unordered_Graph read_data() {
  std::string const fname("data/dijkstraData.txt");
  ifstream data_file(fname);
  // allow the counting of new line characters
  data_file.unsetf(std::ios_base::skipws);
  // count the new lines with a C++ STL algorithm
  auto num_nodes = std::count(std::istream_iterator<char>(data_file), std::istream_iterator<char>(), '\n');
  Unordered_Graph graph(static_cast<std::size_t>(num_nodes));
  data_file.clear();            // clear the EOF flag
  data_file.seekg(0);           // go to start of file
  assert(data_file.is_open());  // NOLINT
  assert(data_file.good());     // NOLINT
  const string space = "\t";
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
    next = rest_of_line.find_first_of(space, current);
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
      next = rest_of_line.find_first_of(space, current);
    }
    (void)next;
  }
  return graph;
}

int main() {
  // Coursera Quiz for SCC graph
  cout << endl << endl;
  cout << "Corsera Quiz Dijkstra's Algorithm:" << endl;

  Unordered_Graph graph = read_data();
  Node::Key_T root_key{1};

  // Find the shortest paths from the source to all other reachable nodes
  auto distances = dijkstra(graph, root_key);

  // Print all of the distances from the root node
  std::vector<int> list_of_nodes{7, 37, 59, 82, 99, 115, 133, 165, 188, 197};  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  for (auto const& node_key : list_of_nodes) {
    std::cout << distances.at(static_cast<size_t>(node_key - 1)) << ",";
  }
  std::cout << std::endl;

  return 0;
}
