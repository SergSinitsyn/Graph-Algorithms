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
  size_t GetVertexCount() const;
  uint GetEdge(uint from, uint to) const;
  AdjacencyMatrix GetMatrix() { return adjacency_matrix_; };

  const AdjacencyMatrix& GetMatrix() const;
  void ExportGraphToDot(const std::string& filename);
  void LoadGraphFromFile(const std::string& filename);

  // void Set_Matrix(AdjacencyMatrix& matrix);

 protected:
  size_t CountVerticesGraph(const std::string& sentence);
  std::string GetNonEmptyLine(std::ifstream& file);
  bool GraphOrientationCheck();
  void ReadLine(uint& line_number, const std::string& line);
  size_t ReadSize(const std::string& line);
  void SetSize(size_t size);
  AdjacencyMatrix adjacency_matrix_;
  size_t size_ = 0;
};
}  // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_H_