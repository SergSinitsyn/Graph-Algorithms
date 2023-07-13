#ifndef NAVIGATOR_S21_GRAPH_H_
#define NAVIGATOR_S21_GRAPH_H_
#include <string>
#include <vector>
namespace s21 {

class Graph {
 public:
  using AdjacencyMatrix = std::vector<std::vector<uint>>;
  static const uint kMinSize = 1;
  static const uint kMaxSize = 100;  //! To be defined!
  size_t size() const { return size_; };
  uint GetEdge(uint from, uint to) const {
    return adjacency_matrix_.at(from - 1).at(to - 1);
  };
  const AdjacencyMatrix& GetMatrix() const { return adjacency_matrix_; };
  // loading a graph from a file in the adjacency matrix format
  void LoadGraphFromFile(const std::string& filename);
  // exporting a graph to a dot file (see materials)
  void ExportGraphToDot(const std::string& filename);

 protected:
  void SetSize(size_t size);
  size_t ReadSize(const std::string& line);
  void ReadLine(uint& line_number, const std::string& line);
  bool GraphOrientationCheck();
  AdjacencyMatrix adjacency_matrix_;
  size_t size_ = 0;
};
}  // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_H_