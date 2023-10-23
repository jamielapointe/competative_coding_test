
#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <string_view>

#include "config.h"
#include "huffman_frequency.h"

using namespace std;
using Node = algorithms::HuffmanFrequencyTable::BinaryTreeNode;
using NodeMinHeap = algorithms::HuffmanFrequencyTable::NodeMinHeap;
using HuffmanCodingTree = algorithms::HuffmanFrequencyTable;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

TEST(HuffmanFrequencyTest, Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  NodeMinHeap data;
  data.emplace(0, 45);
  data.emplace(1, 13);
  data.emplace(2, 12);
  data.emplace(3, 16);
  data.emplace(4, 9);
  data.emplace(5, 5);
  HuffmanCodingTree huffman_tree(data);
  auto min_max_code_length = huffman_tree.get_min_max_code_length();
  EXPECT_EQ(min_max_code_length.max, 4);
  EXPECT_EQ(min_max_code_length.min, 1);
}

TEST(HuffmanFrequencyTest, Test1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  NodeMinHeap data;
  data.emplace(0, 3);
  data.emplace(1, 2);
  data.emplace(2, 6);
  data.emplace(3, 8);
  data.emplace(4, 2);
  data.emplace(5, 6);
  HuffmanCodingTree huffman_tree(data);
  auto min_max_code_length = huffman_tree.get_min_max_code_length();
  EXPECT_EQ(min_max_code_length.max, 4);
  EXPECT_EQ(min_max_code_length.min, 2);
}

TEST(HuffmanFrequencyTest, Test2) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  NodeMinHeap data;
  data.emplace(0, 28);
  data.emplace(1, 27);
  data.emplace(2, 20);
  data.emplace(3, 15);
  data.emplace(4, 10);
  HuffmanCodingTree huffman_tree(data);
  auto min_max_code_length = huffman_tree.get_min_max_code_length();
  EXPECT_EQ(min_max_code_length.max, 3);
  EXPECT_EQ(min_max_code_length.min, 1);
}

TEST(HuffmanFrequencyTest, Test3) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  NodeMinHeap data;
  data.emplace(0, 60);
  data.emplace(1, 25);
  data.emplace(2, 10);
  data.emplace(3, 5);
  HuffmanCodingTree huffman_tree(data);
  auto min_max_code_length = huffman_tree.get_min_max_code_length();
  EXPECT_EQ(min_max_code_length.max, 3);
  EXPECT_EQ(min_max_code_length.min, 1);
}

static inline NodeMinHeap get_data(std::string_view fname) {
  ifstream data_file(fname.data());
  string line;
  getline(data_file, line);
  int number_of_symbols{0};
  istringstream ss(line);
  ss >> number_of_symbols;
  NodeMinHeap pq;
  int index = 0;
  int frequency{0};
  for (; getline(data_file, line);) {
    istringstream ss1(line);
    ss1 >> frequency;
    pq.emplace(index, frequency);
    ++index;
  }
  return pq;
}

TEST(HuffmanFrequencyTest, TestCoursera) {
  string const base_dir(EXECUTABLE_BASE_DIR);
  string const fname("/data/huffman.txt");
  string const full_path = base_dir + fname;
  auto data = get_data(full_path);
  EXPECT_EQ(data.size(), 1000);

  HuffmanCodingTree huffman_tree(data);

  auto min_max_code_length = huffman_tree.get_min_max_code_length();
  EXPECT_EQ(min_max_code_length.max, 19);
  EXPECT_EQ(min_max_code_length.min, 9);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
