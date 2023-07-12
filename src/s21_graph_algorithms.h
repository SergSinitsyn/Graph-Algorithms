#ifndef NAVIGATOR_S21_GRAPH_ALGORITHMS_H_
#define NAVIGATOR_S21_GRAPH_ALGORITHMS_H_

#include "s21_graph.h"
#include "s21_queue.h"
#include "s21_stack.h"

namespace s21 {
class GraphAlgorithms {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  // part 1
  void DepthFirstSearch(Graph &graph, int start_vertex);
  void BreadthFirstSearch(Graph &graph, int start_vertex);
  // part 2
  void GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  void GetShortestPathsBetweenAllVertices(Graph &graph);
  // part 3
  void GetLeastSpanningTree(Graph &graph);
  // part 4
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  // part 6
  TsmResult SolveTravelingSalesmanProblem1(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem2(Graph &graph);
};
};      // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_ALGORITHMS_H_