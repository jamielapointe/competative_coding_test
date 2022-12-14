#include <vector>

#include "breadth_first_search_unordered.h"
#include "gtest/gtest.h"
#include "utilities.h"

namespace {

TEST(BreadthFirstSearchUnorderedTest, Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  std::vector<algorithms::bfs_unordered::Node> bfs_node_container;

  static constexpr uint32_t nodeid0{0};
  static constexpr uint32_t nodeid1{1};
  static constexpr uint32_t nodeid2{2};
  static constexpr uint32_t nodeid3{3};
  static constexpr uint32_t nodeid4{4};
  static constexpr uint32_t nodeid5{5};
  static constexpr uint32_t nodeid6{6};
  static constexpr uint32_t nodeid7{7};
  static constexpr uint32_t nodeid8{8};
  static constexpr uint32_t nodeid9{9};

  algorithms::bfs_unordered::Unordered_Graph graph;
  auto node0 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid0, "Frankfurt");
  auto node1 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid1, "Mannheim");
  auto node2 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid2, "Würzburg");
  auto node3 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid3, "Kassel");
  auto node4 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid4, "Karlsruhe");
  auto node5 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid5, "Nürnberg");
  auto node6 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid6, "Erfurt");
  auto node7 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid7, "München");
  auto node8 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid8, "Augsburg");
  auto node9 = std::make_shared<algorithms::bfs_unordered::Node>(false, nodeid9, "Stuttgart");

  std::vector<algorithms::bfs_unordered::Node> bfs_expected_node_container{*node0, *node1, *node2, *node3, *node4, *node5, *node6, *node7, *node8, *node9};

  graph.add_edge(node0, node1);
  graph.add_edge(node0, node2);
  graph.add_edge(node0, node3);
  graph.add_edge(node1, node4);
  graph.add_edge(node2, node5);
  graph.add_edge(node2, node6);
  graph.add_edge(node3, node7);
  graph.add_edge(node4, node8);
  graph.add_edge(node5, node9);

  bfs(graph, node0,
      [&bfs_node_container](algorithms::bfs_unordered::Unordered_Graph::Node_Pointer node_pointer) { bfs_node_container.push_back(*node_pointer); });
  ASSERT_TRUE(algorithms::are_containers_equal(bfs_node_container, bfs_expected_node_container));
}

}  // namespace
