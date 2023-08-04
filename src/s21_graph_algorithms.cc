#include "s21_graph_algorithms.h"

#include <algorithm>
#include <chrono>  // TODO
#include <limits>
#include <queue>
#include <stack>
#include <stdexcept>

#include "ant_colony_algorithm/ant_colony_algorithm.h"
#include "containers/s21_queue.h"
#include "containers/s21_stack.h"

namespace s21 {

GraphAlgorithms::ResultArray GraphAlgorithms::BreadthFirstSearch(
    const Graph &graph, int start_vertex) {
  start_vertex -= kVertexStartNumber;
  std::vector<bool> visited(graph.size(), false);
  s21::queue<size_t> queue;
  ResultArray path{};
  if (start_vertex < 0 || start_vertex >= +(int)graph.size()) {
    throw std::invalid_argument("Vertex is out of range");
  }
  queue.push(start_vertex);
  visited[start_vertex] = true;
  path.push_back(start_vertex);
  while (!queue.empty()) {
    size_t current = queue.front();
    queue.pop();
    for (size_t i = 0; i < graph.size(); i++) {
      if (graph.GetEdge(current, i) != 0 && !visited[i]) {
        queue.push(i);
        visited[i] = true;
        path.push_back(i);
      }
    }
  }
  std::transform(path.begin(), path.end(), path.begin(),
                 [](size_t v) { return v + kVertexStartNumber; });

  return path;
}

GraphAlgorithms::ResultArray GraphAlgorithms::DepthFirstSearch(
    const Graph &graph, int start_vertex) {
  start_vertex -= kVertexStartNumber;
  std::vector<bool> visited(graph.size(), false);
  s21::stack<size_t> stack;
  ResultArray path{};
  if (start_vertex < 0 || start_vertex >= +(int)graph.size()) {
    throw std::invalid_argument("Vertex is out of range");
  }
  stack.push(start_vertex);
  visited[start_vertex] = true;
  path.push_back(start_vertex);
  while (!stack.empty()) {
    size_t current = stack.top();
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
                 [](size_t v) { return v + kVertexStartNumber; });

  return path;
}

GraphAlgorithms::Result GraphAlgorithms::GetShortestPathBetweenVertices(
    const Graph &graph, int vertex1, int vertex2) {
  size_t size = graph.size();
  if (vertex1 < 1 || vertex1 > (int)size || vertex2 < 1 ||
      vertex2 > (int)size) {
    throw std::invalid_argument("Vertex is out of range");
  }
  vertex1 -= kVertexStartNumber;
  vertex2 -= kVertexStartNumber;
  std::vector<bool> visited(size, false);
  std::vector<size_t> distance(size, SIZE_T_MAX);
  distance.at(vertex1) = 0;
  while (true) {
    size_t min_index = SIZE_T_MAX;
    size_t min_dist = SIZE_T_MAX;
    for (size_t i = 0; i < size; i++) {
      if (!visited.at(i) && (distance.at(i) < min_dist)) {
        min_dist = distance.at(i);
        min_index = i;
      }
    }
    if (min_index == SIZE_T_MAX) {
      break;
    }

    visited.at(min_index) = true;
    for (size_t i = 0; i < size; i++) {
      size_t edge_weight = graph.GetEdge(min_index, i);
      if (edge_weight > 0) {
        size_t temp = min_dist + edge_weight;
        if (temp < distance.at(i)) {
          distance.at(i) = temp;
        }
      }
    }
  }
  return distance.at(vertex2);
}

Graph::AdjacencyMatrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    const Graph &graph) {
  Graph::AdjacencyMatrix result_matrix(graph.GetMatrix());
  size_t size = graph.size();
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (graph.GetEdge(i, j) == 0 && i != j) {
        result_matrix.at(i).at(j) = SIZE_T_MAX;
      }
    }
  }
  for (size_t k = 0; k < size; k++) {
    for (size_t i = 0; i < size; i++) {
      for (size_t j = 0; j < size; j++) {
        if (result_matrix.at(i).at(k) != SIZE_T_MAX &&
            result_matrix.at(k).at(j) != SIZE_T_MAX &&
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

Graph::AdjacencyMatrix GraphAlgorithms::GetLeastSpanningTree(
    const Graph &graph) {
  Graph::AdjacencyMatrix result_matrix(graph.GetMatrix());
  if (!graph.GraphOrientationCheck()) {
    throw std::invalid_argument("Graph is not oriented");
  }
  size_t size = graph.size();
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      result_matrix.at(i).at(j) = 0;
    }
  }
  std::vector<bool> visited(size, false);
  visited.at(0) = true;  // устанавливаем начальную точку построения дерева.
  int unvisited = size - 1;
  while (unvisited) {
    size_t min_dist = SIZE_T_MAX;
    size_t start = 0;
    size_t end = 0;
    for (size_t i = 0; i < size; i++) {
      if (visited.at(i)) {
        for (size_t j = 0; j < size; j++) {
          if (j != i && !visited.at(j) && graph.GetEdge(i, j) != 0 &&
              graph.GetMatrix().at(i).at(j) < min_dist) {
            min_dist = graph.GetEdge(i, j);
            start = i;
            end = j;
          }
        }
      }
    }
    result_matrix.at(start).at(end) = min_dist;
    result_matrix.at(end).at(start) = min_dist;
    visited.at(end) = true;
    --unvisited;
  }
  return result_matrix;
}

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    const Graph &graph) {
  auto start = std::chrono::high_resolution_clock::now();
  AntColonyAlgorithm algorithm(graph);
  algorithm.RunAlgorithm();
  Ant::Solution result = algorithm.GetResult();

  std::vector<size_t> modified_vector = result.second;
  std::transform(modified_vector.begin(), modified_vector.end(),
                 modified_vector.begin(),
                 [](size_t value) { return value + 1; });

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Execution time: " << elapsed.count() << " seconds" << std::endl;
  return {modified_vector, result.first};
}

}  // namespace s21
