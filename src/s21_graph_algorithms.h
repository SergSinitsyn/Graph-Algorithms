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
  struct TsmResult {
    std::vector<size_t> vertices;
    double distance;
  };
  static const int kVertexStartNumber = 1;
  using ResultArray = std::vector<size_t>;
  using Result = size_t;

  // part 1
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
  TsmResult DynamicProgrammingMethod(const Graph &graph);
  TsmResult MonteCarloMethod(const Graph &graph);

 private:
  class TspState {
   public:
    double GetCost() { return cost_; }
    // Получение текущего пути и стоимости
    ResultArray GetPath() { return std::vector(path_.begin(), path_.end()); }
    // Обновление состояния решения
    void UpdateCost(double cost) { this->cost_ = cost; }
    void UpdatePath(size_t vertex) { path_.push_back(vertex); }

    std::vector<size_t> path_;
    double cost_ = 0;
    size_t iteration_ = 0;
  };
  static ResultArray &AddVertexStartNumber(ResultArray &array);
  void FindOptimalPath(const s21::Graph &graph, TspState state,
                       size_t currentVertex, double &upperBound,
                       TspState &optimalState);
};

}  // namespace s21

#endif  // NAVIGATOR_S21_GRAPH_ALGORITHMS_H_
