#include "s21_graph_algorithms.h"

#include <queue>
using namespace s21;

GraphAlgorithms::ResultArray &GraphAlgorithms::BreadthFirstSearch(
    Graph &graph, int start_vertex) {
  std::vector<bool> visited(graph.size(), false);
  std::queue<uint> q;  // TODO: replace with s21_queue
  ResultArray path{};
  if (start_vertex < 0 || start_vertex >= graph.size()) {
    throw std::invalid_argument("Vertex is out of range");
  }
  q.push(start_vertex);
  visited[start_vertex] = true;

  while (!q.empty()) {
    uint current = q.front();
    q.pop();

    for (size_t i = 0; i < graph.size(); i++) {
      if (graph.GetMatrix().at(current).at(i) != 0 && !visited[i]) {
        q.push(i);
        visited[i] = true;
        path.push_back(i);
      }
    }
  }

  return path;
}
