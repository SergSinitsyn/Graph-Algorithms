#include "s21_graph_algorithms.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <stdexcept>

#include "ant_colony_algorithm.h"
#include "monte_carlo_algorithm.h"
#include "s21_queue.h"
#include "s21_stack.h"

#ifndef SIZE_T_MAX
#define SIZE_T_MAX std::numeric_limits<size_t>::max()
#endif

namespace s21 {

GraphAlgorithms::ResultArray &GraphAlgorithms::AddVertexStartNumber(
    ResultArray &array) {
  std::transform(array.begin(), array.end(), array.begin(),
                 [](size_t v) { return v + kVertexStartNumber; });
  return array;
}

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

  return GraphAlgorithms::AddVertexStartNumber(path);
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

  return GraphAlgorithms::AddVertexStartNumber(path);
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
};

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    const Graph &graph) {
  AntColonyAlgorithm algorithm(graph);
  algorithm.RunAlgorithm();
  AntColonyAlgorithm::ResultTSP result = algorithm.GetResult();

  std::vector<size_t> modified_vector = result.first;

  return {GraphAlgorithms::AddVertexStartNumber(modified_vector),
          result.second};
}

GraphAlgorithms::TsmResult GraphAlgorithms::DynamicProgrammingMethod(
    const s21::Graph &graph) {
  TspState optimal_state{};
  double upper_bound = std::numeric_limits<double>::max();

  for (int vertex : graph.GetVertices()) {
    FindOptimalPath(graph, {}, vertex, upper_bound, optimal_state);
  }
  TsmResult optimal_result;
  optimal_result.vertices = optimal_state.GetPath();

  GraphAlgorithms::AddVertexStartNumber(optimal_result.vertices);

  optimal_result.distance = optimal_state.GetCost();
  return optimal_result;
}

GraphAlgorithms::TsmResult GraphAlgorithms::MonteCarloMethod(
    const Graph &graph) {
  MonteCarloAlgorithm algorithm(graph);
  algorithm.RunAlgorithm();
  MonteCarloAlgorithm::ResultTSP result = algorithm.GetResult();

  std::vector<size_t> modified_vector = result.first;

  return {GraphAlgorithms::AddVertexStartNumber(modified_vector),
          result.second};
}

void GraphAlgorithms::FindOptimalPath(const s21::Graph &graph, TspState state,
                                      size_t current_vertex,
                                      double &upper_bound,
                                      TspState &optimal_state) {
  state.UpdatePath(current_vertex);
  optimal_state.iteration_++;

  if (state.path_.size() == graph.GetNumVertices()) {
    double cost =
        state.GetCost() + graph.GetEdge(current_vertex, state.path_[0]);
    if (cost < upper_bound) {
      state.UpdateCost(cost);
      optimal_state = state;
      upper_bound = cost;
    }
  } else {
    if (state.cost_ < upper_bound)
      for (int vertex : graph.GetVertices()) {
        if (std::find(state.path_.begin(), state.path_.end(), vertex) ==
            state.path_.end()) {
          double cost = graph.GetEdge(current_vertex, vertex);

          if (cost + state.cost_ < upper_bound) {
            TspState nextState = state;
            nextState.UpdateCost(cost + state.cost_);
            FindOptimalPath(graph, nextState, vertex, upper_bound,
                            optimal_state);
          } else {
            break;
          }
        }
      }
  }
}
}  // namespace s21