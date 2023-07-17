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
  const GraphAlgorithms::ResultArray &GetResult();
  bool IsModelLoaded();

 private:
  Graph *model_ = nullptr;
  GraphAlgorithms::ResultArray result_;
};
}  // namespace s21
#endif  // NAVIGATOR_CONTROLLER_CONTROLLER_H
