#include <gtest/gtest.h>

#include "../s21_graph.h"
using namespace s21;

TEST(Graph, LoadGraphFromFile_File_empty) {
  try {
    Graph graph;
    std::string file_name = "samples/graph_empty.adj";
    graph.LoadGraphFromFile(file_name);
  } catch (const std::invalid_argument &e) {
    std::string expected_error = "File read error. The file is empty.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Graph, LoadGraphFromFile_bad) {
  Graph graph;
  std::string file_name = "samples/graph_0.adj";
  ASSERT_ANY_THROW(graph.LoadGraphFromFile(file_name));
}

TEST(Graph, LoadGraphFromFile_wrong_size) {
  Graph graph;
  std::string file_name = "samples/wrong_size_graph.adj";
  ASSERT_ANY_THROW(graph.LoadGraphFromFile(file_name));
}

TEST(Graph, LoadGraphFromFile_to_big_size) {
  Graph graph;
  std::string file_name = "samples/to_big_size_graph.adj";
  ASSERT_ANY_THROW(graph.LoadGraphFromFile(file_name));
}

TEST(Graph, LoadGraphFromFile) {
  Graph graph;
  std::string file_name = "samples/graph_11.adj";
  graph.LoadGraphFromFile(file_name);
  size_t result_rows = 11;
  size_t result_cols = 11;
  EXPECT_EQ(graph.size(), 11);

  Graph::AdjacencyMatrix result_matrix = {
      {0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
      {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
      {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
      {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
      {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
      {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
      {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
      {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
      {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
      {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
      {
          18,
          12,
          13,
          25,
          22,
          37,
          84,
          13,
          18,
          38,
          0,
      }};

  const Graph::AdjacencyMatrix &file_matrix = graph.GetMatrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      EXPECT_EQ(file_matrix[i][j], result_matrix[i][j]);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}