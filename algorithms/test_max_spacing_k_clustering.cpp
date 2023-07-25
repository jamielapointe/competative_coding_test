#include <gtest/gtest.h>

#include "max_spacing_k_clustering.h"

using namespace std;
using namespace algorithms::max_spacing_k_clustering;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)

namespace {
using Edge = Edge<int64_t>;

TEST(MaxSpacingKClustering, Basic00) {
  std::vector<Edge> edges{                       //
                          {{0, 0}, {1, 1}, 1},   //
                          {{1, 1}, {2, 2}, 5},   //
                          {{2, 2}, {3, 3}, 10},  //
                          {{0, 0}, {3, 3}, 15},  //
                          {{0, 0}, {2, 2}, 20}};
  int num_nodes = 4;
  int k = 2;
  ASSERT_EQ(max_spacing_k_clustering(edges, num_nodes, k), 10);
}
}  // namespace

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
