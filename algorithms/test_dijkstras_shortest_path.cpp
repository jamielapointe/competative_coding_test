#include <vector>

#include "dijkstras_shortest_path.h"
#include "gtest/gtest.h"
#include "utilities.h"

namespace {

TEST(DijkstraShortestPathTest, Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  std::vector<algorithms::dijkstra_shortest_path::Node> scc_node_container;

  algorithms::dijkstra_shortest_path::Unordered_Graph graph;
  algorithms::dijkstra_shortest_path::Node node0{.id = 0, .label = "Frankfurt"};
  algorithms::dijkstra_shortest_path::Node node1{.id = 1, .label = "Mannheim"};
  algorithms::dijkstra_shortest_path::Node node2{.id = 2, .label = "Würzburg"};
  algorithms::dijkstra_shortest_path::Node node3{.id = 3, .label = "Kassel"};
  algorithms::dijkstra_shortest_path::Node node4{.id = 4, .label = "Karlsruhe"};
  algorithms::dijkstra_shortest_path::Node node5{.id = 5, .label = "Nürnberg"};   // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  algorithms::dijkstra_shortest_path::Node node6{.id = 6, .label = "Erfurt"};     // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  algorithms::dijkstra_shortest_path::Node node7{.id = 7, .label = "München"};    // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  algorithms::dijkstra_shortest_path::Node node8{.id = 8, .label = "Augsburg"};   // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  algorithms::dijkstra_shortest_path::Node node9{.id = 9, .label = "Stuttgart"};  // NOLINT(cppcoreguidelines-avoid-magic-numbers)

  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_0_1{85};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_0_2{217};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_0_3{173};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_1_4{80};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_2_6{186};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_2_5{103};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_9_5{183};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_3_7{502};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_4_8{250};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_8_7{84};
  static constexpr algorithms::dijkstra_shortest_path::Edge::Weight_T node_5_7{167};

  std::vector<algorithms::dijkstra_shortest_path::Edge::Weight_T> expected_distances{
      0,                               // Frankfurt to Frankfurt
      node_0_1,                        // Frankfurt to Mannheim
      node_0_2,                        // Frankfurt to Würzburg
      node_0_3,                        // Frankfurt to Kassel
      node_0_1 + node_1_4,             // Frankfurt to Karlsruhe
      node_0_2 + node_2_5,             // Frankfurt to Nürnberg
      node_0_2 + node_2_6,             // Frankfurt to Erfurt
      node_0_2 + node_2_5 + node_5_7,  // Frankfurt to München
      node_0_1 + node_1_4 + node_4_8,  // Frankfurt to Augsburg
      node_0_2 + node_2_5 + node_9_5   // Frankfurt to Stuttgart
  };

  graph.add_edge(node0, node1, node_0_1);
  graph.add_edge(node0, node2, node_0_2);
  graph.add_edge(node0, node3, node_0_3);
  graph.add_edge(node1, node4, node_1_4);
  graph.add_edge(node2, node6, node_2_6);
  graph.add_edge(node2, node5, node_2_5);
  graph.add_edge(node5, node9, node_9_5);
  graph.add_edge(node3, node7, node_3_7);
  graph.add_edge(node4, node8, node_4_8);
  graph.add_edge(node8, node7, node_8_7);
  graph.add_edge(node5, node7, node_5_7);

  auto distances = algorithms::dijkstra_shortest_path::dijkstra(graph, node0.key());

  ASSERT_TRUE(algorithms::are_containers_equal(distances, expected_distances));
}

}  // namespace
