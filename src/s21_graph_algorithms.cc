#include "s21_graph_algorithms.h"

#include <algorithm>
#include <queue>
#include <stdexcept>
using namespace s21;

/**
 * Performs a breadth-first search on a graph starting from a specified vertex.
 *
 * @param graph The graph to perform the breadth-first search on.
 * @param start_vertex The vertex to start the breadth-first search from.
 * Vertex numbers starts from 1
 *
 * @return The path traversed during the breadth-first search.
 *
 * @throws std::invalid_argument if the start_vertex is out of range.
 */
GraphAlgorithms::ResultArray GraphAlgorithms::BreadthFirstSearch(
    Graph &graph, int start_vertex) {
  start_vertex = start_vertex - 1;
  std::vector<bool> visited(graph.size(), false);
  std::queue<uint> q;  // TODO: replace with s21_queue
  ResultArray path{};
  if (start_vertex < 0 || start_vertex > +(int)graph.size()) {
    throw std::invalid_argument("Vertex is out of range");
  }
  q.push(start_vertex);
  visited[start_vertex] = true;
  path.push_back(start_vertex);

  while (!q.empty()) {
    uint current = q.front();
    q.pop();

    for (size_t i = 0; i < graph.size(); i++) {
      if (graph.GetEdge(current, i) != 0 && !visited[i]) {
        q.push(i);
        visited[i] = true;
        path.push_back(i);
      }
    }
  }

  std::transform(path.begin(), path.end(), path.begin(),
                 [](uint v) { return v + kVertexStartNumber; });

  return path;
}
