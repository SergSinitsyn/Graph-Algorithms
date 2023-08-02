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
  using AdjacencyMatrix = std::vector<std::vector<size_t>>;
  static const size_t kMinSize = 1;
  static const size_t kMaxSize = 100;  //! To be defined!

  Graph() : size_(){};
  Graph(size_t size) : size_(size) { SetSize(size_); };

  size_t size() const { return size_; }
  size_t GetEdge(size_t from, size_t to) const {
    return adjacency_matrix_.at(from).at(to);
  }
  void SetEdge(size_t from, size_t to, size_t value) {
    adjacency_matrix_.at(from).at(to) = value;
  }
  const AdjacencyMatrix& GetMatrix() const { return adjacency_matrix_; }

  void ExportGraphToDot(const std::string& filename);
  bool GraphOrientationCheck() const;
  void LoadGraphFromFile(const std::string& filename);
  void AddGraph(const Graph& graph);
  void MultNumber(const size_t& number);

 private:
  size_t CountVerticesGraph(const std::string& sentence);
  std::string GetNonEmptyLine(std::ifstream& file);
  void ReadLine(const size_t& line_number, const std::string& line);
  size_t ReadSize(const std::string& line);
  void SetSize(size_t size);

  AdjacencyMatrix adjacency_matrix_;
  size_t size_ = 0;
};

}  // namespace s21

#endif  // NAVIGATOR_S21_GRAPH_H_