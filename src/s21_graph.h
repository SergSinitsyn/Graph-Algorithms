#ifndef NAVIGATOR_S21_GRAPH_H_
#define NAVIGATOR_S21_GRAPH_H_

#include <numeric>
#include <string>
#include <vector>

#include "matrix/matrix.h"

namespace s21 {

/** Graph
 *! @brief Внутренняя нумерация вершин с 0!
 *! неоходимо преобразовывать на входе в метод и при выдаче результата
 */
class Graph {
 public:
  using AdjacencyMatrix = std::vector<std::vector<size_t>>;

  static const size_t kMinSize = 1;
  static const size_t kMaxSize = 100;  //! To be defined!

  Graph() : size_(){};
  explicit Graph(size_t size) : size_(size) { SetSize(size_); };

  size_t size() const { return size_; }
  size_t GetNumVertices() const { return adjacency_matrix_.size(); }
  std::vector<uint> GetVertices() const {
    auto vertexes = std::vector<uint>(GetNumVertices());
    std::iota(vertexes.begin(), vertexes.end(), 1);
    return vertexes;
  }
  void SetSize(size_t size);
  size_t GetEdge(size_t from, size_t to) const {
    return adjacency_matrix_.at(from).at(to);
  }

  const AdjacencyMatrix& GetMatrix() const { return adjacency_matrix_; }

  void ExportGraphToDot(const std::string& filename);
  bool GraphOrientationCheck() const;
  void LoadGraphFromFile(const std::string& filename);

 private:
  size_t CountVerticesGraph(const std::string& sentence);
  std::string GetNonEmptyLine(std::ifstream& file);
  void ReadLine(const size_t& line_number, const std::string& line);
  size_t ReadSize(const std::string& line);

  AdjacencyMatrix adjacency_matrix_;
  size_t size_ = 0;  //! что это за размер - плохое название переменной - через
                     //! месяц забыл о чем она
};

}  // namespace s21

#endif  // NAVIGATOR_S21_GRAPH_H_