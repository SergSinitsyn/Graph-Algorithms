#ifndef NAVIGATOR_CONTROLLER_CONTROLLER_H
#define NAVIGATOR_CONTROLLER_CONTROLLER_H

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {
struct GraphAppData {
  int point_a;
  int point_b;
  std::string filename;
};

class Controller {
 public:
  explicit Controller(Graph *m) : model_(m){};

  const GraphAlgorithms::Result &value_result() { return value_result_; }
  const GraphAlgorithms::ResultArray &array_result() { return array_result_; }
  const Graph::AdjacencyMatrix &adjacency_matrix_result() {
    return adjacency_matrix_result_;
  }

  void BreadthFirstSearch(const GraphAppData *data);
  void DepthFirstSearch(const GraphAppData *data);
  void ExportGraphToDot(const GraphAppData *data);
  void GetLeastSpanningTree();
  void GetShortestPathBetweenVertices(const GraphAppData *data);
  void GetShortestPathsBetweenAllVertices();
  bool IsModelLoaded();
  void LoadGraphFromFile(const GraphAppData *data);

 private:
  Graph *model_ = nullptr;
  GraphAlgorithms::Result value_result_;
  GraphAlgorithms::ResultArray array_result_;
  Graph::AdjacencyMatrix adjacency_matrix_result_;
};
}  // namespace s21
#endif  // NAVIGATOR_CONTROLLER_CONTROLLER_H
