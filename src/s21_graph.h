#ifndef NAVIGATOR_S21_GRAPH_H_
#define NAVIGATOR_S21_GRAPH_H_
#include <string>
#include <vector>
namespace s21 {

class Graph {
 public:
  // loading a graph from a file in the adjacency matrix format
  void LoadGraphFromFile(std::string filename);
  // exporting a graph to a dot file (see materials)
  void ExportGraphToDot(std::string filename);

 protected:
  std::vector<std::vector<unsigned>> adjacency_matrix_;
};
};      // namespace s21
#endif  // NAVIGATOR_S21_GRAPH_H_