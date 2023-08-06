#ifndef NAVIGATOR_CONTROLLER_CONTROLLER_H
#define NAVIGATOR_CONTROLLER_CONTROLLER_H

#include <chrono>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

namespace s21 {

struct GraphAppData {
  int point_a;
  int point_b;
  int n_cycles;
  std::string filename;
};

class Controller {
 public:
  explicit Controller(Graph *m) : model_(m){};

  const std::chrono::milliseconds &time_result(int i) const {
    return time_result_[i];
  }
  const GraphAlgorithms::Result &value_result() const { return value_result_; }
  const GraphAlgorithms::ResultArray &array_result() const {
    return array_result_;
  }
  const Graph::AdjacencyMatrix &adjacency_matrix_result() const {
    return adjacency_matrix_result_;
  }

  void BreadthFirstSearch(const GraphAppData *data);
  void DepthFirstSearch(const GraphAppData *data);
  void ExportGraphToDot(const GraphAppData *data);
  void GetLeastSpanningTree();
  void GetShortestPathBetweenVertices(const GraphAppData *data);
  void GetShortestPathsBetweenAllVertices();
  void SolveTravellingSalesmanProblem();
  void PerformTSPMethodsCompare(const GraphAppData *data);
  bool IsModelLoaded();
  void LoadGraphFromFile(const GraphAppData *data);

 private:
  std::chrono::milliseconds RunMethodTimed(
      const GraphAppData *data, GraphAlgorithms *algorithm,
      GraphAlgorithms::TsmResult (GraphAlgorithms::*)(const Graph &graph));
  Graph *model_ = nullptr;
  GraphAlgorithms::Result value_result_ = 0;
  GraphAlgorithms::ResultArray array_result_;
  std::chrono::milliseconds time_result_[3];
  Graph::AdjacencyMatrix adjacency_matrix_result_;
};

}  // namespace s21

#endif  // NAVIGATOR_CONTROLLER_CONTROLLER_H
