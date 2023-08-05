#include <iostream>
#include <limits>
#include <vector>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

using namespace s21;
class TspState {
 public:
  // Обновление состояния решения
  void updatePath(int vertex);
  void updateCost(double cost);
  // Получение текущего пути и стоимости
  std::vector<int> getPath();
  double getCost();

  std::vector<int> path;
  double cost;
};

void TspState::updatePath(int vertex) { path.push_back(vertex); }

void TspState::updateCost(double cost) { this->cost = cost; }

std::vector<int> TspState::getPath() { return path; }

double TspState::getCost() { return cost; }

void findOptimalPath(const s21::Graph& graph, TspState state, int currentVertex,
                     double& upperBound, TspState& optimalState) {
  state.updatePath(currentVertex);

  if (state.path.size() == graph.GetNumVertices()) {
    double cost = graph.GetEdge(currentVertex, state.path[0]);

    if (cost < upperBound) {
      state.updateCost(cost);
      optimalState = state;
      upperBound = cost;
    }
  } else {
    for (int vertex : graph.GetVertices()) {
      if (std::find(state.path.begin(), state.path.end(), vertex) ==
          state.path.end()) {
        double cost = graph.GetEdge(currentVertex, vertex);

        if (cost + state.cost < upperBound) {
          TspState nextState = state;
          findOptimalPath(graph, nextState, vertex, upperBound, optimalState);
        }
      }
    }
  }
}

GraphAlgorithms::TsmResult solveTsp(const s21::Graph& graph) {
  TspState optimalState;
  double upperBound = std::numeric_limits<double>::max();

  for (int vertex : graph.GetVertices()) {
    TspState state;
    findOptimalPath(graph, state, vertex, upperBound, optimalState);
  }
  GraphAlgorithms::TsmResult optimalResult;
  optimalResult.vertices = optimalState.getPath();
  optimalResult.distance = optimalState.getCost();
  return optimalResult;
}