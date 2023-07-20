#include "s21_graph_algorithms.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <stdexcept>

#include "containers/s21_stack.h"
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
  start_vertex -= kVertexStartNumber;
  std::vector<bool> visited(graph.size(), false);
  std::queue<uint> q;  // TODO: replace with s21_queue
  ResultArray path{};
  if (start_vertex < 0 || start_vertex >= +(int)graph.size()) {
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

GraphAlgorithms::ResultArray GraphAlgorithms::GetShortestPathBetweenVertices(
    Graph &graph, int vertex1, int vertex2) {
  vertex1 -= kVertexStartNumber;
  vertex2 -= kVertexStartNumber;
  uint size = graph.size();
  std::vector<bool> visited(size, false);
  std::vector<uint> distance(size, UINT_MAX);
  distance.at(vertex1) = 0;
  while (true) {
    uint min_index = UINT_MAX;
    uint min_dist = UINT_MAX;
    for (uint i = 0; i < size; i++) {
      if (!visited.at(i) && (distance.at(i) < min_dist)) {
        min_dist = distance.at(i);
        min_index = i;
      }
    }
    if (min_index == UINT_MAX) {
      break;
    }

    visited.at(min_index) = true;
    for (uint i = 0; i < size; i++) {
      uint edge_weight = graph.GetEdge(min_index, i);
      if (edge_weight > 0) {
        uint temp = min_dist + edge_weight;
        if (temp < distance.at(i)) {
          distance.at(i) = temp;
        }
      }
    }
  }
  ResultArray path{distance.at(vertex2)};
  return path;
}

Graph::AdjacencyMatrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    Graph &graph) {
  Graph::AdjacencyMatrix result_matrix(graph.GetMatrix());
  uint size = graph.size();
  for (uint i = 0; i < size; i++) {
    for (uint j = 0; j < size; j++) {
      if (graph.GetEdge(i, j) == 0 && i != j) {
        result_matrix.at(i).at(j) = UINT_MAX;
      }
    }
  }

  for (uint k = 0; k < size; k++) {
    for (uint i = 0; i < size; i++) {
      for (uint j = 0; j < size; j++) {
        if (result_matrix.at(i).at(k) != UINT_MAX &&
            result_matrix.at(k).at(j) != UINT_MAX &&
            (result_matrix.at(i).at(j) >
             result_matrix.at(i).at(k) + result_matrix.at(k).at(j))) {
          result_matrix.at(i).at(j) =
              result_matrix.at(i).at(k) + result_matrix.at(k).at(j);
        }
      }
    }
  }
  return result_matrix;
}

GraphAlgorithms::ResultArray GraphAlgorithms::DepthFirstSearch(
    Graph &graph, int start_vertex) {
  start_vertex -= kVertexStartNumber;
  std::vector<bool> visited(graph.size(), false);
  s21::stack<uint> stack;
  ResultArray path{};
  if (start_vertex < 0 || start_vertex >= +(int)graph.size()) {
    throw std::invalid_argument("Vertex is out of range");
  }
  stack.push(start_vertex);
  visited[start_vertex] = true;
  path.push_back(start_vertex);

  while (!stack.empty()) {
    uint current = stack.top();
    for (size_t i = 0; i < graph.size(); i++) {
      if (graph.GetEdge(current, i) != 0 && !visited[i]) {
        stack.push(i);
        visited[i] = true;
        path.push_back(i);
        break;
      }
    }
    if (current == stack.top()) {
      stack.pop();
    }
  }
  std::transform(path.begin(), path.end(), path.begin(),
                 [](uint v) { return v + kVertexStartNumber; });

  return path;
}
