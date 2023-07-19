#include <gtest/gtest.h>

#include <fstream>

#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"
using namespace s21;

bool CompareFiles(const std::string &file1, const std::string &file2) {
  std::ifstream f1(file1);
  std::ifstream f2(file2);

  char ch1, ch2;
  while (f1.get(ch1) && f2.get(ch2)) {
    if (ch1 != ch2) {
      return false;
    }
  }

  return !f1.eof() || !f2.eof();
}

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

TEST(Graph, LoadGraphFromFile_to_incorrect_size_0) {
  Graph graph;
  std::string file_name = "samples/to_incorrect_size_graph.adj";
  ASSERT_ANY_THROW(graph.LoadGraphFromFile(file_name));
}

TEST(Graph, LoadGraphFromFile_to_incorrect_size_1) {
  Graph graph;
  std::string file_name = "samples/to_incorrect_size_graph_2.adj";
  ASSERT_ANY_THROW(graph.LoadGraphFromFile(file_name));
}

TEST(Graph, LoadGraphFromFile_0) {
  Graph graph;
  std::string file_name = "samples/graph_1.adj";
  graph.LoadGraphFromFile(file_name);
  size_t result_rows = 1;
  size_t result_cols = 1;
  EXPECT_EQ(graph.size(), 1);

  Graph::AdjacencyMatrix result_matrix = {{3}};

  const Graph::AdjacencyMatrix &file_matrix = graph.GetMatrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      EXPECT_EQ(file_matrix[i][j], result_matrix[i][j]);
    }
  }
}

TEST(Graph, LoadGraphFromFile_1) {
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
      {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};

  const Graph::AdjacencyMatrix &file_matrix = graph.GetMatrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      EXPECT_EQ(file_matrix[i][j], result_matrix[i][j]);
    }
  }
}

TEST(Graph, ExportGraphToDot_0) {
  Graph graph;
  std::string file_name = "samples/graph_4.adj";
  graph.LoadGraphFromFile(file_name);
  graph.ExportGraphToDot("samples/temp.dot");
  EXPECT_TRUE(CompareFiles("samples/temp.dot", "samples/graph_4.dot"));
}

TEST(Graph, ExportGraphToDot_1) {
  Graph graph;
  std::string file_name = "samples/graph_4_orient.adj";
  graph.LoadGraphFromFile(file_name);
  graph.ExportGraphToDot("samples/temp.dot");
  EXPECT_TRUE(CompareFiles("samples/temp.dot", "samples/graph_4_orient.dot"));
}

TEST(Graph, ExportGraphToDot_2) {
  Graph graph;
  std::string file_name = "samples/graph_11.adj";
  graph.LoadGraphFromFile(file_name);
  graph.ExportGraphToDot("samples/temp.dot");
  EXPECT_TRUE(CompareFiles("samples/temp.dot", "samples/graph_11.dot"));
}

TEST(GraphAlgorithms, BFS_0) {
  Graph graph;
  std::string file_name = "samples/matrices/matrices/test_wiki.txt";
  graph.LoadGraphFromFile(file_name);
  GraphAlgorithms::ResultArray result =
      GraphAlgorithms::BreadthFirstSearch(graph, 1);
  GraphAlgorithms::ResultArray expected_result{1, 2, 4, 3, 5, 6, 7};
  EXPECT_EQ(result.size(), 7);
  EXPECT_EQ(result, expected_result);
}

TEST(GraphAlgorithms, BFS_1) {
  Graph graph;
  std::string file_name = "samples/graph_11.adj";
  graph.LoadGraphFromFile(file_name);
  GraphAlgorithms::ResultArray result =
      GraphAlgorithms::BreadthFirstSearch(graph, 1);
  GraphAlgorithms::ResultArray expected_result{1, 2, 3, 4,  5, 6,
                                               7, 8, 9, 10, 11};
  EXPECT_EQ(result.size(), 11);
  EXPECT_EQ(result, expected_result);
}

TEST(GraphAlgorithms, BFS_2) {
  Graph graph;
  std::string file_name = "samples/matrices/matrices/test_1.txt";
  graph.LoadGraphFromFile(file_name);
  GraphAlgorithms::ResultArray result =
      GraphAlgorithms::BreadthFirstSearch(graph, 1);
  GraphAlgorithms::ResultArray expected_result{1, 5, 6, 7, 4, 3, 8, 2, 9, 10};
  EXPECT_EQ(result.size(), 10);
  EXPECT_EQ(result, expected_result);
}

TEST(GraphAlgorithms, DFS_0) {
  Graph graph;
  std::string file_name = "samples/matrices/matrices/test_wiki.txt";
  graph.LoadGraphFromFile(file_name);
  GraphAlgorithms::ResultArray result =
      GraphAlgorithms::DepthFirstSearch(graph, 1);
  GraphAlgorithms::ResultArray expected_result{1, 2, 3, 5, 4, 6, 7};
  EXPECT_EQ(result.size(), 7);
  EXPECT_EQ(result, expected_result);
}

TEST(GraphAlgorithms, DFS_1) {
  Graph graph;
  std::string file_name = "samples/graph_11.adj";
  graph.LoadGraphFromFile(file_name);
  GraphAlgorithms::ResultArray result =
      GraphAlgorithms::DepthFirstSearch(graph, 1);
  GraphAlgorithms::ResultArray expected_result{1, 2, 3, 4,  5, 6,
                                               7, 8, 9, 10, 11};
  EXPECT_EQ(result.size(), 11);
  EXPECT_EQ(result, expected_result);
}

TEST(GraphAlgorithms, DFS_2) {
  Graph graph;
  std::string file_name = "samples/matrices/matrices/test_1.txt";
  graph.LoadGraphFromFile(file_name);
  GraphAlgorithms::ResultArray result =
      GraphAlgorithms::DepthFirstSearch(graph, 1);
  GraphAlgorithms::ResultArray expected_result{1, 5, 4, 2, 3, 8, 6, 10, 9, 7};
  EXPECT_EQ(result.size(), 10);
  EXPECT_EQ(result, expected_result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}