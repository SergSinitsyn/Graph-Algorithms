#ifndef NAVIGATOR_S21_GRAPH_H_
#define NAVIGATOR_S21_GRAPH_H_
#include <numeric>
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

  size_t size() const { return size_; }
  size_t GetNumVertices() const { return adjacency_matrix_.size(); }
  std::vector<uint> GetVertices() const {
    auto vertexes = std::vector<uint>(GetNumVertices());
    std::iota(vertexes.begin(), vertexes.end(), 1);
    return std::move(vertexes);
  }
  uint GetEdge(uint from, uint to) const {
    return adjacency_matrix_.at(from).at(to);
  }
  const AdjacencyMatrix& GetMatrix() const { return adjacency_matrix_; }

  void ExportGraphToDot(const std::string& filename);
  bool GraphOrientationCheck() const;
  void LoadGraphFromFile(const std::string& filename);

 private:
  size_t CountVerticesGraph(const std::string& sentence);
  std::string GetNonEmptyLine(std::ifstream& file);
  void ReadLine(const uint& line_number, const std::string& line);
  size_t ReadSize(const std::string& line);
  void SetSize(size_t size);

  AdjacencyMatrix adjacency_matrix_;
  size_t size_ = 0;  //! что это за размер - плохое название переменной - через
                     //! месяц забыл о чем она
};
}  // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_H_