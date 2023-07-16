#include "s21_graph_algorithms.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

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
    Graph& graph, int start_vertex) {
  start_vertex -= kVertexStartNumber;  // Use internal vertex numbering from 0
  std::vector<bool> visited(graph.size(), false);
  std::queue<uint> q;  // TODO: replace with s21_queue
  ResultArray path{};
  if (start_vertex < 0 || start_vertex >= (int)graph.size()) {
    throw std::invalid_argument("Vertex is out of range");
  }
  q.push(start_vertex);
  visited[start_vertex] = true;
  path.push_back(start_vertex);

  while (!q.empty()) {
    uint current = q.front();
    q.pop();

    for (size_t i = 0; i < graph.size(); i++) {
      if (graph.EdgeWeight(current, i) != 0 && !visited[i]) {
        q.push(i);
        visited[i] = true;
        path.push_back(i);
      }
    }
  }
  // Restore external vertex numbering to start from 1
  std::transform(path.begin(), path.end(), path.begin(),
                 [](uint i) { return i + kVertexStartNumber; });
  return path;
}

uint GraphAlgorithms::CalculateCost(const Graph& graph,
                                    const ResultArray& path) {
  uint cost = 0;
  uint n = path.size();
  if (n > 0) {
    for (uint i = 0; i < n - 1; i++) {
      cost += graph.EdgeWeight(path[i], path[i + 1]);
    }
    cost += graph.EdgeWeight(path[n - 1], path[0]);
  }
  return cost;
}

Graph::AdjacencyMatrix GraphAlgorithms::ReduceMatrix(const Graph& graph) {
  uint n = graph.VertexCount();  //! EdgeCount();//! ???
  Graph::AdjacencyMatrix reduced_matrix(n, ResultArray(n, 0));

  for (uint i = 0; i < n; i++) {
    uint min_val = std::numeric_limits<uint>::max();
    for (uint j = 0; j < n; j++) {
      if (graph.HasEdge(i, j) && graph.EdgeWeight(i, j) < min_val) {
        min_val = graph.EdgeWeight(i, j);
      }
    }
    for (uint j = 0; j < n; j++) {
      if (graph.HasEdge(i, j)) {
        reduced_matrix[i][j] = graph.EdgeWeight(i, j) - min_val;
      }
    }
  }

  for (uint j = 0; j < n; j++) {
    uint min_val = std::numeric_limits<uint>::max();
    for (uint i = 0; i < n; i++) {
      if (graph.HasEdge(i, j) && reduced_matrix[i][j] < min_val) {
        min_val = reduced_matrix[i][j];
      }
    }
    for (uint i = 0; i < n; i++) {
      if (graph.HasEdge(i, j)) {
        reduced_matrix[i][j] -= min_val;
      }
    }
  }

  return reduced_matrix;
}

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem1(
    const Graph& source_graph) {
  Graph graph = source_graph.GetInfinityGraph();

  uint n = graph.VertexCount();
  std::vector<Node> priority_queue;
  Node current_node;
  current_node.level = 0;
  current_node.path.push_back(0);
  current_node.reduced_matrix = ReduceMatrix(graph);
  current_node.cost = CalculateCost(graph, current_node.path);
  priority_queue.push_back(current_node);

  uint min_cost = std::numeric_limits<uint>::max();
  ResultArray min_path;

  while (!priority_queue.empty()) {
    current_node = priority_queue.front();
    priority_queue.erase(priority_queue.begin());

    if (current_node.level == n - 1) {
      current_node.path.push_back(0);
      uint current_cost = CalculateCost(graph, current_node.path);
      if (current_cost < min_cost) {
        min_cost = current_cost;
        min_path = current_node.path;
      }
      continue;
    }

    for (uint i = 1; i < n; i++) {
      if (std::find(current_node.path.begin(), current_node.path.end(), i) ==
          current_node.path.end()) {
        Node new_node;
        new_node.level = current_node.level + 1;
        new_node.path = current_node.path;
        new_node.path.push_back(i);
        new_node.reduced_matrix = ReduceMatrix(graph);
        new_node.cost = CalculateCost(graph, new_node.path);

        if (new_node.cost < min_cost) {
          priority_queue.push_back(new_node);
        }
      }
    }

    std::sort(priority_queue.begin(), priority_queue.end(),
              [](const Node& a, const Node& b) { return a.cost < b.cost; });
  }

  std::transform(min_path.begin(), min_path.end(), min_path.begin(),
                 [](uint i) { return i + kVertexStartNumber; });
  return {min_path, (double)min_cost};
}
