#ifndef NAVIGATOR_S21_GRAPH_H_
#define NAVIGATOR_S21_GRAPH_H_
#include <string>
#include <vector>
namespace s21 {

class Graph {
 public:
  static const unsigned int kMinSize = 1;
  static const unsigned int kMaxSize = 100;  //! To be defined!
  // loading a graph from a file in the adjacency matrix format
  void LoadGraphFromFile(const std::string& filename);
  // exporting a graph to a dot file (see materials)
  void ExportGraphToDot(const std::string& filename);

 protected:
  void SetSize(unsigned int size);
  unsigned int ReadSize(const std::string& line);
  void ReadLine(size_t& line_number, const std::string& line);
  std::vector<std::vector<unsigned int>> adjacency_matrix_;
};
};      // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_H_