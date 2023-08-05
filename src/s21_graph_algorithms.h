#ifndef NAVIGATOR_S21_GRAPH_ALGORITHMS_H_
#define NAVIGATOR_S21_GRAPH_ALGORITHMS_H_

#include <iostream>
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
  using Result = uint;
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  //  part 1
  static ResultArray BreadthFirstSearch(const Graph &graph, int start_vertex);
  static ResultArray DepthFirstSearch(const Graph &graph, int start_vertex);
  // part 2
  static Result GetShortestPathBetweenVertices(const Graph &graph, int vertex1,
                                               int vertex2);
  static Graph::AdjacencyMatrix GetShortestPathsBetweenAllVertices(
      const Graph &graph);
  // part 3
  static Graph::AdjacencyMatrix GetLeastSpanningTree(const Graph &graph);
  // part 4
  TsmResult SolveTravelingSalesmanProblem(const Graph &graph);
  // part 6
  TsmResult SolveTravelingSalesmanProblem1(const Graph &graph);
  TsmResult SolveTravelingSalesmanProblem2(const Graph &graph);

 private:
  class TspState {
   public:
    // Обновление состояния решения
    void updatePath(int vertex);
    void updateCost(double cost);
    // Получение текущего пути и стоимости
    std::vector<int> getPath();
    double getCost();

    std::vector<int> path;
    double cost;
  };
  void findOptimalPath(const s21::Graph &graph, TspState state,
                       int currentVertex, double &upperBound,
                       TspState &optimalState);
  static bool FullTrack(std::vector<bool> visited);
};
};      // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_ALGORITHMS_H_