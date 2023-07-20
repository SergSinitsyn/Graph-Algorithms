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
  void LoadGraphFromFile(const GraphAppData *data);
  void ExportGraphToDot(const GraphAppData *data);
  void BreadthFirstSearch(const GraphAppData *data);
  void DepthFirstSearch(const GraphAppData *data);
  void GetShortestPathBetweenVertices(const GraphAppData *data);
  void GetShortestPathsBetweenAllVertices();

  const GraphAlgorithms::ResultArray &Controller::result() { return result_; }
  const Graph::AdjacencyMatrix &s21::Controller::result_adjacency_matrix() {
    return result_adjacency_matrix_;
  }
  bool IsModelLoaded();

 private:
  Graph *model_ = nullptr;
  GraphAlgorithms::ResultArray result_;
  Graph::AdjacencyMatrix result_adjacency_matrix_;
};
}  // namespace s21
#endif  // NAVIGATOR_CONTROLLER_CONTROLLER_H
