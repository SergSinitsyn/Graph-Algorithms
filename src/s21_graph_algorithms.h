#ifndef NAVIGATOR_S21_GRAPH_ALGORITHMS_H_
#define NAVIGATOR_S21_GRAPH_ALGORITHMS_H_

#include <vector>

#include "s21_graph.h"

/** Graph
 *! @brief Внутренняя нумерация вершин с 0!
 *! неоходимо преобразовывать на входе в метод и при выдаче результата
 */
namespace s21 {
class GraphAlgorithms {
 public:
  static const int kVertexStartNumber = 1;
  using ResultArray = std::vector<uint>;
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  // TODO: Тип возвращаемого результата для частей 1-4 определить в процессе
  // TODO: исполнения
  //  part 1
  static ResultArray DepthFirstSearch(Graph &graph, int start_vertex);
  static ResultArray BreadthFirstSearch(Graph &graph, int start_vertex);
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

 private:
  static bool FullTrack(std::vector<bool> visited);
};
};      // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_ALGORITHMS_H_