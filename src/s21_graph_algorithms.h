#ifndef NAVIGATOR_S21_GRAPH_ALGORITHMS_H_
#define NAVIGATOR_S21_GRAPH_ALGORITHMS_H_

#include "s21_graph.h"

namespace s21 {
/** Graph
 *! @brief Внутренняя нумерация вершин с 0!
 *! неоходимо преобразовывать на входе в метод и при выдаче результата
 */
class GraphAlgorithms {
 public:
  using ResultArray = std::vector<uint>;
  // using namespace Graph;
  struct TsmResult {
    std::vector<uint> vertices;
    double distance;
  };
  struct Node {
    uint level;
    ResultArray path;
    Graph::AdjacencyMatrix reduced_matrix;
    uint cost;
  };
  static const int kVertexStartNumber = 1;

  // TODO: Тип возвращаемого результата для частей 1-4 определить в процессе
  // TODO: исполнения
  //  part 1
  ResultArray DepthFirstSearch(Graph &graph, int start_vertex);
  static ResultArray BreadthFirstSearch(Graph &graph, int start_vertex);
  // part 2
  void GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  void GetShortestPathsBetweenAllVertices(Graph &graph);
  // part 3
  void GetLeastSpanningTree(Graph &graph);
  // part 4
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  // part 6
  static TsmResult SolveTravelingSalesmanProblem1(const Graph &graph);
  TsmResult SolveTravelingSalesmanProblem2(Graph &graph);

  //  protected:
  static uint CalculateCost(const Graph &graph, const ResultArray &path);
  static Graph::AdjacencyMatrix ReduceMatrix(const Graph &graph);
};
};      // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_ALGORITHMS_H_