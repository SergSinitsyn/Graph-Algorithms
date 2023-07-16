#ifndef NAVIGATOR_S21_GRAPH_H_
#define NAVIGATOR_S21_GRAPH_H_
#include <string>
#include <vector>
namespace s21 {

/** Graph
 *! @brief Внутренняя нумерация вершин с 0!
 *! неоходимо преобразовывать на входе в метод и при выдаче результата
 */
class Graph {
 public:
  using AdjacencyMatrix = std::vector<std::vector<uint>>;
  static const uint kMinSize = 1;
  static const uint kMaxSize = 100;  //! To be defined!
  size_t size() const;
  size_t VertexCount() const;
  bool HasEdge(uint from, uint to) const;
  uint EdgeWeight(uint from, uint to) const;
  const AdjacencyMatrix& GetMatrix() const;
  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
  Graph GetInfinityGraph() const;

 protected:
  uint NoEdgeValue() const;
  void SetSize(size_t size);
  size_t ReadSize(const std::string& line);
  void ReadLine(uint& line_number, const std::string& line);
  bool GraphOrientationCheck();
  AdjacencyMatrix adjacency_matrix_;
  size_t size_ = 0;
  bool is_infinity_ = false;
};
}  // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_H_